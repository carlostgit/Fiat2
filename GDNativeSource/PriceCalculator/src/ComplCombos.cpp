#include "ComplCombos.h"

#include "ComplCombo.h"


pca::CComplCombos::CComplCombos(std::map<std::string, std::set<COption*> >  mapOfComplCombos)
{
	for (auto& pairNameOptions : mapOfComplCombos)
	{
		std::unique_ptr<pca::CComplCombo> upComplCombo(new pca::CComplCombo(pairNameOptions.first, pairNameOptions.second));
		m_setComplCombos.insert(std::move(upComplCombo));
	}
}

void pca::CComplCombos::AddComplCombo(std::unique_ptr<pca::CComplCombo> upComplCombo)
{
	m_setComplCombos.insert(std::move(upComplCombo));
}
