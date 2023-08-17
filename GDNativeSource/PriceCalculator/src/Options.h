#ifndef COPTIONS_H
#define COPTIONS_H

#include <set>
#include <memory>
#include <string>
#include <vector>


#include "Option.h"
#include "Product.h"

namespace pca
{
    //class COption;
    //class CProduct;

    class COptions
    {
    public:
        COptions() {}
        COptions(std::initializer_list< std::string> optionNameListInit);
        COptions(std::initializer_list< std::pair<std::string,CProduct*> > optionNameListInit);
        virtual ~COptions();

        void AddOption(std::unique_ptr<pca::COption> upOption);
        std::vector<pca::COption*> GetOptions();

        pca::COption* GetOption(std::string sOptionName);
        
    protected:

    private:
        std::set<std::unique_ptr<pca::COption>> m_setOptions;
    };
}
#endif // COPTIONS_H
