#ifndef CCOMPLCOMBOS_H
#define CCOMPLCOMBOS_H


#include "ComplCombo.h"
#include <memory>
#include <string>
#include <set>
#include <map>
#include <vector>

namespace pca
{
    class COption;

    class CComplCombos
    {
        

    public:
        CComplCombos() {}
        CComplCombos(std::map<std::string,std::set<COption*> > mapOfComplCombos);
        virtual ~CComplCombos();

        void AddComplCombo(std::unique_ptr<pca::CComplCombo> upComplCombo);

        std::vector<pca::CComplCombo*> GetComplCombos();

        pca::CComplCombo* GetComplCombo(std::string sComplCombo);

    protected:

    private:
        std::set<std::unique_ptr<pca::CComplCombo>> m_setComplCombos;
    };
}
#endif // CCOMPLCOMBOS_H
