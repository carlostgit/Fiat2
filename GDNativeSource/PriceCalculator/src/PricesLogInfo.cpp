#include "PricesLogInfo.h"
#include "Reality.h"
#include "ProductPriceAdjustmentInfo.h"
#include "Prices.h"
#include "Market.h"

#include "Product.h"


pca::CPricesLogInfo::CPricesLogInfo(pca::CMarket* pMarketRef):m_pMarketRef(pMarketRef)
{
	m_pPricesRef = pMarketRef->GetPricesRef();

	//std::cout << "Initializing CPricesLogInfo with CReality::GetProducts" << std::endl;
	//std::cout << "ATENCION! CREO QUE ESTO ES UN BUG. Cada vez que se cambian los Products en CReality habría que actualizar esto" << std::endl;	

	SynchronizeProducts();
}

void pca::CPricesLogInfo::SynchronizeProducts()
{
	auto vProducts = m_pMarketRef->GetProducts();
	for (auto& pProduct : vProducts)
	{
		if (m_mapProduct_AdjustmentInfo.find(pProduct) == m_mapProduct_AdjustmentInfo.end())
		{
			std::unique_ptr<CProductPriceAdjustmentInfo> upProductPriceAdjustmentInfo(new CProductPriceAdjustmentInfo());
			m_mapProduct_AdjustmentInfo[pProduct] = std::move(upProductPriceAdjustmentInfo);
		}
	}

	if (m_mapProduct_AdjustmentInfo.size() > vProducts.size())
	{
		for (auto it = m_mapProduct_AdjustmentInfo.begin(); it != m_mapProduct_AdjustmentInfo.end(); )
		{
			bool bFound = false;
			for (auto& pProduct : vProducts)
			{
				if (it->first == pProduct)
				{
					bFound = true;
					break;
				}
			}
			if (!bFound)
			{
				it = m_mapProduct_AdjustmentInfo.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

pca::CPricesLogInfo::~CPricesLogInfo()
{

}


void pca::CPricesLogInfo::AddPriceChangeStepToVector(double dValueArg)
{
	m_vPriceChangeStepsVector.push_back(dValueArg);
}

void pca::CPricesLogInfo::ResetLastPrices()
{
	SynchronizeProducts();
	for (auto& pProduct : m_pMarketRef->GetProducts())
	{
		CProductPriceAdjustmentInfo* pProductPriceAdjustmentInfo = m_mapProduct_AdjustmentInfo.at(pProduct).get();
		pProductPriceAdjustmentInfo->ResetLastPrices();
	}
}


void pca::CPricesLogInfo::RegisterPrices()
{
	SynchronizeProducts();
	for (auto& pProduct : m_pMarketRef->GetProducts())
	{
		//std::cout << "Adjusting product: " << pProduct->GetName() << std::endl;
		//std::cout << "m_mapProduct_AdjustmentInfo: " << std::endl;
		//for (auto& pairProd_adjustInfo : m_mapProduct_AdjustmentInfo)
		//{
		//	auto pProd = pairProd_adjustInfo.first;
		//	std::cout << "Adjusting product: " << pProd->GetName() << std::endl;
		//	auto pAdjustInfo = pairProd_adjustInfo.second.get();
		//	std::cout << "Adjusting info: " << pAdjustInfo << std::endl;

		//}
		CProductPriceAdjustmentInfo* pProductPriceAdjustmentInfo = m_mapProduct_AdjustmentInfo.at(pProduct).get();

		double dPrice = m_pPricesRef->GetPriceOfProduct(pProduct);
		pProductPriceAdjustmentInfo->AddPriceIteration(dPrice);
	}
}

bool pca::CPricesLogInfo::ArePricesEvolving()
{
	SynchronizeProducts();
	bool bPricesEvolving = false;

	for (auto& pProduct : m_pMarketRef->GetProducts())
	{
		CProductPriceAdjustmentInfo* pProductPriceAdjustmentInfo = m_mapProduct_AdjustmentInfo.at(pProduct).get();
		if (pProductPriceAdjustmentInfo->GetPrices().size() > 1 and
			false == pProductPriceAdjustmentInfo->ArePricesChanging())
		{
			continue;
		}
		else
		{
			if (pProductPriceAdjustmentInfo->GetNumPriceTops() < 1)
			{
				bPricesEvolving = true;
				break;
			}
			if (pProductPriceAdjustmentInfo->GetNumPriceBottoms() < 1)
			{
				bPricesEvolving = true;
				break;
			}
		}
	}	

	return bPricesEvolving;

}

std::map<pca::CProduct*, std::vector<double> > pca::CPricesLogInfo::GetProductPrices()
{
	SynchronizeProducts();
	std::map<pca::CProduct*, std::vector<double> > mapProduct_vPrices;
	for (auto& pProduct : m_pMarketRef->GetProducts())
	{
		CProductPriceAdjustmentInfo* pProductPriceAdjustmentInfo = m_mapProduct_AdjustmentInfo.at(pProduct).get();
		std::vector<double> vPrices = pProductPriceAdjustmentInfo->GetPrices();
		mapProduct_vPrices[pProduct] = vPrices;
	}
	return mapProduct_vPrices;
}

std::map<pca::CProduct*, std::vector<double> > pca::CPricesLogInfo::GetProductAllPrices()
{
	SynchronizeProducts();
	std::map<pca::CProduct*, std::vector<double> > mapProduct_vPrices;
	for (auto& pProduct : m_pMarketRef->GetProducts())
	{
		CProductPriceAdjustmentInfo* pProductPriceAdjustmentInfo = m_mapProduct_AdjustmentInfo.at(pProduct).get();
		std::vector<double> vPrices = pProductPriceAdjustmentInfo->GetAllPrices();
		mapProduct_vPrices[pProduct] = vPrices;
	}
	return mapProduct_vPrices;
}


std::vector<double> pca::CPricesLogInfo::GetAllPriceChangeStepsVector()
{
	return m_vPriceChangeStepsVector;
}

std::map<pca::CProduct*, std::vector<long> > pca::CPricesLogInfo::GetProductPriceTops()
{
	SynchronizeProducts();
	std::map<pca::CProduct*, std::vector<long> > mapProduct_vPrices;
	for (auto& pProduct : m_pMarketRef->GetProducts())
	{
		CProductPriceAdjustmentInfo* pProductPriceAdjustmentInfo = m_mapProduct_AdjustmentInfo.at(pProduct).get();
		std::vector<long> vPrices = pProductPriceAdjustmentInfo->GetNumPriceTopsArray();
		mapProduct_vPrices[pProduct] = vPrices;
	}
	return mapProduct_vPrices;
}

std::map<pca::CProduct*, std::vector<long> > pca::CPricesLogInfo::GetProductPriceBottoms()
{
	SynchronizeProducts();
	std::map<pca::CProduct*, std::vector<long> > mapProduct_vPrices;
	for (auto& pProduct : m_pMarketRef->GetProducts())
	{
		CProductPriceAdjustmentInfo* pProductPriceAdjustmentInfo = m_mapProduct_AdjustmentInfo.at(pProduct).get();
		std::vector<long> vPrices = pProductPriceAdjustmentInfo->GetNumPriceBottomsArray();
		mapProduct_vPrices[pProduct] = vPrices;
	}

	return mapProduct_vPrices;
}

