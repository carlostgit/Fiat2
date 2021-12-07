
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
	
	$OptionsItemList.clear()
	for option in satisf_calc.get_options():
		$OptionsItemList.add_item(option)
	
	$CompCombosItemList.clear()
	for comp_combo in satisf_calc.get_complementary_combos():
		$CompCombosItemList.add_item(comp_combo)
		
	$SupCombosItemList.clear()
	for sup_combo in satisf_calc.get_supplementary_combos():
		$SupCombosItemList.add_item(sup_combo)
	
	$SatisfCurvesForOptions/SatisfCurvesItemList.clear()	
	for satisf_curve in satisf_calc.get_satisfaction_curves_of_options():
		$SatisfCurvesForOptions/SatisfCurvesItemList.add_item(satisf_curve)	

	$SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.clear()
	for satisf_curve in satisf_calc.get_satisfaction_curves_of_complementary_combos():
		$SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.add_item(satisf_curve)	
	
	$SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.clear()
	for satisf_curve in satisf_calc.get_satisfaction_curves_of_supplementary_combos():
		$SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.add_item(satisf_curve)


	
#	TODO seguir por aquí

func set_satisfaction_calculator_ref(satisf_calculator_arg):
	_satisfaction_calculator_ref = satisf_calculator_arg

#	He creado un _init en SatisfactionCalculator, que hace de constructor de copia
	_satisfaction_calculator_copy = SatisfactionCalculator.new(satisf_calculator_arg)

	update_satisfaction_calculator_data()


#func add_option(option_arg:String):
#	$OptionsItemList.add_item(option_arg)
#
#func add_comp_combo(comp_combo_arg:String):
#	$CompCombosItemList.add_item(comp_combo_arg)
#
#func add_sup_combo(sup_combo_arg:String):
#	$SupCombosItemList.add_item(sup_combo_arg)
#
#func add_satisf_curve(satif_curve_arg:String):
#	$SatisfCurvesForOptions/SatisfCurvesItemList.add_item(satif_curve_arg)	
#
#func add_satisf_curve_for_comp_combo(satif_curve_arg:String):
#	$SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.add_item(satif_curve_arg)	
#
#func add_satisf_curve_for_sup_combo(satif_curve_arg:String):
#	$SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.add_item(satif_curve_arg)	

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

func _on_CompCombosItemList_item_selected(index):
	var comp_combo:String = $CompCombosItemList.get_item_text(index)
	var options:Array = _satisfaction_calculator_copy.get_options_from_complementary_combo(comp_combo)
	$OptionsOfCompComboItemList.clear()
	for option in options:
		$OptionsOfCompComboItemList.add_item(option)
	
func _on_SupCombosItemList_item_selected(index):
	var sup_combo:String = $SupCombosItemList.get_item_text(index)
	var options:Array = _satisfaction_calculator_copy.get_options_from_supplementary_combo(sup_combo)
	$OptionsOfSupComboItemList.clear()
	for option in options:
		$OptionsOfSupComboItemList.add_item(option)		
#		get_weighted_options_from_supplementary_combo

func _on_OptionsOfSupComboItemList_item_selected(index):	
	var option:String = $OptionsOfSupComboItemList.get_item_text(index)
	var selected_combos_indexes:PoolIntArray = $SupCombosItemList.get_selected_items()
	if false==selected_combos_indexes.empty():
		var selected_combo_index:int = selected_combos_indexes[0]
		var comp_combo:String = $SupCombosItemList.get_item_text(selected_combo_index)
		var weighted_options:Dictionary = _satisfaction_calculator_copy.get_weighted_options_from_supplementary_combo(comp_combo)
		if weighted_options.has(option):
			var weight:float = weighted_options[option]
			$WeightOfOptionOfSupComboSpinBox.set_value(weight)
	


func _on_OptionsItemList_nothing_selected():
	$DeleteOption.set_disabled(true) 
	


func _on_OptionsItemList_item_selected(index):
	$DeleteOption.set_disabled(false)


func _on_DeleteOption_pressed():
	var select:Array = $OptionsItemList.get_selected_items()
	if false == select.empty():
#		$OptionsItemList.remove_item(select[0])
		var item_to_erase:String = $OptionsItemList.get_item_text(select[0])
		_satisfaction_calculator_copy.erase_option(item_to_erase)
		update_satisfaction_calculator_data()
	
