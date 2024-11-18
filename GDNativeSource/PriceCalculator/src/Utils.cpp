#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Person.h"
#include "Option.h"
#include "SupplCombo.h"
#include "ComplCombo.h"
#include "Product.h"
#include "Reality.h"
#include "Prices.h"
#include "Market.h"
#include "PricesLogInfo.h"
#include "SatisfactionCalculator.h"

#include <algorithm>

pca::CUtils::CUtils()
{
    //ctor

}

pca::CUtils::~CUtils()
{
    //dtor
}

void pca::CUtils::PrintPersonsOptionAdjustmentToFile(CMarket* pMarket)
{
    std::string fileName = "log_market_adjustment.csv";
    // Open a CSV file for writing
    std::ofstream csvFile(fileName);

    // Check if the file is open
    if (!csvFile.is_open()) {
        std::cerr << "Failed to create the CSV file." << std::endl;
        return;
    }

    auto vOptions = pMarket->GetOptions();

    //todo: meter aquí los titulos de los precios de productos
    auto vProducts = pMarket->GetProducts();
    
    csvFile << "PriceChangeStep"; // Writing header row
    csvFile << ",";

    for (auto & pProduct:vProducts)
    {
        std::string sProductName = pProduct->GetName();
        csvFile << "Price_" + sProductName; // Writing header row
        csvFile << ",";
    }
    
    auto vPersons = pMarket->GetPersons();

    for (int i1=0;i1<vPersons.size();i1++)
    //for (auto& pPerson : vPersons)
    {
        auto pPerson = vPersons[i1];

        auto sPersonName = pPerson->GetName();

        csvFile << "Satisfaction_" + sPersonName; // Writing header row
        csvFile << ",";

        for (int i = 0;i < vOptions.size();i++)
        {
            std::string optionName = vOptions[i]->GetName();

            csvFile << optionName << "_" << sPersonName; // Writing header row
    
            csvFile << ",";
            
        }

        for (int i = 0;i < vProducts.size();i++)
        {
            std::string productName = vProducts[i]->GetName();

            csvFile << productName << "_" << sPersonName; // Writing header row

            csvFile << ",";

        }
    }

    csvFile << std::endl;

    long nNumLog = 0;
    if (false==vPersons.empty())
        nNumLog = vPersons.front()->GetLogOfBestCombinations().size();

    std::map<CProduct*,std::vector<double> > mapProd_vPriceAmount = pMarket->GetPricesLogInfoRef()->GetProductAllPrices();    

    std::vector<double> vPriceChangeStepVector = pMarket->GetPricesLogInfoRef()->GetAllPriceChangeStepsVector();

    

    long nNumPrices = 0;
    if (false == mapProd_vPriceAmount.empty())
        nNumPrices = mapProd_vPriceAmount.begin()->second.size();

    for (int i1 = 0;i1 < nNumLog;i1++)
    {
        double dPriceChangeStep = 0.0;
        if (i1 < vPriceChangeStepVector.size())
            dPriceChangeStep = vPriceChangeStepVector.at(i1);

        csvFile << dPriceChangeStep; // Writing header row        
        csvFile << ",";

        for (auto& pProduct : vProducts)
        {
            double dProductAmount = 0;
            if(mapProd_vPriceAmount.end()== mapProd_vPriceAmount.find(pProduct))
            {
                ;
            }
            else
            {
                std::vector<double> vProductAmount = mapProd_vPriceAmount.at(pProduct);
                if (i1 < vProductAmount.size())
                    dProductAmount = vProductAmount.at(i1);
            }

            csvFile << dProductAmount; // Writing header row        
            csvFile << ",";                     
        }

        for (auto& pPerson : vPersons)
        {
            auto sPersonName = pPerson->GetName();

            auto vmapOptionsLog = pPerson->GetLogOfBestCombinations();

            if (i1 >= vmapOptionsLog.size())
                continue;

            std::map<COption*,double> mapOption_Amount = vmapOptionsLog[i1];
            //for (auto& mapOption_Amount : vmapOptionsLog)
            //{
            double dSatisfaction = pPerson->GetSatisfactionCalculatorRef()->CalculateSatisfOfCombidict(mapOption_Amount);
            csvFile << dSatisfaction; // Writing header row        
            csvFile << ",";

            for (int i = 0;i < vOptions.size();i++)
            {
                auto pOption = vOptions[i];
                std::string optionName = pOption->GetName();

                if (mapOption_Amount.end() == mapOption_Amount.find(pOption))
                    continue;

                double dAmount = mapOption_Amount.at(pOption);

                csvFile << dAmount;
                
                csvFile << ",";                                
            }

            auto vmapTradeLog = pPerson->GetLogOfTrade();

            if (i1 >= vmapTradeLog.size())
                continue;

            std::map<CProduct*, double> mapProduct_Amount = vmapTradeLog[i1];

            for (int i = 0;i < vProducts.size();i++)
            {
                auto pProduct = vProducts[i];
                std::string productName = pProduct->GetName();

                if (mapProduct_Amount.end() == mapProduct_Amount.find(pProduct))
                    continue;

                auto dAmount = mapProduct_Amount.at(pProduct);

                csvFile << dAmount;

                csvFile << ",";
            }

            //}
        }

        csvFile << std::endl;
    }

    csvFile.close();
}

