extends Control

#const Combination = preload("res://Combination.gd")

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

#var _products = ["chocolate","candy","nut"]
#var _equivalent_product_dict:Dictionary = { "candy_savings": "candy",
#									"candy_consumption": "candy",
#									"chocolate_savings": "chocolate",
#									"chocolate_consumption": "chocolate",}
#var _products = Globals._products
var _currency = "bill"
#var _amounts_dict = {"chocolate": 1.0, "candy":0.5,"nut":0.5}
var _amounts_dict = {}
#var PriceCalculationGlobals = load("res://PriceCalculation/PriceCalculationGlobals.gd")

# Called when the node enters the scene tree for the first time.
func _ready():
	
#	for product in _products:
#		print(product +": " + str(get_price_of_product(product)))
	
#	var combination_dict:Dictionary = {"chocolate": 4,"candy":6}
#	print("combination price: "+str(calculate_price(combination_dict)))
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _init():
	for product in PriceCalculationGlobals._products:
		_amounts_dict[product] = 1.0

func set_amount_of_product(product_arg:String, price_arg:float)->void:
	if PriceCalculationGlobals._products.has(product_arg):
		_amounts_dict[product_arg]=price_arg
		
func set_price_of_product(product_arg:String, price_arg:float)->void:
	if product_arg != _currency:
		var amount_of_currency:float = _amounts_dict[_currency]
		if PriceCalculationGlobals._products.has(product_arg):
			_amounts_dict[product_arg]=amount_of_currency*price_arg		

func get_price_of_product(product_arg:String)->float:
	var amount_of_currency:float = _amounts_dict[_currency]
	if PriceCalculationGlobals._products.has(product_arg):
		return _amounts_dict[product_arg]/amount_of_currency
	else:
		return 0.0

func get_amount_of_product(product_arg:String)->float:
	if PriceCalculationGlobals._products.has(product_arg):
		return _amounts_dict[product_arg]
	else:
		return 0.0


#func calculate_combination_price(combination_arg:Combination)->float:
#	return calculate_combidict_price(combination_arg.get_combidict())

func calculate_combidict_price(combidict_arg:Dictionary)->float:

	var total_price:float = 0.0
	for product in combidict_arg.keys():
		if _amounts_dict.has(product):
			total_price += _amounts_dict[product]*combidict_arg[product]

	var amount_of_currency:float = _amounts_dict[_currency]
	
	var total_price_for_currency = total_price/amount_of_currency
	
	return total_price_for_currency

func get_products()->Array:
	return PriceCalculationGlobals._products

func get_combidict()->Dictionary:
	return _amounts_dict

func set_currency(currency_arg:String)->void:
	self._currency = currency_arg
	assert(currency_arg in PriceCalculationGlobals._products)

func get_currency()->String:
	return self._currency
	
func set_products(products_array_arg:Array):
	PriceCalculationGlobals._products = products_array_arg
	set_init_price_for_products(products_array_arg)
	
func set_init_price_for_products(products_array_arg:Array):
	for product in products_array_arg:
		_amounts_dict[product]=1.0
		
func get_prices()->Dictionary:
	var product_price:Dictionary = {}
	for product in PriceCalculationGlobals._products:
		product_price[product] = self.get_price_of_product(product)
	return product_price
	
