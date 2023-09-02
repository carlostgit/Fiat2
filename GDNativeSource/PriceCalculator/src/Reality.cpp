#include "Reality.h"

#include "Product.h"
#include "Option.h"
#include "ComplCombo.h"
#include "SupplCombo.h"

#include "Products.h"
#include "Options.h"
#include "ComplCombos.h"
#include "SupplCombos.h"

#include <assert.h>

std::unique_ptr<pca::CProducts> pca::CReality::m_upProducts = std::unique_ptr<CProducts>();
std::unique_ptr<pca::COptions> pca::CReality::m_upOptions = std::unique_ptr<pca::COptions>();
std::unique_ptr<pca::CComplCombos> pca::CReality::m_upComplCombos = std::unique_ptr<pca::CComplCombos>();
std::unique_ptr<pca::CSupplCombos> pca::CReality::m_upSupplCombos = std::unique_ptr<pca::CSupplCombos>();



void pca::CReality::Init()
{
    InitDefaultProductsAndOptions();
}

void pca::CReality::InitEmpty()
{
    std::unique_ptr<CProducts> upProducts(new CProducts());
    m_upProducts = std::move(upProducts);

    std::unique_ptr<COptions> upOptions(new COptions());
    m_upOptions = std::move(upOptions);

    std::unique_ptr<pca::CComplCombos> upComplCombos(new pca::CComplCombos());
    m_upComplCombos = move(upComplCombos);

    std::unique_ptr<pca::CSupplCombos> upSupplCombos(new pca::CSupplCombos());
    m_upSupplCombos = std::move(upSupplCombos);
    
}


void pca::CReality::Clear()
{
    m_upProducts.reset();
    m_upOptions.reset();
    m_upComplCombos.reset();
    m_upSupplCombos.reset();
}

void pca::CReality::InitDefaultProductsAndOptions()
{
    //Products
    std::unique_ptr<CProducts> upProducts(new CProducts({ "candy","chocolate","nut"}));
    m_upProducts = std::move(upProducts);

    //Options and products
    std::map<std::string, std::string> mapOptionName_ProductName{
        {"candy savings", "candy"},
        {"chocolate savings", "chocolate"},
        {"nut savings", "nut"},
        {"candy consumption", "candy"},
        {"chocolate consumption", "chocolate"},
        {"nut consumption", "nut"},
    };

    //Options
    std::unique_ptr<COptions> upOptions(new COptions());
    for (auto& pairOptionName_ProductName : mapOptionName_ProductName)
    {
        std::string sOptionName = pairOptionName_ProductName.first;
        std::string sProductName = pairOptionName_ProductName.second;

        CProduct* pProduct = m_upProducts.get()->GetProduct(sProductName);

        if (pProduct)
        {
            std::unique_ptr<COption> upOption(new COption(sOptionName, pProduct));
            upOptions.get()->AddOption(std::move(upOption));
        }
        else
        {
            assert("" == "error en CReality::InitDefaultProductsAndOptions, añadiendo Option");
        }
    }

    m_upOptions = std::move(upOptions);

    //ComplCombos
    std::map<std::string, std::set<std::string>> mapComplComboName_OptionNames({
        { "sweets" , { "candy", "chocolate"} }
        }
    );

    std::unique_ptr<pca::CComplCombos> upComplCombos(new pca::CComplCombos());
    m_upComplCombos = move(upComplCombos);
    for (auto& pairComplName_OptionNames : mapComplComboName_OptionNames)
    {
        std::string sComplComboName = pairComplName_OptionNames.first;
        std::unique_ptr<CComplCombo> upComplCombo(new CComplCombo(sComplComboName));
        std::set<std::string> setOptionNames;
        for (auto& optionName : setOptionNames)
        {
            COption* pOptionRef = m_upOptions->GetOption(optionName);
            upComplCombo->AddOption(pOptionRef);
        }
        
        m_upComplCombos->AddComplCombo(std::move(upComplCombo));
    }

    //SupplCombos
    const std::map<std::string, std::map<std::string, double> > mapSupplementaryComboName_mapOptionName_dWeight = {
        {"consumption", {{"candy consumption", 1.0},
                         {"chocolate consumption", 1.0},
                         {"nut consumption", 1.0}}
        },
        {"savings", {{"candy savings", 1.0},
                     {"chocolate savings", 1.0},
                     {"nut savings", 1.0}}
        }        
    };

    std::unique_ptr<pca::CSupplCombos> upSupplCombos(new pca::CSupplCombos());
    m_upSupplCombos = std::move(upSupplCombos);
    for (auto& pairSupplName_mapOptionName_dWeight : mapSupplementaryComboName_mapOptionName_dWeight)
    {
        std::string sSupplComboName = pairSupplName_mapOptionName_dWeight.first;
        std::unique_ptr<CSupplCombo> upSupplCombo(new CSupplCombo(sSupplComboName));
        std::map<std::string, double> mapOptionName_dWeight;
        for (auto& pairOptionName_dWeight: mapOptionName_dWeight)
        {
            std::string optionName = pairOptionName_dWeight.first;
            double dWeight = pairOptionName_dWeight.second;
            COption* pOptionRef = m_upOptions->GetOption(optionName);
            upSupplCombo->AddOptionAndWeight(pOptionRef, dWeight);
        }

        m_upSupplCombos->AddSupplCombo(std::move(upSupplCombo));
    }
}

