#ifndef CPRODUCTS_H
#define CPRODUCTS_H

#include <memory>
#include <string>
#include <set>
#include <vector>


#include "Product.h"

namespace pca
{
    //class CProduct;

    class CProducts
    {
    public:
        CProducts() {}
        CProducts(std::initializer_list< std::string> productNameListInit);
        virtual ~CProducts();

        void AddProduct(std::unique_ptr<pca::CProduct> upProduct);
        std::vector<pca::CProduct*> GetProducts();

    protected:

    private:
        std::set<std::unique_ptr<pca::CProduct>> m_setProducts;
    };
}
#endif // CPRODUCTS_H
