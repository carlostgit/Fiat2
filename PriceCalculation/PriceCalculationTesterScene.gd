
extends Control


const SatisfactionModelEditorRes = preload("res://PriceCalculation/SatisfactionModelEditor.tscn")
const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")
const SatisfactionCurve = preload("res://PriceCalculation/SatisfactionCurve.gd")


var _name_satisf_calc_dic:Dictionary = {}	



# Declare member variables here. Examples:
# var a = 2
# var b = "text"

# Called when the node enters the scene tree for the first time.
func _ready():
	
	var name_of_satisf = "prueba satisfaction model"
	var satisfaction_calculator:SatisfactionCalculator = _create_default_satisfaction_model(name_of_satisf)
	_name_satisf_calc_dic[name_of_satisf] = satisfaction_calculator
	#$SatisfactionModelEditor.set_satisfaction_calculator_ref(satisfaction_calculator)
	#$TradeTesterScene.set_satisfaction_calculator_ref(satisfaction_calculator)
	#$MarketTesterScene.set_satisfaction_calculator_ref(satisfaction_calculator)
	#$MarketTesterScene.init_default_example(satisfaction_calculator)
	_new_model_activated(name_of_satisf)
	update_item_list()

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

	
func update_item_list():

	$SatisfactionModelItemList.clear()
	for name in _name_satisf_calc_dic.keys():
		$SatisfactionModelItemList.add_item(name)

	
func _create_default_satisfaction_model(name_arg:String="default_satisf_calc") -> Node:
	
	var satisfaction_calculator:SatisfactionCalculator = SatisfactionCalculator.new()

	satisfaction_calculator.set_name(name_arg)

	var options_array:Array = ["candy_savings","chocolate_savings","bill_savings",
						"candy_consumption","chocolate_consumption","bill_consumption",
						]

	satisfaction_calculator.set_options(options_array)
	
	var option_product_dict:Dictionary = { "candy_savings": "candy",
									"candy_consumption": "candy",
									"chocolate_savings": "chocolate",
									"chocolate_consumption": "chocolate",
									"bill_savings": "bill",
									"bill_consumption": "bill",
									}

	
	var param_preference_at_0_for_candy_consu = 1.0
	var maximum_satisf_for_candy_consu = 10.0
	var satisfaction_curve_for_candy_consu:SatisfactionCurve = SatisfactionCurve.new(param_preference_at_0_for_candy_consu, maximum_satisf_for_candy_consu)
	satisfaction_calculator.set_satisfaction_curve("candy_consumption",satisfaction_curve_for_candy_consu)

	var param_preference_at_0_for_chocolate_consu = 1.0
	var maximum_satisf_for_chocolate_consu = 10.0
	var satisfaction_curve_for_chocolate_consu:SatisfactionCurve = SatisfactionCurve.new(param_preference_at_0_for_chocolate_consu, maximum_satisf_for_chocolate_consu)
	satisfaction_calculator.set_satisfaction_curve("chocolate_consumption",satisfaction_curve_for_chocolate_consu)
	
	var param_preference_at_0_for_nut_consu = 1.0
	var maximum_satisf_for_nut_consu = 10.0
	var satisfaction_curve_for_nut_consu:SatisfactionCurve = SatisfactionCurve.new(param_preference_at_0_for_nut_consu, maximum_satisf_for_nut_consu)
	satisfaction_calculator.set_satisfaction_curve("bill_consumption",satisfaction_curve_for_nut_consu)
	
	#var param_preference_at_0_for_sweets = 1.0
	#var maximum_satisf_for_sweets = 10.0
	#var satisfaction_curve_for_sweets:SatisfactionCurve = SatisfactionCurve.new(param_preference_at_0_for_sweets, maximum_satisf_for_sweets)
	#satisfaction_calculator.set_complementary_combo("sweets_consumption",["candy_consumption","chocolate_consumption"])
	#satisfaction_calculator.set_satisfaction_curve_for_complementary_combo("sweets_consumption",satisfaction_curve_for_sweets)
	
	var param_preference_at_0_for_candy_sav = 1.0
	var maximum_satisf_for_candy_sav = 10.0
	var satisfaction_curve_for_candy_sav:SatisfactionCurve = SatisfactionCurve.new(param_preference_at_0_for_candy_sav, maximum_satisf_for_candy_sav)
	satisfaction_calculator.set_satisfaction_curve("candy_savings",satisfaction_curve_for_candy_sav)

	var param_preference_at_0_for_chocolate_sav = 1.0
	var maximum_satisf_for_chocolate_sav = 10.0
	var satisfaction_curve_for_chocolate_sav:SatisfactionCurve = SatisfactionCurve.new(param_preference_at_0_for_chocolate_sav, maximum_satisf_for_chocolate_sav)
	satisfaction_calculator.set_satisfaction_curve("chocolate_savings",satisfaction_curve_for_chocolate_sav)	

	var param_preference_at_0_for_nut_sav = 1.0
	var maximum_satisf_for_nut_sav = 10.0
	var satisfaction_curve_for_nut_sav:SatisfactionCurve = SatisfactionCurve.new(param_preference_at_0_for_nut_sav, maximum_satisf_for_nut_sav)
	satisfaction_calculator.set_satisfaction_curve("bill_savings",satisfaction_curve_for_nut_sav)	

	
	satisfaction_calculator.set_option_product_dict(option_product_dict)
	
	return satisfaction_calculator


