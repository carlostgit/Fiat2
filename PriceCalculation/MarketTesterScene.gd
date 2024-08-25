extends Control


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

const Market = preload("res://PriceCalculation/Market.gd")

const PriceCalculatorGDNBind = preload("res://PriceCalculatorGDNBind.gdns")
var _priceCalculatorGDNBind:PriceCalculatorGDNBind = null


var _market:Node = null

#var _default_satisf_calc = null

var _satisfaction_calculator_ref:Node = null
var _name_of_model:String = ""

# Called when the node enters the scene tree for the first time.
func _ready():
	
	_market = Market.new()
	update_person_list()
	
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func set_satisfaction_calculator_ref(satisf_calculator_arg):
	_satisfaction_calculator_ref = satisf_calculator_arg
	self._name_of_model = _satisfaction_calculator_ref.get_name()
	$SatisfactionModelNameLabel.set_text(self._name_of_model)

func update_person_list():
	$PersonsItemList.clear()
	for person in _market.get_persons():
		$PersonsItemList.add_item(person)
	

func init_default_example(satisf_calc_arg:Node):
	_market.init_default_example(satisf_calc_arg)
	_satisfaction_calculator_ref = satisf_calc_arg
	update_person_list()


func _on_PersonsItemList_item_selected(index):
	var person:String = $PersonsItemList.get_item_text(index)
	$OwnedProductsItemList.clear()
	for product in _market.get_owned_products(person):
		$OwnedProductsItemList.add_item(product)
	$AmountOwnedSpinBox.hide()
	
#	_market.calculate_value_of_owned()
	_update_value_of_owned(person)


func _on_OwnedProductsItemList_item_selected(index):
	var selected_persons:Array = $PersonsItemList.get_selected_items()
	if selected_persons.size()>0:
		var selected_person_index:int = selected_persons.front()
		var person:String = $PersonsItemList.get_item_text(selected_person_index)
		var selected_products:Array = $OwnedProductsItemList.get_selected_items()
		if selected_products.size()>0:
			var selected_product_index:int = selected_products.front()
			var product:String = $OwnedProductsItemList.get_item_text(selected_product_index)
			var own_products_dict = _market.get_owned_products(person)
			if own_products_dict.has(product):
				var amount = own_products_dict[product]
				$AmountOwnedSpinBox.set_value(amount)
			var traded_products_dict:Dictionary = _market.get_traded_products(person)
			if traded_products_dict.has(product):
				var amount = traded_products_dict[product]
				$TradeLabel.set_text(str(amount))
		$AmountOwnedSpinBox.show()


#func update_aumount_owned_spinbox(person_arg:String, product_arg:String):
#	var own_products_dict = _market.get_owned_products(person_arg)
#	if own_products_dict.has(product_arg):
#		var amount = own_products_dict[product_arg]
#		$AmountOwnedSpinBox.set_value(amount)
#


func _update_amount_traded_label(person_arg:String, product_arg:String):
	var traded_products_dict:Dictionary = _market.get_traded_products(person_arg)
	if traded_products_dict.has(product_arg):
		var amount = traded_products_dict[product_arg]
		$TradeLabel.set_text(str(amount))


func get_selected_person_and_product():
	var person_product_dict:Dictionary = {}
	var selected_persons:Array = $PersonsItemList.get_selected_items()
	if selected_persons.size()>0:
		var selected_person_index:int = selected_persons.front()
		var person:String = $PersonsItemList.get_item_text(selected_person_index)
#		person_output_arg = person
		person_product_dict["person"] = person
		var selected_products:Array = $OwnedProductsItemList.get_selected_items()
		if selected_products.size()>0:
			var selected_product_index:int = selected_products.front()
			var product:String = $OwnedProductsItemList.get_item_text(selected_product_index)
#			product_output_arg = product
			person_product_dict["product"] = product
	return person_product_dict

func _on_AmountOwnedSpinBox_value_changed(value):
	var person_product_dict:Dictionary = {}
	person_product_dict = get_selected_person_and_product()
	if person_product_dict.has("person") and person_product_dict.has("product"):
		var person = person_product_dict["person"]
		var product = person_product_dict["product"]
		_market.set_amount_of_product(person,product,value)


