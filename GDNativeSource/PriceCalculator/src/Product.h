#ifndef CPRODUCT_H
#define CPRODUCT_H

#include <string>

namespace pca
{

    class CProduct
    {
    public:
        CProduct();
        CProduct(std::string sName);
        virtual ~CProduct();

        long GetID() { return m_nID; }
        std::string GetName() { return m_sName; }
        void SetName(std::string sName) { m_sName = sName; }

    protected:

    private:
        static long m_nCount;
        long m_nID = 0;
        std::string m_sName = "";

    };
}

#endif // CPRODUCT_H
