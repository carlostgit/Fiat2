#include "Products.h"

//#include "Product.h"
#include <string>

pca::CProducts::~CProducts()
{

}

pca::CProducts::CProducts(std::initializer_list< std::string> productNameListInit)
{
	for (auto& name : productNameListInit)
	{
		std::unique_ptr<pca::CProduct> upProduct(new pca::CProduct(name));
		m_setProducts.insert(std::move(upProduct));
	}
}

void pca::CProducts::AddProduct(std::unique_ptr<pca::CProduct> upProduct)
{
	m_setProducts.insert(std::move(upProduct));
}

std::vector<pca::CProduct*> pca::CProducts::GetProducts()
{
	std::vector<pca::CProduct*> vProducts;
	for (auto & upProduct : m_setProducts)
	{
		vProducts.push_back(upProduct.get());
	}

	return vProducts;
}
