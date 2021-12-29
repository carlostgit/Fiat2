extends Control


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")
const TradeCalculator = preload("res://PriceCalculation/TradeCalculator.gd")

var _persons:Array = ["Person1","Person2"]
var _person_tradecalc:Dictionary = {}
var _person_owned_dict:Dictionary = {"Person1": {"candy":1,"chocolate":2
												},
									"Person2": {"candy":1,"chocolate":2
												}  
									}


#resultados:
var _person_best_combination_dict:Dictionary = {}
var _person_trade_combination_dict:Dictionary = {}
var _sum_of_trade:Dictionary = {}
var _person_value_of_owned:Dictionary = {}
# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func init_default_example(satisf_calc_arg:Node):
	_persons.clear()
	_person_tradecalc.clear()
	_person_owned_dict.clear()
	var trade_calculator:TradeCalculator = TradeCalculator.new(satisf_calc_arg)
	add_person("Person 1", trade_calculator)
	add_person("Person 2", trade_calculator)


func get_persons()->Array:
	return _persons

	
func add_person(person_arg:String, trade_calc_arg:Node):
	if false==_persons.has(person_arg):
		_persons.append(person_arg)
#		var satisf_calc:SatisfactionCalculator = SatisfactionCalculator.new()
#		var trade_calculator:TradeCalculator = TradeCalculator.new(satisf_calc)
		self._person_tradecalc[person_arg] = trade_calc_arg
		var empty_owned_products_combidict:Dictionary = {}
		for product in Prices.get_products():
			empty_owned_products_combidict[product] = 0.0			
		self._person_owned_dict[person_arg] = empty_owned_products_combidict

		
func calculate_best_combinations():
	for person in _persons:
		var best_combidict = self.calculate_best_combination_for_person(person)
		_person_best_combination_dict[person] = best_combidict
		
func get_trade_calculator(person_arg:String)->Node:
	var node:Node = null
	if _person_tradecalc.has(person_arg):
		return _person_tradecalc[person_arg]
	return node
	
func calculate_trades():
	calculate_best_combinations()
	for person in _person_best_combination_dict.keys():
		var best_option_combidict:Dictionary = _person_best_combination_dict[person]
		
		var trade_calculator:TradeCalculator = get_trade_calculator(person)
		if trade_calculator:
			var satisfaction_calculator:SatisfactionCalculator = trade_calculator.get_satisfaction_calculator()
			var best_product_combidict:Dictionary = satisfaction_calculator.get_product_combidict_from_option_combidict(best_option_combidict)
#			print(person)
#			print("best_option_combidict")
#			print(best_option_combidict)
#			print("best_product_combidict")
#			print(best_product_combidict)
			var trade:Dictionary = self.calculate_trade_from_best_combination(person,best_product_combidict)
			self._person_trade_combination_dict[person] = trade
		
func calculate_sum_of_trade():
	var sum:Dictionary = {}
	for person in _person_trade_combination_dict.keys():
		sum = Utils.sum_combidict(sum, _person_trade_combination_dict[person])
	_sum_of_trade = sum

func get_sum_of_trade():
	return _sum_of_trade		

func calculate_trade_from_best_combination(person_arg:String, best_combination_arg:Dictionary)->Dictionary:
	var owned_combidict:Dictionary = {}
	if _person_owned_dict.has(person_arg):
		owned_combidict = _person_owned_dict[person_arg]
	var trade:Dictionary = Utils.calculate_combination_difference(best_combination_arg,owned_combidict)
	return trade
	
func calculate_best_combination_for_person(person_arg:String)->Dictionary:
	if _person_owned_dict.has(person_arg):
		var combidict:Dictionary = _person_owned_dict[person_arg]
		var budget:float = Prices.calculate_combidict_price(combidict)
#		print("Budget for "+person_arg+": "+str(budget))
		_person_value_of_owned[person_arg] = budget
		if self._person_tradecalc.has(person_arg):
			var trade_calc:TradeCalculator = self._person_tradecalc[person_arg]
#			Hay formas de guardar los resultados de:
			var best_combidict:Dictionary = trade_calc.calculate_best_combidict(budget)
			return best_combidict
	var null_dictionary = {}
	return null_dictionary

func get_owned_products(person_arg:String)->Dictionary:
	var empty_dict:Dictionary = {}
	if _person_owned_dict.has(person_arg):
		return _person_owned_dict[person_arg]
	return empty_dict

func set_amount_of_product(person_arg:String, product_arg:String, amount_arg:float):
	if _person_owned_dict.has(person_arg):
		var owned_product_dict:Dictionary = _person_owned_dict[person_arg]
		if owned_product_dict.has(product_arg):
			_person_owned_dict[person_arg][product_arg] = amount_arg
	
	
func get_traded_products(person_arg:String)->Dictionary:
	var empty_dict:Dictionary = {}
	if _person_trade_combination_dict.has(person_arg):
		return _person_trade_combination_dict[person_arg]
	return empty_dict

func calculate_value_of_owned():
	for person in self._persons:
		if _person_owned_dict.has(person):
			var combidict:Dictionary = _person_owned_dict[person]
			var budget:float = Prices.calculate_combidict_price(combidict)
			_person_value_of_owned[person] = budget

func get_value_of_owned(person_arg:String):
	if _person_value_of_owned.has(person_arg):
		return _person_value_of_owned[person_arg]
	else:
		return 0.0