void pca::CReality::CreateProduct(std::string sProduct)
{
    std::unique_ptr<CProduct> upProduct(new CProduct(sProduct));
    m_upProducts->AddProduct(std::move(upProduct));
}

void pca::CReality::CreateOption(std::string sProduct, std::string sOption)
{
    CProduct* pProduct = m_upProducts->GetProduct(sProduct);

    if (pProduct)
    {
        std::unique_ptr<COption> upOption(new COption(sOption, pProduct));
        m_upOptions->AddOption(std::move(upOption));
    }
}



void pca::CReality::CreateComplCombo(std::string sComplCombo)
{
    std::unique_ptr<CComplCombo> upComplCombo(new CComplCombo(sComplCombo));
    upComplCombo->SetName(sComplCombo);

    m_upComplCombos->AddComplCombo(std::move(upComplCombo));
}

void pca::CReality::AddOptionToComplCombo(std::string sComplCombo, std::string sOption)
{
    COption* pOption = m_upOptions->GetOption(sOption);

    CComplCombo* pComplCombo = m_upComplCombos->GetComplCombo(sComplCombo);

    if (pComplCombo && pOption)
    {
        pComplCombo->AddOption(pOption);
    }
}

void pca::CReality::CreateSupplCombo(std::string sSupplCombo)
{
    std::unique_ptr<CSupplCombo> upSupplCombo(new CSupplCombo(sSupplCombo));
    upSupplCombo->SetName(sSupplCombo);

    m_upSupplCombos->AddSupplCombo(std::move(upSupplCombo));
}

void pca::CReality::AddOptionToSupplCombo(std::string sSupplCombo, std::string sOption, double dWeight)
{
    COption* pOption = m_upOptions->GetOption(sOption);

    CSupplCombo* pSupplCombo = m_upSupplCombos->GetSupplCombo(sSupplCombo);

    if (pSupplCombo && pOption)
    {
        pSupplCombo->AddOptionAndWeight(pOption, dWeight);
    }
}


std::vector<pca::CProduct*> pca::CReality::GetProducts()
{
    return m_upProducts->GetProducts();
}

std::vector<pca::COption*> pca::CReality::GetOptions()
{
    return m_upOptions->GetOptions();
}

std::vector<pca::CComplCombo*> pca::CReality::GetComplCombos()
{
    return m_upComplCombos->GetComplCombos();
}

std::vector<pca::CSupplCombo*> pca::CReality::GetSupplCombos()
{
    return m_upSupplCombos->GetSupplCombos();
}


