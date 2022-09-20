extends Node2D


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

signal person_owned_updated_signal(node_person, product_amount_dict)
signal send_to_shop_from_traderperson(amountdict, traderperson)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_Fiat_trade_of_person_updated_signal(trader_person_node, trade_dict):
	var node:Node = $TraderPerson
	if (trader_person_node==node):
		node.trade_of_person_updated_received(trade_dict)


func _on_Fiat_consumption_of_person_updated_signal(trader_person_node, trade_dict):
	var node:Node = $TraderPerson
	if (trader_person_node==node):
		node.consumption_of_person_updated_received(trade_dict)


func _on_TraderPerson_person_owned_updated_signal(node_person, product_amount_dict):
	emit_signal("person_owned_updated_signal", node_person, product_amount_dict)


func _on_Fiat_initialize_owned_products_signal(trader_person_node, owned_products):
	var node:Node = $TraderPerson
	if (trader_person_node==node):
		node.initialize_owned_products(owned_products)
		


func _on_TraderPerson_send_to_shop_from_traderperson(amountdict, traderperson):
	emit_signal("send_to_shop_from_traderperson",amountdict, traderperson)
	pass # Replace with function body.




func _on_Government_send_money_to_civil_servant(amount_to_send):
	var products:Dictionary = {}
	products["bill"]=amount_to_send
	$TraderPerson.add_products(products)
	pass # Replace with function body.
