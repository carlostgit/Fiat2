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

