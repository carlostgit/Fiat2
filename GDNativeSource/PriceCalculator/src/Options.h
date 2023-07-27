#ifndef COPTIONS_H
#define COPTIONS_H

#include <set>
#include <memory>
#include <string>

namespace pca
{
    class COption;

    class COptions
    {
    public:
        COptions() {}
        COptions(std::initializer_list< std::string> optionNameListInit);
        virtual ~COptions() {}

        void AddOption(std::unique_ptr<pca::COption> upOption);
        
    protected:

    private:
        std::set<std::unique_ptr<pca::COption>> m_setOptions;
    };
}
#endif // COPTIONS_H