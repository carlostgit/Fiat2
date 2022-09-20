extends Sprite


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

#
#var _amountsdict:Dictionary = {"bill":0.0,
#								"candy":0.0,
#								"chocolate":0.0}
								

var _traderperson_amounts:Dictionary = {}

# Called when the node enters the scene tree for the first time.
func _ready():
	pass
# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass



func _on_ResetShopButton_pressed():
	
#	_amountsdict["bill"] = 0.0
#	_amountsdict["candy"] = 0.0
#	_amountsdict["chocolate"] = 0.0
	$Bill/MoneyInMarketLabel.set_text(str(0))
	$Candies/CandiesInMarketLabel.set_text(str(0))
	$Chocolate/ChocolatesInMarketLabel.set_text(str(0))
	_traderperson_amounts.clear()
	
#func add_products(product_amount_dict:Dictionary):
#	if product_amount_dict.has("bill"):
#		var old_value:float = _amountsdict["bill"]
#		var value_to_add:float = product_amount_dict["bill"]
#		var new_value:float = old_value+value_to_add
#		$Bill/MoneyInMarketLabel.set_text(str(new_value))
#		_amountsdict["bill"]=new_value
#	if product_amount_dict.has("candy"):
#		var old_value:float = _amountsdict["candy"]
#		var value_to_add:float = product_amount_dict["candy"]
#		var new_value:float = old_value+value_to_add
#		$Candies/CandiesInMarketLabel.set_text(str(new_value))
#		_amountsdict["candy"]=new_value
#	if product_amount_dict.has("chocolate"):
#		var old_value:float = _amountsdict["chocolate"]
#		var value_to_add:float = product_amount_dict["chocolate"]
#		var new_value:float = old_value+value_to_add
#		$Chocolate/ChocolatesInMarketLabel.set_text(str(new_value))
#		_amountsdict["chocolate"]=new_value

func update_labels():
	
	var sum_of_bill:float = 0.0
	var sum_of_candy:float = 0.0
	var sum_of_chocolate:float = 0.0
	for traderperson in _traderperson_amounts.keys():
		var amountsdict:Dictionary = _traderperson_amounts[traderperson]	
		if amountsdict.has("bill"):
			var value_to_add:float = amountsdict["bill"]
			sum_of_bill += value_to_add
		if amountsdict.has("candy"):
			var value_to_add:float = amountsdict["candy"]
			sum_of_candy += value_to_add
		if amountsdict.has("chocolate"):
			var value_to_add:float = amountsdict["chocolate"]
			sum_of_chocolate += value_to_add
						
	$Bill/MoneyInMarketLabel.set_text(str(sum_of_bill))
	$Candies/CandiesInMarketLabel.set_text(str(sum_of_candy))
	$Chocolate/ChocolatesInMarketLabel.set_text(str(sum_of_chocolate))

func _on_Producer1_send_to_shop_from_traderperson(amountdict, traderperson):
#	add_products(amountdict)
	_traderperson_amounts[traderperson] = amountdict
	update_labels()

func _on_Producer2_send_to_shop_from_traderperson(amountdict, traderperson):
#	add_products(amountdict)
	_traderperson_amounts[traderperson] = amountdict
	update_labels()

func _on_CivilServant_send_to_shop_from_traderperson(amountdict, traderperson):
#	add_products(amountdict)
	_traderperson_amounts[traderperson] = amountdict
	update_labels()
