extends Control


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")
var _satisfaction_calculator_ref:SatisfactionCalculator = null
var _satisfaction_calculator_copy:SatisfactionCalculator = null

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
	var satisf_calc:SatisfactionCalculator = _satisfaction_calculator_copy
	
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
	_satisfaction_calculator_ref = satisf_calculator_arg

#	He creado un _init en SatisfactionCalculator, que hace de constructor de copia
	_satisfaction_calculator_copy = SatisfactionCalculator.new(satisf_calculator_arg)

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

func draw_satisfaction_curve(satisf_curve_arg, curve_name_arg:String = "satisf"):
#	$Plotter.clear()
	if satisf_curve_arg:
		var test_funcref = funcref( satisf_curve_arg, "calculate_satifaction")
#		$Plotter.add_func_ref(test_funcref,[],curve_name_arg)
		$Plotter/GraphsControl.add_graph(test_funcref,curve_name_arg)
		


func _on_SatisfCurvesItemList_item_selected(index):
	var option:String = $SatisfCurvesForOptions/SatisfCurvesItemList.get_item_text(index)
	show_data_of_option(option)

func _on_SatisfCurvesForCompCombosItemList_item_selected(index):
	var option:String = $SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.get_item_text(index)
	show_data_of_comp_combo(option)

func _on_SatisfCurvesForSupCombosItemList_item_selected(index):
	var option:String = $SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.get_item_text(index)
	show_data_of_sup_combo(option)

func _on_SatisfCurvesItemList_item_activated(index):
	var option:String = $SatisfCurvesForOptions/SatisfCurvesItemList.get_item_text(index)
	show_data_of_option(option)

func _on_SatisfCurvesForCompCombosItemList_item_activated(index):
	var option:String = $SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.get_item_text(index)
	show_data_of_comp_combo(option)

func _on_SatisfCurvesForSupCombosItemList_item_activated(index):
	var option:String = $SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.get_item_text(index)
	show_data_of_sup_combo(option)


func show_data_of_option(option_arg:String):	
	if (_satisfaction_calculator_copy):
		var max_satisf = _satisfaction_calculator_copy.get_option_max_satisfaction(option_arg)
		$SatisfCurvesForOptions/MaxSatisfSpinBox.set_value(max_satisf)
		var pref_at_0 = _satisfaction_calculator_copy.get_option_preference_at_0(option_arg)
		$SatisfCurvesForOptions/PrefAt0SpinBox.set_value(pref_at_0)
		
		var satisf_curve = _satisfaction_calculator_copy.get_satisfaction_curve_of_option(option_arg)		
		draw_satisfaction_curve(satisf_curve,"satisf. "+option_arg)


func show_data_of_comp_combo(comp_combo_arg:String):	
	if (_satisfaction_calculator_copy):
		var max_satisf = _satisfaction_calculator_copy.get_complementary_combo_max_satisfaction(comp_combo_arg)		
		$SatisfCurvesForCompCombos/MaxSatisfForCompCombosSpinBox.set_value(max_satisf)
		var pref_at_0 = _satisfaction_calculator_copy.get_complementary_combo_preference_at_0(comp_combo_arg)
		$SatisfCurvesForCompCombos/PrefAt0ForCompCombosSpinBox.set_value(pref_at_0)

		var satisf_curve = _satisfaction_calculator_copy.get_satisfaction_curve_of_comp_combo(comp_combo_arg)		
		draw_satisfaction_curve(satisf_curve, "satisf. "+comp_combo_arg)

func show_data_of_sup_combo(sup_combo_arg:String):	
	if (_satisfaction_calculator_copy):
		var max_satisf = _satisfaction_calculator_copy.get_supplementary_combo_max_satisfaction(sup_combo_arg)
		$SatisfCurvesForSupCombos/MaxSatisfForSupCombosSpinBox.set_value(max_satisf)
		var pref_at_0 = _satisfaction_calculator_copy.get_supplementary_combo_preference_at_0(sup_combo_arg)
		$SatisfCurvesForSupCombos/PrefAt0ForSupCombosSpinBox.set_value(pref_at_0)
		
		var satisf_curve = _satisfaction_calculator_copy.get_satisfaction_curve_of_sup_combo(sup_combo_arg)		
		draw_satisfaction_curve(satisf_curve, "satisf. "+sup_combo_arg)