void pca::CUtils::PrintScenarioInfoToFile(CMarket* pMarket)
{
    std::string fileName = "scenario_info.txt";
    // Open a CSV file for writing
    std::ofstream csvFile(fileName);

    // Check if the file is open
    if (!csvFile.is_open()) {
        std::cerr << "Failed to create the CSV file." << std::endl;
        return;
    }

    csvFile << std::endl;

    csvFile << "Scenario info" << std::endl;
    csvFile << std::endl;

    std::vector<pca::COption*> vOptions = pMarket->GetOptions();
    std::sort(vOptions.begin(), vOptions.end(), [](pca::COption* pOption1, pca::COption* pOption2)->bool{
            return (pOption1->GetName() < pOption2->GetName());});

    csvFile << "Options:" << std::endl;

    for (int i = 0;i < vOptions.size();i++)
    {
        std::string optionName = vOptions[i]->GetName();

        csvFile << "Option " + optionName; // Writing header row        
        //csvFile << ",";
        csvFile << std::endl;
    }

    csvFile << std::endl;

//TODO: Obtener también las supplementary options y las completmentary options!

    auto pReality = pMarket->GetRealityRef();

    std::vector<pca::CSupplCombo*> vSupplCombos = pReality->GetSupplCombos();
    std::sort(vSupplCombos.begin(), vSupplCombos.end(), [](pca::CSupplCombo* pCombo1, pca::CSupplCombo* pCombo2)->bool {
        return (pCombo1->GetName() < pCombo2->GetName());});

    csvFile << "SupplCombos:" << std::endl;

    for (int i = 0;i < vSupplCombos.size();i++)
    {
        std::string supplComboName = vSupplCombos[i]->GetName();

        csvFile << "SupplCombo " + supplComboName; // Writing header row        
        //csvFile << ",";
        csvFile << std::endl;
    }

    csvFile << std::endl;

    std::vector<pca::CComplCombo*> vComplCombos = pReality->GetComplCombos();
    std::sort(vComplCombos.begin(), vComplCombos.end(), [](pca::CComplCombo* pCombo1, pca::CComplCombo* pCombo2)->bool {
        return (pCombo1->GetName() < pCombo2->GetName());});

    csvFile << "ComplCombos:" << std::endl;

    for (int i = 0;i < vComplCombos.size();i++)
    {
        std::string complComboName = vComplCombos[i]->GetName();

        csvFile << "ComplCombo " + complComboName; // Writing header row        
        //csvFile << ",";
        csvFile << std::endl;
    }


    csvFile << std::endl;
    //todo: meter aquí los titulos de los precios de productos
    auto vProducts = pMarket->GetProducts();
    std::sort(vProducts.begin(), vProducts.end(), [](pca::CProduct* pProduct1, pca::CProduct* pProduct2)->bool {
        return (pProduct1->GetName() < pProduct2->GetName());});

    csvFile << "Products:" << std::endl;

    for (auto& pProduct : vProducts)
    {
        std::string sProductName = pProduct->GetName();
        csvFile << "Product " + sProductName; // Writing header row
        csvFile << ",";
    }

    csvFile << std::endl;
    csvFile << std::endl;

    auto vPersons = pMarket->GetPersons();
    std::sort(vPersons.begin(), vPersons.end(), [](pca::CPerson* pPerson1, pca::CPerson* pPerson2)->bool {
        return (pPerson1->GetName() < pPerson2->GetName());});

    csvFile << "Persons:" << std::endl;
    
    for (int i1 = 0;i1 < vPersons.size();i1++)
        //for (auto& pPerson : vPersons)
    {
        auto pPerson = vPersons[i1];

        auto sPersonName = pPerson->GetName();

        csvFile << "Person " + sPersonName; // Writing header row
        auto pPersonRef = pMarket->GetPersonRef(sPersonName);
        auto pSatisfCalcRef = pPersonRef->GetSatisfactionCalculatorRef();
        
        csvFile << std::endl;

        for (int i = 0;i < vOptions.size();i++)
        {
            std::string optionName = vOptions[i]->GetName();

            csvFile << "Option " + optionName; // Writing header row        
            //csvFile << ",";
            csvFile << std::endl;
            
            double dMaximumSatisf = pSatisfCalcRef->GetMaximumSatisf(vOptions[i]);
            csvFile << "dMaximumSatisf: " << dMaximumSatisf << std::endl;

            double dPreferenceAt0 = pSatisfCalcRef->GetPreferenceAt0(vOptions[i]);
            csvFile << "dPreferenceAt0: " << dPreferenceAt0 << std::endl;
        }

        csvFile << std::endl;

        for (int i = 0;i < vSupplCombos.size();i++)
        {
            std::string supplComboName = vSupplCombos[i]->GetName();

            csvFile << "SupplCombo " + supplComboName; // Writing header row        
            //csvFile << ",";
            csvFile << std::endl;

            double dMaximumSatisf = pSatisfCalcRef->GetMaximumSatisf(vSupplCombos[i]);
            csvFile << "dMaximumSatisf: " << dMaximumSatisf << std::endl;

            double dPreferenceAt0 = pSatisfCalcRef->GetPreferenceAt0(vSupplCombos[i]);
            csvFile << "dPreferenceAt0: " << dPreferenceAt0 << std::endl;

        }

        csvFile << std::endl;

        for (int i = 0;i < vComplCombos.size();i++)
        {
            std::string complComboName = vComplCombos[i]->GetName();

            csvFile << "ComplCombo " + complComboName; // Writing header row        
            //csvFile << ",";
            csvFile << std::endl;

            double dMaximumSatisf = pSatisfCalcRef->GetMaximumSatisf(vComplCombos[i]);
            csvFile << "dMaximumSatisf: " << dMaximumSatisf << std::endl;

            double dPreferenceAt0 = pSatisfCalcRef->GetPreferenceAt0(vComplCombos[i]);
            csvFile << "dPreferenceAt0: " << dPreferenceAt0 << std::endl;

        }

        //csvFile << ",";
        csvFile << std::endl;
        
    }

    csvFile << std::endl;
    csvFile << std::endl;

    csvFile.close();
}

