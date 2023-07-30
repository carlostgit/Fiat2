#include "SupplCombo.h"

long pca::CSupplCombo::m_nCount = 0;
pca::CSupplCombo::CSupplCombo()
{
	m_nCount++;
	m_nID = m_nCount;
}

pca::CSupplCombo::CSupplCombo(std::string sName)
{
	m_nCount++;
	m_nID = m_nCount;
	m_sName = sName;
}

void pca::CSupplCombo::AddOptionsAndWeights(std::initializer_list< std::pair<pca::COption*, double>> optionWeightNameListInit)
{
	for (auto& pairOptWeight : optionWeightNameListInit)
	{
		m_mapOption_Weight[pairOptWeight.first] = pairOptWeight.second;
	}
}
