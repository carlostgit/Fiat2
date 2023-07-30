#include "SupplCombos.h"

#include "SupplCombo.h"
#include <string>

pca::CSupplCombos::CSupplCombos(std::initializer_list< std::string> supplComboNameListInit)
{
	for (auto& name : supplComboNameListInit)
	{
		std::unique_ptr<pca::CSupplCombo> upSupplCombo(new pca::CSupplCombo(name));
		m_setSupplCombos.insert(std::move(upSupplCombo));
	}
}

void pca::CSupplCombos::AddSupplCombo(std::unique_ptr<pca::CSupplCombo> upSupplCombo)
{
	m_setSupplCombos.insert(std::move(upSupplCombo));
}
