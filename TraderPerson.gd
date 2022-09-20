extends Sprite


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

signal signal_trade_and_consumption_calc(node)
signal person_owned_updated_signal(node_person,product_amount_dict)
signal send_to_shop_from_traderperson(amountdict,traderperson)
# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass



	
func trade_of_person_updated_received(trade_dict):
	$Trader.set_products(trade_dict)
#	if trade_dict.has("bill"):
#		var amount:float = trade_dict["bill"]
#		$Trader/BillsInMarketLabel.set_text(str(amount))
#	if trade_dict.has("candy"):
#		var amount:float = trade_dict["candy"]
#		$Trader/CandiesInMarketLabel.set_text(str(amount))
#	if trade_dict.has("chocolate"):
#		var amount:float = trade_dict["chocolate"]
#		$Trader/ChocolatesInMarketLabel.set_text(str(amount))	

func consumption_of_person_updated_received(trade_dict):
	if trade_dict.has("bill"):
		var amount:float = trade_dict["bill"]
		$Consumer/Bill/BillsToEatLabel.set_text(str(amount))
	if trade_dict.has("candy"):
		var amount:float = trade_dict["candy"]
		$Consumer/Candy/CandiesToEatLabel.set_text(str(amount))
	if trade_dict.has("chocolate"):
		var amount:float = trade_dict["chocolate"]
		$Consumer/Chocolate/ChocolatesToEatLabel.set_text(str(amount))	

func add_products(product_amount_dict:Dictionary):
	$Owner.add_products(product_amount_dict)
	


func _on_Owner_owner_products_updated_signal(product_amount_dict):
	emit_signal("person_owned_updated_signal",self,product_amount_dict)
	


func _on_CalcTradeAndConsumptionButton_pressed():
	emit_signal("signal_trade_and_consumption_calc",self)
	pass # Replace with function body.

func initialize_owned_products(owned_products:Dictionary):
	$Owner.initialize_products(owned_products)


func _on_Trader_send_to_shop_signal(amountsdict):
	emit_signal("send_to_shop_from_traderperson",amountsdict,self)

