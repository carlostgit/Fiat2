#include "Options.h"
//#include "Option.h"
#include <string>

pca::COptions::COptions(std::initializer_list< std::string> optionNameListInit)
{
	for (auto & name:optionNameListInit)
	{
		std::unique_ptr<pca::COption> upOption(new pca::COption(name));
		m_setOptions.insert(std::move(upOption));	
	}
}

void pca::COptions::AddOption(std::unique_ptr<pca::COption> upOption)
{
	m_setOptions.insert(std::move(upOption));
}
