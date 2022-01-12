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

#ajuste de precios
var _prices_log_info:PricesLogInfo = null

class PricesLogInfo:
	var _product_loginfo:Dictionary = {}
	
	func _init():
		for product in Prices.get_products():
			var product_info:ProductPriceAdjustmentInfo = ProductPriceAdjustmentInfo.new()
			_product_loginfo[product] = product_info
			
	func register_prices():
		for product in Prices.get_products():
			var product_info:ProductPriceAdjustmentInfo = _product_loginfo[product]
			var price:float = Prices.get_price_of_product(product)
			product_info.add_price_iteration(price)
	
	func are_prices_evolving()->bool:
		var prices_evolving:bool = false
		for product in Prices.get_products():
			var product_info:ProductPriceAdjustmentInfo = _product_loginfo[product]
			if product_info.get_num_price_tops()<2:
				prices_evolving = true
				break;
			if product_info.get_num_price_bottoms()<2:
				prices_evolving = true
				break;
		return prices_evolving
		
	func get_product_pricesarray()->Dictionary:
		var product_pricesarray:Dictionary = {}
		for product in _product_loginfo.keys():
			var pricesinfo:ProductPriceAdjustmentInfo = _product_loginfo[product]
			product_pricesarray[product] = pricesinfo.get_prices()
		
		return product_pricesarray
	
class ProductPriceAdjustmentInfo:
	const _param_iterations_log = 10
	var _iteration:int = 0
	var _min_price:float = 1.79769e308
	var _max_price:float = 0.0
#	var _min_last_iterations:float = 1.79769e308
#	var _max_last_iterations:float = 0.0
	var _last_prices:Array = []
	
	func reset():
		_iteration = 0
		_min_price = 1.79769e308
		_max_price = 0.0
#		_min_last_iterations = 1.79769e308
#		_max_last_iterations = 0.0
		_last_prices.clear()
		
	func get_prices():
		return _last_prices

	func add_price_iteration(price_arg:float):
		_iteration += 1
		if price_arg<_min_price:
			_min_price = price_arg
		if price_arg>_max_price:
			_max_price = price_arg		
		if _last_prices.size()>_param_iterations_log:
			_last_prices.remove(0)
		
		_last_prices.push_back(price_arg)
		
#	func get_max_price_from_last_iterations():
#		var max_price:float = 0.0
#		for i in range(_last_prices.size()-1, 0, -1):
#			var price:float = _last_prices[i]
#			if price>max_price:
#				max_price = price				
#		return max_price
#
#	func get_min_price_from_last_iterations():
#		var min_price:float = 1.79769e308
#		for i in range(_last_prices.size()-1, 0, -1):
#			var price:float = _last_prices[i]
#			if price>min_price:
#				min_price = price				
#		return min_price
	
	func get_num_price_tops()->int:
		var num_max_price_tops:int = 0
		var last_price:float = 0.0
		var last_price_going_up:bool = true
		var count:int = 0
		for price in _last_prices:
			if price>=last_price:
				last_price_going_up = true;
			if price<=last_price:
				if last_price_going_up and count>1:
					num_max_price_tops += 1
				last_price_going_up = false;
			last_price = price
			count += 1
		return num_max_price_tops
	
	func get_num_price_bottoms()->int:
		var num_min_price_bottoms:int = 0
		var last_price:float = 0.0
		var last_price_going_up:bool = true
		var count:int = 0
		for price in _last_prices:
			if price>=last_price:
				if false == last_price_going_up and count>1:
					num_min_price_bottoms += 1
				last_price_going_up = true;
			if price<=last_price:
				last_price_going_up = false;
			last_price = price
			count += 1
		return num_min_price_bottoms
	
func _init():
	_prices_log_info = PricesLogInfo.new()

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
	
	_person_owned_dict = {"Person 1": {"candy":1,"chocolate":20
												},
									"Person 2": {"candy":1,"chocolate":40
												}  
									}
	

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

func remove_person(person_arg:String):
	if _persons.has(person_arg):
		_persons.erase(person_arg)
		
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
			var best_combidict:Dictionary = trade_calc.calculate_best_combidict_simple(budget)
