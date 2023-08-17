#include "SupplCombos.h"

#include "SupplCombo.h"
#include <string>
#include <vector>

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


std::vector<pca::CSupplCombo*> pca::CSupplCombos::GetSupplCombos()
{
	std::vector<pca::CSupplCombo*> vSupplCombos;
	for (auto& upSupplCombo : m_setSupplCombos)
	{
		vSupplCombos.push_back(upSupplCombo.get());
	}

	return vSupplCombos;
}

