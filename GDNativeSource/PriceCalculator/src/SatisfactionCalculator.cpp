#include "SatisfactionCalculator.h"
#include "SatisfactionCurve.h"
//#include "PriceCalculationDefines.h"
#include "Reality.h"
#include "SupplCombo.h"
#include "ComplCombo.h"

#include <memory>

pca::CSatisfactionCalculator::CSatisfactionCalculator()
{
    //ctor
    DefaultInitialization();
}

pca::CSatisfactionCalculator::~CSatisfactionCalculator()
{
    //dtor
}

void pca::CSatisfactionCalculator::DefaultInitialization()
{
    //Default init for options:
    //m_Option_SatisfactionCurveb
	//for (auto& nOpt : c_setOptions)
    for (auto & pOpt:CReality::GetOptions())
    {
        std::unique_ptr<pca::CSatisfactionCurve> satisfOfOpt = std::make_unique<pca::CSatisfactionCurve>();
        m_Option_SatisfactionCurve[pOpt] = std::move(satisfOfOpt);
    }

    //Default init for complementary combos
    //m_mapComplementaryCombo_pSatisfCurve
    //for (auto & pairCombo_setOptions:c_mapComplementaryCombo_setOptions)
	for (auto& pCombos : CReality::GetComplCombos())
    {
        //eCompComb nCombo = pairCombo_setOptions.first;
		
        std::unique_ptr<CSatisfactionCurve> satisfOfOpt = std::make_unique<CSatisfactionCurve>();
        m_mapComplementaryCombo_pSatisfCurve[pCombos] = std::move(satisfOfOpt);
    }

    //Default init for supplementary combos
    //m_mapSupplementaryCombo_pSatisfCurve
    //m_mapSupplementaryCombo_mapOption_dWeight

	for (auto & pSuppCombo:CReality::GetSupplCombos())
	{
	//}
 //   for (auto & pairCombo_setOptions:c_mapSupplementaryCombo_setOptions)
 //   {
		std::map<pca::COption*, double> mapOptionsAndWeights = pSuppCombo->GetOptionsAndWeights();

        //eSuppComb nCombo = pairCombo_setOptions.first;
        std::unique_ptr<CSatisfactionCurve> satisfOfOpt = std::make_unique<CSatisfactionCurve>();
        //m_mapSupplementaryCombo_pSatisfCurve[nCombo] = std::move(satisfOfOpt);
		m_mapSupplementaryCombo_pSatisfCurve[pSuppCombo] = std::move(satisfOfOpt);

        //Default weight for each option
        //m_mapSupplementaryCombo_mapOption_dWeight
        //std::set<eOpt> setOptions = pairCombo_setOptions.second;
        //std::map<eOpt,double> mapOption_dWeight;
        //for (auto & nOption: setOptions)
        //{
        //    mapOption_dWeight[nOption] = 1.0; //Por defecto, el peso es 1 para todas las opciones
        //}
        //m_mapSupplementaryCombo_mapOption_dWeight[nCombo] = mapOption_dWeight;
    }
}

//_calculate_satifaction_of_opt_supplementary_combo
double pca::CSatisfactionCalculator::CalculateSatifactionOfOptSupplementaryCombo(CSupplCombo* pSuppCombo, double dAmount)
{
	//todo

	//std::map<COption*,double> mapSuppCombo_dWeight = pSuppCombo->GetOptionsAndWeights();

	//if (c_mapSupplementaryCombo_mapOption_dWeight.end()==c_mapSupplementaryCombo_mapOption_dWeight.find(nCombo))
	//	return 0.0;

	if (m_mapSupplementaryCombo_pSatisfCurve.end()==this->m_mapSupplementaryCombo_pSatisfCurve.find(pSuppCombo))
		return 0.0;

	double dRetSatisf = 0.0;

	CSatisfactionCurve* pSatisfactionCurve = (this->m_mapSupplementaryCombo_pSatisfCurve.at(pSuppCombo)).get();
	dRetSatisf = pSatisfactionCurve->CalculateSatifaction(dAmount);

	return dRetSatisf;
}

