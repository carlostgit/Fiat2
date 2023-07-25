#ifndef COPTION_H
#define COPTION_H

#include <string>

namespace pca
{

    class COption
    {
    public:
        COption();
        COption(std::string sName);
        virtual ~COption() {}

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
#endif // COPTION_H