void pca::CUtils::PrintPersonOptionAdjustmentToFile(CPerson* pPerson)
{
    CMarket* pMarketRef = pPerson->GetMarketRef();

    auto personName = pPerson->GetName();

    std::string fileName = "log_option_adjustment_" + personName + ".csv";
    // Open a CSV file for writing
    std::ofstream csvFile(fileName);

    // Check if the file is open
    if (!csvFile.is_open()) {
        std::cerr << "Failed to create the CSV file." << std::endl;
        return;
    }

    //

    auto vOptions = pMarketRef->GetOptions();

    csvFile << "Satisfaction"; // Writing header row
    csvFile << ",";

    for (int i=0;i< vOptions.size();i++)
    {
        std::string optionName = vOptions[i]->GetName();

        csvFile << optionName; // Writing header row

        
        csvFile << ",";
        
    }

    csvFile << std::endl;

    auto vmapOptionsLog = pPerson->GetLogOfBestCombinations();

    for (auto& mapOption_Amount : vmapOptionsLog)
    {
        double dSatisfaction = pPerson->GetSatisfactionCalculatorRef()->CalculateSatisfOfCombidict(mapOption_Amount);
        csvFile << dSatisfaction; // Writing header row        
        csvFile << ",";

        for (int i = 0;i < vOptions.size();i++)
        {
            auto pOption = vOptions[i];
            std::string optionName = pOption->GetName();

            if (mapOption_Amount.end() == mapOption_Amount.find(pOption))
                continue;

            double dAmount = mapOption_Amount.at(pOption);


            csvFile << dAmount; // Writing header row

            
            csvFile << ",";
            

        }
        csvFile << std::endl;
    }

    csvFile.close();
}