//_calculate_satisf_of_combidict_from_supplementary_combos
double pca::CSatisfactionCalculator::CalculateSatisfOfCombidictFromSupplementaryCombos(std::map<COption*,double> mapOption_dAmount)
{
//#	Satisfacción de los supplementary combos
//#var _supplementary_combos:Dictionary = {	"savings":	{	"candy_savings":0.1,
//#															"chocolate_savings":1.0
//#														}
//#	}

	//std::map<COption*,double> mapSuppCombo_dWeight = pSuppCombo->GetOptionsAndWeights();

	double dSatisfOfCombi = 0.0;
	for (auto& pSupplCombo : pca::CReality::GetSupplCombos())
	//for (auto & pair_Combo_mapOption_dWeight:c_mapSupplementaryCombo_mapOption_dWeight)
    {
        //eSuppComb nCombo = pair_Combo_mapOption_dWeight.first;

        double dAmountOfSuppCombo = 0.0;
		//std::map<eOpt,double> mapOption_dWeight = c_mapSupplementaryCombo_mapOption_dWeight.at(nCombo);
		std::map<COption*, double> mapOption_dWeight = pSupplCombo->GetOptionsAndWeights();

		for (auto & pairOption_dWeight: mapOption_dWeight)
        {
            //eOpt nOption = pairOption_dWeight.first;
			COption* pOption = pairOption_dWeight.first;
            double dWeight = pairOption_dWeight.second;
			double dAmountOfOption = 0.0;
			if (mapOption_dAmount.end()!=mapOption_dAmount.find(pOption))
            {
                dAmountOfOption = mapOption_dAmount.at(pOption);
            }

			double dWeightedAmountOfOption = dWeight*dAmountOfOption;
			dAmountOfSuppCombo += dWeightedAmountOfOption;
        }

		dSatisfOfCombi += this->CalculateSatifactionOfOptSupplementaryCombo(pSupplCombo,dAmountOfSuppCombo);
    }

	return dSatisfOfCombi;
}

//_calculate_satifaction_of_opt_complementary_combo
double pca::CSatisfactionCalculator::CalculateSatifactionOfOptComplementaryCombo(CComplCombo* pCombo, double dAmount)
{
	//if (c_mapComplementaryCombo_setOptions.end() == c_mapComplementaryCombo_setOptions.find(nCombo))
	//	return 0.0;

	if (this->m_mapComplementaryCombo_pSatisfCurve.end() == this->m_mapComplementaryCombo_pSatisfCurve.find(pCombo))
		return 0.0;


	double dRetSatisf = 0.0;

	CSatisfactionCurve* pSatisfactionCurve = (this->m_mapComplementaryCombo_pSatisfCurve.at(pCombo)).get();
	dRetSatisf = pSatisfactionCurve->CalculateSatifaction(dAmount);

	return dRetSatisf;
}

//_calculate_satisf_of_combidict_from_complementary_combos
double pca::CSatisfactionCalculator::CalculateSatisfOfCombidictFromComplementaryCombos(std::map<COption*,double> mapOption_dAmount)
{
    //#var _complementary_combos:Dictionary = {"sweets_consumption":["chocolate_consumption","candy_consumption"]}

	double dSatisfOfCombi = 0.0;

	//for ( auto & pairCombo_Options :c_mapComplementaryCombo_setOptions)
	for(auto & pComplCombo:pca::CReality::GetComplCombos())
    {
        //std::set<eOpt> setOptions = pairCombo_Options.second;		
		//pairCombo_Options

		//std::set<COption*> setOptions = pairCombo_Options.second;
		std::set<COption*> setOptions = pComplCombo->GetOptions();
		
		double dAmountOfCombi = 0.0;
		int nCount = 0;
		for (auto & pOption :setOptions)
        {
			double dAmountOfOption = 0.0;
			if (mapOption_dAmount.end() != mapOption_dAmount.find(pOption))
				dAmountOfOption = mapOption_dAmount.at(pOption);
			if (dAmountOfOption < dAmountOfCombi || 0 == nCount)
				dAmountOfCombi = dAmountOfOption;
			if (dAmountOfOption == 0)
				break;
			nCount += 1;
        }
        //eCompComb nCombo = pairCombo_Options.first;
		//CComplCombo* pComplCombo = pairCombo_Options.first;
		dSatisfOfCombi += this->CalculateSatifactionOfOptComplementaryCombo(pComplCombo,dAmountOfCombi);
    }
	return dSatisfOfCombi;
}