func _on_AddOption_pressed():
	$NewOptionAcceptDialog.show_modal(true)

func _on_NewOptionAcceptDialog_ok_pressed(text):
	for i in range(0,$OptionsItemList.get_item_count()):
		if text==$OptionsItemList.get_item_text(i):
			return
	_satisfaction_calculator_copy.add_option(text)
	update_satisfaction_calculator_data()


func _on_DeleteCompCombo_pressed():
	var select:Array = $CompCombosItemList.get_selected_items()
	if false == select.empty():
		var item_to_erase:String = $CompCombosItemList.get_item_text(select[0])
		_satisfaction_calculator_copy.erase_complementary_combo(item_to_erase)
		update_satisfaction_calculator_data()
		$OptionsOfCompComboItemList.clear()
		

func _on_AddCompCombo_pressed():
	$NewCompComboAcceptDialog.show_modal(true)
#	pass # Replace with function body.


func _on_NewCompComboAcceptDialog_ok_pressed(text):
	for i in range(0,$CompCombosItemList.get_item_count()):
		if text==$CompCombosItemList.get_item_text(i):
			return
#	$CompCombosItemList.add_item(text)
	_satisfaction_calculator_copy.set_complementary_combo(text,[])
	update_satisfaction_calculator_data()



func _on_DeleteOptionOfCompCombo_pressed():
	var select:Array = $OptionsOfCompComboItemList.get_selected_items()
	var select_combo:Array = $CompCombosItemList.get_selected_items()
	if false == select.empty() and false == select_combo.empty():
#		$OptionsOfCompComboItemList.remove_item(select[0])
		var item_to_erase:String = $OptionsOfCompComboItemList.get_item_text(select[0])
		var combo_of_items_to_erase:String = $CompCombosItemList.get_item_text(select_combo[0])
		_satisfaction_calculator_copy.erase_option_in_comp_combo(combo_of_items_to_erase,item_to_erase)
		update_satisfaction_calculator_data()
		$CompCombosItemList.select(select_combo[0])
		var options:Array = _satisfaction_calculator_copy.get_options_from_complementary_combo(combo_of_items_to_erase)
		$OptionsOfCompComboItemList.clear()
		for option in options:
			$OptionsOfCompComboItemList.add_item(option)
	


func _on_AddOptionOfCompCombo_pressed():
	$NewOptionOfCompComboAcceptDialog.show_modal(true)


func _on_NewOptionOfCompComboAcceptDialog_ok_pressed(text):
	for i in range(0,$OptionsOfCompComboItemList.get_item_count()):
		if text==$OptionsOfCompComboItemList.get_item_text(i):
			return
	$OptionsOfCompComboItemList.add_item(text)
	
	var select_combo:Array = $CompCombosItemList.get_selected_items()
	if false == select_combo.empty():
		var combo_of_options_to_add:String = $CompCombosItemList.get_item_text(select_combo[0])
		_satisfaction_calculator_copy.add_option_in_comp_combo(combo_of_options_to_add,text)

		update_satisfaction_calculator_data()
		$CompCombosItemList.select(select_combo[0])
		var options:Array = _satisfaction_calculator_copy.get_options_from_complementary_combo(combo_of_options_to_add)
		$OptionsOfCompComboItemList.clear()
		for option in options:
			$OptionsOfCompComboItemList.add_item(option)
		



func _on_DeleteSupCombo_pressed():
	var select:Array = $SupCombosItemList.get_selected_items()
	if false == select.empty():
		var item_to_erase:String = $SupCombosItemList.get_item_text(select[0])
		_satisfaction_calculator_copy.erase_supplementary_combo(item_to_erase)
		update_satisfaction_calculator_data()
		$OptionsOfSupComboItemList.clear()


func _on_NewSupComboAcceptDialog_ok_pressed(text):
	for i in range(0,$SupCombosItemList.get_item_count()):
		if text==$SupCombosItemList.get_item_text(i):
			return
#	$CompCombosItemList.add_item(text)
	_satisfaction_calculator_copy.set_supplementary_combo(text,{})
	update_satisfaction_calculator_data()


