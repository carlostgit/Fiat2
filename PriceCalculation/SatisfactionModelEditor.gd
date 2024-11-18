
extends Control


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")
var _satisfaction_calculator_ref:SatisfactionCalculator = null
#var _satisfaction_calculator_copy:SatisfactionCalculator = null

var name_of_model:String = ""

export(Texture) var _product_texture = preload("res://PriceCalculation/link.png")

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _update_satisfaction_calculator_data():
	
	$NameOfModelLabel.set_text(self.name_of_model)
	
	var satisf_calc:SatisfactionCalculator = _satisfaction_calculator_ref
	
	$OptionsItemList.clear()
	for option in satisf_calc.get_options():
		$OptionsItemList.add_item(option)
	
	$ProductsItemList.clear()
	for product in satisf_calc.get_products():
		$ProductsItemList.add_item(product)
	
	
	$CompCombosItemList.clear()
	for comp_combo in satisf_calc.get_complementary_combos():
		$CompCombosItemList.add_item(comp_combo)

	$OptionsOfCompComboItemList.hide()
		
	$SupCombosItemList.clear()
	for sup_combo in satisf_calc.get_supplementary_combos():
		$SupCombosItemList.add_item(sup_combo)
	
	$OptionsOfSupComboItemList.hide()
	$WeightOfOptionOfSupComboSpinBox.hide()
	
	$SatisfCurvesForOptions/SatisfCurvesItemList.clear()	
	for satisf_curve in satisf_calc.get_satisfaction_curves_of_options():
		$SatisfCurvesForOptions/SatisfCurvesItemList.add_item(satisf_curve)	

	$SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.clear()
	for satisf_curve in satisf_calc.get_satisfaction_curves_of_complementary_combos():
		$SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.add_item(satisf_curve)	
	
	$SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.clear()
	for satisf_curve in satisf_calc.get_satisfaction_curves_of_supplementary_combos():
		$SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.add_item(satisf_curve)

#	$SatisfCurvesForOptions/MaxSatisfSpinBox.disconnect("changed",self,"_on_MaxSatisfSpinBox_value_changed")
#	$SatisfCurvesForOptions/MaxSatisfSpinBox.set_value(0)
#	$SatisfCurvesForOptions/MaxSatisfSpinBox.connect("changed",self,"_on_MaxSatisfSpinBox_value_changed")
#
#	$SatisfCurvesForOptions/PrefAt0SpinBox.disconnect("changed",self,"_on_MaxSatisfSpinBox_value_changed")
#	$SatisfCurvesForOptions/PrefAt0SpinBox.set_value(0)
#	$SatisfCurvesForOptions/PrefAt0SpinBox.connect("changed",self,"_on_MaxSatisfSpinBox_value_changed")

	$SatisfCurvesForOptions/MaxSatisfSpinBox.hide()
	$SatisfCurvesForOptions/PrefAt0SpinBox.hide()
	$SatisfCurvesForCompCombos/MaxSatisfForCompCombosSpinBox.hide()
	$SatisfCurvesForCompCombos/PrefAt0ForCompCombosSpinBox.hide()
	$SatisfCurvesForSupCombos/MaxSatisfForSupCombosSpinBox.hide()
	$SatisfCurvesForSupCombos/PrefAt0ForSupCombosSpinBox.hide()
	

func set_satisfaction_calculator_ref(satisf_calculator_arg):
	_satisfaction_calculator_ref = satisf_calculator_arg
	self.name_of_model = satisf_calculator_arg.get_name()
	
#	He creado un _init en SatisfactionCalculator, que hace de constructor de copia
#	_satisfaction_calculator_copy = SatisfactionCalculator.new(satisf_calculator_arg)

	_update_satisfaction_calculator_data()
	
func get_satisfaction_calculator_ref():
	return _satisfaction_calculator_ref