func _on_CalculateTradeButton_pressed():
	_market.calculate_trades_with_current_best_combinations()
	var person_product_dict:Dictionary = get_selected_person_and_product()
	if person_product_dict.has("person") and person_product_dict.has("product"):
		var person:String = person_product_dict["person"]
		var product:String = person_product_dict["product"]
	#	update_aumount_owned_spinbox(person,product)
		_update_amount_traded_label(person,product)


func _on_CalculateValueButton_pressed():
	#_market.calculate_value_of_owned()	
	var person_product_dict:Dictionary = get_selected_person_and_product()
	if person_product_dict.has("person"):
		var person:String = person_product_dict["person"]
		_update_value_of_owned(person)
	
func _update_value_of_owned(person_arg:String):
	var value:float = _market.get_value_of_owned(person_arg)
	$ValueOfOwnedLabel.set_text(str(value))
	
	


func _on_SumTradeButton_pressed():
	_market.calculate_sum_of_trade()
	var sum_product_combidict:Dictionary = _market.get_sum_of_trade()
	$SumOfTradeItemList.clear()
	for product in sum_product_combidict.keys():
		var amount:float = sum_product_combidict[product]
		$SumOfTradeItemList.add_item(product+" "+str(amount))
	pass # Replace with function body.


#func _on_SumOfTradeItemList_item_selected(index):
#	var product:String = $SumOfTradeItemList.get_item_text(index)
#	var sum_product_combidict:Dictionary = _market.get_sum_of_trade()
#	if sum_product_combidict.has(product):
#		var amount:float = sum_product_combidict[product]
#		$AmountSumOfTradeLabel.set_text(str(amount))


func _on_NextStepButton_pressed():
	#_market.change_prices_step(0.1)
	_market._change_prices(0.1)
	


func _on_CalculateNewPricesButton_pressed():
#	
#
	TimeMeasurement.reset()

	_market.calculate_new_prices()
	$PricesItemList.clear()
	for product in Prices.get_products():
		var price:float = Prices.get_price_of_product(product)
		var product_price_text:String = product+" "+str(price)
		$PricesItemList.add_item(product_price_text)
#	var product_pricearray = _market.get_last_price_calculation_prices()
	var product_pricearray = _market.get_all_price_calculation_prices()
	_draw_product_pricearray(product_pricearray)
	var price_change_step_array:Array = _market.get_all_price_change_step()
	_draw_price_change_step_array(price_change_step_array)
	
	var product_pricetops = _market.get_product_price_tops()
	var product_pricebottoms = _market.get_product_price_bottoms()
	_draw_product_price_tops_bottoms(product_pricetops,product_pricebottoms)
	
	
	#var elapsed = TimeMeasurement.get_average_time("draw_test5_simple_continuity")
	var elapsed = TimeMeasurement.get_total_time("calculate_best_combidict_simple_with_continuity")
	var num_calls = TimeMeasurement.get_num_measurements("calculate_best_combidict_simple_with_continuity")
	
	TimeMeasurement.print_info()

#	$CalcCostLabel.set_text("calculate_best_combidict_simple_with_continuity: "+ str(elapsed))
#	$CalcCostLabelExtraInfo.set_text("num calls:" +str(num_calls))

	
	
func _on_RemoveButton_pressed():
	var person_product_dict:Dictionary = {}
	var selected_persons:Array = $PersonsItemList.get_selected_items()
	if selected_persons.size()>0:
		var selected_person_index:int = selected_persons.front()
		var person:String = $PersonsItemList.get_item_text(selected_person_index)
		_market.remove_person(person)
		update_person_list()
	


func _on_AddButton_pressed():
	$AddPersonAcceptDialog.popup()
#	print("$AddPersonAcceptDialog.get_position()")
#	print($AddPersonAcceptDialog.get_position())
	$AddPersonAcceptDialog.set_position(self.get_position())


func _on_AddPersonAcceptDialog_ok_pressed(text):
	for i in range(0,$PersonsItemList.get_item_count()):
		if text==$PersonsItemList.get_item_text(i):
			return
	_market.add_person(text,_satisfaction_calculator_ref)
	self.update_person_list()


func _on_MarketTesterScene_gui_input(event):
	if event as InputEventScreenDrag:
		var input_event_screen_drag:InputEventScreenDrag = event as InputEventScreenDrag
		$MousePositionLabel.set_text(str(self.get_position()))
		self.set_position(self.get_position()+input_event_screen_drag.relative)