func _on_AddSupCombo_pressed():
	$NewSupComboAcceptDialog.show_modal(true)


func _on_DeleteOptionOfSupCombo_pressed():
	var select:Array = $OptionsOfSupComboItemList.get_selected_items()
	var select_combo:Array = $SupCombosItemList.get_selected_items()
	if false == select.empty() and false == select_combo.empty():
#		$OptionsOfCompComboItemList.remove_item(select[0])
		var item_to_erase:String = $OptionsOfSupComboItemList.get_item_text(select[0])
		var combo_of_items_to_erase:String = $SupCombosItemList.get_item_text(select_combo[0])
		_satisfaction_calculator_copy.erase_option_in_sup_combo(combo_of_items_to_erase,item_to_erase)
		update_satisfaction_calculator_data()
		$SupCombosItemList.select(select_combo[0])
		var options:Array = _satisfaction_calculator_copy.get_options_from_supplementary_combo(combo_of_items_to_erase)
		$OptionsOfSupComboItemList.clear()
		for option in options:
			$OptionsOfSupComboItemList.add_item(option)


func _on_AddOptionOfSupCombo_pressed():
	$NewOptionOfSupComboAcceptDialog.show_modal(true)


func _on_NewOptionOfSupComboAcceptDialog_ok_pressed(text):
	for i in range(0,$OptionsOfSupComboItemList.get_item_count()):
		if text==$OptionsOfSupComboItemList.get_item_text(i):
			return
	$OptionsOfSupComboItemList.add_item(text)
	
	var select_combo:Array = $SupCombosItemList.get_selected_items()
	if false == select_combo.empty():
		var combo_of_options_to_add:String = $SupCombosItemList.get_item_text(select_combo[0])
		_satisfaction_calculator_copy.add_option_in_sup_combo(combo_of_options_to_add,text)

		update_satisfaction_calculator_data()
		$SupCombosItemList.select(select_combo[0])
		var options:Array = _satisfaction_calculator_copy.get_options_from_supplementary_combo(combo_of_options_to_add)
		$OptionsOfSupComboItemList.clear()
		for option in options:
			$OptionsOfSupComboItemList.add_item(option)


func _on_WeightOfOptionOfSupComboSpinBox_value_changed(value):
	var select_combo:Array = $SupCombosItemList.get_selected_items()
	var select_option:Array = $OptionsOfSupComboItemList.get_selected_items()
	if false == select_combo.empty() and false == select_option.empty():
		var combo_text:String = $SupCombosItemList.get_item_text(select_combo[0])
		var option_text:String = $OptionsOfSupComboItemList.get_item_text(select_option[0])
		_satisfaction_calculator_copy.set_weight_of_option_in_sup_combo(combo_text,option_text,value)
		update_satisfaction_calculator_data()
		$SupCombosItemList.select(select_combo[0])
		$OptionsOfSupComboItemList.select(select_option[0])
#		var value_debug:float = _satisfaction_calculator_copy.get_weight_of_option_in_sup_combo(combo_text,option_text)


func _on_SaveButton_pressed():
	var saved_dict = self._satisfaction_calculator_copy.save()
	
	var satisfaction_calculator_new:SatisfactionCalculator = SatisfactionCalculator.new()
	satisfaction_calculator_new.from_dict(saved_dict)
	
	var saved_dict_new = satisfaction_calculator_new.save()

#	print("Original:")
#	print(saved_dict)
#	print("Nuevo:")
#	print(saved_dict_new)

	var save_game = File.new()
	save_game.open("user://savegame.save", File.WRITE)
	var json:String = to_json(saved_dict_new)
#	print("JSON")
#	print(json)
	save_game.store_line(json)
	save_game.close()
	
	var save_game_new = File.new()
	if not save_game_new.file_exists("user://savegame.save"):
		return
	save_game_new.open("user://savegame.save", File.READ)
	var loaded_string:String = ""
#	while save_game_new.get_position() < save_game_new.get_len():
#		# Get the saved dictionary from the next line in the save file
#		loaded_string += save_game_new.get_line()
#
	loaded_string = save_game_new.get_as_text()

	var loaded_dict:Dictionary = parse_json(loaded_string)
	print("loaded_dict:")
	print(loaded_dict)
	save_game_new.close()
	
#	pass # Replace with function body.