void pca::CUtils::PrintOptions(std::map<pca::COption*, double> mapOpt_Amount)
{
    std::cout << "Option amounts: " << std::endl;
    for (auto& pairOpt_Amount : mapOpt_Amount)
    {
        COption* pOption = pairOpt_Amount.first;

        //std::cout << " '" << std::left << std::setw(10) << c_mapOption_Name.at(pairOpt_Amount.first).substr(0, 10) << "':'" << pairOpt_Amount.second<<"'";
        std::cout << " '" << std::left << std::setw(10) << pOption->GetName().substr(0, 10) << "':'" << pairOpt_Amount.second << "'";
    }
    std::cout << std::endl;
}

void pca::CUtils::PrintPersonOptions(CPerson* pPerson)
{
    auto personName = pPerson->GetName();
    std::cout <<"Person '"<< pPerson->GetId() << "'  Person name: '" << personName << "'" << std::endl;
    auto mapOpt_Amount = pPerson->GetMapCurrentOpt_Amount();
    std::cout << "Option amounts: " << std::endl;
    for (auto& pairOpt_Amount : mapOpt_Amount)
    {
        //std::cout << " '" << std::left << std::setw(10) << c_mapOption_Name.at(pairOpt_Amount.first).substr(0, 10) << "':'" << pairOpt_Amount.second << "'";
        COption* pOption = pairOpt_Amount.first;
        std::cout << " '" << std::left << std::setw(10) << pOption->GetName().substr(0, 10) << "':'" << pairOpt_Amount.second << "'";
    }
    std::cout << std::endl;
}

void pca::CUtils::PrintPrices(CPrices* pPrices)
{
    pca::CMarket* pMarketRef = pPrices->GetMarketRef();

    std::cout << "Prices:" << std::endl;
    
    for (auto& pProduct : pMarketRef->GetProducts())
    {        
        std::cout << " '" << std::left << std::setw(10) << pProduct->GetName().substr(0, 10) << "':'" << pPrices->GetPriceOfProduct(pProduct) << "'";
    }
    std::cout << std::endl;
}

std::map<pca::CProduct*, double> pca::CUtils::CalculateProductdictFromOptiondict(std::map<COption*, double> mapOptiondictArg)
{
    std::map<CProduct*, double> mapProductdict;

    for (auto& pairOptionAmount : mapOptiondictArg)
    {
        COption* pOption = pairOptionAmount.first;
        double dAmount = pairOptionAmount.second;

        //if (c_mapOption_Product.end() != c_mapOption_Product.find(pOption))
        {
            //CProduct* pProduct = c_mapOption_Product.at(pOption);

            CProduct* pProduct = pOption->GetProduct();

            if (mapProductdict.end() != mapProductdict.find(pProduct))
            {
                mapProductdict[pProduct] = dAmount + mapProductdict.at(pProduct);
            }
            else
            {
                mapProductdict[pProduct] = dAmount;
            }
        }
    }

    return mapProductdict;
}

std::map<pca::CProduct*, double> pca::CUtils::SumProducts(const std::map<pca::CProduct*, double> & mapProductAmount_1, const std::map<pca::CProduct*, double> & mapProductAmount_2)
{
    std::map<pca::CProduct*, double> mapsumProductAmount;

    for (auto& pairProductAmount : mapProductAmount_1)
    {
        pca::CProduct* pProduct = pairProductAmount.first;
        double dAmount_1 = pairProductAmount.second;
        if(mapProductAmount_2.find(pProduct) != mapProductAmount_2.end())
        {
            double dAmount_2 = mapProductAmount_2.at(pProduct);
            mapsumProductAmount[pProduct] = dAmount_1 + dAmount_2;
        }
        else
        {
            mapsumProductAmount[pProduct] = dAmount_1;
        }
    }

    for (auto& pairProductAmount_2 : mapProductAmount_2)
    {
        pca::CProduct* pProduct_2 = pairProductAmount_2.first;
        double dAmount_2 = pairProductAmount_2.second;
        
        if (mapProductAmount_1.find(pProduct_2) == mapProductAmount_1.end())
        {
            mapsumProductAmount[pProduct_2] = dAmount_2;
        }
    }

    return mapsumProductAmount;
}

