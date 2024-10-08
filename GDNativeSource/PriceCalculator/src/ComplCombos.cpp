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

pca::CComplCombos::~CComplCombos()
{

}

void pca::CComplCombos::AddComplCombo(std::unique_ptr<pca::CComplCombo> upComplCombo)
{
	m_setComplCombos.insert(std::move(upComplCombo));
}

std::vector<pca::CComplCombo*> pca::CComplCombos::GetComplCombos()
{
	std::vector<pca::CComplCombo*> vComplCombos;
	for (auto& upComplCombo : m_setComplCombos)
	{
		vComplCombos.push_back(upComplCombo.get());
	}

	return vComplCombos;
}

pca::CComplCombo* pca::CComplCombos::GetComplCombo(std::string sComplCombo)
{
	for (auto& upComplCombo : m_setComplCombos)
	{		
		if (sComplCombo == upComplCombo->GetName())
			return upComplCombo.get();
	}

	return nullptr;
}
