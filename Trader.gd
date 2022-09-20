extends Sprite


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

#var _for_trade_bills:float = 0.0
#var _for_trade_chocolates:float = 0.0
#var _for_trade_candies:float = 0.0

var _amounts_dict:Dictionary = {"bill":0,
								"candy":0,
								"chocolate":0}

signal send_to_shop_signal(amountsdict)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func add_products(product_amount_dict:Dictionary):
	if product_amount_dict.has("bill"):
		var old_value:float = _amounts_dict["bill"]
		var value_to_add:float = product_amount_dict["bill"]
		var new_value:float = old_value+value_to_add
		$BillsInMarketLabel.set_text(str(new_value))
		_amounts_dict["bill"]=new_value
	if product_amount_dict.has("candy"):
		var old_value:float = _amounts_dict["candy"]
		var value_to_add:float = product_amount_dict["candy"]
		var new_value:float = old_value+value_to_add
		$CandiesInMarketLabel.set_text(str(new_value))
		_amounts_dict["candy"]=new_value
	if product_amount_dict.has("chocolate"):
		var old_value:float = _amounts_dict["chocolate"]
		var value_to_add:float = product_amount_dict["chocolate"]
		var new_value:float = old_value+value_to_add
		$ChocolatesInMarketLabel.set_text(str(new_value))
		_amounts_dict["chocolate"]=new_value
	
func set_products(product_amount_dict:Dictionary):
	if product_amount_dict.has("bill"):
		var value:float = product_amount_dict["bill"]
		$BillsInMarketLabel.set_text(str(value))
		_amounts_dict["bill"]=value
	if product_amount_dict.has("candy"):		
		var value:float = product_amount_dict["candy"]
		$CandiesInMarketLabel.set_text(str(value))
		_amounts_dict["candy"]=value
	if product_amount_dict.has("chocolate"):
		var value:float = product_amount_dict["chocolate"]
		$ChocolatesInMarketLabel.set_text(str(value))
		_amounts_dict["chocolate"]=value
	
func get_products()->Dictionary:
#	var product_amount_dict:Dictionary = {}
#	product_amount_dict["bill"] = _for_trade_bills
#	product_amount_dict["candy"] = _for_trade_candies
#	product_amount_dict["chocolate"] = _for_trade_chocolates
#	return product_amount_dict
	return _amounts_dict


func _on_SendToShopButton_pressed():
	emit_signal("send_to_shop_signal",_amounts_dict)
	
