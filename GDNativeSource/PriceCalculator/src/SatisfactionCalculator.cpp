#include "SatisfactionCalculator.h"
#include "SatisfactionCurve.h"
#include "PriceCalculationDefines.h"


CSatisfactionCalculator::CSatisfactionCalculator()
{
    //ctor
    DefaultInitialization();
}

CSatisfactionCalculator::~CSatisfactionCalculator()
{
    //dtor
}

void CSatisfactionCalculator::DefaultInitialization()
{
    //Default init for options:
    //m_Option_SatisfactionCurveb
    for (auto & nOpt:c_setOptions)
    {
        std::unique_ptr<CSatisfactionCurve> satisfOfOpt = std::make_unique<CSatisfactionCurve>();
        m_Option_SatisfactionCurve[nOpt] = std::move(satisfOfOpt);
    }

    //Default init for complementary combos
    //m_mapComplementaryCombo_pSatisfCurve
    for (auto & pairCombo_setOptions:c_mapComplementaryCombo_setOptions)
    {
        int nCombo = pairCombo_setOptions.first;
        std::unique_ptr<CSatisfactionCurve> satisfOfOpt = std::make_unique<CSatisfactionCurve>();
        m_mapComplementaryCombo_pSatisfCurve[nCombo] = std::move(satisfOfOpt);
    }

    //Default init for supplementary combos
    //m_mapSupplementaryCombo_pSatisfCurve
    //m_mapSupplementaryCombo_mapOption_dWeight
    for (auto & pairCombo_setOptions:c_mapSupplementaryCombo_setOptions)
    {
        int nCombo = pairCombo_setOptions.first;
        std::unique_ptr<CSatisfactionCurve> satisfOfOpt = std::make_unique<CSatisfactionCurve>();
        m_mapSupplementaryCombo_pSatisfCurve[nCombo] = std::move(satisfOfOpt);

        //Default weight for each option
        //m_mapSupplementaryCombo_mapOption_dWeight
        std::set<int> setOptions = pairCombo_setOptions.second;
        std::map<int,double> mapOption_dWeight;
        for (auto & nOption: setOptions)
        {
            mapOption_dWeight[nOption] = 1.0; //Por defecto, el peso es 1 para todas las opciones
        }
        m_mapSupplementaryCombo_mapOption_dWeight[nCombo] = mapOption_dWeight;
    }


}

//_calculate_satifaction_of_opt_supplementary_combo
double CSatisfactionCalculator::CalculateSatifactionOfOptSupplementaryCombo(int nCombo, double dAmount)
{


	if (m_mapSupplementaryCombo_mapOption_dWeight.end()==this->m_mapSupplementaryCombo_mapOption_dWeight.find(nCombo))
		return 0.0;

	if (m_mapSupplementaryCombo_pSatisfCurve.end()==this->m_mapSupplementaryCombo_pSatisfCurve.find(nCombo))
		return 0.0;


	double dRetSatisf = 0.0;

	CSatisfactionCurve* pSatisfactionCurve = (this->m_mapSupplementaryCombo_pSatisfCurve.at(nCombo)).get();
	dRetSatisf = pSatisfactionCurve->CalculateSatifaction(dAmount);

	return dRetSatisf;
}

//_calculate_satisf_of_combidict_from_supplementary_combos
double CSatisfactionCalculator::CalculateSatisfOfCombidictFromSupplementaryCombos(std::map<int,double> mapOption_dAmount)
{

//#	Satisfacción de los supplementary combos
//#var _supplementary_combos:Dictionary = {	"savings":	{	"candy_savings":0.1,
//#															"chocolate_savings":1.0
//#														}
//#										}
	double dSatisfOfCombi = 0.0;
	for (auto & pair_Combo_mapOption_dWeight:this->m_mapSupplementaryCombo_mapOption_dWeight)
    {
        int nCombo = pair_Combo_mapOption_dWeight.first;
        double dAmountOfSuppCombo = 0.0;
		std::map<int,double> mapOption_dWeight = this->m_mapSupplementaryCombo_mapOption_dWeight.at(nCombo);
		for (auto & pairOption_dWeight: mapOption_dWeight)
        {
            int nOption = pairOption_dWeight.first;
            double dWeight = pairOption_dWeight.second;
			double dAmountOfOption = 0.0;
			if (mapOption_dAmount.end()!=mapOption_dAmount.find(nOption))
            {
                dAmountOfOption = mapOption_dAmount.at(nOption);
            }

			double dWeightedAmountOfOption = dWeight*dAmountOfOption;
			dAmountOfSuppCombo += dWeightedAmountOfOption;
        }

		dSatisfOfCombi += this->CalculateSatifactionOfOptSupplementaryCombo(nCombo,dAmountOfSuppCombo);
    }

	return dSatisfOfCombi;
}