func _on_MaxSatisfSpinBox_value_changed(value):
	if value >= 0:
		var max_satisf = value
		var selected_items = $SatisfCurvesForOptions/SatisfCurvesItemList.get_selected_items()
		if (selected_items.size()):
			var first_select_index = selected_items[0]
			var option = $SatisfCurvesForOptions/SatisfCurvesItemList.get_item_text(first_select_index)
			var option_satisf_curve_dict = _satisfaction_calculator_copy.get_option_satisf_curve_dict()
			if (option_satisf_curve_dict.has(option)):
				var satisf_curve = option_satisf_curve_dict.get(option)
				satisf_curve.set_maximum_satisf(value)
				$Plotter.update()	

func _on_PrefAt0SpinBox_value_changed(value):
	if value >= 0:
		var max_satisf = value
		var selected_items = $SatisfCurvesForOptions/SatisfCurvesItemList.get_selected_items()
		if (selected_items.size()):
			var first_select_index = selected_items[0]
			var option = $SatisfCurvesForOptions/SatisfCurvesItemList.get_item_text(first_select_index)
			var option_satisf_curve_dict = _satisfaction_calculator_copy.get_option_satisf_curve_dict()
			if (option_satisf_curve_dict.has(option)):
				var satisf_curve = option_satisf_curve_dict.get(option)				
				satisf_curve.set_preference_at_0(value)
				$Plotter.update()	

func _on_MaxSatisfForCompCombosSpinBox_value_changed(value):
	if value >= 0:
		var max_satisf = value
		var selected_items = $SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.get_selected_items()
		if (selected_items.size()):
			var first_select_index = selected_items[0]
			var option = $SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.get_item_text(first_select_index)
			var option_satisf_curve_dict = _satisfaction_calculator_copy.get_complementary_combo_satisf_curve_dict()
			if (option_satisf_curve_dict.has(option)):
				var satisf_curve = option_satisf_curve_dict.get(option)
				satisf_curve.set_maximum_satisf(value)
				$Plotter.update()	


func _on_PrefAt0ForCompCombosSpinBox_value_changed(value):
	if value >= 0:
		var max_satisf = value
		var selected_items = $SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.get_selected_items()
		if (selected_items.size()):
			var first_select_index = selected_items[0]
			var option = $SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.get_item_text(first_select_index)
			var option_satisf_curve_dict = _satisfaction_calculator_copy.get_complementary_combo_satisf_curve_dict()
			if (option_satisf_curve_dict.has(option)):
				var satisf_curve = option_satisf_curve_dict.get(option)				
				satisf_curve.set_preference_at_0(value)
				$Plotter.update()	



func _on_MaxSatisfForSupCombosSpinBox_value_changed(value):
	if value >= 0:
		var max_satisf = value
		var selected_items = $SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.get_selected_items()
		if (selected_items.size()):
			var first_select_index = selected_items[0]
			var option = $SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.get_item_text(first_select_index)
			var option_satisf_curve_dict = _satisfaction_calculator_copy.get_supplementary_combo_satisf_curve_dict()
			if (option_satisf_curve_dict.has(option)):
				var satisf_curve = option_satisf_curve_dict.get(option)
				satisf_curve.set_maximum_satisf(value)
				$Plotter.update()	


func _on_PrefAt0ForSupCombosSpinBox_value_changed(value):
	if value >= 0:
		var max_satisf = value
		var selected_items = $SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.get_selected_items()
		if (selected_items.size()):
			var first_select_index = selected_items[0]
			var option = $SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.get_item_text(first_select_index)
			var option_satisf_curve_dict = _satisfaction_calculator_copy.get_supplementary_combo_satisf_curve_dict()
			if (option_satisf_curve_dict.has(option)):
				var satisf_curve = option_satisf_curve_dict.get(option)				
				satisf_curve.set_preference_at_0(value)
				$Plotter.update()	


func _on_XMaxSpinBox_value_changed(value):
	$Plotter.set_max_x_axis_value(value)



func _on_YMaxSpinBox_value_changed(value):
	$Plotter.set_max_y_axis_value(value)
