extends Sprite



# Declare member variables here. Examples:
# var a = 2
# var b = "text"

signal owner_products_updated_signal(product_amount_dict)

#var _owned_bills:float = 0.0
#var _owned_chocolates:float = 0.0
#var _owned_candies:float = 0.0

var _owned_amounts:Dictionary = {"bill":0.0,
								"candy":0.0,
								"chocolate":0.0}

var _in_market_amounts:Dictionary = {"bill":0.0,
								"candy":0.0,
								"chocolate":0.0}

var _for_consumption_amounts:Dictionary = {"bill":0.0,
								"candy":0.0,
								"chocolate":0.0}


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func get_amount_of_product(product_arg:String)->float:
	if _owned_amounts.has(product_arg):
		return _owned_amounts[product_arg]
	else:
		return 0.0
		
func update_labels():
	var owned_minus_in_market:Dictionary = Utils.calculate_combination_difference(_owned_amounts,_in_market_amounts)
	var owned_minus_in_market_minus_consumed:Dictionary = Utils.calculate_combination_difference(owned_minus_in_market, _for_consumption_amounts)
	if owned_minus_in_market_minus_consumed.has("bill"):
		var value_to_add:float = owned_minus_in_market_minus_consumed["bill"]
		$Bill/OwnedBillsLabel.set_text(str(value_to_add))
	if owned_minus_in_market_minus_consumed.has("candy"):
		var value_to_add:float = owned_minus_in_market_minus_consumed["candy"]
		$Candy/OwnedCandiesLabel.set_text(str(value_to_add))
	if owned_minus_in_market_minus_consumed.has("chocolate"):
		var value_to_add:float = owned_minus_in_market_minus_consumed["chocolate"]
		$Chocolate/OwnedChocolatesLabel.set_text(str(value_to_add))
		
		
func add_products(product_amount_dict:Dictionary):
	if product_amount_dict.has("bill"):
		var old_value:float = _owned_amounts["bill"]
		var value_to_add:float = product_amount_dict["bill"]
		var new_value:float = old_value+value_to_add
		_owned_amounts["bill"]=new_value
	if product_amount_dict.has("candy"):
		var old_value:float = _owned_amounts["candy"]
		var value_to_add:float = product_amount_dict["candy"]
		var new_value:float = old_value+value_to_add
		_owned_amounts["candy"]=new_value
	if product_amount_dict.has("chocolate"):
		var old_value:float = _owned_amounts["chocolate"]
		var value_to_add:float = product_amount_dict["chocolate"]
		var new_value:float = old_value+value_to_add
		_owned_amounts["chocolate"]=new_value
	update_labels()
	emit_products_updated_signal()
	
func initialize_products(product_amount_dict:Dictionary):
	if product_amount_dict.has("bill"):
		var value:float = product_amount_dict["bill"]
		_owned_amounts["bill"]=value
	if product_amount_dict.has("candy"):		
		var value:float = product_amount_dict["candy"]
		_owned_amounts["candy"]=value
	if product_amount_dict.has("chocolate"):
		var value:float = product_amount_dict["chocolate"]
		_owned_amounts["chocolate"]=value
	update_labels()
	
func get_products()->Dictionary:
	return _owned_amounts
	
func emit_products_updated_signal():
	var product_amount_dict:Dictionary = get_products()
	emit_signal("owner_products_updated_signal",product_amount_dict)
	


func _on_Trader_signal_send_to_shop(amountsdict):
	_in_market_amounts = amountsdict.duplicate()
	update_labels()
	emit_products_updated_signal()
	


func _on_Consumer_send_products_to_consume_signal(to_be_consumed_dict):
	_for_consumption_amounts = to_be_consumed_dict.duplicate()
	update_labels()



func _on_ConsumeButton_pressed():
	_owned_amounts = Utils.calculate_combination_difference(_owned_amounts,_for_consumption_amounts)
	_for_consumption_amounts.clear()
	update_labels() #No hace falta
	
