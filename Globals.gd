extends Node


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

var _product_price = 1
var _tax_rate = 0.2

var _products = ["chocolate","candy"]

signal signal_tax_rate_changed(tax_rate)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func set_products(products_array_arg:Array):
	_products = products_array_arg
	
func get_price_without_taxes()->float:
	return (1-_tax_rate)*_product_price
	
func set_tax_rate(tax_rate_arg:float):
	_tax_rate =tax_rate_arg
	emit_signal("signal_tax_rate_changed",tax_rate_arg)
	
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
