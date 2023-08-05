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

pca::COption* pca::COptions::GetOption(std::string sOptionName)
{
	for (auto& option : m_setOptions)
	{
		if (sOptionName == option->GetName())
			return option.get();
	}

	return nullptr;
}

std::vector<pca::COption*> pca::COptions::GetOptions()
{
	std::vector<pca::COption*> vOptions;
	for (auto& upOption : m_setOptions)
	{
		vOptions.push_back(upOption.get());
	}

	return vOptions;
}
