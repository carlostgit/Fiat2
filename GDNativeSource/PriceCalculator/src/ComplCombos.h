#ifndef CCOMPLCOMBOS_H
#define CCOMPLCOMBOS_H


#include "ComplCombo.h"
#include <memory>
#include <string>
#include <set>
#include <map>

namespace pca
{
    //class CComplCombo;
    class COption;

    class CComplCombos
    {
        

    public:
        CComplCombos() {}
        CComplCombos(std::map<std::string,std::set<COption*> > mapOfComplCombos);
        virtual ~CComplCombos() {}

        void AddComplCombo(std::unique_ptr<pca::CComplCombo> upComplCombo);

    protected:

    private:
        std::set<std::unique_ptr<pca::CComplCombo>> m_setComplCombos;
    };
}
#endif // CCOMPLCOMBOS_H
