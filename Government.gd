extends Sprite


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

signal send_money_to_civil_servant(amount_to_send)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_GiveMoneyButton_pressed():
	var spin_box_value:float = $GiveMoneyButton/MoneyToGiveSpinBox.get_value()
	var money:float = $Owner.get_amount_of_product("bill")
	var amount_to_send:float = min(spin_box_value,money)
	emit_signal("send_money_to_civil_servant",amount_to_send)
	
	var amount_to_remove:Dictionary = {}
	amount_to_remove["bill"] = -amount_to_send
	$Owner.add_products(amount_to_remove)
	

func _on_Factory_produced_signal(node, product_amount_dict):
	$Owner.add_products(product_amount_dict)
	
	
	
