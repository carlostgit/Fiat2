#include "ComplCombos.h"

#include "ComplCombo.h"
#include <string>

pca::CComplCombos::CComplCombos(std::initializer_list< std::string> complComboNameListInit)
{
	for (auto& name : complComboNameListInit)
	{
		std::unique_ptr<pca::CComplCombo> upComplCombo(new pca::CComplCombo(name));
		m_setComplCombos.insert(std::move(upComplCombo));
	}
}

void pca::CComplCombos::AddComplCombo(std::unique_ptr<pca::CComplCombo> upComplCombo)
{
	m_setComplCombos.insert(std::move(upComplCombo));
}
