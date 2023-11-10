#include "Person.h"
//#include "PriceCalculationDefines.h"
#include "Reality.h"
#include "Prices.h"
#include "Market.h"
#include "TradeCalculator.h"
#include "SatisfactionCalculator.h"
#include "Utils.h"
#include "Product.h"
#include "Option.h"
#include <iostream>


long pca::CPerson::ms_nId = 0;

pca::CPerson::CPerson(CPrices* pPricesRef, std::string sName)
{
    ms_nId++;
    m_nId = ms_nId;

    m_sName = sName;

    //m_pMarketRef = pMarketRef;
    //m_pPricesRef = pMarketRef->GetPrices();
    std::unique_ptr<CSatisfactionCalculator> upSatisfactionCalculator(new CSatisfactionCalculator());
    std::unique_ptr<pca::CTradeCalculator> upTradeCalculator(new CTradeCalculator(std::move(upSatisfactionCalculator), pPricesRef));

    m_upTradeCalculator = std::move(upTradeCalculator);

    //ctor
    InitDefaultAmounts();
}


pca::CPerson::CPerson(std::unique_ptr<CTradeCalculator> upTradeCalculator)
{
    ms_nId++;
    m_nId = ms_nId;

    m_sName = "Person "+std::to_string(ms_nId);
    
    //m_pMarketRef = pMarketRef;
    //m_pPricesRef = pMarketRef->GetPrices();
    m_upTradeCalculator = std::move(upTradeCalculator);

    //ctor
    InitDefaultAmounts();
}

pca::CPerson::~CPerson()
{
    //dtor
}

void pca::CPerson::InitDefaultAmounts()
{
    //for (auto& nProduct : c_setProducts)
    for (auto& nProduct : pca::CReality::GetProducts())
    {
        m_mapOwnedProd_Amount[nProduct] = 0.0;
    }
}

void pca::CPerson::AddProductAmount(CProduct* pProductRef, double dAmount)
{
    if(m_mapOwnedProd_Amount.end()==m_mapOwnedProd_Amount.find(pProductRef))
    {
        m_mapOwnedProd_Amount[pProductRef]=dAmount;
    }
    else
    {
        m_mapOwnedProd_Amount[pProductRef] += dAmount;
    }
}

void pca::CPerson::SetProductAmount(CProduct* pProductRef, double dAmount)
{
    m_mapOwnedProd_Amount[pProductRef] = dAmount;    
}

void pca::CPerson::SubtractProductAmount(CProduct* pProductRef, double dAmount)
{
    AddProductAmount(pProductRef, -dAmount);
}

void pca::CPerson::AddProducts(std::map<pca::CProduct*, double> mapProductAmount)
{
    m_mapOwnedProd_Amount = CUtils::SumProducts(m_mapOwnedProd_Amount, mapProductAmount);
}

void pca::CPerson::SubtractProducts(std::map<pca::CProduct*, double> mapProductAmount)
{
    m_mapOwnedProd_Amount = CUtils::SubtractProducts(m_mapOwnedProd_Amount, mapProductAmount);
}

void pca::CPerson::AdjustBestCombinationForPerson()
{
    double dBudgetStep = 0.01;
    int nMaxNumSteps = 5;
    AdjustBestCombinationForPersonWithMaxNumSteps(dBudgetStep,nMaxNumSteps);
}
//func adjust_best_combination_for_person(person_arg:String) :
//    var budget_step = 0.01
//    var max_num_steps = 5
//    adjust_best_combination_for_person_with_max_num_steps(person_arg, budget_step, max_num_steps)


void pca::CPerson::AdjustBestCombinationForPersonWithMaxNumSteps(double dBudgetStepArg, int nMaxNumStepsArg)
{
    //CPrices* pPrices = m_pMarketRef->GetPrices();
    //pPrices->CalculateCombidictPrice(m_mapOwnedProd_Amount);
    std::map<pca::COption*, double> mapBestCombidict = m_upTradeCalculator->ImproveCombination(m_mapOwnedProd_Amount, m_mapCurrentOpt_Amount, dBudgetStepArg, nMaxNumStepsArg);

    this->m_mapCurrentOpt_Amount = mapBestCombidict;

    //Register bestcombi
    m_vLogBestOpt_Amount.push_back(mapBestCombidict);
    
    //return mapBestCombidict;
}

std::map<pca::COption*, double> pca::CPerson::CalculateImprovedCombination(std::map<CProduct*, double> mapOwnedCombidictArg, std::map<COption*, double> mapCurrentBestCombidictArg, double dBudgetStepArg, int nMaxNumStepsArg)
{
    return m_upTradeCalculator->ImproveCombination(mapOwnedCombidictArg, mapCurrentBestCombidictArg, dBudgetStepArg, nMaxNumStepsArg);
}

std::map<pca::CProduct*, double> pca::CPerson::GetSavedProductsFromOptions(const std::map<pca::COption*, double> & mapOptionAmount)
{
    std::map<pca::CProduct*, double> mapsumProductAmount;

    for (auto& pairOptionAmount : mapOptionAmount)
    {
        auto pOption = pairOptionAmount.first;
        if (pOption->IsSaving())
        {
            auto pProduct = pOption->GetProduct();
            if (pProduct)
            {
                double dAmount = pairOptionAmount.second;
                mapsumProductAmount[pProduct] = dAmount;
            }                
        }
    }

    return mapsumProductAmount;
}

