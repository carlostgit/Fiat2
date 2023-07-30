#ifndef CCOMPLCOMBO_H
#define CCOMPLCOMBO_H

#include <string>
#include <set>



namespace pca
{
    class COption;

    class CComplCombo
    {
    public:
        CComplCombo();
        CComplCombo(std::string sName);
        virtual ~CComplCombo() {}

        long GetID() { return m_nID; }
        std::string GetName() { return m_sName; }
        void SetName(std::string sName) { m_sName = sName; }

        void AddOption(pca::COption* pOptionRef) {
            m_setOptions.insert(pOptionRef);
        }

        void AddOptions(std::initializer_list< pca::COption*> optionNameListInit);

    protected:

    private:
        static long m_nCount;
        long m_nID = 0;
        std::string m_sName = "";

        std::set<pca::COption*> m_setOptions;

    };
}

#endif // CCOMPLCOMBO_H