#	name_output = self.name_of_model

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
	if (_satisfaction_calculator_ref):
		var max_satisf = _satisfaction_calculator_ref.get_option_max_satisfaction(option_arg)
		$SatisfCurvesForOptions/MaxSatisfSpinBox.set_value(max_satisf)
		var pref_at_0 = _satisfaction_calculator_ref.get_option_preference_at_0(option_arg)
		$SatisfCurvesForOptions/PrefAt0SpinBox.set_value(pref_at_0)
		$SatisfCurvesForOptions/MaxSatisfSpinBox.show()
		$SatisfCurvesForOptions/PrefAt0SpinBox.show()
		
		var satisf_curve = _satisfaction_calculator_ref.get_satisfaction_curve_of_option(option_arg)		
		draw_satisfaction_curve(satisf_curve,"satisf. "+option_arg)


func show_data_of_comp_combo(comp_combo_arg:String):	
	if (_satisfaction_calculator_ref):
		var max_satisf = _satisfaction_calculator_ref.get_complementary_combo_max_satisfaction(comp_combo_arg)		
		$SatisfCurvesForCompCombos/MaxSatisfForCompCombosSpinBox.set_value(max_satisf)
		var pref_at_0 = _satisfaction_calculator_ref.get_complementary_combo_preference_at_0(comp_combo_arg)
		$SatisfCurvesForCompCombos/PrefAt0ForCompCombosSpinBox.set_value(pref_at_0)
		$SatisfCurvesForCompCombos/MaxSatisfForCompCombosSpinBox.show()
		$SatisfCurvesForCompCombos/PrefAt0ForCompCombosSpinBox.show()

		var satisf_curve = _satisfaction_calculator_ref.get_satisfaction_curve_of_comp_combo(comp_combo_arg)		
		draw_satisfaction_curve(satisf_curve, "satisf. "+comp_combo_arg)

func show_data_of_sup_combo(sup_combo_arg:String):	
	if (_satisfaction_calculator_ref):
		var max_satisf = _satisfaction_calculator_ref.get_supplementary_combo_max_satisfaction(sup_combo_arg)
		$SatisfCurvesForSupCombos/MaxSatisfForSupCombosSpinBox.set_value(max_satisf)
		var pref_at_0 = _satisfaction_calculator_ref.get_supplementary_combo_preference_at_0(sup_combo_arg)
		$SatisfCurvesForSupCombos/PrefAt0ForSupCombosSpinBox.set_value(pref_at_0)
		$SatisfCurvesForSupCombos/MaxSatisfForSupCombosSpinBox.show()
		$SatisfCurvesForSupCombos/PrefAt0ForSupCombosSpinBox.show()
		
		var satisf_curve = _satisfaction_calculator_ref.get_satisfaction_curve_of_sup_combo(sup_combo_arg)		
		draw_satisfaction_curve(satisf_curve, "satisf. "+sup_combo_arg)

func _on_MaxSatisfSpinBox_value_changed(value):
	if value >= 0:
		var max_satisf = value
		var selected_items = $SatisfCurvesForOptions/SatisfCurvesItemList.get_selected_items()
		if (selected_items.size()):
			var first_select_index = selected_items[0]
			var option = $SatisfCurvesForOptions/SatisfCurvesItemList.get_item_text(first_select_index)
			var option_satisf_curve_dict = _satisfaction_calculator_ref.get_option_satisf_curve_dict()
			if (option_satisf_curve_dict.has(option)):
				var satisf_curve = option_satisf_curve_dict.get(option)
				satisf_curve.set_maximum_satisf(value)
				$Plotter.update()
				_satisfaction_calculator_ref.set_satisfaction_curve(option,satisf_curve)
#				print(_satisfaction_calculator_copy.get_option_max_satisfaction(option))