std::map<pca::COption*, double> pca::CUtils::SumOptions(const std::map<pca::COption*, double>& mapOptionAmount_1, const std::map<pca::COption*, double> & mapOptionAmount_2)
{
    std::map<pca::COption*, double> mapsumOptionAmount;

    for (auto& pairOptionAmount : mapOptionAmount_1)
    {
        pca::COption* pOption = pairOptionAmount.first;
        double dAmount_1 = pairOptionAmount.second;
        if (mapOptionAmount_2.find(pOption) != mapOptionAmount_2.end())
        {
            double dAmount_2 = mapOptionAmount_2.at(pOption);
            mapsumOptionAmount[pOption] = dAmount_1 + dAmount_2;
        }
        else
        {
            mapsumOptionAmount[pOption] = dAmount_1;
        }
    }

    for (auto& pairOptionAmount_2 : mapOptionAmount_2)
    {
        pca::COption* pOption_2 = pairOptionAmount_2.first;
        double dAmount_2 = pairOptionAmount_2.second;

        if (mapOptionAmount_1.find(pOption_2) == mapOptionAmount_1.end())
        {
            mapsumOptionAmount[pOption_2] = dAmount_2;
        }
    }

    return mapsumOptionAmount;
}

std::map<pca::CProduct*, double> pca::CUtils::SubtractProducts(const std::map<pca::CProduct*, double>& mapProductAmount_1, const std::map<pca::CProduct*, double>& mapProductAmount_2)
{
    std::map<pca::CProduct*, double> mapsubtractProductAmount;

    for (auto& pairProductAmount : mapProductAmount_1)
    {
        pca::CProduct* pProduct = pairProductAmount.first;
        double dAmount_1 = pairProductAmount.second;
        if (mapProductAmount_2.find(pProduct) != mapProductAmount_2.end())
        {
            double dAmount_2 = mapProductAmount_2.at(pProduct);
            mapsubtractProductAmount[pProduct] = dAmount_1 - dAmount_2;
        }
        else
        {
            mapsubtractProductAmount[pProduct] = dAmount_1;
        }
    }

    for (auto& pairProductAmount_2 : mapProductAmount_2)
    {
        pca::CProduct* pProduct_2 = pairProductAmount_2.first;
        double dAmount_2 = pairProductAmount_2.second;

        if (mapProductAmount_1.find(pProduct_2) == mapProductAmount_1.end())
        {
            mapsubtractProductAmount[pProduct_2] = -dAmount_2;
        }
    }

    return mapsubtractProductAmount;
}

std::map<pca::COption*, double> pca::CUtils::SubtractOptions(const std::map<pca::COption*, double>& mapOptionAmount_1, const std::map<pca::COption*, double>& mapOptionAmount_2)
{
    std::map<pca::COption*, double> mapsubtractOptionAmount;

    for (auto& pairOptionAmount : mapOptionAmount_1)
    {
        pca::COption* pOption = pairOptionAmount.first;
        double dAmount_1 = pairOptionAmount.second;
        if (mapOptionAmount_2.find(pOption) != mapOptionAmount_2.end())
        {
            double dAmount_2 = mapOptionAmount_2.at(pOption);
            mapsubtractOptionAmount[pOption] = dAmount_1 - dAmount_2;
        }
        else
        {
            mapsubtractOptionAmount[pOption] = dAmount_1;
        }
    }

    for (auto& pairOptionAmount_2 : mapOptionAmount_2)
    {
        pca::COption* pOption_2 = pairOptionAmount_2.first;
        double dAmount_2 = pairOptionAmount_2.second;

        if (mapOptionAmount_1.find(pOption_2) == mapOptionAmount_1.end())
        {
            mapsubtractOptionAmount[pOption_2] = -dAmount_2;
        }
    }

    return mapsubtractOptionAmount;
}

void pca::CUtils::PrintPricesEvolution(CMarket* pMarket)
{
    pca::CPricesLogInfo* pPricesLogInfo = pMarket->GetPricesLogInfoRef();
    auto mapProduct_Prices = pPricesLogInfo->GetProductAllPrices();
    for (auto & pairProduct_Prices : mapProduct_Prices)
    {
        pca::CProduct* pProduct = pairProduct_Prices.first;
        std::cout << std::endl;
        std::cout << "Product: " << pProduct->GetName() << std::endl;
        std::vector<double> vPrices = pairProduct_Prices.second;
        for (auto& price : vPrices)
        {
            std::cout << " " << price;
        }
    }
}

