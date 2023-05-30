#ifndef CPERSON_H
#define CPERSON_H

#include <map>

namespace pca
{
    class CPerson
    {
    public:
        CPerson();
        virtual ~CPerson();

        void AddProductAmount(int nProductId, double dAmount);
        void RemoveProductAmount(int nProductId, double dAmount);

    protected:

    private:

        std::map<int, double> m_mapOwnedProd_Amount;

    };
}
#endif // CPERSON_H
