#include "Option.h"

long pca::COption::m_nCount = 0;
pca::COption::COption()
{
	m_nCount++;
	m_nID = m_nCount;
}

pca::COption::COption(std::string sName)
{
	m_nCount++;
	m_nID = m_nCount;
	m_sName = sName;
}

