extends Sprite



# Declare member variables here. Examples:
# var a = 2
# var b = "text"

signal owner_products_updated_signal(product_amount_dict)

var _owned_bills:float = 0.0
var _owned_chocolates:float = 0.0
var _owned_candies:float = 0.0

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func add_products(product_amount_dict:Dictionary):
	if product_amount_dict.has("bill"):
		var old_value:float = _owned_bills
		var value_to_add:float = product_amount_dict["bill"]
		var new_value:float = old_value+value_to_add
		$Bill/OwnedBillsLabel.set_text(str(new_value))
		_owned_bills=new_value
	if product_amount_dict.has("candy"):
		var old_value:float = _owned_candies
		var value_to_add:float = product_amount_dict["candy"]
		var new_value:float = old_value+value_to_add
		$Candy/OwnedCandiesLabel.set_text(str(new_value))
		_owned_candies=new_value
	if product_amount_dict.has("chocolate"):
		var old_value:float = _owned_chocolates
		var value_to_add:float = product_amount_dict["chocolate"]
		var new_value:float = old_value+value_to_add
		$Chocolate/OwnedChocolatesLabel.set_text(str(new_value))
		_owned_chocolates=new_value
	products_updated()
	
func initialize_products(product_amount_dict:Dictionary):
	if product_amount_dict.has("bill"):
		var value:float = product_amount_dict["bill"]
		$Bill/OwnedBillsLabel.set_text(str(value))
		_owned_bills=value
	if product_amount_dict.has("candy"):		
		var value:float = product_amount_dict["candy"]
		$Candy/OwnedCandiesLabel.set_text(str(value))
		_owned_candies=value
	if product_amount_dict.has("chocolate"):
		var value:float = product_amount_dict["chocolate"]
		$Chocolate/OwnedChocolatesLabel.set_text(str(value))
		_owned_chocolates=value
	
func get_products()->Dictionary:
	var product_amount_dict:Dictionary = {}
	product_amount_dict["bill"] = _owned_bills
	product_amount_dict["candy"] = _owned_candies
	product_amount_dict["chocolate"] = _owned_chocolates
	return product_amount_dict
	
func products_updated():
	var product_amount_dict:Dictionary = get_products()
	emit_signal("owner_products_updated_signal",product_amount_dict)
	
