extends Node2D


# Declare member variables here. Examples:
# var a = 2
# var b = "text"



signal signal_trade_and_consumption_calc(node)
signal signal_person_owned_updated(node_person, product_amount_dict)
signal signal_send_to_shop_from_traderperson(amountdict, traderperson)
signal signal_trade(traderperson)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


	

func _on_Fiat_signal_trade_of_person_updated(trader_person_node, trade_dict):
	var node:Node = $TraderPerson
	if (trader_person_node==node):
		node.trade_of_person_updated_received(trade_dict)



func _on_Fiat_signal_consumption_of_person_updated(trader_person_node, trade_dict):
	var node:Node = $TraderPerson
	if (trader_person_node==node):
		node.consumption_of_person_updated_received(trade_dict)


func _on_Factory_signal_produced(node, product_amount_dict):	
	$TraderPerson.add_products(product_amount_dict)
	



func _on_TraderPerson_signal_person_owned_updated(node_person, product_amount_dict):
	emit_signal("signal_person_owned_updated", node_person, product_amount_dict)



func _on_TraderPerson_signal_trade_and_consumption_calc(node):
	emit_signal("signal_trade_and_consumption_calc",node)



func _on_Fiat_signal_initialize_owned_products(trader_person_node, owned_products):
	var node:Node = $TraderPerson
	if (trader_person_node==node):
		node.initialize_owned_products(owned_products)


func _on_TraderPerson_signal_send_to_shop_from_traderperson(amountdict, traderperson):
	emit_signal("signal_send_to_shop_from_traderperson",amountdict, traderperson)
	

func _on_TraderPerson_signal_trade(traderperson):
	emit_signal("signal_trade",traderperson)
	