func _on_AddAcceptDialog_ok_pressed(text):
	for i in range(0,$SatisfactionModelItemList.get_item_count()):
		if text==$SatisfactionModelItemList.get_item_text(i):
			return
	_name_satisf_calc_dic[text] = _create_default_satisfaction_model(text)
	update_item_list()	


func _on_AddButton_pressed():
	$AddAcceptDialog.popup()
#	$AddAcceptDialog.show_modal(true)
	


func _on_EditButton_pressed():
#	var satisfactionModelEditor:SatisfactionModelEditorRes = SatisfactionModelEditorRes.instance()

	var selected_items = $SatisfactionModelItemList.get_selected_items()
	if (selected_items.size()):
		
		var old_satisf
#		var old_name=""
		old_satisf = $SatisfactionModelEditor.get_satisfaction_calculator_ref()
		_name_satisf_calc_dic[old_satisf.get_name()]=old_satisf
		
		var first_select_index = selected_items[0]
		var name = $SatisfactionModelItemList.get_item_text(first_select_index)
		var satisf_calc:SatisfactionCalculator = _name_satisf_calc_dic[name]
		$SatisfactionModelEditor.set_satisfaction_calculator_ref(satisf_calc)
		
	$SatisfactionModelEditor.show()


func _on_RemoveButton_pressed():
	var selected_items = $SatisfactionModelItemList.get_selected_items()
	if (selected_items.size()):
		var first_select_index = selected_items[0]
		var name = $SatisfactionModelItemList.get_item_text(first_select_index)
		_name_satisf_calc_dic.erase(name)
		self.update_item_list()

func _on_SaveAsButton_pressed():
	$SaveAsFileDialog.popup()


func _on_SaveAsFileDialog_file_selected(path):
	
	var name_satisf_mod_save_dict:Dictionary = {}
	for name_of_model in _name_satisf_calc_dic.keys():
		var satisf_mod = _name_satisf_calc_dic[name_of_model]
		var stisf_mod_dict:Dictionary = satisf_mod.to_dict()
		name_satisf_mod_save_dict[name_of_model] = stisf_mod_dict
		
	var save_game = File.new()
#	var file_path = "user://"+file_name_arg
	save_game.open(path, File.WRITE)
#	var json:String = to_json(saved_dict_new)
	var json:String = to_json(name_satisf_mod_save_dict)
	save_game.store_line(json)
	save_game.close()


func _on_LoadFileDialog_file_selected(path):
	var save_game_new = File.new()
	if not save_game_new.file_exists(path):
		return
	
	save_game_new.open(path, File.READ)
	var loaded_string:String = save_game_new.get_as_text()
	var loaded_dict:Dictionary = parse_json(loaded_string)
	save_game_new.close()

	for name_model in loaded_dict.keys():
		var satisf_mod_dict:Dictionary = loaded_dict[name_model]
		var satisfaction_calculator_new:SatisfactionCalculator = SatisfactionCalculator.new()
		satisfaction_calculator_new.from_dict(satisf_mod_dict)	
		_name_satisf_calc_dic[name_model] = satisfaction_calculator_new
	
	update_item_list()


func _on_LoadButton_pressed():
	$LoadFileDialog.popup()

func _on_HideButton_pressed():
	$SatisfactionModelEditor.hide()
	

func _on_TradeTesterButton_pressed():
	var selected_items = $SatisfactionModelItemList.get_selected_items()
	if (selected_items.size()):
		var first_select_index = selected_items[0]
		var name = $SatisfactionModelItemList.get_item_text(first_select_index)
		var satisf_calc:SatisfactionCalculator = _name_satisf_calc_dic[name]
		$TradeTesterScene.set_satisfaction_calculator_ref(satisf_calc)
	
	$TradeTesterScene.show()
		

func _on_HideTradeTesterButton_pressed():
	$TradeTesterScene.hide()

func _on_ShowPricesEditorButton_pressed():
	$PricesEditor.show()

func _on_HidePricesEditorButton_pressed():
	$PricesEditor.hide()

func _on_ShowMarketTesterButton_pressed():
	$MarketTesterScene.show()

func _on_HideMarketTesterButton_pressed():
	$MarketTesterScene.hide()


func _new_model_activated(modelSelected):
	if _name_satisf_calc_dic.has(modelSelected):
		$ActiveModelLabel.text = modelSelected
		var satisf_model = _name_satisf_calc_dic[modelSelected]
		$SatisfactionModelEditor.set_satisfaction_calculator_ref(satisf_model)
		$TradeTesterScene.set_satisfaction_calculator_ref(satisf_model)
		#TODO: Hacer que se puedan guardar datos sobre la cantidad de personas y sus posesiones, en MarketTesterScene
		$MarketTesterScene.set_satisfaction_calculator_ref(satisf_model)
		$MarketTesterScene.init_default_example(satisf_model)
		
	else:
		$ActiveModelLabel.text = "Error. Not found model: " +modelSelected
		

func _on_SatisfactionModelItemList_item_activated(index):
	var model_selected = $SatisfactionModelItemList.get_item_text(index)	
	$ActiveModelLabel.text = model_selected
	_new_model_activated(model_selected)
	
	pass # Replace with function body.
