#ifndef CSUPPLCOMBOS_H
#define CSUPPLCOMBOS_H

#include <memory>
#include <string>
#include <set>
#include <vector>

namespace pca
{
    class CSupplCombo;

    class CSupplCombos
    {
    public:
        CSupplCombos() {}
        CSupplCombos(std::initializer_list< std::string> supplComboNameListInit);
        virtual ~CSupplCombos();

        void AddSupplCombo(std::unique_ptr<pca::CSupplCombo> upSupplCombo);
        std::vector<pca::CSupplCombo*> GetSupplCombos();

        pca::CSupplCombo* GetSupplCombo(std::string sSupplCombo);

    protected:

    private:
        std::set<std::unique_ptr<pca::CSupplCombo>> m_setSupplCombos;
    };
}
#endif // CSUPPLCOMBOS_H