func _on_PrefAt0SpinBox_value_changed(value):
	if value >= 0:
		var max_satisf = value
		var selected_items = $SatisfCurvesForOptions/SatisfCurvesItemList.get_selected_items()
		if (selected_items.size()):
			var first_select_index = selected_items[0]
			var option = $SatisfCurvesForOptions/SatisfCurvesItemList.get_item_text(first_select_index)
			var option_satisf_curve_dict = _satisfaction_calculator_ref.get_option_satisf_curve_dict()
			if (option_satisf_curve_dict.has(option)):
				var satisf_curve = option_satisf_curve_dict.get(option)				
				satisf_curve.set_preference_at_0(value)
				$Plotter.update()
				_satisfaction_calculator_ref.set_satisfaction_curve(option,satisf_curve)

func _on_MaxSatisfForCompCombosSpinBox_value_changed(value):
	if value >= 0:
		var max_satisf = value
		var selected_items = $SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.get_selected_items()
		if (selected_items.size()):
			var first_select_index = selected_items[0]
			var option = $SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.get_item_text(first_select_index)
			var option_satisf_curve_dict = _satisfaction_calculator_ref.get_complementary_combo_satisf_curve_dict()
			if (option_satisf_curve_dict.has(option)):
				var satisf_curve = option_satisf_curve_dict.get(option)
				satisf_curve.set_maximum_satisf(value)
				$Plotter.update()
				_satisfaction_calculator_ref.set_satisfaction_curve_for_complementary_combo(option,satisf_curve)


func _on_PrefAt0ForCompCombosSpinBox_value_changed(value):
	if value >= 0:
		var max_satisf = value
		var selected_items = $SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.get_selected_items()
		if (selected_items.size()):
			var first_select_index = selected_items[0]
			var option = $SatisfCurvesForCompCombos/SatisfCurvesForCompCombosItemList.get_item_text(first_select_index)
			var option_satisf_curve_dict = _satisfaction_calculator_ref.get_complementary_combo_satisf_curve_dict()
			if (option_satisf_curve_dict.has(option)):
				var satisf_curve = option_satisf_curve_dict.get(option)				
				satisf_curve.set_preference_at_0(value)
				$Plotter.update()	
				_satisfaction_calculator_ref.set_satisfaction_curve_for_complementary_combo(option,satisf_curve)


func _on_MaxSatisfForSupCombosSpinBox_value_changed(value):
	if value >= 0:
		var max_satisf = value
		var selected_items = $SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.get_selected_items()
		if (selected_items.size()):
			var first_select_index = selected_items[0]
			var option = $SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.get_item_text(first_select_index)
			var option_satisf_curve_dict = _satisfaction_calculator_ref.get_supplementary_combo_satisf_curve_dict()
			if (option_satisf_curve_dict.has(option)):
				var satisf_curve = option_satisf_curve_dict.get(option)
				satisf_curve.set_maximum_satisf(value)
				$Plotter.update()	
				_satisfaction_calculator_ref.set_satisfaction_curve_for_supplementary_combo(option,satisf_curve)

func _on_PrefAt0ForSupCombosSpinBox_value_changed(value):
	if value >= 0:
		var max_satisf = value
		var selected_items = $SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.get_selected_items()
		if (selected_items.size()):
			var first_select_index = selected_items[0]
			var option = $SatisfCurvesForSupCombos/SatisfCurvesForSupCombosItemList.get_item_text(first_select_index)
			var option_satisf_curve_dict = _satisfaction_calculator_ref.get_supplementary_combo_satisf_curve_dict()
			if (option_satisf_curve_dict.has(option)):
				var satisf_curve = option_satisf_curve_dict.get(option)				
				satisf_curve.set_preference_at_0(value)
				$Plotter.update()	
				_satisfaction_calculator_ref.set_satisfaction_curve_for_supplementary_combo(option,satisf_curve)


func _on_XMaxSpinBox_value_changed(value):
	$Plotter.set_max_x_axis_value(value)

func _on_YMaxSpinBox_value_changed(value):
	$Plotter.set_max_y_axis_value(value)

