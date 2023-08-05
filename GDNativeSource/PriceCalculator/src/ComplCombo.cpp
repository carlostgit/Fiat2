#include "ComplCombo.h"

long pca::CComplCombo::m_nCount = 0;
pca::CComplCombo::CComplCombo()
{
	m_nCount++;
	m_nID = m_nCount;
}

pca::CComplCombo::CComplCombo(std::string sName)
{
	m_nCount++;
	m_nID = m_nCount;
	m_sName = sName;
}

pca::CComplCombo::CComplCombo(std::string sName, std::set< pca::COption*> setOptions)
{
	m_nCount++;
	m_nID = m_nCount;
	m_sName = sName;

	for (auto& option : setOptions)
	{
		m_setOptions.insert(option);
	}
}

void pca::CComplCombo::AddOptions(std::set< pca::COption*> setOptions)
{
	for (auto& option : setOptions)
	{
		m_setOptions.insert(option);
	}
}

