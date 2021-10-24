extends Control


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")
var _satisfaction_calculator:SatisfactionCalculator = null


# Called when the node enters the scene tree for the first time.
func _ready():
	
#	Pruebas
#	$OptionsItemList.add_item("Prueba 1")
#	$OptionsItemList.add_item("Prueba 2")
##	
	
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func update_satisfaction_calculator_data():
	var satisf_calc:SatisfactionCalculator = _satisfaction_calculator
	
	for option in satisf_calc.get_options():
		add_option(option)
	
	for comp_combo in satisf_calc.get_complementary_combos():
		add_comp_combo(comp_combo)
	
	for sup_combo in satisf_calc.get_supplementary_combos():
		add_sup_combo(sup_combo)
	
	for satisf_curve in satisf_calc.get_satisfaction_curves_of_options():
		add_satisf_curve(satisf_curve)

	for satisf_curve in satisf_calc.get_satisfaction_curves_of_complementary_combos():
		add_satisf_curve_for_comp_combo(satisf_curve)
	
	for satisf_curve in satisf_calc.get_satisfaction_curves_of_supplementary_combos():
		add_satisf_curve_for_sup_combo(satisf_curve)
	
#	TODO seguir por aquí

func set_satisfaction_calculator_ref(satisf_calculator_arg):
	_satisfaction_calculator = satisf_calculator_arg
	update_satisfaction_calculator_data()


func add_option(option_arg:String):
	$OptionsItemList.add_item(option_arg)

func add_comp_combo(comp_combo_arg:String):
	$CompCombosItemList.add_item(comp_combo_arg)
	
func add_sup_combo(sup_combo_arg:String):
	$SupCombosItemList.add_item(sup_combo_arg)
	
func add_satisf_curve(satif_curve_arg:String):
	$SatisfCurvesForOptions/SatisfCurvesItemList.add_item(satif_curve_arg)	

func add_satisf_curve_for_comp_combo(satif_curve_arg:String):
	$SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.add_item(satif_curve_arg)	

func add_satisf_curve_for_sup_combo(satif_curve_arg:String):
	$SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.add_item(satif_curve_arg)	


func _on_SatisfCurvesItemList_item_selected(index):
	if (_satisfaction_calculator):
		var option:String = $SatisfCurvesForOptions/SatisfCurvesItemList.get_item_text(index)
		var max_satisf = _satisfaction_calculator.get_option_max_satisfaction(option)
		$SatisfCurvesForOptions/MaxSatisfSpinBox.set_value(max_satisf)
		var pref_at_0 = _satisfaction_calculator.get_option_preference_at_0(option)
		$SatisfCurvesForOptions/SatisfAt0SpinBox.set_value(pref_at_0)

func _on_SatisfCurvesForCompCombosItemList_item_selected(index):
	if (_satisfaction_calculator):
		var option:String = $SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.get_item_text(index)
		var max_satisf = _satisfaction_calculator.get_complementary_combo_max_satisfaction(option)		
		$SatisfCurvesForCompCombos/MaxSatisfSpinBox.set_value(max_satisf)
		var pref_at_0 = _satisfaction_calculator.get_complementary_combo_preference_at_0(option)
		$SatisfCurvesForCompCombos/SatisfAt0SpinBox.set_value(pref_at_0)

func _on_SatisfCurvesForSupCombosItemList_item_selected(index):
	if (_satisfaction_calculator):
		var option:String = $SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.get_item_text(index)
		var max_satisf = _satisfaction_calculator.get_supplementary_combo_max_satisfaction(option)		
		$SatisfCurvesForSupCombos/MaxSatisfSpinBox.set_value(max_satisf)
		var pref_at_0 = _satisfaction_calculator.get_supplementary_combo_preference_at_0(option)
		$SatisfCurvesForSupCombos/SatisfAt0SpinBox.set_value(pref_at_0)
