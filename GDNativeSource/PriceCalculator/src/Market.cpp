#include "Market.h"
#include "Person.h"
#include "Utils.h"
#include "PricesLogInfo.h"
#include "Prices.h"
#include "Reality.h"


#include <iostream>
#include <iomanip>

//var _param_price_precission : float = 0.01
//var _param_initial_price_change_step : float = 0.5 #Tiene que ser < 1
//    var _param_max_steps_calculating_new_prices : int = 80
//    var _param_product_step_for_best_combidict_calc : float = 5

const long c_paramMaxStpesCalculatingNewPrices = 80;
const double c_paramPricePrecission = 0.01;
const double c_paramInitialPriceChangeStep = 0.5;
const double c_paramProductStepForBestCombidictCalc= 5.0;

pca::CMarket::CMarket()
{
    //ctor

}

pca::CMarket::~CMarket()
{
    //dtor
}

void pca::CMarket::AddPerson(std::unique_ptr<CPerson> upPerson)
{
    m_vPersons.push_back(std::move(upPerson));
}

void pca::CMarket::AdjustBestCombinations(double dBudgetStep, int nMaxNumSteps)
{
    for (auto& personRef : m_vPersons)
    {
        personRef->AdjustBestCombinationForPersonWithMaxNumSteps(dBudgetStep, nMaxNumSteps);
    }
}

void pca::CMarket::RemovePerson(std::string sPersonArg)
{
    std::vector<std::unique_ptr<pca::CPerson>>::iterator it;
    for (it = m_vPersons.begin();it<m_vPersons.end();it++)
    {
        if ((*it).get()->GetName() == sPersonArg)
        {
            m_vPersons.erase(it);
            break;
        }
    }
}

void pca::CMarket::RemovePerson(long nId)
{
    std::vector<std::unique_ptr<pca::CPerson>>::iterator it;
    for (it = m_vPersons.begin();it < m_vPersons.end();it++)
    {
        if ((*it).get()->GetId() == nId)
        {
            m_vPersons.erase(it);
            break;
        }
    }
}

void pca::CMarket::CalculateTradesWithCurrentBestCombinations()
{
    for (auto& upPerson : m_vPersons)
    {
        upPerson->CalculateTradeWithCurrentBestCombination();
    }
}

void pca::CMarket::CalculateSumOfTrade()
{
    for (auto& upPerson : m_vPersons)
    {
        std::map<pca::CProduct*, double> mapTrade = upPerson->GetTrade();
        m_mapSumOfTrade = pca::CUtils::SumProducts(m_mapSumOfTrade, mapTrade);
    }
}

void pca::CMarket::CalculateNewPrices()
{
    bool bExit = false;
    long nCount = 0;
    long nMaxCount = c_paramMaxStpesCalculatingNewPrices;
    double dParamPriceChangeStep = c_paramInitialPriceChangeStep; //Tiene que ser < 1
    double dParamPricePrecission = c_paramPricePrecission;

    while (false == bExit)
    {
        nCount += 1;
        bool bPriceChanged = ChangePrices(dParamPriceChangeStep);
        m_upPricesLogInfo->RegisterPrices();
        bool bPricesEvolving = m_upPricesLogInfo->ArePricesEvolving();
        m_upPricesLogInfo->AddPriceChangeStepToVector(dParamPriceChangeStep);
        if (false == bPricesEvolving)
        {
            if (dParamPriceChangeStep < dParamPricePrecission)
                break;
            else if (false == bPriceChanged)
                break;
            else
            {
                dParamPriceChangeStep = dParamPriceChangeStep / 2.0;
                m_upPricesLogInfo->ResetLastPrices();
            }
        }

        if (nCount > nMaxCount)
            break;
    }

    SetExcessProducts(m_mapSumOfTrade);
}

bool pca::CMarket::ChangePrices(double dParamPriceChangeStepArg)
{
    bool bPriceChanged = false;
    double dBudgetStep = 0.01;
    long nMaxNumSteps = 5;
    AdjustBestCombinations(dBudgetStep, nMaxNumSteps);
    CalculateTradesWithCurrentBestCombinations();
    CalculateSumOfTrade();
    std::map<CProduct*,double> mapNewPricesIncrements = CalculateNewPricesIncrement(dParamPriceChangeStepArg);
    for (auto & pProduct:CReality::GetProducts() )
    {
        if (false == m_upPrices->IsCurrency(pProduct))
        {
            double dIncrement = mapNewPricesIncrements[pProduct];
            if (dIncrement != 0)
            {
                double dCurrentPrice = m_upPrices->GetPriceOfProduct(pProduct);
                double dNewPrice = dCurrentPrice + dCurrentPrice * dIncrement;
                m_upPrices->SetPriceOfProduct(pProduct, dNewPrice);
                bPriceChanged = true;

            }
        }
    }
    
    return bPriceChanged;
}

