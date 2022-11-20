#include "Person.h"

CPerson::CPerson()
{
    //ctor
}

CPerson::~CPerson()
{
    //dtor
}

void CPerson::AddProductAmount(int nProductId, double dAmount)
{
    if(m_mapOwnedProd_Amount.end()==m_mapOwnedProd_Amount.find(nProductId))
    {
        m_mapOwnedProd_Amount[nProductId]=dAmount;
    }
    else
    {
        m_mapOwnedProd_Amount[nProductId] += dAmount;
    }
}

void CPerson::RemoveProductAmount(int nProductId, double dAmount)
{
    AddProductAmount(nProductId, -dAmount);
}