func _on_CompCombosItemList_item_selected(index):
	var comp_combo:String = $CompCombosItemList.get_item_text(index)
	var options:Array = _satisfaction_calculator_ref.get_options_from_complementary_combo(comp_combo)
	$OptionsOfCompComboItemList.clear()
	for option in options:
		$OptionsOfCompComboItemList.add_item(option)
		
	if index>= 0:
		$OptionsOfCompComboItemList.show()
	else:
		$OptionsOfCompComboItemList.hide()
	
func _on_SupCombosItemList_item_selected(index):
	var sup_combo:String = $SupCombosItemList.get_item_text(index)
	var options:Array = _satisfaction_calculator_ref.get_options_from_supplementary_combo(sup_combo)
	$OptionsOfSupComboItemList.clear()
	for option in options:
		$OptionsOfSupComboItemList.add_item(option)		
#		get_weighted_options_from_supplementary_combo

	if index>= 0:
		$OptionsOfSupComboItemList.show()
	else:
		$OptionsOfSupComboItemList.hide()
		

func _on_OptionsOfSupComboItemList_item_selected(index):	
	var option:String = $OptionsOfSupComboItemList.get_item_text(index)
	var selected_combos_indexes:PoolIntArray = $SupCombosItemList.get_selected_items()
	if false==selected_combos_indexes.empty():
		var selected_combo_index:int = selected_combos_indexes[0]
		var comp_combo:String = $SupCombosItemList.get_item_text(selected_combo_index)
		var weighted_options:Dictionary = _satisfaction_calculator_ref.get_weighted_options_from_supplementary_combo(comp_combo)
		if weighted_options.has(option):
			var weight:float = weighted_options[option]
			$WeightOfOptionOfSupComboSpinBox.set_value(weight)
	
	if index>= 0:
		$WeightOfOptionOfSupComboSpinBox.show()

func _on_OptionsItemList_nothing_selected():
	$DeleteOption.set_disabled(true) 
	
func _on_OptionsItemList_item_selected(index):
#	Desactivo el botón de borrar
	$DeleteOption.set_disabled(false)
	
#	Muestro el produto asociado a la opción
	show_product_linked_to_option(index)

#	Muestro el produto asociado a la opción	
func show_product_linked_to_option(option_index:int):
	var option:String = $OptionsItemList.get_item_text(option_index)	
	var option_product_dict:Dictionary = _satisfaction_calculator_ref.get_option_product_dict()
	if option_product_dict.has(option):
		var product:String = option_product_dict[option]
		for i in $ProductsItemList.get_item_count():
			if product == $ProductsItemList.get_item_text(i):
#				$ProductsItemList.select(i)
#				$ProductsItemList.set_item_custom_bg_color(i,Color(1,0,0))
				$ProductsItemList.set_item_icon(i,_product_texture)
			else:
				$ProductsItemList.set_item_icon(i,null)

func _on_DeleteOption_pressed():
	var select:Array = $OptionsItemList.get_selected_items()
	if false == select.empty():
#		$OptionsItemList.remove_item(select[0])
		var item_to_erase:String = $OptionsItemList.get_item_text(select[0])
		_satisfaction_calculator_ref.erase_option(item_to_erase)
		_update_satisfaction_calculator_data()
	
func _on_AddOption_pressed():
	$NewOptionAcceptDialog.show_modal(true)

func _on_NewOptionAcceptDialog_ok_pressed(text):
	for i in range(0,$OptionsItemList.get_item_count()):
		if text==$OptionsItemList.get_item_text(i):
			return
	_satisfaction_calculator_ref.add_option(text)
	_update_satisfaction_calculator_data()

func _on_DeleteCompCombo_pressed():
	var select:Array = $CompCombosItemList.get_selected_items()
	if false == select.empty():
		var item_to_erase:String = $CompCombosItemList.get_item_text(select[0])
		_satisfaction_calculator_ref.erase_complementary_combo(item_to_erase)
		_update_satisfaction_calculator_data()
		$OptionsOfCompComboItemList.clear()

