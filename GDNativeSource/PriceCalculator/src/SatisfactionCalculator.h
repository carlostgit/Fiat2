#ifndef CSATISFACTIONCALCULATOR_H
#define CSATISFACTIONCALCULATOR_H

//#include "PriceCalculationDefines.h"

#include <map>
#include <vector>
#include <set>
#include <memory>

namespace pca
{
    class CSatisfactionCurve;
    class COption;
    class CComplCombo;
    class CSupplCombo;

    class CSatisfactionCalculator
    {
        friend class CTester;

    public:
        CSatisfactionCalculator();
        virtual ~CSatisfactionCalculator();

        //std::map<pca::eProd, double> CalculateProductdictFromOptiondict(std::map<eOpt, double> mapOptiondictArg);
        double CalculateSatisfOfCombidict(std::map<COption*, double> map_nOption_dAmount);
        
        void SetPreferenceAt0(COption* pOpt, double dPrefAt0);
        void SetMaximumSatisf(COption* pOpt, double dMaxSatisf);
        void SetPreferenceAt0(CComplCombo* pCompComb, double dPrefAt0);
        void SetMaximumSatisf(CComplCombo* pCompComb, double dMaxSatisf);
        void SetPreferenceAt0(CSupplCombo* pSuppComb, double dPrefAt0);
        void SetMaximumSatisf(CSupplCombo* pSuppComb, double dMaxSatisf);


    protected:
        double CalculateSatisfOfCombidictFromIndividualOptions(std::map<COption*, double> map_pOption_dAmount);
        double CalculateSatifactionOfOption(COption* pOption, double dQuantity);
        double CalculateSatisfOfCombidictFromComplementaryCombos(std::map<COption*, double> mapOption_dAmount);
        double CalculateSatifactionOfOptComplementaryCombo(CComplCombo* pCombo, double dAmount);
        double CalculateSatisfOfCombidictFromSupplementaryCombos(std::map<COption*, double> mapOption_dAmount);
        double CalculateSatifactionOfOptSupplementaryCombo(CSupplCombo* pCombo, double dAmount);
        

        void DefaultInitialization();

    private:
        //std::vector<long> m_vOptions; //Igual se puede sustituir esto por otra cosa
        //std::set<long> m_setOptions;//TODO: sustituir por lo de PriceCalculationDefines
        std::map<COption*, std::unique_ptr<CSatisfactionCurve> > m_Option_SatisfactionCurve;

        //std::map<long, std::set<long> > m_mapComplementaryCombo_setOptions;
        std::map<CComplCombo*, std::unique_ptr<CSatisfactionCurve> > m_mapComplementaryCombo_pSatisfCurve;

        //std::map<eSuppComb, std::map<eOpt, double> > m_mapSupplementaryCombo_mapOption_dWeight;
        std::map<CSupplCombo*, std::unique_ptr<CSatisfactionCurve> > m_mapSupplementaryCombo_pSatisfCurve;

        int m_nId = 0;


        /*
        //Combos suplementarios y complementarios con su ponderación
        var _complementary_combos:Dictionary = {} #Hay que inicializarlo
        #var _complementary_combos:Dictionary = {"sweets_consumption":["chocolate_consumption","candy_consumption"]}
        var _supplementary_combos:Dictionary = {} #Hay que inicializarlo
        #var _supplementary_combos:Dictionary = {	"savings":	{	"candy_savings":0.1,
        #															"chocolate_savings":1.0,
        #															"nut_savings":0.2
        #														}
        #										}

        //Todas las diferentes opciones. Tal vez debería ir en un fichero aparte?
        var _options:Array = [] #Hay que inicializarlo a partir de los productos
        var _option_product_dict:Dictionary = {} #Hay que inicializarlo a partir de los productos
        #var _option_product_dict:Dictionary = { "candy_savings": "candy",
        #									"candy_consumption": "candy",
        #									"chocolate_savings": "chocolate",
        #									"chocolate_consumption": "chocolate",
        #									"nut_savings": "nut",
        #									"nut_consumption": "nut"
        #									}
        var _option_use:Dictionary = {}
        #{candy_consumption:consumption}
        var _name:String = "satisf_calc_default_name"


        var _option_satisf_curve_dict:Dictionary = {}
        var _complementary_combo_satisf_curve_dict:Dictionary = {}
        var _supplementary_combo_satisf_curve_dict:Dictionary = {}
        */
    };
}

#endif // CSATISFACTIONCALCULATOR_H
