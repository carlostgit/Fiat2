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

pca::COption::COption(std::string sName, pca::CProduct* pProduct, bool bSaving)
{
	m_nCount++;
	m_nID = m_nCount;
	m_sName = sName;
	m_pProduct = pProduct;
	m_bSaving = bSaving;
}