func _draw_price_change_step_array(price_change_step_array:Array):
	var param_group_id = 5
	var red = 1
	var green = 1
	var blue = 1
	var color:Color = Color(red,green,blue)
	
	var price_array_vector2:Array = []
	var count:int = 0
	for price_change_step in price_change_step_array:
		price_array_vector2.append(Vector2(count,price_change_step))
		count += 1
	
	$Plotter.add_point_group(param_group_id, price_array_vector2, color, "price_change_step")
	

func _draw_product_pricearray(product_pricearray_arg:Dictionary):
	
#	$Plotter.set_max_x_axis_value(20)
#	$Plotter.set_max_y_axis_value(0.4)	
	
	var count:int = 0
	for product in product_pricearray_arg.keys(): 
		count+=1
#		var option_text:String = $OptionsItemList.get_item_text(option_idx)
		
		var price_array_vector2:Array = []
		var price_count:int = 0
		for price in product_pricearray_arg[product]:
			price_array_vector2.append(Vector2(price_count,price))
			price_count += 1
		
		var red = float(count)/5.0+0.2
		var green = float(count)/5.0+0.0
		var blue = float(-count)/5.0+1.0
		var color:Color = Color(red,green,blue)
		
		$Plotter.add_point_group(count, price_array_vector2, color, product)
	
func _draw_product_price_tops_bottoms(product_pricetops_arg:Dictionary,product_pricebottoms_arg:Dictionary):
	var count:int = 10
	for product in product_pricetops_arg.keys(): 
		count+=1
#		var option_text:String = $OptionsItemList.get_item_text(option_idx)
		
		var price_array_vector2:Array = []
		var price_count:int = 0
		for price in product_pricetops_arg[product]:
			price_array_vector2.append(Vector2(price_count,price))
			price_count += 1
		
#		var red = float(count)/2.0+0.8
#		var green = float(count)/2.0+0.0
#		var blue = float(-count)/2.0+1.0
##		var color:Color = Color(red,green,blue)
		var color:Color = Color(0,1,0,0.5)
				
		$Plotter.add_point_group(count, price_array_vector2, color, "tops_"+product)
	
	for product in product_pricebottoms_arg.keys(): 
		count+=1
#		var option_text:String = $OptionsItemList.get_item_text(option_idx)
		
		var price_array_vector2:Array = []
		var price_count:int = 0
		for price in product_pricebottoms_arg[product]:
			price_array_vector2.append(Vector2(price_count,price))
			price_count += 1
		
#		var red = float(count)/5.0+1.0
#		var green = float(count)/5.0+0.5
#		var blue = float(-count)/5.0+1.0
##		var color:Color = Color(red,green,blue)
		var color:Color = Color(1,0,0,0.5)
		
		if product == "candy":
			color = Color(0,1,1,0.5)
		
		$Plotter.add_point_group(count, price_array_vector2, color, "bottoms_"+product)
	
	
func _on_XMaxSpinBox_value_changed(value):
	$Plotter.set_max_x_axis_value(value)



func _on_YMaxSpinBox_value_changed(value):
	$Plotter.set_max_y_axis_value(value)	


func _on_XMinSpinBox_value_changed(value):
	$Plotter.set_min_x_axis_value(value)


func _on_YMinSpinBox_value_changed(value):
	$Plotter.set_min_y_axis_value(value)	


func _on_CalcNewPricesGDNatButton_pressed():
	#
	assert(""!="_on_CalcNewPricesGDNatButton_pressed")

	if (null==_priceCalculatorGDNBind):
		_priceCalculatorGDNBind = PriceCalculatorGDNBind.new()	

	if (null!=_priceCalculatorGDNBind):
				
			
		var gdn_input_dict:Dictionary = {}
		
#		Voy a ir rellenando gdn_input_dict
#		Relleno Prsons
		var persons:Array = _market.get_persons()
		gdn_input_dict["Persons"] = persons
		
		var products = PriceCalculationGlobals._products
		gdn_input_dict["Products"] = products
				
		#var options:Array =_satisfaction_calculator_ref.get_options_of_use("consumption")		
