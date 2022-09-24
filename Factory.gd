extends Node2D

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

export(Texture) var _product_texture = preload("res://candy_small.png")
#export(String) var _demanded_product_type = "Chocolate"
export(bool) var _produce_candy = true

signal signal_produced(node,product_amount_dict)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass
# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func get_product_amount_to_produce()->Dictionary:
	var product_amount_dict:Dictionary = {}
	product_amount_dict["candy"] =$CandiesToProduceSpinBox.get_value()
	product_amount_dict["chocolate"] =$ChocolatesToProduceSpinBox.get_value()
	product_amount_dict["bill"] =$MoneyToProduceSpinBox.get_value()
	return product_amount_dict

func produce():
	var product_amount_dict:Dictionary = get_product_amount_to_produce()
	emit_signal("signal_produced",self,product_amount_dict)
		
func _on_ProduceButton_pressed():
	produce()
	
