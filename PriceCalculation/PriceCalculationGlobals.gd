extends Node


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

#var _product_price = 1
#var _tax_rate = 0.2

var _products = ["chocolate","candy","bill"]
var _product_uses = ["savings","consumption"]
var _complementary_groups = {
							"sweets_consumption_group":
							{"use": "consumption",
							"products":["chocolate","candy"]		
							}}
var _supplementary_groups = {
							"savings_group":
							{"use": "savings",
							"products":["chocolate","candy","bill"]		
							}}


#signal signal_tax_rate_changed(tax_rate)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func get_option_name_from_product_and_use(product_arg:String,use_arg:String)->String:
	return product_arg+"_"+use_arg
	
func get_complementary_group_names()->Array:
	var names:Array = []
	for group_name in _complementary_groups.keys():		
		names.append(group_name)
	return names

func get_supplementary_group_names()->Array:
	var names:Array = []
	for group_name in _supplementary_groups.keys():		
		names.append(group_name)
	return names


func get_use_of_complementary_group(group_name_arg:String)->String:
	if _complementary_groups.has(group_name_arg):
		var group_info_dict:Dictionary = _complementary_groups[group_name_arg]
		if group_info_dict.has("use"):
			return group_info_dict["use"]
	return ""

func get_use_of_supplementary_group(group_name_arg:String)->String:
	if _supplementary_groups.has(group_name_arg):
		var group_info_dict:Dictionary = _supplementary_groups[group_name_arg]
		if group_info_dict.has("use"):
			return group_info_dict["use"]
	return ""


func get_products_of_complementary_group(group_name_arg:String)->Array:
	var products:Array = []
	if _complementary_groups.has(group_name_arg):
		var group_info_dict:Dictionary = _complementary_groups[group_name_arg]
		if group_info_dict.has("products"):
			products = group_info_dict["products"]
	return products

func get_products_of_supplementary_group(group_name_arg:String)->Array:
	var products:Array = []
	if _supplementary_groups.has(group_name_arg):
		var group_info_dict:Dictionary = _supplementary_groups[group_name_arg]
		if group_info_dict.has("products"):
			products = group_info_dict["products"]
	return products


func set_products(products_array_arg:Array):
	_products = products_array_arg

func add_product(product_arg:String):
	if false==_products.has(product_arg):
		_products.append(product_arg)
		
func remove_product(product_arg:String):
	var prod_index:int = _products.find(product_arg)
	if prod_index>=0:
		_products.remove(prod_index)
	
#func get_price_without_taxes()->float:
#	return (1-_tax_rate)*_product_price
	
#func set_tax_rate(tax_rate_arg:float):
#	_tax_rate =tax_rate_arg
#	emit_signal("signal_tax_rate_changed",tax_rate_arg)
	
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