//calculate_satifaction_of_option
double pca::CSatisfactionCalculator::CalculateSatifactionOfOption(COption* pOption, double dQuantity)
{
	//if (c_setOptions.end()==c_setOptions.find(nOption))
	//	return 0.0;

	double dRetSatisf = 0.0;

	CSatisfactionCurve* pOptionSatisfactionCurve = (this->m_Option_SatisfactionCurve[pOption]).get();

	dRetSatisf = pOptionSatisfactionCurve->CalculateSatifaction(dQuantity);

	return dRetSatisf;
}

//_calculate_satisf_of_combidict_from_individual_options
double pca::CSatisfactionCalculator::CalculateSatisfOfCombidictFromIndividualOptions(std::map<COption*,double> map_nOption_dAmount)
{
    double dSatisfOfOptIndividually = 0.0;
    //for (auto & nOption: c_setOptions)
	for (auto& pOption : pca::CReality::GetOptions())
    {
        if(map_nOption_dAmount.end() != map_nOption_dAmount.find(pOption))
        {
            double dAmountOfOption = map_nOption_dAmount.at(pOption);

            dSatisfOfOptIndividually += this->CalculateSatifactionOfOption(pOption,dAmountOfOption);
        }
    }

    return dSatisfOfOptIndividually;
}


//func calculate_satisf_of_combidict(combidict_arg:Dictionary) -> float:
double pca::CSatisfactionCalculator::CalculateSatisfOfCombidict(std::map<COption*,double> map_nOption_dAmount)
{
    double dSatisfOfOptIndividually = CalculateSatisfOfCombidictFromIndividualOptions(map_nOption_dAmount);

    double dSatisfOfOptComplementaryCombi = CalculateSatisfOfCombidictFromComplementaryCombos(map_nOption_dAmount);

    double dSatisfOfOptSupplementaryCombi = CalculateSatisfOfCombidictFromSupplementaryCombos(map_nOption_dAmount);

    double dSatisfactionReturn = dSatisfOfOptIndividually + dSatisfOfOptComplementaryCombi + dSatisfOfOptSupplementaryCombi;

    return dSatisfactionReturn;

}

void pca::CSatisfactionCalculator::SetPreferenceAt0(pca::COption* pOpt, double dPrefAt0)
{
	if (m_Option_SatisfactionCurve.end() == m_Option_SatisfactionCurve.find(pOpt))
	{
		auto pSatisfCurve = m_Option_SatisfactionCurve.at(pOpt).get();
		pSatisfCurve->SetPreferenceAt0(dPrefAt0);
	}
}

void pca::CSatisfactionCalculator::SetMaximumSatisf(pca::COption* pOpt, double dMaxSatisf)
{
	if (m_Option_SatisfactionCurve.end() == m_Option_SatisfactionCurve.find(pOpt))
	{
		auto pSatisfCurve = m_Option_SatisfactionCurve.at(pOpt).get();
		pSatisfCurve->SetMaximumSatisf(dMaxSatisf);
	}
}

void pca::CSatisfactionCalculator::SetPreferenceAt0(pca::CComplCombo* pCompComb, double dPrefAt0)
{
	if (m_mapComplementaryCombo_pSatisfCurve.end() == m_mapComplementaryCombo_pSatisfCurve.find(pCompComb))
	{
		auto pSatisfCurve = m_mapComplementaryCombo_pSatisfCurve.at(pCompComb).get();
		pSatisfCurve->SetPreferenceAt0(dPrefAt0);
	}
}

void pca::CSatisfactionCalculator::SetMaximumSatisf(pca::CComplCombo* pCompComb, double dMaxSatisf)
{
	if (m_mapComplementaryCombo_pSatisfCurve.end() == m_mapComplementaryCombo_pSatisfCurve.find(pCompComb))
	{
		auto pSatisfCurve = m_mapComplementaryCombo_pSatisfCurve.at(pCompComb).get();
		pSatisfCurve->SetMaximumSatisf(dMaxSatisf);
	}
}

void pca::CSatisfactionCalculator::SetPreferenceAt0(pca::CSupplCombo* pSuppComb, double dPrefAt0)
{
	if (m_mapSupplementaryCombo_pSatisfCurve.end() == m_mapSupplementaryCombo_pSatisfCurve.find(pSuppComb))
	{
		auto pSatisfCurve = m_mapSupplementaryCombo_pSatisfCurve.at(pSuppComb).get();
		pSatisfCurve->SetPreferenceAt0(dPrefAt0);
	}
}