#			TODO: Hacer una versión precalculada (para unos precios), de calculate_best_combidict en TradeCalculator
#			El cálculo tendría que hacerse con pasos de precisión de decimales, y el metodo interpolaría para resultados intermedios
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

func calculate_new_prices():
#	TODO: Hacer versión de calculate_new_prices() y change_prices_step()
#	en las que:
#	Haya un control para saber cuándo dejar de calcular.
#	Haya un control para saber cuándo empezar a hacer cáclulos con mejor precisión
#		Para eso, habría que:
#			Tener en cuenta si el precio de todos los productos no hace otra cosa que variar entre un máximo y mínimo
#			Tal vez el máximo y mínimo tenga que ser solo de los últimos pasosç
#			Puedo ir guardando los mínimos y máximos de precio absolutos, y los últimos mínimos y máximos
#
	var exit:bool = false
	var count:int = 0
	var max_count:int = 40
	
	var param_price_change_step:float = 0.5 #Tiene que ser < 1
	var param_price_precission:float = 0.001
	
	while false==exit:
		count += 1
		var price_changed:bool = change_prices_step(param_price_change_step)
		_prices_log_info.register_prices()
		var prices_evolving:bool = _prices_log_info.are_prices_evolving()
		if false==prices_evolving:
			if param_price_change_step<param_price_precission:
				break
			else:
				param_price_change_step = param_price_change_step/2.0
		if count>max_count:
			break

#		if false == prices_evolving or count>max_count:
#			exit=true
		
func change_prices_step(param_price_change_step_arg:float)->bool:
	var price_changed:bool = false
	calculate_trades()
	calculate_sum_of_trade()
	var new_prices_increment:Dictionary = calculate_new_prices_increment(param_price_change_step_arg)
#	print("new_prices_increment")
#	print(new_prices_increment)
#	todo: Actualizar precios en Prices
#	Todo. Cambiar esto. Es mejor que los cambios de precios sean proporcionales a los precios actuales
	var param_min_price:float = 0.001 
	for product in Prices.get_products():
		if product != Prices.get_currency():
			if new_prices_increment.has(product):
				var increment:float = new_prices_increment[product]
				if increment!=0:					
					var current_price:float = Prices.get_price_of_product(product)
#					var new_price = current_price+increment
#					TODO: PROBAR LO SIGUIENTE:
#					tal vez debería hacer algo como:
					var new_price = current_price+current_price*increment
					if new_price<param_min_price:
						new_price = param_min_price
					Prices.set_price_of_product(product, new_price)
					price_changed = true
	return price_changed

func calculate_new_prices_increment(param_price_change_step_arg:float):
	var new_prices_increment:Dictionary = _sum_of_trade.duplicate()
	var amount_of_currency_excess = 0.0
	for product in _sum_of_trade.keys():
		if product == Prices.get_currency():
			amount_of_currency_excess = _sum_of_trade[product]
		
	var excess_relative_to_currency:Dictionary = {}
	for product in _sum_of_trade.keys():
		var amount = _sum_of_trade[product]
		excess_relative_to_currency[product] = amount - amount_of_currency_excess
	
	
	var max_amount_of_product_excess=0.0
	for product in excess_relative_to_currency.keys():
		var amount = abs(excess_relative_to_currency[product])
		if amount > max_amount_of_product_excess:
			max_amount_of_product_excess = amount
	
#	TODO: Este parámetro deberá ser 0, cuando desarrolle un mejor método para controlar cuándo dejar de calcular:
	var param_min_product_excess_to_change_price = 0.0
	
	#TODO: Este parámetro deberían pasarse por argumento al método calculate_new_prices_increment():
	var param_price_change_step = param_price_change_step_arg 

	if (max_amount_of_product_excess > param_min_product_excess_to_change_price):
		for product in excess_relative_to_currency.keys():
			var amount = excess_relative_to_currency[product]

			new_prices_increment[product] = param_price_change_step*amount/max_amount_of_product_excess
		
	return new_prices_increment
	
		
func get_last_price_calculation_prices()->Dictionary:
	return _prices_log_info.get_product_pricesarray()
