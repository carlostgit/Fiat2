#ifndef CCOMPLCOMBOS_H
#define CCOMPLCOMBOS_H

#include <memory>
#include <string>
#include <set>

#include "ComplCombo.h"

namespace pca
{
    //class CComplCombo;

    class CComplCombos
    {
    public:
        CComplCombos() {}
        CComplCombos(std::initializer_list< std::string> complComboNameListInit);
        virtual ~CComplCombos() {}

        void AddComplCombo(std::unique_ptr<pca::CComplCombo> upComplCombo);

    protected:

    private:
        std::set<std::unique_ptr<pca::CComplCombo>> m_setComplCombos;
    };
}
#endif // CCOMPLCOMBOS_H
