#include "Products.h"

//#include "Product.h"
#include <string>

#include <iostream>

pca::CProducts::CProducts()
{
	std::cout << "CProducts constructor" << std::endl;
}

pca::CProducts::~CProducts()
{
	std::cout << "CProducts destructor" << std::endl;
}

pca::CProducts::CProducts(std::initializer_list< std::string> productNameListInit)
{
	std::cout << "CProducts constructor with initializer_list" << std::endl;
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

pca::CProduct* pca::CProducts::GetProduct(std::string sName)
{
	for (auto& upProduct : m_setProducts)
	{
		if (upProduct.get()->GetName() == sName)
		{
			return upProduct.get();
		}
	}
	return nullptr;
}

