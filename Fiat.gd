extends Node2D

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

var PriceCalculationInterface = load("res://PriceCalculation/PriceCalculationInterface.gd")

export(Resource) var _Producer = null

var _price_calculation_interface = null
var _person_node_dict = {}
var _node_person_dict = {}

signal price_updated_signal
signal trade_of_person_updated_signal(trader_person_node, trade_dict)
signal consumption_of_person_updated_signal(trader_person_node, trade_dict)
signal initialize_owned_products_signal(trader_person_node,owned_products)


# Called when the node enters the scene tree for the first time.
func _ready():
	
	_price_calculation_interface = PriceCalculationInterface.new()
	create_person("Person 1", $Producer1/TraderPerson)
	create_person("Person 2", $Producer2/TraderPerson)
	create_person("Person 3", $CivilServant/TraderPerson)
	
#	Inicializo cantidades iniciales de productos
	var owned_products = {"candy":1.0,"chocolate":2.0,"bill":3.0}
	for person in get_persons():
		_price_calculation_interface.set_owned_products(person,owned_products)
		print(_price_calculation_interface.get_owned_products(person))
		emit_signal("initialize_owned_products_signal",_person_node_dict[person],owned_products)
	
#	print(Prices.get_prices())
#	_price_calculation_interface.calculate_new_prices()
#	_price_calculation_interface.calculate_trades()
#	print(Prices.get_prices())
#	for person in get_persons():
#		var trade:Dictionary = _price_calculation_interface.get_traded_products(person)
#		print(trade)
	
#	_price_calculation_interface.calculate_new_prices()
#	print(Prices.get_prices())
	
#	Para que se escriban los precios en los labels correspondientes:
	prices_updated()
	
		
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func create_person(person_name_arg:String, trader_person_arg:Node):
	_price_calculation_interface.add_person(person_name_arg)
	_person_node_dict[person_name_arg] = trader_person_arg
	_node_person_dict[trader_person_arg] = person_name_arg

func get_persons()->Array:
	return _person_node_dict.keys()
	
func calculate_prices():
	_price_calculation_interface.calculate_new_prices()
	prices_updated()
	
func prices_updated():
	var price_candy:float = Prices.get_price_of_product("candy")
	$Shop/PricesLabel/CandyPriceLabel.set_text(str(price_candy))

	var price_chocolate:float = Prices.get_price_of_product("chocolate")
	$Shop/PricesLabel/ChocolatePriceLabel.set_text(str(price_chocolate))
	
	emit_signal("price_updated_signal")

func trade_of_person_updated(trader_person_node:Node,trade_dict:Dictionary):
	emit_signal("trade_of_person_updated_signal",trader_person_node, trade_dict)

func consumption_of_person_updated(trader_person_node:Node,consumption_dict:Dictionary):
	emit_signal("consumption_of_person_updated_signal",trader_person_node, consumption_dict)
	

func calc_trade_and_consumption(trader_person_node:Node):
	if (_node_person_dict.has(trader_person_node)):
		var person:String = _node_person_dict[trader_person_node]
		_price_calculation_interface.adjust_best_combination_for_person(person)
		var trade_dict:Dictionary = _price_calculation_interface.calculate_trade_for_person_with_current_best_combinations(person)
		trade_of_person_updated(trader_person_node,trade_dict)
		
		var consumption_dict:Dictionary = _price_calculation_interface.calculate_consumption_for_person_with_current_best_combinations(person)
		consumption_of_person_updated(trader_person_node, consumption_dict)
	
func person_owned_updated(node_person, product_amount_dict):
	if _node_person_dict.has(node_person):
		var person:String = _node_person_dict[node_person]
		_price_calculation_interface.set_owned_products(person, product_amount_dict)

func _on_Button_pressed():
	var price_calculation_interface = PriceCalculationInterface.new()
	price_calculation_interface.init_default_scenario()
	price_calculation_interface.print_scenario_info()
	pass # Replace with function body.


func _on_CalculatePrices_pressed():
	self.calculate_prices()
#	pass # Replace with function body.


func _on_Producer1_person_owned_updated_signal(node_person, product_amount_dict):
	person_owned_updated(node_person, product_amount_dict)


func _on_CivilServant_person_owned_updated_signal(node_person, product_amount_dict):
	person_owned_updated(node_person, product_amount_dict)

func _on_Producer2_person_owned_updated_signal(node_person, product_amount_dict):
	person_owned_updated(node_person, product_amount_dict)


func _on_Producer1_signal_trade_and_consumption_calc(node):
	calc_trade_and_consumption(node)
	
func _on_Producer2_signal_trade_and_consumption_calc(node):
	calc_trade_and_consumption(node)
	
func _on_TraderPerson_signal_trade_and_consumption_calc(node):
	calc_trade_and_consumption(node)

