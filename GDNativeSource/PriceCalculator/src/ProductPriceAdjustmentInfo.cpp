#include "ProductPriceAdjustmentInfo.h"


pca::CProductPriceAdjustmentInfo::CProductPriceAdjustmentInfo()
{

}

pca::CProductPriceAdjustmentInfo::~CProductPriceAdjustmentInfo()
{

}

void pca::CProductPriceAdjustmentInfo::Reset()
{
    //m_nParamIterationsLog = 10;
    m_nIteration = 0;
    m_dMinPrice = std::numeric_limits<double>::max();
    m_dMaxPrice = 0.0;

    m_vLastPrices.clear();
    m_vAllPrices.clear();
    m_vNumLastPriceTops.clear();
    m_vNumLastPriceBottoms.clear();
}

bool pca::CProductPriceAdjustmentInfo::ArePricesChanging()
{
    if (m_vAllPrices.size() > 1)
    {
        if (0 == m_vAllPrices[m_vAllPrices.size() - 1] - m_vAllPrices[m_vAllPrices.size() - 2])
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

std::vector<double> pca::CProductPriceAdjustmentInfo::GetPrices()
{
    return m_vLastPrices;
}

std::vector<double> pca::CProductPriceAdjustmentInfo::GetAllPrices()
{
    return m_vAllPrices;
}

void pca::CProductPriceAdjustmentInfo::ResetLastPrices()
{
    m_vLastPrices.clear();
}

void pca::CProductPriceAdjustmentInfo::AddPriceIteration(double dPriceArg)
{
    m_nIteration += 1;
    if (dPriceArg < m_dMinPrice)
    {
        m_dMinPrice = dPriceArg;
    }
    if (dPriceArg > m_dMaxPrice)
    {
        m_dMaxPrice = dPriceArg;
    }
    if (m_vLastPrices.size() > m_nParamIterationsLog)
    {
        m_vLastPrices.erase(m_vLastPrices.begin());
    }

    m_vLastPrices.push_back(dPriceArg);
    m_vAllPrices.push_back(dPriceArg);
    m_vNumLastPriceTops.push_back(CalculateNumPriceTops());
    m_vNumLastPriceBottoms.push_back(CalculateNumPriceBottoms());
}

std::vector<long>  pca::CProductPriceAdjustmentInfo::GetNumPriceTopsArray()
{
    return m_vNumLastPriceTops;
}

std::vector<long>  pca::CProductPriceAdjustmentInfo::GetNumPriceBottomsArray()
{
    return m_vNumLastPriceBottoms;
}

long pca::CProductPriceAdjustmentInfo::GetNumPriceTops()
{
    return m_vNumLastPriceTops.back();
}

long pca::CProductPriceAdjustmentInfo::GetNumPriceBottoms()
{
    return m_vNumLastPriceBottoms.back();
}

//func _calculate_num_price_tops()->int:
//
//#		Estaría bien registrar esto, para poder verlo gráficamente
//var num_max_price_tops : int = 0
//var last_price : float = 0.0
//var last_price_going_up : bool = true
//var count : int = 0
//for price in _last_prices :
//if price > last_price:
//last_price_going_up = true;
//if price < last_price:
//if last_price_going_up and count>1:
//num_max_price_tops += 1
//last_price_going_up = false;
//last_price = price
//count += 1
//return num_max_price_tops
//
//
//func _calculate_num_price_bottoms()->int:
//var num_min_price_bottoms : int = 0
//var last_price : float = 0.0
//var last_price_going_up : bool = true
//var count : int = 0
//for price in _last_prices :
//if price > last_price:
//if false == last_price_going_up and count > 1:
//num_min_price_bottoms += 1
//last_price_going_up = true;
//if price < last_price:
//last_price_going_up = false;
//last_price = price
//count += 1
//return num_min_price_bottoms

long pca::CProductPriceAdjustmentInfo::CalculateNumPriceTops()
{
    long nNumMaxPriceTops = 0;
    double dLastPrice = 0.0;
    bool bLastPriceGoingUp = true;
    long nCount = 0;
    for (auto& dPrice : m_vLastPrices)
    {
        if (dPrice > dLastPrice)
        {
            bLastPriceGoingUp = true;
        }

        if (dPrice < dLastPrice)
        {
            if (bLastPriceGoingUp && nCount > 1)
            {
                nNumMaxPriceTops += 1;
            }

            bLastPriceGoingUp = false;
        }

        dLastPrice = dPrice;
        nCount += 1;
    }

    return nNumMaxPriceTops;
}

long pca::CProductPriceAdjustmentInfo::CalculateNumPriceBottoms()
{
    long nNumMinPriceBottoms = 0;
    double dLastPrice = 0.0;
    bool bLastPriceGoingUp = true;
    long nCount = 0;
    for (auto& dPrice : m_vLastPrices)
    {
        if (dPrice > dLastPrice)
        {
            if (false == bLastPriceGoingUp && nCount > 1)
            {
                nNumMinPriceBottoms += 1;
            }
            bLastPriceGoingUp = true;
        }

        if (dPrice < dLastPrice)
        {
            bLastPriceGoingUp = false;
        }

        dLastPrice = dPrice;
        nCount += 1;
    }

    return nNumMinPriceBottoms;
}

//func reset() :
//	_iteration = 0
//	_min_price = 1.79769e308
//	_max_price = 0.0
//	#		_min_last_iterations = 1.79769e308
//	#		_max_last_iterations = 0.0
//	_last_prices.clear()
//
//	func are_prices_changing() :
//	if _all_prices.size() > 1:
//if (0 == _all_prices[_all_prices.size() - 1] - _all_prices[_all_prices.size() - 2]) :
//	return false
//else :
//	return true
//	else:
//return false
//
//func get_prices() :
//	return _last_prices
//
//	func get_all_prices() :
//	return _all_prices
//
//	func reset_last_prices() :
//	_last_prices.clear()
//
//	func add_price_iteration(price_arg : float) :
//	_iteration += 1
//	if price_arg<_min_price :
//		_min_price = price_arg
//		if price_arg>_max_price :
//			_max_price = price_arg
//			if _last_prices.size() > _param_iterations_log:
//_last_prices.remove(0)
//
//_last_prices.push_back(price_arg)
//_all_prices.push_back(price_arg)
//
//_num_last_price_tops.push_back(_calculate_num_price_tops())
//_num_last_price_bottoms.push_back(_calculate_num_price_bottoms())
//#	func get_max_price_from_last_iterations() :
//	#		var max_price : float = 0.0
//	#		for i in range(_last_prices.size() - 1, 0, -1) :
//	#			var price : float = _last_prices[i]
//#			if price>max_price:
//	#				max_price = price
//	#		return max_price
//#
//	#	func get_min_price_from_last_iterations() :
//	#		var min_price : float = 1.79769e308
//	#		for i in range(_last_prices.size() - 1, 0, -1) :
//	#			var price : float = _last_prices[i]
//#			if price>min_price:
//	#				min_price = price
//	#		return min_price
//
//	func get_num_price_tops_array()->Array:
//return _num_last_price_tops
//
//func get_num_price_bottoms_array()->Array :
//	return _num_last_price_bottoms
//
//
//	func get_num_price_tops()->int :
//	return _num_last_price_tops.back()
//
//	func get_num_price_bottoms()->int :
//	return _num_last_price_bottoms.back()
//
//
//	func _calculate_num_price_tops()->int :
//
//	#		Estaría bien registrar esto, para poder verlo gráficamente
//	var num_max_price_tops : int = 0
//	var last_price : float = 0.0
//	var last_price_going_up : bool = true
//	var count : int = 0
//	for price in _last_prices :
//if price > last_price:
//last_price_going_up = true;
//if price < last_price:
//if last_price_going_up and count>1:
//num_max_price_tops += 1
//last_price_going_up = false;
//last_price = price
//count += 1
//return num_max_price_tops
//
//
//func _calculate_num_price_bottoms()->int:
//var num_min_price_bottoms : int = 0
//var last_price : float = 0.0
//var last_price_going_up : bool = true
//var count : int = 0
//for price in _last_prices :
//if price > last_price:
//if false == last_price_going_up and count > 1:
//num_min_price_bottoms += 1
//last_price_going_up = true;
//if price < last_price:
//last_price_going_up = false;
//last_price = price
//count += 1
//return num_min_price_bottoms
