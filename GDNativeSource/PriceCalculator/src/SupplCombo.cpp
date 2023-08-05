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


pca::CSupplCombo::CSupplCombo(std::string sName, std::map<pca::COption*, double> mapOptionWeight)
{
	m_nCount++;
	m_nID = m_nCount;
	m_sName = sName;

	for (auto& pairOptWeight : mapOptionWeight)
	{
		m_mapOption_Weight[pairOptWeight.first] = pairOptWeight.second;
	}

}

void pca::CSupplCombo::AddOptionsAndWeights(std::map<pca::COption*, double> mapOptionWeight)
{
	for (auto& pairOptWeight : mapOptionWeight)
	{
		m_mapOption_Weight[pairOptWeight.first] = pairOptWeight.second;
	}
}