#		gdn_input_dict["Consumption"] = options
					
		var person_owned:Dictionary = {}
		for person in persons:
			var product_amount:Dictionary = _market.get_owned_products(person)
			person_owned[person] = product_amount
		gdn_input_dict["Owned"] = person_owned
		var option_product_dict = _satisfaction_calculator_ref.get_option_product_dict()
		
		var options:Array =_satisfaction_calculator_ref.get_options()
		
		var consumoption_product_dict = {}
		for option in option_product_dict.keys():
			if option in options:
				consumoption_product_dict[option] = option_product_dict[option]				 
		
		gdn_input_dict["OptionProduct"] = consumoption_product_dict
		gdn_input_dict["Currency"] = Prices.get_currency()
		
		
		var person_preferences_dict = {}		
		for person in persons:			
			var preferences_at_0_dict = {}			
			var maximum_satisfaction_dict = {}
			for option in options:
				
				var preference_at_0:float = _satisfaction_calculator_ref.get_option_preference_at_0(option)
				var max_satisf:float = _satisfaction_calculator_ref.get_option_max_satisfaction(option)				
				preferences_at_0_dict[option] = preference_at_0
				maximum_satisfaction_dict[option] = max_satisf
				
			var preferences_dict = {}	
			preferences_dict["PreferenceAt0"]=preferences_at_0_dict;
			preferences_dict["MaximumSatisfaction"]=maximum_satisfaction_dict;
			person_preferences_dict[person] = preferences_dict
		
		gdn_input_dict["Preferences"] = person_preferences_dict
		
		#ComplementaryComboPreferences
		person_preferences_dict = {}
		var complementary_combos:Array = _satisfaction_calculator_ref.get_complementary_combos().keys()
		for person in persons:
			var preferences_at_0_dict = {}
			var maximum_satisfaction_dict = {}
			for compl_combo in complementary_combos:
				var preference_at_0:float = _satisfaction_calculator_ref.get_complementary_combo_preference_at_0(compl_combo)
				var max_satisf:float = _satisfaction_calculator_ref.get_complementary_combo_max_satisfaction(compl_combo)
				preferences_at_0_dict[compl_combo] = preference_at_0
				maximum_satisfaction_dict[compl_combo] = max_satisf
			var preferences_dict = {}	
			preferences_dict["PreferenceAt0"]=preferences_at_0_dict;
			preferences_dict["MaximumSatisfaction"]=maximum_satisfaction_dict;
			person_preferences_dict[person] = preferences_dict
		gdn_input_dict["ComplementaryComboPreferences"] = person_preferences_dict
		#
		
		#SupplementaryComboPreferences
		person_preferences_dict = {}
		var supplementary_combos:Array = _satisfaction_calculator_ref.get_supplementary_combos().keys()
		for person in persons:
			var preferences_at_0_dict = {}
			var maximum_satisfaction_dict = {}
			for suppl_combo in supplementary_combos:
				var preference_at_0:float = _satisfaction_calculator_ref.get_supplementary_combo_preference_at_0(suppl_combo)
				var max_satisf:float = _satisfaction_calculator_ref.get_supplementary_combo_max_satisfaction(suppl_combo)
				preferences_at_0_dict[suppl_combo] = preference_at_0
				maximum_satisfaction_dict[suppl_combo] = max_satisf
			var preferences_dict = {}	
			preferences_dict["PreferenceAt0"]=preferences_at_0_dict;
			preferences_dict["MaximumSatisfaction"]=maximum_satisfaction_dict;
			person_preferences_dict[person] = preferences_dict
		gdn_input_dict["SupplementaryComboPreferences"] = person_preferences_dict
		#
		
