#ifndef CREALITY_H
#define CREALITY_H

#include <memory>
#include <vector>
#include <string>

namespace pca
{
    class CProducts;
    class COptions;
    class CComplCombos;
    class CSupplCombos;

    class CProduct;
    class COption;
    class CComplCombo;
    class CSupplCombo;
    class CMarket;

    class CReality
    {
    public:

        //CReality() = delete;
        //virtual ~CReality() {}
        CReality(bool bCreateDefaultProductsAndOptions = true);
        virtual ~CReality();

        void Init();
        void InitEmpty();
        void Clear();

        void InitDefaultProductsAndOptions();

        std::vector<pca::CProduct*> GetProducts();
        std::vector<pca::COption*> GetOptions();

        std::vector<pca::CComplCombo*> GetComplCombos();
        std::vector<pca::CSupplCombo*> GetSupplCombos();

        
        void CreateProduct(std::string sProduct);        
        void CreateOption(std::string sProduct, std::string sOption);
        void CreateOption(CProduct* pProduct, std::string sOption);

        void CreateComplCombo(std::string sComplCombo);        
        void AddOptionToComplCombo(std::string sComplCombo, std::string sOption);
        void AddOptionToComplCombo(CComplCombo* pComplCombo, COption* pOption);

        void CreateSupplCombo(std::string sSupplCombo);
        void AddOptionToSupplCombo(std::string sSupplCombo, std::string sOption, double dWeight);
        void AddOptionToSupplCombo(CSupplCombo* pSupplCombo, COption* pOption, double dWeight);

        //
        CProduct* GetProduct(std::string sProduct);
        COption* GetOption(std::string sOption);
        CComplCombo* GetComplCombo(std::string sComplCombo);
        CSupplCombo* GetSupplCombo(std::string sSupplCombo);

        void AddMarket(std::unique_ptr<pca::CMarket> &upMarket);
        pca::CMarket* GetLastMarketRef();

    protected:

        std::unique_ptr<CProducts> m_upProducts         = std::unique_ptr<CProducts>();
        std::unique_ptr<COptions> m_upOptions           = std::unique_ptr<pca::COptions>();
        std::unique_ptr<CComplCombos> m_upComplCombos   = std::unique_ptr<pca::CComplCombos>();
        std::unique_ptr<CSupplCombos> m_upSupplCombos   = std::unique_ptr<pca::CSupplCombos>();

        std::vector< std::unique_ptr<pca::CMarket> > m_vupMerketRefs;

    };    
}

#endif //CREALITY_H