//_calculate_satifaction_of_opt_complementary_combo
double CSatisfactionCalculator::CalculateSatifactionOfOptComplementaryCombo(int nCombo, double dAmount)
{
	if (c_mapComplementaryCombo_setOptions.end() == c_mapComplementaryCombo_setOptions.find(nCombo))
		return 0.0;

	if (this->m_mapComplementaryCombo_pSatisfCurve.end() == this->m_mapComplementaryCombo_pSatisfCurve.find(nCombo))
		return 0.0;


	double dRetSatisf = 0.0;

	CSatisfactionCurve* pSatisfactionCurve = (this->m_mapComplementaryCombo_pSatisfCurve.at(nCombo)).get();
	dRetSatisf = pSatisfactionCurve->CalculateSatifaction(dAmount);

	return dRetSatisf;
}


//_calculate_satisf_of_combidict_from_complementary_combos
double CSatisfactionCalculator::CalculateSatisfOfCombidictFromComplementaryCombos(std::map<int,double> mapOption_dAmount)
{
    //#var _complementary_combos:Dictionary = {"sweets_consumption":["chocolate_consumption","candy_consumption"]}

	double dSatisfOfCombi = 0.0;
	for ( auto & pairCombo_Options :c_mapComplementaryCombo_setOptions)
    {
        std::set<int> setOptions = pairCombo_Options.second;
		double dAmountOfCombi = 0.0;
		int nCount = 0;
		for (auto & nOption :setOptions)
        {
			double dAmountOfOption = 0.0;
			if (mapOption_dAmount.end() != mapOption_dAmount.find(nOption))
				dAmountOfOption = mapOption_dAmount.at(nOption);
			if (dAmountOfOption < dAmountOfCombi || 0 == nCount)
				dAmountOfCombi = dAmountOfOption;
			if (dAmountOfOption == 0)
				break;
			nCount += 1;
        }
        int nCombo = pairCombo_Options.first;
		dSatisfOfCombi += this->CalculateSatifactionOfOptComplementaryCombo(nCombo,dAmountOfCombi);
    }
	return dSatisfOfCombi;
}


//calculate_satifaction_of_option
double CSatisfactionCalculator::CalculateSatifactionOfOption(int nOption, double dQuantity)
{
	if (c_setOptions.end()==c_setOptions.find(nOption))
		return 0.0;

	double dRetSatisf = 0.0;

	CSatisfactionCurve* pOptionSatisfactionCurve = (this->m_Option_SatisfactionCurve[nOption]).get();

	dRetSatisf = pOptionSatisfactionCurve->CalculateSatifaction(dQuantity);

	return dRetSatisf;
}

//_calculate_satisf_of_combidict_from_individual_options
double CSatisfactionCalculator::CalculateSatisfOfCombidictFromIndividualOptions(std::map<int,double> map_nOption_dAmount)
{
    double dSatisfOfOptIndividually = 0.0;
    for (auto & nOption: c_setOptions)
    {
        if(map_nOption_dAmount.end() != map_nOption_dAmount.find(nOption))
        {
            double dAmountOfOption = map_nOption_dAmount.at(nOption);

            dSatisfOfOptIndividually += this->CalculateSatifactionOfOption(nOption,dAmountOfOption);
        }
    }

    return dSatisfOfOptIndividually;
}

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