void pca::CSatisfactionCalculator::SetMaximumSatisf(pca::CSupplCombo* pSuppComb, double dMaxSatisf)
{
	if (m_mapSupplementaryCombo_pSatisfCurve.end() == m_mapSupplementaryCombo_pSatisfCurve.find(pSuppComb))
	{
		auto pSatisfCurve = m_mapSupplementaryCombo_pSatisfCurve.at(pSuppComb).get();
		pSatisfCurve->SetMaximumSatisf(dMaxSatisf);
	}
}





//
//std::map<pca::eProd,double> pca::CSatisfactionCalculator::CalculateProductdictFromOptiondict(std::map<eOpt,double> mapOptiondictArg )
//{
//    std::map<eProd,double> mapProductdict;
//
//    for(auto & pairOptionAmount:mapOptiondictArg)
//    {
//        eOpt nOption = pairOptionAmount.first;
//        double dAmount = pairOptionAmount.second;
//
//        if (c_mapOption_Product.end()!=c_mapOption_Product.find(nOption))
//        {
//            eProd nProduct = c_mapOption_Product.at(nOption);
//
//            if (mapProductdict.end()!=mapProductdict.find(nProduct))
//            {
//                mapProductdict[nProduct] = dAmount + mapProductdict.at(nProduct);
//            }
//            else
//            {
//                mapProductdict[nProduct]=dAmount;
//            }
//        }
//    }
//
//    return mapProductdict;
//}

/*
func calculate_productdict_from_optiondict(option_dict_arg:Dictionary)->Dictionary:
	var product_dict:Dictionary = {}
	for option in option_dict_arg:
		if _option_product_dict.has(option):
			var product = _option_product_dict[option]
			if (product_dict.has(product)):
				product_dict[product] += option_dict_arg[option]
			else:
				product_dict[product] = option_dict_arg[option]

		else:
	#	No sé si está bien que pueda haber products entre las options
			if PriceCalculationGlobals._products.has(option):
				if (product_dict.has(option)):
					product_dict[option] += option_dict_arg[option]
				else:
					product_dict[option] = option_dict_arg[option]

	return product_dict
*/


/*
func calculate_productdict_from_optiondict(option_dict_arg:Dictionary)->Dictionary:
	var product_dict:Dictionary = {}
	for option in option_dict_arg:
		if _option_product_dict.has(option):
			var product = _option_product_dict[option]
			if (product_dict.has(product)):
				product_dict[product] += option_dict_arg[option]
			else:
				product_dict[product] = option_dict_arg[option]

		else:
	#	No sé si está bien que pueda haber products entre las options
			if PriceCalculationGlobals._products.has(option):
				if (product_dict.has(option)):
					product_dict[option] += option_dict_arg[option]
				else:
					product_dict[option] = option_dict_arg[option]

	return product_dict
*/

