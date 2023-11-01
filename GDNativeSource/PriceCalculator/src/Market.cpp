#include "Market.h"
#include "Person.h"
#include "Utils.h"
#include "PricesLogInfo.h"
#include "Prices.h"
#include "Reality.h"
#include "Product.h"

#include <iostream>
#include <iomanip>

const long c_paramMaxStepsCalculatingNewPrices = 100;
const double c_paramPricePrecission = 0.01;
const double c_paramInitialPriceChangeStep = 0.1;
const double c_paramProductStepForBestCombidictCalc= 0.1;

pca::CMarket::CMarket()
{
    //ctor
    m_upPrices = std::unique_ptr<CPrices>(new CPrices());
    m_upPricesLogInfo = std::unique_ptr<CPricesLogInfo>(new CPricesLogInfo(m_upPrices.get()));

}

pca::CMarket::~CMarket()
{
    //dtor
}

void pca::CMarket::AddPerson(std::unique_ptr<CPerson> upPerson)
{
    m_vPersons.push_back(std::move(upPerson));
}

void pca::CMarket::CreatePerson(std::string sName)
{
    CPrices* pPricesRef = this->GetPricesRef();
    std::unique_ptr<CPerson> upPerson(new CPerson(this->GetPricesRef(), sName));
    m_vPersons.push_back(std::move(upPerson));
}

pca::CPerson* pca::CMarket::GetPersonRef(std::string sName)
{
    for (auto& pPerson : m_vPersons)
    {
        if (pPerson->GetName() == sName)
        {
            return pPerson.get();
        }
    }

    return nullptr;
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
    long nMaxCount = c_paramMaxStepsCalculatingNewPrices;
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

    //
    //m_mapSumOfTrade
    //for (auto& produt_trade : m_mapSumOfTrade)
    //{
    //    CProduct* pProduct = produt_trade.first;
    //    double dTrade = produt_trade.second;

    //    std::cout << "-" << pProduct->GetName() << " dTrade: " << dTrade << std::endl;
    //}

    //std::cout << "mapNewPricesIncrements: " << std::endl;
    //for (auto& produt_price : mapNewPricesIncrements)
    //{
    //    CProduct* pProduct = produt_price.first;
    //    double dIncrement = produt_price.second;

    //    std::cout << "-" << pProduct->GetName() << " price increment: " << dIncrement << std::endl;
    //}

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

std::map<pca::CProduct*, double>  pca::CMarket::CalculateNewPricesIncrement(double dParamPriceChangeStepArg)
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

pca::CPricesLogInfo* pca::CMarket::GetPricesLogInfoRef()
{
    return m_upPricesLogInfo.get();
}