#		var gdn_input_dict:Dictionary = {
#			"Persons": ["Peter","George"], 
#			"Products":["bill","chocolate","candy"], 
#Este lo elimino:			"Consumption":["bill_consumption","chocolate_consumption","candy_consumption"],
#			"Owned": {
#				"Peter":
#						{"bill":1,"chocolate":2,"candy":3},
#				"George":
#						{"bill":4,"chocolate":5,"candy":6}
#				},
#			"Preferences": {
#				"Peter":					
#						{
#							"PreferenceAt0":
#									{"bill_consumption":1.0,"chocolate_consumption":1.0,"candy_consumption":1.0},
#							"MaximumSatisfaction":
#									{"bill_consumption":1.0,"chocolate_consumption":1.0,"candy_consumption":1.0},
#						},
#				"George":					
#						{
#							"PreferenceAt0":
#									{"bill_consumption":1.0,"chocolate_consumption":1.0,"candy_consumption":1.0},
#							"MaximumSatisfaction":
#									{"bill_consumption":1.0,"chocolate_consumption":1.0,"candy_consumption":1.0},
#						},
#				},
#			"Currency":"bill"			
#    //    "ComplementaryCombos":
#    //                {"sweets_consumption":["chocolate_consumption","candy_consumption"]},
#    //    "SupplementaryCombos":
#    //              {"consumption", { {"candy consumption", 1.0},
#    //                              {"chocolate consumption", 1.0},
#    //                              {"nut consumption", 1.0} }
#    //              },
#    //              {"savings", { {"candy savings", 1.0},
#    //                          {"chocolate savings", 1.0},
#    //                          {"nut savings", 1.0} }
#    //              }

#		}

		#var complementary_combos:Dictionary = _satisfaction_calculator_ref.get_complementary_combos()
		gdn_input_dict["ComplementaryCombos"] = complementary_combos
	
		#var supplementary_combos:Dictionary = _satisfaction_calculator_ref.get_supplementary_combos()
		gdn_input_dict["SupplementaryCombos"] = supplementary_combos
		
		#var input_dict:Dictionary = {"cucu": 5.0, "coco":"lulu", "caca":["a","b"]}
		var gdn_output_dict:Dictionary = {}
		
		#var text_dict_answ:Dictionary = data.get_and_set_dict(text_dict_arg)
	#	var text_dict_answ:Dictionary = data.calc_info_from_market_test()

	#	Paso una copia, para que no haya modificaciones del input
		var gdn_input_dict_copy:Dictionary = Utils.deep_copy(gdn_input_dict)
		
		print( str(gdn_input_dict))
		print("Calculando precios con: _priceCalculatorGDNBind.calc_info_from_price_calculator_dll")
		var returnValue = _priceCalculatorGDNBind.adjust_price_with_price_calculator_dll(gdn_input_dict_copy,gdn_output_dict)
		
		print("Return value:")
		print(returnValue)
				
		print("output dict:")
		print(gdn_output_dict)
	
		assert(""!="TODO: actualizar los precios con el resultado")	
		
		var prices_dict = {}
		if gdn_output_dict.has("Prices"):
			prices_dict = gdn_output_dict.get("Prices")
		
		$PricesItemList.clear()
		for product in Prices.get_products():					
			var new_price:float = 0.0
			if prices_dict.has(product):
				new_price = prices_dict.get(product)
			
			if(new_price!=0.0):
				Prices.set_price_of_product(product,new_price)
				
			var price:float = Prices.get_price_of_product(product)
			var product_price_text:String = product+" "+str(price)
			$PricesItemList.add_item(product_price_text)
			
		$PricesItemList.add_item(str(gdn_output_dict))

#	TimeMeasurement.reset()
#
#	_market.calculate_new_prices()
#	$PricesItemList.clear()
#	for product in Prices.get_products():
#		var price:float = Prices.get_price_of_product(product)
#		var product_price_text:String = product+" "+str(price)
#		$PricesItemList.add_item(product_price_text)
##	var product_pricearray = _market.get_last_price_calculation_prices()
#	var product_pricearray = _market.get_all_price_calculation_prices()
#	_draw_product_pricearray(product_pricearray)
#	var price_change_step_array:Array = _market.get_all_price_change_step()
#	_draw_price_change_step_array(price_change_step_array)
#
#	var product_pricetops = _market.get_product_price_tops()
#	var product_pricebottoms = _market.get_product_price_bottoms()
#	_draw_product_price_tops_bottoms(product_pricetops,product_pricebottoms)
#
#
#	#var elapsed = TimeMeasurement.get_average_time("draw_test5_simple_continuity")
#	var elapsed = TimeMeasurement.get_total_time("calculate_best_combidict_simple_with_continuity")
#	var num_calls = TimeMeasurement.get_num_measurements("calculate_best_combidict_simple_with_continuity")
#
#	TimeMeasurement.print_info()
#
##	$CalcCostLabel.set_text("calculate_best_combidict_simple_with_continuity: "+ str(elapsed))
##	$CalcCostLabelExtraInfo.set_text("num calls:" +str(num_calls))