func _on_AddCompCombo_pressed():
	$NewCompComboAcceptDialog.show_modal(true)


func _on_NewCompComboAcceptDialog_ok_pressed(text):
	for i in range(0,$CompCombosItemList.get_item_count()):
		if text==$CompCombosItemList.get_item_text(i):
			return
#	$CompCombosItemList.add_item(text)
	_satisfaction_calculator_ref.set_complementary_combo(text,[])
	_update_satisfaction_calculator_data()

func _on_DeleteOptionOfCompCombo_pressed():
	var select:Array = $OptionsOfCompComboItemList.get_selected_items()
	var select_combo:Array = $CompCombosItemList.get_selected_items()
	if false == select.empty() and false == select_combo.empty():
#		$OptionsOfCompComboItemList.remove_item(select[0])
		var item_to_erase:String = $OptionsOfCompComboItemList.get_item_text(select[0])
		var combo_of_items_to_erase:String = $CompCombosItemList.get_item_text(select_combo[0])
		_satisfaction_calculator_ref.erase_option_in_comp_combo(combo_of_items_to_erase,item_to_erase)
		_update_satisfaction_calculator_data()
		$CompCombosItemList.select(select_combo[0])
		var options:Array = _satisfaction_calculator_ref.get_options_from_complementary_combo(combo_of_items_to_erase)
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
		_satisfaction_calculator_ref.add_option_in_comp_combo(combo_of_options_to_add,text)

		_update_satisfaction_calculator_data()
		$CompCombosItemList.select(select_combo[0])
		var options:Array = _satisfaction_calculator_ref.get_options_from_complementary_combo(combo_of_options_to_add)
		$OptionsOfCompComboItemList.clear()
		for option in options:
			$OptionsOfCompComboItemList.add_item(option)
		

func _on_DeleteSupCombo_pressed():
	var select:Array = $SupCombosItemList.get_selected_items()
	if false == select.empty():
		var item_to_erase:String = $SupCombosItemList.get_item_text(select[0])
		_satisfaction_calculator_ref.erase_supplementary_combo(item_to_erase)
		_update_satisfaction_calculator_data()
		$OptionsOfSupComboItemList.clear()


func _on_NewSupComboAcceptDialog_ok_pressed(text):
	for i in range(0,$SupCombosItemList.get_item_count()):
		if text==$SupCombosItemList.get_item_text(i):
			return
#	$CompCombosItemList.add_item(text)
	_satisfaction_calculator_ref.set_supplementary_combo(text,{})
	_update_satisfaction_calculator_data()


func _on_AddSupCombo_pressed():
	$NewSupComboAcceptDialog.show_modal(true)


func _on_DeleteOptionOfSupCombo_pressed():
	var select:Array = $OptionsOfSupComboItemList.get_selected_items()
	var select_combo:Array = $SupCombosItemList.get_selected_items()
	if false == select.empty() and false == select_combo.empty():
#		$OptionsOfCompComboItemList.remove_item(select[0])
		var item_to_erase:String = $OptionsOfSupComboItemList.get_item_text(select[0])
		var combo_of_items_to_erase:String = $SupCombosItemList.get_item_text(select_combo[0])
		_satisfaction_calculator_ref.erase_option_in_sup_combo(combo_of_items_to_erase,item_to_erase)
		_update_satisfaction_calculator_data()
		$SupCombosItemList.select(select_combo[0])
		var options:Array = _satisfaction_calculator_ref.get_options_from_supplementary_combo(combo_of_items_to_erase)
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
		_satisfaction_calculator_ref.add_option_in_sup_combo(combo_of_options_to_add,text)

		_update_satisfaction_calculator_data()
		$SupCombosItemList.select(select_combo[0])
		var options:Array = _satisfaction_calculator_ref.get_options_from_supplementary_combo(combo_of_options_to_add)
		$OptionsOfSupComboItemList.clear()
		for option in options:
			$OptionsOfSupComboItemList.add_item(option)


