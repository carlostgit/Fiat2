#ifndef CSUPPLCOMBO_H
#define CSUPPLCOMBO_H

#include <string>
#include <map>

namespace pca
{
    class COption;

    class CSupplCombo
    {
    public:
        CSupplCombo();
        CSupplCombo(std::string sName);
        CSupplCombo(std::string sName, std::map<pca::COption*, double> mapOptionWeight);
        virtual ~CSupplCombo() {}

        long GetID() { return m_nID; }
        std::string GetName() { return m_sName; }
        void SetName(std::string sName) { m_sName = sName; }

        void AddOptionAndWeight(pca::COption* pOptionRef, double dWeight) {
            m_mapOption_Weight[pOptionRef] = dWeight;
        }

        void AddOptionsAndWeights(std::map<pca::COption*, double> mapOptionWeight);

    protected:

    private:
        static long m_nCount;
        long m_nID = 0;
        std::string m_sName = "";

        std::map<pca::COption*, double> m_mapOption_Weight;

    };
}

#endif // CSUPPLCOMBO_H