//pca::CReality::~CReality() 
//{
//
//}
    ////TODO. Cambiar esto por enumeradores. O crear clases (Clase CProduct etc...)

    //enum eProd {
    //    eProdCandy = 1,
    //    eProdChocolate = 2,
    //    eProdNut = 3,
    //};
    ////const int c_nProdCandy = 1;
    ////const int c_nProdChocolate = 2;
    ////const int c_nProdNut = 3;

    //enum eOptTyp {
    //    eOptTypSavings = 4,
    //    eOptTypConsumption = 5
    //};

    ////const int eOptTypSavings = 4;
    ////const int eOptTypConsumption = 5;
    //
    //enum eOpt {
    //    eOptCandySavings = 6,
    //    eOptChocolateSavings = 7,
    //    eOptNutSavings = 8,
    //    eOptCandyConsumption = 9,
    //    eOptChocolateConsumption = 10,
    //    eOptNutConsumption = 11
    //};

    ////const int eOptCandySavings = 6;
    ////const int eOptChocolateSavings = 7;
    ////const int eOptNutSavings = 8;
    ////const int eOptCandyConsumption = 9;
    ////const int eOptChocolateConsumption = 10;
    ////const int eOptNutConsumption = 11;
    //
    //enum eCompComb {
    //    eCompCombSweets = 12
    //};

    ////const int c_nCompCombSweets = 12;

    //enum eSuppComb {
    //    c_nSuppCombConsumption = 13,
    //    c_nSuppCombSavings = 14
    //};

    ////const int c_nSuppCombConsumption = 13;
    ////const int c_nSuppCombSavings = 14;


    //const std::set<pca::eProd> c_setProducts = {
    //eProdCandy,
    //eProdChocolate,
    //eProdNut
    //};

    //const std::map<pca::eProd, std::set<pca::eOpt> > c_mapProduct_setOptions = {
    //{eProdCandy,{eOptCandySavings,eOptCandyConsumption}},
    //{eProdChocolate,{eOptChocolateSavings,eOptChocolateConsumption}},
    //{eProdNut,{eOptNutSavings,eOptNutConsumption}},
    //};

    ////Esto debería sacarse a partir de lo anterior
    //const std::map<pca::eOpt, pca::eProd > c_mapOption_Product = {

    //{eOptCandySavings,eProdCandy},
    //{eOptChocolateSavings,eProdChocolate},
    //{eOptNutSavings,eProdNut},
    //{eOptCandyConsumption,eProdCandy},
    //{eOptChocolateConsumption,eProdChocolate},
    //{eOptNutConsumption,eProdNut }

    //};

    //const std::set<pca::eOpt> c_setOptions = {
    //eOptCandySavings,
    //eOptChocolateSavings,
    //eOptNutSavings,
    //eOptCandyConsumption,
    //eOptChocolateConsumption,
    //eOptNutConsumption
    //};

    //const std::set<pca::eOpt> c_setGroupSavings = {
    //eOptCandySavings,
    //eOptChocolateSavings,
    //eOptNutSavings
    //};

    //const std::set<pca::eOpt> c_setGroupConsumption = {
    //eOptCandyConsumption,
    //eOptChocolateConsumption,
    //eOptNutConsumption
    //};

    //const std::set<pca::eOpt> c_setGroupSweets = {
    //eOptCandyConsumption,
    //eOptChocolateConsumption,
    //};

    //const std::map<pca::eCompComb, std::set<pca::eOpt> > c_mapComplementaryCombo_setOptions = {
    //    {eCompCombSweets, c_setGroupSweets}
    //};

    //const std::map<pca::eSuppComb, std::set<pca::eOpt> > c_mapSupplementaryCombo_setOptions = {
    //    {c_nSuppCombConsumption, c_setGroupConsumption},
    //    {c_nSuppCombSavings, c_setGroupSavings}
    //};

    //const std::map<pca::eProd, std::string> c_mapProd_Name = {
    //    {eProdCandy,"candy"},
    //    {eProdChocolate,"chocolate"},
    //    {eProdNut,"nut"}
    //};

    //const std::map<pca::eOpt,std::string> c_mapOption_Name = {
    //    {eOptCandySavings,"candy savings"},
    //    {eOptChocolateSavings,"chocolate savings"},
    //    {eOptNutSavings,"nut savings"},
    //    {eOptCandyConsumption,"candy consumption"},
    //    {eOptChocolateConsumption,"chocolate consumption"},
    //    {eOptNutConsumption,"nut consumption"}
    //};

    //const std::map<pca::eCompComb, std::string > c_mapComplementaryCombo_Name = {
    //    {eCompCombSweets, "sweets"}
    //};

    //const std::map<pca::eSuppComb, std::string > c_mapSupplementaryCombo_Name = {
    //    {c_nSuppCombConsumption, "consumption"},
    //    {c_nSuppCombSavings, "savings"}
    //};

    ////std::set<eOpt> setOptions = pairCombo_setOptions.second;
    ////std::map<eOpt, double> mapOption_dWeight;
    ////for (auto& nOption : setOptions)
    ////{
    ////    mapOption_dWeight[nOption] = 1.0; //Por defecto, el peso es 1 para todas las opciones
    ////}
    ////m_mapSupplementaryCombo_mapOption_dWeight[nCombo] = mapOption_dWeight;

    //const std::map<eSuppComb, std::map<eOpt, double> > c_mapSupplementaryCombo_mapOption_dWeight = {
    //    {c_nSuppCombConsumption, {{eOptCandyConsumption, 1.0},
    //                             {eOptChocolateConsumption, 1.0},
    //                             {eOptNutConsumption, 1.0}}
    //    },
    //    {c_nSuppCombSavings, {{eOptCandySavings, 1.0},
    //                             {eOptChocolateSavings, 1.0},
    //                             {eOptNutSavings, 1.0}}
    //    }        
    //};