func _on_WeightOfOptionOfSupComboSpinBox_value_changed(value):
	var select_combo:Array = $SupCombosItemList.get_selected_items()
	var select_option:Array = $OptionsOfSupComboItemList.get_selected_items()
	if false == select_combo.empty() and false == select_option.empty():
		var combo_text:String = $SupCombosItemList.get_item_text(select_combo[0])
		var option_text:String = $OptionsOfSupComboItemList.get_item_text(select_option[0])
		_satisfaction_calculator_ref.set_weight_of_option_in_sup_combo(combo_text,option_text,value)
#		update_satisfaction_calculator_data()
#		$SupCombosItemList.select(select_combo[0])
#		$OptionsOfSupComboItemList.select(select_option[0])
#		var value_debug:float = _satisfaction_calculator_copy.get_weight_of_option_in_sup_combo(combo_text,option_text)


func _on_SaveButton_pressed():
	save("user://satisf_calc_param_default.save")


func save(file_path_arg:String):
	var saved_dict = self._satisfaction_calculator_ref.save()
	var save_game = File.new()
#	var file_path = "user://"+file_name_arg
	save_game.open(file_path_arg, File.WRITE)
#	var json:String = to_json(saved_dict_new)
	var json:String = to_json(saved_dict)
	save_game.store_line(json)
	save_game.close()
	

func _on_LoadButton_pressed():
	$LoadFileDialog.popup()


func _on_LoadFileDialog_file_selected(path):
	var save_game_new = File.new()
	if not save_game_new.file_exists(path):
		return
	save_game_new.open(path, File.READ)
	var loaded_string:String = save_game_new.get_as_text()
	var loaded_dict:Dictionary = parse_json(loaded_string)
#	print("loaded_dict:")
#	print(loaded_dict)
	save_game_new.close()

	#TODO: ver por qué se ha roto lo de guardar y cargar escenarios muy simples
	var satisfaction_calculator_new:SatisfactionCalculator = SatisfactionCalculator.new()
	satisfaction_calculator_new.from_dict(loaded_dict)
	


	self._satisfaction_calculator_copy = satisfaction_calculator_new
	self._update_satisfaction_calculator_data()


func _on_SaveAsButton_pressed():
	$SaveAsFileDialog.popup()
	
	
func _on_SaveAsFileDialog_file_selected(path):
	save(path)
	




func _on_LinkButton_pressed():
	var selected_items = $OptionsItemList.get_selected_items()
	if (selected_items.size()):
		var first_select_index = selected_items[0]
		var option = $OptionsItemList.get_item_text(first_select_index)
	
		var selected_products = $ProductsItemList.get_selected_items()
		if (selected_products.size()):
			var first_product_select_index = selected_products[0]
			var product = $ProductsItemList.get_item_text(first_product_select_index)
		
			_satisfaction_calculator_ref.set_product_for_option(product,option)
			show_product_linked_to_option(first_select_index)


func _on_AddProductButton_pressed():
	$NewProductAcceptDialog.show_modal(true)


func _on_DeleteProductButton_pressed():
	var selected_items = $ProductsItemList.get_selected_items()
	if (selected_items.size()):
		var first_select_index = selected_items[0]
		var product = $ProductsItemList.get_item_text(first_select_index)
		_satisfaction_calculator_ref.remove_product(product)
		_update_satisfaction_calculator_data()

func _on_NewProductAcceptDialog_ok_pressed(text):
	for i in range(0,$ProductsItemList.get_item_count()):
		if text==$ProductsItemList.get_item_text(i):
			return
	_satisfaction_calculator_ref.add_product(text)
	_update_satisfaction_calculator_data()


func _on_SatisfactionModelEditor_gui_input(event):
	if event as InputEventScreenDrag:
		var input_event_screen_drag:InputEventScreenDrag = event as InputEventScreenDrag
		self.set_position(self.get_position()+input_event_screen_drag.relative)