std::map<CProduct*, double>  pca::CMarket::CalculateNewPricesIncrement(double dParamPriceChangeStepArg)
{
    //m_mapSumOfTrade
    std::map<CProduct*, double> mapNewPricesIncrements;
    std::map<CProduct*, double> mapSumOfTradeAndExcessTrade = CUtils::SumProducts(m_mapSumOfTrade, m_mapExcessProducts);
    double dAmountOfCurrencyExcess = 0.0;

    if (m_mapSumOfTrade.end() != m_mapSumOfTrade.find(m_upPrices->GetCurrency()))
    {
        dAmountOfCurrencyExcess = m_mapSumOfTrade.at(m_upPrices->GetCurrency());
    }

    std::map<CProduct*, double> mapExcessRelativeToCurrency;
    for (auto& pairProductAmount : mapSumOfTradeAndExcessTrade)
    {
        double dAmount = pairProductAmount.second;
        CProduct* dProduct = pairProductAmount.first;

        mapExcessRelativeToCurrency[dProduct] = dAmount - dAmountOfCurrencyExcess;
    }

    double dMaxAmountOfProductExcess = 0.0;
    for (auto& productAmount : mapExcessRelativeToCurrency)
    {
        double dAmount = fabs(productAmount.second);
        if (dAmount > dMaxAmountOfProductExcess)
        {
            dMaxAmountOfProductExcess = dAmount;
        }
    }
    
    double dParamMinProductExcessToChangePrice = 0.0;

    //Este parámetro deberían pasarse por argumento al método calculate_new_prices_increment() :
    double dParamPriceChangeStep = dParamPriceChangeStepArg;

    if (dMaxAmountOfProductExcess > dParamMinProductExcessToChangePrice)
    {
        for (auto & pairProductAmount:mapExcessRelativeToCurrency)
        {
            double dAmount = pairProductAmount.second;
            CProduct* dProduct = pairProductAmount.first;
            mapNewPricesIncrements[dProduct] = dParamPriceChangeStep * dAmount / dMaxAmountOfProductExcess;
            
        }

    }
    
    return mapNewPricesIncrements;

}

//
//func _calculate_new_prices_increment(param_price_change_step_arg:float) :
//    #	var new_prices_increment : Dictionary = _sum_of_trade.duplicate() #Creo que esto sobra
//    var new_prices_increment : Dictionary = {}
//
//    var sum_of_trade_and_excess_trade = Utils.sum_combidict(_sum_of_trade, _excess_products_dict)
//
//    var amount_of_currency_excess = 0.0
//    #	for product in _sum_of_trade.keys() :
//#		if product == Prices.get_currency():
//    #			amount_of_currency_excess = _sum_of_trade[product]
//
//    if (sum_of_trade_and_excess_trade.has(Prices.get_currency())) :
//        amount_of_currency_excess = sum_of_trade_and_excess_trade[Prices.get_currency()]
//
//        var excess_relative_to_currency : Dictionary = {}
//        for product in sum_of_trade_and_excess_trade.keys() :
//            var amount = sum_of_trade_and_excess_trade[product]
//            excess_relative_to_currency[product] = amount - amount_of_currency_excess
//            #	Añadimos el _excess_products_dict
//
//#		
//
//            var max_amount_of_product_excess = 0.0
//            for product in excess_relative_to_currency.keys() :
//                var amount = abs(excess_relative_to_currency[product])
//                if amount > max_amount_of_product_excess:
//max_amount_of_product_excess = amount
//
//var param_min_product_excess_to_change_price = 0.0
//
//#Este parámetro deberían pasarse por argumento al método calculate_new_prices_increment() :
//    var param_price_change_step = param_price_change_step_arg
//
//    if (max_amount_of_product_excess > param_min_product_excess_to_change_price) :
//        for product in excess_relative_to_currency.keys() :
//            var amount = excess_relative_to_currency[product]
//
//            new_prices_increment[product] = param_price_change_step * amount / max_amount_of_product_excess
//
//            return new_prices_increment
