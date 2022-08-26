extends Node


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
#const Prices = preload("res://PriceCalculation/Prices.gd")
const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")
const TradeCalculator = preload("res://PriceCalculation/TradeCalculator.gd")

const Market = preload("res://PriceCalculation/Market.gd")


#var _prices:Node = null
var _trade_calculators = []
var _trade_calculator_owned_prod = {}
var _market:Node = null

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _init():
#	_prices = Prices.new()
	_market = Market.new()
	
func init_default_scenario():
	set_products(["chocolate","candy","bill"])
	set_currency("bill")
	
	add_person("Person 1")
	add_person("Person 2")
	
func add_person(person_arg:String):
	if _market:
		var satisfaction_calculator1 = SatisfactionCalculator.new()
		var trade_calculator1:TradeCalculator = TradeCalculator.new(satisfaction_calculator1)
		_market.add_person(person_arg, trade_calculator1)
	
	
func set_products(products_array_arg:Array):
	Prices.set_products(products_array_arg)
	Prices.set_init_price_for_products(products_array_arg)
	PriceCalculationGlobals.set_products(products_array_arg)
	
func set_currency(product_arg:String):
	Prices.set_currency(product_arg)
	
func get_persons()->Array:
	if _market:
		return _market.get_persons()
	else:
		return []
		
func _get_trade_calculator(person_arg:String)->Node:
	var node:Node = null
	if _market:
		node = _market.get_trade_calculator(person_arg)
	return node

func get_satisfaction_calculator(person_arg:String)->Node:
	var node:Node = null
	var trade_calculator = _get_trade_calculator(person_arg)
	if trade_calculator:
		node = trade_calculator.get_satisfaction_calculator()
	return node

func get_owned_products(person_arg:String)->Dictionary:
	if _market:
		return _market.get_owned_products(person_arg)
	else:
		return {}

func print_scenario_info():
	if null == _market:
		print("No market")
		return
	print("Persons:")
	print("--------")
	
	var persons:Array = self.get_persons() 
	print(" Number:"+str(persons.size()))
	for person in persons:
		print(" "+person)
	
	print("")
	
	print("Owned products:")
	print("---------------")
	for person in persons:
		print(" "+person+":")
		var owned_products:Dictionary = _market.get_owned_products(person)
		for product in owned_products.keys():
			print("  "+product+": "+str(owned_products[product]))
			
	print("Options preference info:")
	print("-----------------------")
	for person in persons:
		print(" "+person+":")
		var trade_calculator = _market.get_trade_calculator(person)
		var statisfaction_calculator = trade_calculator.get_satisfaction_calculator()
		var options:Array = statisfaction_calculator.get_options()
		var num_simple_options = options.size()
		print("  Num simple options: " +str(num_simple_options))
		for option in options:
			var max_satisf:float = statisfaction_calculator.get_option_max_satisfaction(option)
			var pref_at_0:float = statisfaction_calculator.get_option_preference_at_0(option)
			print("   "+option+":")
			print("    Max satis: "+str(max_satisf) +" Pref at 0: "+str(pref_at_0))
		
		var comp_combos:Array = statisfaction_calculator.get_complementary_combo_names()
		print("  Num complementary combos: " +str(comp_combos.size()))
		for combo in comp_combos:
			var max_satisf:float = statisfaction_calculator.get_complementary_combo_max_satisfaction(combo)
			var pref_at_0:float = statisfaction_calculator.get_complementary_combo_preference_at_0(combo)
			print("   Name of combo: "+combo+":")
			print("    Max satis: "+str(max_satisf) +" Pref at 0: "+str(pref_at_0))
			print("    Options:")
			for option in statisfaction_calculator.get_options_of_complementary_combo(combo):
				print ("     "+option)
#			func get_options_of_complementary_combo(combo_name:String)->Array:
			

			
			
		var supp_combos:Array = statisfaction_calculator.get_supplementary_combo_names()
		print("  Num supplementary combos: " +str(comp_combos.size()))
		for combo in supp_combos:
			var max_satisf:float = statisfaction_calculator.get_supplementary_combo_max_satisfaction(combo)
			var pref_at_0:float = statisfaction_calculator.get_supplementary_combo_preference_at_0(combo)
			print("   Name of combo: "+combo+":")
			print("    Max satis: "+str(max_satisf) +" Pref at 0: "+str(pref_at_0))
			print("    Options:")
			var option_weigh_dict:Dictionary = statisfaction_calculator.get_weighed_options_of_supplementary_combo(combo) 
			for option in option_weigh_dict.keys():
				print ("     "+option+" "+str(option_weigh_dict[option]))
			#func get_weighed_options_of_supplementary_combo(combo_name:String)->Dictionary:
	
#func create_trade_calculator() -> Node:
#	var satisfaction_calculator = SatisfactionCalculator.new()
#	var trade_calculator = TradeCalculator.new(satisfaction_calculator)
#	_trade_calculators.append(trade_calculator)	
#	return trade_calculator
#
#func set_owned_products_for_trade_calculator(trade_calculator_arg:Node, combidict_arg:Dictionary):
#	if (-1 != _trade_calculators.find(trade_calculator_arg)):	
#		_trade_calculator_owned_prod[trade_calculator_arg] = combidict_arg
#
#func add_owned_products_for_trade_calculator(trade_calculator_arg:Node, combidict_to_be_added_arg:Dictionary):
#	if (-1 != _trade_calculators.find(trade_calculator_arg)):
#		var new_owned_prod:Dictionary = Utils.sum_combidict(_trade_calculator_owned_prod[trade_calculator_arg], combidict_to_be_added_arg)
#		set_owned_products_for_trade_calculator(trade_calculator_arg,new_owned_prod)
#
#func calculate_all_trade() -> Dictionary:
#	var total_trade:Dictionary = {}
#	for trade_calculator in _trade_calculator_owned_prod.keys():
#		var trade:Dictionary = trade_calculator.calculate_trade_for_combidict(_trade_calculator_owned_prod[trade_calculator])
#
#
#		total_trade = Utils.sum_combidict(total_trade, trade)
#	return total_trade	
#
##
##
##
##
#
#
#
#
#
