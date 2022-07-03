extends Node


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
const Prices = preload("res://PriceCalculation/Prices.gd")
const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")
const TradeCalculator = preload("res://PriceCalculation/TradeCalculator.gd")


var _prices:Node = null
var _trade_calculators = []
var _trade_calculator_owned_prod = {}

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _init():
	_prices = Prices.new()
	set_products(["chocolate","candy"])
	set_currency("candy")
	
func set_products(products_array_arg:Array):
	_prices.set_products(products_array_arg)
	_prices.set_init_price_for_products(products_array_arg)
	
func set_currency(product_arg:String):
	_prices.set_currency(product_arg)
	
func create_trade_calculator() -> Node:
	var satisfaction_calculator = SatisfactionCalculator.new()
	var trade_calculator = TradeCalculator.new(satisfaction_calculator)
	_trade_calculators.append(trade_calculator)	
	return trade_calculator

func set_owned_products_for_trade_calculator(trade_calculator_arg:Node, combidict_arg:Dictionary):
	if (-1 != _trade_calculators.find(trade_calculator_arg)):	
		_trade_calculator_owned_prod[trade_calculator_arg] = combidict_arg
		
func add_owned_products_for_trade_calculator(trade_calculator_arg:Node, combidict_to_be_added_arg:Dictionary):
	if (-1 != _trade_calculators.find(trade_calculator_arg)):
		var new_owned_prod:Dictionary = Utils.sum_combidict(_trade_calculator_owned_prod[trade_calculator_arg], combidict_to_be_added_arg)
		set_owned_products_for_trade_calculator(trade_calculator_arg,new_owned_prod)

func calculate_all_trade() -> Dictionary:
	var total_trade:Dictionary = {}
	for trade_calculator in _trade_calculator_owned_prod.keys():
		var trade:Dictionary = trade_calculator.calculate_trade_for_combidict(_trade_calculator_owned_prod[trade_calculator])


		total_trade = Utils.sum_combidict(total_trade, trade)
	return total_trade	
	
#
#
#
#
#
#
#
#
#