std::map<pca::CProduct*, double> pca::CPerson::GetConsumedProductsFromOptions(const std::map<pca::COption*, double> & mapOptionAmount)
{
    std::map<pca::CProduct*, double> mapsumProductAmount;

    for (auto& pairOptionAmount : mapOptionAmount)
    {
        auto pOption = pairOptionAmount.first;
        if (false == pOption->IsSaving())
        {
            auto pProduct = pOption->GetProduct();
            if (pProduct)
            {
                double dAmount = pairOptionAmount.second;
                mapsumProductAmount[pProduct] = dAmount;
            }
        }
    }

    return mapsumProductAmount;
}

void pca::CPerson::CalculateTradeWithCurrentBestCombination()
{
    std::map<pca::CProduct*, double> mapCurrentDesiredProd_Amount;
    mapCurrentDesiredProd_Amount = CUtils::CalculateProductdictFromOptiondict(m_mapCurrentOpt_Amount);
    m_mapCurrentTradProd_Amount = CUtils::SubtractProducts(mapCurrentDesiredProd_Amount, m_mapOwnedProd_Amount);

    ////mapCurrentDesiredProd_Amount
    //std::cout << "mapCurrentDesiredProd_Amount of person: " << this->GetName() << std::endl;
    //for (auto& pCurrent_DesiredProd : mapCurrentDesiredProd_Amount)
    //{
    //    pca::CProduct* pProduct = pCurrent_DesiredProd.first;
    //    double dDesired = pCurrent_DesiredProd.second;
    //    std::cout << "--" << pProduct->GetName() << ": desired: " << dDesired << std::endl;

    //}

    ////m_mapCurrentTradProd_Amount
    //std::cout << "m_mapCurrentTradProd_Amount of person: " << this->GetName() << std::endl;
    //for (auto& pCurrent_CurrentTradProd : m_mapCurrentTradProd_Amount)
    //{
    //    pca::CProduct* pProduct = pCurrent_CurrentTradProd.first;
    //    double dCurrentTradeProd = pCurrent_CurrentTradProd.second;
    //    std::cout << "--" << pProduct->GetName() << ": dCurrentTradeProd: " << dCurrentTradeProd << std::endl;

    //}

}

std::map<pca::CProduct*, double> pca::CPerson::GetTrade()
{
    return m_mapCurrentTradProd_Amount;
}

pca::CTradeCalculator* pca::CPerson::GetTradeCalculatorRef()
{
    return m_upTradeCalculator.get();
}

pca::CSatisfactionCalculator* pca::CPerson::GetSatisfactionCalculatorRef()
{
    return m_upTradeCalculator->GetSatisfactionCalculatorRef();
}

double pca::CPerson::GetCurrentOptAmount(pca::COption* pOptionRef)
{
    if (this->m_mapCurrentOpt_Amount.find(pOptionRef) != this->m_mapCurrentOpt_Amount.end())
    {
        return this->m_mapCurrentOpt_Amount.at(pOptionRef);
    }

    return 0.0;
}

double pca::CPerson::GetOwnedProdAmount(pca::CProduct* pProductRef)
{
    if (this->m_mapOwnedProd_Amount.find(pProductRef) != this->m_mapOwnedProd_Amount.end())
    {
        return this->m_mapOwnedProd_Amount.at(pProductRef);
    }

    return 0.0;
}

double pca::CPerson::GetDesiredProdAmount(pca::CProduct* pProduct)
{
    std::map<pca::CProduct*, double> mapCurrentDesiredProd_Amount;
    mapCurrentDesiredProd_Amount = CUtils::CalculateProductdictFromOptiondict(m_mapCurrentOpt_Amount);
    
    if (mapCurrentDesiredProd_Amount.end() != mapCurrentDesiredProd_Amount.find(pProduct))
    {
        return mapCurrentDesiredProd_Amount.at(pProduct);
    }

    return 0.0;
}


// 
//    func adjust_best_combination_for_person_with_max_num_steps(person_arg:String, budget_step : float, max_num_steps : int)->Dictionary:
//    if _person_owned_dict.has(person_arg) :
//        #		var combidict : Dictionary = _person_owned_dict[person_arg]
//        #		var budget : float = Prices.calculate_combidict_price(combidict)
//        ##		print("Budget for " + person_arg + ": " + str(budget))
//        #		_person_value_of_owned[person_arg] = budget
//#
//        #		var budget : float = self.get_value_of_owned(person_arg)
//        if self._person_tradecalc.has(person_arg) :
//            var trade_calc : TradeCalculator = self._person_tradecalc[person_arg]
//
//            if _person_best_combination_dict.has(person_arg) == false :
//                var empty_combidict : Dictionary = {}
//                _person_best_combination_dict[person_arg] = empty_combidict
//                var current_best_combidict = _person_best_combination_dict[person_arg]
//                #			var best_combidict : Dictionary = trade_calc.adjust_best_combidict(budget, current_best_combidict_arg, budget_step, max_num_steps)
//                #			TODO : Probar adjust_best_combidict_changing_step
//                #			var init_budget_step = budget_step * 8
//                #			var best_combidict : Dictionary = trade_calc.adjust_best_combidict_changing_step(budget, current_best_combidict, init_budget_step, budget_step, max_num_steps)
//                #			_person_best_combination_dict[person_arg] = best_combidict
//#
//                var best_combidict : Dictionary = improve_combination(trade_calc, _person_owned_dict[person_arg], current_best_combidict, budget_step, max_num_steps)
//                _person_best_combination_dict[person_arg] = best_combidict
//                #			El cálculo tendría que hacerse con pasos de precisión de decimales, y el metodo interpolaría para resultados intermedios
//                return best_combidict
//                var null_dictionary = {}
//                _person_best_combination_dict[person_arg] = null_dictionary
//                return null_dictionary


