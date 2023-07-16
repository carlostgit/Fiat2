#include "Utils.h"
#include <iostream>
#include <iomanip>
#include "Person.h"

pca::CUtils::CUtils()
{
    //ctor

}

pca::CUtils::~CUtils()
{
    //dtor
}

void pca::CUtils::PrintOptions(std::map<eOpt, double> mapOpt_Amount)
{
    std::cout << "Option amounts: " << std::endl;
    for (auto& pairOpt_Amount : mapOpt_Amount)
    {
        std::cout << " '" << std::left << std::setw(10) << c_mapOption_Name.at(pairOpt_Amount.first).substr(0, 10) << "':'" << pairOpt_Amount.second<<"'";
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
        std::cout << " '" << std::left << std::setw(10) << c_mapOption_Name.at(pairOpt_Amount.first).substr(0, 10) << "':'" << pairOpt_Amount.second << "'";
    }
    std::cout << std::endl;
}


