#ifndef CPERSON_H
#define CPERSON_H

//#include "PriceCalculationDefines.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace pca
{
    class CPrices;
    class CMarket;
    class CTradeCalculator;
    class CProduct;
    class COption;
    class CSatisfactionCalculator;

    class CPerson
    {
    public:
        CPerson(std::string sName, pca::CMarket* pMarketRef);
        //CPerson(std::unique_ptr<CTradeCalculator> upTradCalculator);
        virtual ~CPerson();

        void AddProductAmount(CProduct* pProductRef, double dAmount);
        void SetProductAmount(CProduct* pProductRef, double dAmount);
        void SubtractProductAmount(CProduct* pProductRef, double dAmount);

        void AddProducts(std::map<pca::CProduct*, double> mapProductAmount);
        void SubtractProducts(std::map<pca::CProduct*, double> mapProductAmount);

        std::map<pca::CProduct*, double> GetSavedProductsFromOptions(const std::map<pca::COption*, double> & mapOptionAmount);
        std::map<pca::CProduct*, double> GetConsumedProductsFromOptions(const std::map<pca::COption*, double>& mapOptionAmount);

        //void AdjustBestCombinationForPerson();        
        void AdjustBestCombinationForPersonWithMaxNumSteps(double dInitBudgetStepArg, double dTargetBudgetStepArg, int nMaxNumStepsArg);
        //func adjust_best_combination_for_person(person_arg:String) :
        //    var budget_step = 0.01
        //    var max_num_steps = 5
        //    adjust_best_combination_for_person_with_max_num_steps(person_arg, budget_step, max_num_steps)

        std::map<pca::COption*, double> GetMapCurrentOpt_Amount() {
            return this->m_mapCurrentOpt_Amount;
        }

        std::map<pca::CProduct*, double> GetMapOwnedProd_Amount() {
            return this->m_mapOwnedProd_Amount;
        }

        double GetCurrentOptAmount(pca::COption* pOptionRef);

        double GetDesiredProdAmount(pca::CProduct* pProduct);

        double GetOwnedProdAmount(pca::CProduct* pProductRef);

        long GetId() {
            return this->m_nId;
        }

        void SetName(std::string sName) {
            this->m_sName = sName;
        }

        std::string GetName() {
            return this->m_sName;
        }

        void CalculateTradeWithCurrentBestCombination();

        std::map<pca::CProduct*, double> GetTrade();

        double GetTradedAmount(pca::CProduct* pProduct);

        pca::CTradeCalculator* GetTradeCalculatorRef();

        pca::CSatisfactionCalculator* GetSatisfactionCalculatorRef();

        //std::map<pca::COption*, double> CalculateImprovedCombination(std::map<CProduct*, double> mapOwnedCombidictArg, std::map<COption*, double> mapCurrentBestCombidictArg, double dBudgetStep, int nMaxNumSteps);

        std::vector < std::map<pca::COption*, double>> GetLogOfBestCombinations() {
            return m_vLogBestOpt_Amount;
        }

        std::vector < std::map<pca::CProduct*, double>> GetLogOfTrade() {
            return m_vLogTrade_Amount;
        }

        pca::CMarket* GetMarketRef() {
            return m_pMarketRef;
        }

    protected:

        void InitDefaultAmounts();

    private:

        static long ms_nId;
        long m_nId = 0;
        std::string m_sName = "No name";

        std::map<pca::CProduct*, double> m_mapOwnedProd_Amount;
        std::map<pca::COption*, double> m_mapCurrentOpt_Amount;

        std::map<pca::CProduct*, double> m_mapCurrentTradProd_Amount;

        //CPrices* m_pPricesRef = nullptr;
        //CMarket* m_pMarketRef = nullptr;
        std::unique_ptr<CTradeCalculator> m_upTradeCalculator;

        std::vector < std::map<pca::COption*, double>> m_vLogBestOpt_Amount;
        std::vector < std::map<pca::CProduct*, double>> m_vLogTrade_Amount;

        pca::CMarket* m_pMarketRef = nullptr;

    };
}
#endif // CPERSON_H
