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

void pca::CComplCombo::AddOptions(std::initializer_list< pca::COption*> optionNameListInit)
{
	for (auto& option : optionNameListInit)
	{
		m_setOptions.insert(option);
	}
}

