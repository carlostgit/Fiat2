#ifndef CSUPPLCOMBOS_H
#define CSUPPLCOMBOS_H

#include <memory>
#include <string>
#include <set>

namespace pca
{
    class CSupplCombo;

    class CSupplCombos
    {
    public:
        CSupplCombos() {}
        CSupplCombos(std::initializer_list< std::string> supplComboNameListInit);
        virtual ~CSupplCombos() {}

        void AddSupplCombo(std::unique_ptr<pca::CSupplCombo> upSupplCombo);

    protected:

    private:
        std::set<std::unique_ptr<pca::CSupplCombo>> m_setSupplCombos;
    };
}
#endif // CSUPPLCOMBOS_H
