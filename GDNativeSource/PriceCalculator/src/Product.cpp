#include "Product.h"

long pca::CProduct::m_nCount = 0;
pca::CProduct::CProduct()
{
	m_nCount++;
	m_nID = m_nCount;
}

pca::CProduct::CProduct(std::string sName)
{
	m_nCount++;
	m_nID = m_nCount;
	m_sName = sName;
}

pca::CProduct::~CProduct()
{

}
