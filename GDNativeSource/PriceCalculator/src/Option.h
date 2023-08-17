#ifndef COPTION_H
#define COPTION_H

#include <string>

namespace pca
{
    class CProduct;

    class COption
    {
    public:
        COption();
        COption(std::string sName);
        COption(std::string sName, pca::CProduct* pProduct);
        virtual ~COption() {}

        long GetID() { return m_nID; }
        std::string GetName() { return m_sName; }
        void SetName(std::string sName) { m_sName = sName; }

        void SetProduct(CProduct* pProduct) {
            m_pProduct = pProduct;
        }

        CProduct* GetProduct() {
            return m_pProduct;
        }

    protected:
        
    private:
        static long m_nCount;
        long m_nID = 0;
        std::string m_sName = "";

        pca::CProduct* m_pProduct = nullptr;

    };
}
#endif // COPTION_H
