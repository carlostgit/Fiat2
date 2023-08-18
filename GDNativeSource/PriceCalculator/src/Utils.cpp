#include "Utils.h"
#include <iostream>
#include <iomanip>
#include "Person.h"
#include "Option.h"
#include "Reality.h"

pca::CUtils::CUtils()
{
    //ctor

}

pca::CUtils::~CUtils()
{
    //dtor
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
    auto mapOpt_Amount = pPerson->GetCurrentOpt_Amount();
    std::cout << "Option amounts: " << std::endl;
    for (auto& pairOpt_Amount : mapOpt_Amount)
    {
        //std::cout << " '" << std::left << std::setw(10) << c_mapOption_Name.at(pairOpt_Amount.first).substr(0, 10) << "':'" << pairOpt_Amount.second << "'";
        COption* pOption = pairOpt_Amount.first;
        std::cout << " '" << std::left << std::setw(10) << pOption->GetName().substr(0, 10) << "':'" << pairOpt_Amount.second << "'";
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
            mapsumProductAmount.at(pProduct) = dAmount_1 + dAmount_2;
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
            mapsumOptionAmount.at(pOption) = dAmount_1 + dAmount_2;
        }
        else
        {
            mapsumOptionAmount.at(pOption) = dAmount_1;
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
            mapsubtractProductAmount.at(pProduct) = dAmount_1 - dAmount_2;
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
            mapsubtractOptionAmount.at(pOption) = dAmount_1 - dAmount_2;
        }
        else
        {
            mapsubtractOptionAmount.at(pOption) = dAmount_1;
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

