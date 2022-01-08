extends Control


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

const Market = preload("res://PriceCalculation/Market.gd")

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
	update_value_of_owned(person)


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


func update_aumount_owned_spinbox(person_arg:String, product_arg:String):
	var own_products_dict = _market.get_owned_products(person_arg)
	if own_products_dict.has(product_arg):
		var amount = own_products_dict[product_arg]
		$AmountOwnedSpinBox.set_value(amount)
		
func update_amount_traded_label(person_arg:String, product_arg:String):
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
	_market.calculate_trades()
	var person_product_dict:Dictionary = get_selected_person_and_product()
	if person_product_dict.has("person") and person_product_dict.has("product"):
		var person:String = person_product_dict["person"]
		var product:String = person_product_dict["product"]
	#	update_aumount_owned_spinbox(person,product)
		update_amount_traded_label(person,product)


func _on_CalculateValueButton_pressed():
	_market.calculate_value_of_owned()
	var person_product_dict:Dictionary = get_selected_person_and_product()
	if person_product_dict.has("person"):
		var person:String = person_product_dict["person"]
		update_value_of_owned(person)
	
func update_value_of_owned(person_arg:String):
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
	_market.change_prices_step()
	


func _on_CalculateNewPricesButton_pressed():
	_market.calculate_new_prices()
	$PricesItemList.clear()
	for product in Prices.get_products():
		var price:float = Prices.get_price_of_product(product)
		var product_price_text:String = product+" "+str(price)
		$PricesItemList.add_item(product_price_text)
	
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
	print("$AddPersonAcceptDialog.get_position()")
	print($AddPersonAcceptDialog.get_position())
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


