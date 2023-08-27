#include "Tester.h"
#include <iostream>
#include <chrono>
//#include "PriceCalculationDefines.h"
#include "Reality.h"
#include "SatisfactionCurve.h"
#include "SatisfactionCalculator.h"
#include "TradeCalculator.h"
#include "Prices.h"
#include "Market.h"
#include "Option.h"
#include "Utils.h"




pca::CTester::CTester()
{
    //ctor

    std::cout << "Creating CTester" << std::endl;
}

pca::CTester::~CTester()
{
    //dtor
}

int pca::CTester::Test_SatisfactionCurve()
{
    std::cout << "Starting Test_SatisfactionCurve" << std::endl;

    CSatisfactionCurve oSatCurve;

    for (int i=0; i<20; i++)
    {
        double dSatisf = oSatCurve.CalculateSatifaction(i);
        std::cout << "dSatisfAt_"<<i << ": "<< dSatisf << std::endl;
    }

    std::cout << "Test_SatisfactionCurve finished" << std::endl;
    
    return 0;
}

int pca::CTester::Test_SatisfactionCalculator()
{
    std::cout << "Starting Test_SatisfactionCalculator" << std::endl;
    {
        CReality::Init();
        CSatisfactionCalculator oSatCalculator;
        std::map<COption*, double> map_nOption_dAmount;
        //for (auto& nOption : c_setOptions)
        for (auto& nOption : pca::CReality::GetOptions())
        {
            map_nOption_dAmount[nOption] = 1.0;
        }

        std::cout << "Prueba..." << std::endl;
        double dSatisfFormIndivOptions = oSatCalculator.CalculateSatisfOfCombidictFromIndividualOptions(map_nOption_dAmount);
        std::cout << "dSatisfFormIndivOptions: " << dSatisfFormIndivOptions << std::endl;
        double dSatisfFormSuppCombos = oSatCalculator.CalculateSatisfOfCombidictFromSupplementaryCombos(map_nOption_dAmount);
        std::cout << "dSatisfFormSuppCombos " << dSatisfFormSuppCombos << std::endl;
        double dSatisfFormCompCombos = oSatCalculator.CalculateSatisfOfCombidictFromComplementaryCombos(map_nOption_dAmount);
        std::cout << "dSatisfFormCompCombos " << dSatisfFormCompCombos << std::endl;
        double dSatisfTotal = oSatCalculator.CalculateSatisfOfCombidict(map_nOption_dAmount);
        std::cout << "dSatisfTotal " << dSatisfTotal << std::endl;
    }
    std::cout << "Test_SatisfactionCalculator finished" << std::endl;
    
    std::cout << "Starting test TradeCalculator" << std::endl;
    {
        CPrices oPrices;
        std::unique_ptr<CSatisfactionCalculator> upSatisfactionCalculator(new CSatisfactionCalculator);
        CTradeCalculator oTradeCalculator(std::move(upSatisfactionCalculator), &oPrices);
        std::map<COption*, double> map_nOption_dAmount;
        //for (auto& nOption : c_setOptions)
        for (auto& nOption : pca::CReality::GetOptions())
        {
            map_nOption_dAmount[nOption] = 1.0;
        }
        std::cout << "Probando AdjustBestCombidict..." << std::endl;
        std::map<COption*, double> mapOpAmmAdjusted = oTradeCalculator.AdjustBestCombidict(10.0, map_nOption_dAmount, 1.0, 100);
        for (auto& pair_Op_Am : mapOpAmmAdjusted)
        {
            std::cout << "Option: " << pair_Op_Am.first->GetName() << std::endl;
            std::cout << "Amount: " << pair_Op_Am.second << std::endl;
        }
    }
    std::cout << "Test TradeCalculator finished" << std::endl;

    std::cout << "TODO test Market" << std::endl;
    std::cout << "Starting test Market" << std::endl;
    {
        CMarket oMarket;
 
        std::unique_ptr<CSatisfactionCalculator> upSatisfactionCalculator_1(new CSatisfactionCalculator());
        std::unique_ptr<CTradeCalculator> upTradeCalculator_1(new CTradeCalculator(std::move(upSatisfactionCalculator_1), oMarket.GetPricesRef()));
        std::unique_ptr<CSatisfactionCalculator> upSatisfactionCalculator_2(new CSatisfactionCalculator());
        std::unique_ptr<CTradeCalculator> upTradeCalculator_2(new CTradeCalculator(std::move(upSatisfactionCalculator_2), oMarket.GetPricesRef()));
        std::unique_ptr<CSatisfactionCalculator> upSatisfactionCalculator_3(new CSatisfactionCalculator());
        std::unique_ptr<CTradeCalculator> upTradeCalculator_3(new CTradeCalculator(std::move(upSatisfactionCalculator_3), oMarket.GetPricesRef()));

        std::unique_ptr<CPerson> upPerson_1(new CPerson(std::move(upTradeCalculator_1)));
        std::unique_ptr<CPerson> upPerson_2(new CPerson(std::move(upTradeCalculator_2)));
        std::unique_ptr<CPerson> upPerson_3(new CPerson(std::move(upTradeCalculator_3)));

        std::map<CProduct*, double> mapProd_Amm;
        //for (auto& nProd : c_setProducts)
        for (auto& pProd : pca::CReality::GetProducts())
        {
            upPerson_1->AddProductAmount(pProd, 1.0);
            upPerson_2->AddProductAmount(pProd, 1.0);
            upPerson_3->AddProductAmount(pProd, 1.0);
        }

        CPerson* pPerson_1_Ref = upPerson_1.get();
        CPerson* pPerson_2_Ref = upPerson_2.get();
        CPerson* pPerson_3_Ref = upPerson_3.get();

        oMarket.AddPerson(std::move(upPerson_1));
        oMarket.AddPerson(std::move(upPerson_2));
        oMarket.AddPerson(std::move(upPerson_3));
        
        std::cout << "Person options before CalculateNewPrices:" << std::endl;
        CUtils::PrintPersonOptions(pPerson_1_Ref);
        CUtils::PrintPersonOptions(pPerson_2_Ref);
        CUtils::PrintPersonOptions(pPerson_3_Ref);

        std::cout << "Prices before CalculateNewPrices:" << std::endl;
                
        CUtils::PrintPrices(oMarket.GetPricesRef());

        //Voy a medir el tiempo de los siguientes cálculos:
        auto start = std::chrono::high_resolution_clock::now();

        //double dStep = 1.0;
        //double dMaxNumSteps = 10;
        //oMarket.AdjustBestCombinations(dStep, dMaxNumSteps); //Es método protected, pero Tester es friend
        oMarket.CalculateNewPrices();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << std::endl;

        std::cout << "Person options after CalculateNewPrices:" << std::endl;
        CUtils::PrintPersonOptions(pPerson_1_Ref);
        CUtils::PrintPersonOptions(pPerson_2_Ref);
        CUtils::PrintPersonOptions(pPerson_3_Ref);

        std::cout << "Prices after CalculateNewPrices:" << std::endl;
        CUtils::PrintPrices(oMarket.GetPricesRef());

    }    
    
    std::cout << "Test Market finished" << std::endl;

    return 0;
}