/*
func _calculate_satisf_of_combidict_from_individual_options(combidict_arg:Dictionary) -> float:

	var satisf_of_opt_individually = 0.0
	for option in self._options:
		if combidict_arg.has(option):
			var amount_of_option = combidict_arg[option]

			satisf_of_opt_individually += self.calculate_satifaction_of_option(option,amount_of_option)


	return satisf_of_opt_individually


func _calculate_satisf_of_combidict_from_complementary_combos(combidict_arg:Dictionary) -> float:

	var satisf_of_combi = 0.0
	for combi_name in self._complementary_combos.keys():
		var amount_of_combi = 0
		var count = 0
		for option in _complementary_combos[combi_name]:
			var amount_of_option = 0.0
			if combidict_arg.has(option):
				amount_of_option = combidict_arg[option]
			if amount_of_option < amount_of_combi or 0 == count:
				amount_of_combi = amount_of_option
			if amount_of_option == 0:
				break
			count += 1

		satisf_of_combi += self._calculate_satifaction_of_opt_complementary_combo(combi_name,amount_of_combi)

	return satisf_of_combi


func _calculate_satisf_of_combidict_from_supplementary_combos(combidict_arg:Dictionary) -> float:
#	Satisfacción de los supplementary combos
#var _supplementary_combos:Dictionary = {	"savings":	{	"candy_savings":0.1,
#															"chocolate_savings":1.0
#														}
#										}
	var satisf_of_combi:float = 0.0
	for supp_combo_name in self._supplementary_combos.keys():
		var amount_of_supp_combo = 0.0
		var supplementary_combo_dict:Dictionary = self._supplementary_combos[supp_combo_name]
		for option in supplementary_combo_dict.keys():
			var weighting_of_option:float = supplementary_combo_dict[option]
			var amount_of_option:float = 0.0
			if combidict_arg.has(option):
				amount_of_option = combidict_arg[option]
			var weigted_amount_of_option:float = weighting_of_option*amount_of_option
			amount_of_supp_combo += weigted_amount_of_option

		satisf_of_combi += self._calculate_satifaction_of_opt_supplementary_combo(supp_combo_name,amount_of_supp_combo)

	return satisf_of_combi


func calculate_satisf_of_combidict(combidict_arg:Dictionary) -> float:

	TimeMeasurement.start("calculate_satisf_of_combidict")

	var satisf_of_opt_individually = 0.0
	satisf_of_opt_individually = _calculate_satisf_of_combidict_from_individual_options(combidict_arg)


	var satisf_of_complementary_combi = 0.0
	satisf_of_complementary_combi = _calculate_satisf_of_combidict_from_complementary_combos(combidict_arg)



	var satisf_of_supplementary_combi = 0.0
	satisf_of_supplementary_combi = _calculate_satisf_of_combidict_from_supplementary_combos(combidict_arg)


	var satisfaction_return = 0.0
	satisfaction_return = satisf_of_opt_individually+satisf_of_complementary_combi+satisf_of_supplementary_combi

	TimeMeasurement.stop("calculate_satisf_of_combidict")

	return satisfaction_return



func calculate_satifaction_of_option(option_arg:String, quantity_arg:float) -> float:

	if false==_options.has(option_arg):
		return 0.0

	var ret_satisf = 0.0
#	var pref_at_0 = _param_preference_at_0[product_arg]
#	var max_satisf = _maximum_satisf[product_arg]
#
#	ret_satisf = max_satisf*get_diminishing_returns_factor(quantity_arg*pref_at_0/max_satisf)

	var option_satisf_curve:SatisfactionCurve = self._option_satisf_curve_dict[option_arg]


	ret_satisf = option_satisf_curve.calculate_satifaction(quantity_arg)


	return ret_satisf

func _calculate_satifaction_of_opt_complementary_combo(combo_arg:String, quantity_arg:float) -> float:

	if false==self._complementary_combos.has(combo_arg):
		return 0.0

	if false==self._complementary_combo_satisf_curve_dict.has(combo_arg):
		return 0.0


	var ret_satisf = 0.0
#	var pref_at_0 = self._param_combo_preference_at_0[combi_arg]
#	var max_satisf = self._param_combo_maximum_quantity_satisf[combi_arg]
#
#	ret_satisf = max_satisf*get_diminishing_returns_factor(quantity_arg*pref_at_0/max_satisf)
#

	var combo_satisf_curve:SatisfactionCurve = self._complementary_combo_satisf_curve_dict[combo_arg]
	ret_satisf = combo_satisf_curve.calculate_satifaction(quantity_arg)

	return ret_satisf

func _calculate_satifaction_of_opt_supplementary_combo(combo_arg:String, quantity_arg:float) -> float:

	if false==self._supplementary_combos.has(combo_arg):
		return 0.0

	if false==self._supplementary_combo_satisf_curve_dict.has(combo_arg):
		return 0.0


	var ret_satisf = 0.0
#	var pref_at_0 = self._param_combo_preference_at_0[combi_arg]
#	var max_satisf = self._param_combo_maximum_quantity_satisf[combi_arg]
#
#	ret_satisf = max_satisf*get_diminishing_returns_factor(quantity_arg*pref_at_0/max_satisf)
#

	var combo_satisf_curve:SatisfactionCurve = self._supplementary_combo_satisf_curve_dict[combo_arg]
	ret_satisf = combo_satisf_curve.calculate_satifaction(quantity_arg)

	return ret_satisf


*/
