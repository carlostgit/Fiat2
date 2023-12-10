#include "Reality.h"

#include "Product.h"
#include "Option.h"
#include "ComplCombo.h"
#include "SupplCombo.h"

#include "Products.h"
#include "Options.h"
#include "ComplCombos.h"
#include "SupplCombos.h"

#include "Market.h"

#include <assert.h>
//
//std::unique_ptr<pca::CProducts> pca::CReality::m_upProducts =       std::unique_ptr<CProducts>();
//std::unique_ptr<pca::COptions> pca::CReality::m_upOptions =         std::unique_ptr<pca::COptions>();
//std::unique_ptr<pca::CComplCombos> pca::CReality::m_upComplCombos = std::unique_ptr<pca::CComplCombos>();
//std::unique_ptr<pca::CSupplCombos> pca::CReality::m_upSupplCombos = std::unique_ptr<pca::CSupplCombos>();


pca::CReality::CReality(bool bCreateDefaultProductsAndOptions)
{
    if (bCreateDefaultProductsAndOptions)
        Init();
    else
        InitEmpty();
}

pca::CReality::~CReality()
{

}

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
    if (false == m_vupMerketRefs.empty())
    {
        assert("" == "This Reality is already being used!!");
        return;
    }
        

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
    if (false == m_vupMerketRefs.empty())
    {
        assert("" == "This Reality is already being used!!");
        return;
    }

    std::unique_ptr<CProduct> upProduct(new CProduct(sProduct));
    m_upProducts->AddProduct(std::move(upProduct));
}

void pca::CReality::CreateOption(std::string sProduct, std::string sOption)
{
    if (false == m_vupMerketRefs.empty())
    {
        assert("" == "This Reality is already being used!!");
        return;
    }

    CProduct* pProduct = m_upProducts->GetProduct(sProduct);

    if (pProduct)
    {
        std::unique_ptr<COption> upOption(new COption(sOption, pProduct));
        m_upOptions->AddOption(std::move(upOption));
    }
}

void pca::CReality::CreateOption(CProduct* pProduct, std::string sOption)
{
    if (false == m_vupMerketRefs.empty())
    {
        assert("" == "This Reality is already being used!!");
        return;
    }

    if (pProduct)
    {
        std::unique_ptr<COption> upOption(new COption(sOption, pProduct));
        m_upOptions->AddOption(std::move(upOption));
    }
}



void pca::CReality::CreateComplCombo(std::string sComplCombo)
{
    if (false == m_vupMerketRefs.empty())
    {
        assert("" == "This Reality is already being used!!");
        return;
    }

    std::unique_ptr<CComplCombo> upComplCombo(new CComplCombo(sComplCombo));
    upComplCombo->SetName(sComplCombo);

    m_upComplCombos->AddComplCombo(std::move(upComplCombo));
}

void pca::CReality::AddOptionToComplCombo(std::string sComplCombo, std::string sOption)
{
    if (false == m_vupMerketRefs.empty())
    {
        assert("" == "This Reality is already being used!!");
        return;
    }

    COption* pOption = m_upOptions->GetOption(sOption);

    CComplCombo* pComplCombo = m_upComplCombos->GetComplCombo(sComplCombo);

    if (pComplCombo && pOption)
    {
        pComplCombo->AddOption(pOption);
    }
}

void pca::CReality::AddOptionToComplCombo(CComplCombo* pComplCombo, COption* pOption)
{
    if (false == m_vupMerketRefs.empty())
    {
        assert("" == "This Reality is already being used!!");
        return;
    }

    if (pComplCombo && pOption)
    {
        pComplCombo->AddOption(pOption);
    }
}

void pca::CReality::CreateSupplCombo(std::string sSupplCombo)
{
    if (false == m_vupMerketRefs.empty())
    {
        assert("" == "This Reality is already being used!!");
        return;
    }

    std::unique_ptr<CSupplCombo> upSupplCombo(new CSupplCombo(sSupplCombo));
    upSupplCombo->SetName(sSupplCombo);

    m_upSupplCombos->AddSupplCombo(std::move(upSupplCombo));
}

void pca::CReality::AddOptionToSupplCombo(std::string sSupplCombo, std::string sOption, double dWeight)
{
    if (false == m_vupMerketRefs.empty())
    {
        assert("" == "This Reality is already being used!!");
        return;
    }

    COption* pOption = m_upOptions->GetOption(sOption);

    CSupplCombo* pSupplCombo = m_upSupplCombos->GetSupplCombo(sSupplCombo);

    if (pSupplCombo && pOption)
    {
        pSupplCombo->AddOptionAndWeight(pOption, dWeight);
    }
}

void pca::CReality::AddOptionToSupplCombo(CSupplCombo* pSupplCombo, COption* pOption, double dWeight)
{
    if (false == m_vupMerketRefs.empty())
    {
        assert("" == "This Reality is already being used!!");
        return;
    }

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

pca::CProduct* pca::CReality::GetProduct(std::string sProduct)
{
    return m_upProducts->GetProduct(sProduct);
}

pca::COption* pca::CReality::GetOption(std::string sOption)
{
    return m_upOptions->GetOption(sOption);
}

pca::CComplCombo* pca::CReality::GetComplCombo(std::string sComplCombo)
{
    return m_upComplCombos->GetComplCombo(sComplCombo);
}

pca::CSupplCombo* pca::CReality::GetSupplCombo(std::string sSupplCombo)
{
    return m_upSupplCombos->GetSupplCombo(sSupplCombo);
}

void pca::CReality::AddMarket(std::unique_ptr<pca::CMarket> &upMarket)
{
    this->m_vupMerketRefs.push_back(std::move(upMarket));
}

pca::CMarket* pca::CReality::GetLastMarketRef()
{
    if (this->m_vupMerketRefs.empty())
        return nullptr;
    else
    {
        return this->m_vupMerketRefs.back().get();
    }
}
