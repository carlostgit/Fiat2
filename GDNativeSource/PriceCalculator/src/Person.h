#ifndef CPERSON_H
#define CPERSON_H

//#include "PriceCalculationDefines.h"
#include <map>
#include <memory>
#include <string>

namespace pca
{
    class CPrices;
    class CMarket;
    class CTradeCalculator;
    class CProduct;
    class COption;

    class CPerson
    {
    public:
        CPerson(CPrices* pPricesRef, CMarket* pMarketRef, std::unique_ptr<CTradeCalculator> upTradCalculator);
        virtual ~CPerson();

        void AddProductAmount(CProduct* pProductRef, double dAmount);
        void RemoveProductAmount(CProduct* pProductRef, double dAmount);

        void AddProducts(std::map<pca::CProduct*, double> mapProductAmount);
        void SubtractProducts(std::map<pca::CProduct*, double> mapProductAmount);

        std::map<pca::CProduct*, double> GetSavedProductsFromOptions(const std::map<pca::COption*, double> & mapOptionAmount);
        std::map<pca::CProduct*, double> GetConsumedProductsFromOptions(const std::map<pca::COption*, double>& mapOptionAmount);

        void AdjustBestCombinationForPerson();
        std::map<pca::COption*, double> AdjustBestCombinationForPersonWithMaxNumSteps(double dBudgetStepArg, int nMaxNumSteps);
        //func adjust_best_combination_for_person(person_arg:String) :
        //    var budget_step = 0.01
        //    var max_num_steps = 5
        //    adjust_best_combination_for_person_with_max_num_steps(person_arg, budget_step, max_num_steps)

        std::map<pca::COption*, double> GetCurrentOpt_Amount() {
            return this->m_mapCurrentOpt_Amount;
        }

        std::map<pca::CProduct*, double> GetOwnedProd_Amount() {
            return this->m_mapOwnedProd_Amount;
        }

        long GetId() {
            return this->m_nId;
        }

        void SetName(std::string sName) {
            this->m_sName = sName;
        }

        std::string GetName() {
            return this->m_sName;
        }

    protected:

        void InitDefaultAmounts();

    private:

        static long ms_nId;
        long m_nId = 0;
        std::string m_sName = "No name";

        std::map<pca::CProduct*, double> m_mapOwnedProd_Amount;
        std::map<pca::COption*, double> m_mapCurrentOpt_Amount;

        CPrices* m_pPricesRef = nullptr;
        CMarket* m_pMarketRef = nullptr;
        std::unique_ptr<CTradeCalculator> m_upTradeCalculator;

    };
}
#endif // CPERSON_H
