extends Control


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

var _param_price_precission:float = 0.01
var _param_initial_price_change_step:float = 0.5 #Tiene que ser < 1
var _param_max_steps_calculating_new_prices:int = 80
var _param_product_step_for_best_combidict_calc:float = 5

const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")
const TradeCalculator = preload("res://PriceCalculation/TradeCalculator.gd")

#var _persons:Array = ["Person1","Person2"]
var _persons:Array = []
var _person_tradecalc:Dictionary = {}
#var _person_owned_dict:Dictionary = {"Person1": {"candy":1,"chocolate":2,"nut":2
#												},
#									"Person2": {"candy":1,"chocolate":2,"nut":2
#												}  
#									}

var _person_owned_dict:Dictionary = {}


#resultados:
var _person_best_combination_dict:Dictionary = {}
var _person_best_combination_dict_test:Dictionary = {} #Solo para pruebas
var _person_trade_combination_dict:Dictionary = {}
var _sum_of_trade:Dictionary = {}
#var _person_value_of_owned:Dictionary = {}
var _excess_products_dict:Dictionary = {} #La idea es que esto se sume de alguna manera al _sum_of_trade, para corregir errores en los precios
# Called when the node enters the scene tree for the first time.

#ajuste de precios
var _prices_log_info:PricesLogInfo = null

class PricesLogInfo:
	var _product_loginfo:Dictionary = {}
	var _pricechangestepsarray:Array = []
	
	func _init():
		for product in Prices.get_products():
			var product_info:ProductPriceAdjustmentInfo = ProductPriceAdjustmentInfo.new()
			_product_loginfo[product] = product_info
			
	func add_pricechangestep_to_array(value_arg:float):
		_pricechangestepsarray.append(value_arg)
		
	func reset_last_prices():
		for product in Prices.get_products():
			var product_info:ProductPriceAdjustmentInfo = _product_loginfo[product]
			product_info.reset_last_prices()
			
	func register_prices():
		for product in Prices.get_products():
			var product_info:ProductPriceAdjustmentInfo = _product_loginfo[product]
			var price:float = Prices.get_price_of_product(product)
#			if product == "candy":
#				print(price)
			product_info.add_price_iteration(price)
	
	func are_prices_evolving()->bool:
		
		var prices_evolving:bool = false
		for product in Prices.get_products():
			var product_info:ProductPriceAdjustmentInfo = _product_loginfo[product]
#			if 125==product_info.get_all_prices().size():
#				print("debugeo")
			if (product_info.get_prices().size()>1 and 
				false == product_info.are_prices_changing()):
				continue
			else:				
				if product_info.get_num_price_tops()<1:
					prices_evolving = true
					break;
				if product_info.get_num_price_bottoms()<1:
					prices_evolving = true
					break;
		return prices_evolving
		
	func get_product_pricesarray()->Dictionary:
		var product_pricesarray:Dictionary = {}
		for product in _product_loginfo.keys():
			var pricesinfo:ProductPriceAdjustmentInfo = _product_loginfo[product]
			product_pricesarray[product] = pricesinfo.get_prices()
		
		return product_pricesarray
		
	func get_product_allpricesarray()->Dictionary:
		var product_pricesarray:Dictionary = {}
		for product in _product_loginfo.keys():
			var pricesinfo:ProductPriceAdjustmentInfo = _product_loginfo[product]
			product_pricesarray[product] = pricesinfo.get_all_prices()
		
		return product_pricesarray
	
	func get_allpricechangesteparray()->Array:
		return _pricechangestepsarray
	
	func get_product_price_tops()->Dictionary:
		var product_pricesarray:Dictionary = {}
		for product in _product_loginfo.keys():
			var pricesinfo:ProductPriceAdjustmentInfo = _product_loginfo[product]
			product_pricesarray[product] = pricesinfo.get_num_price_tops_array()
		
		return product_pricesarray
	
	func get_product_price_bottoms()->Dictionary:
		var product_pricesarray:Dictionary = {}
		for product in _product_loginfo.keys():
			var pricesinfo:ProductPriceAdjustmentInfo = _product_loginfo[product]
			product_pricesarray[product] = pricesinfo.get_num_price_bottoms_array()
		
		return product_pricesarray
	
	
class ProductPriceAdjustmentInfo:
	const _param_iterations_log = 10
	var _iteration:int = 0
	var _min_price:float = 1.79769e308
	var _max_price:float = 0.0
#	var _min_last_iterations:float = 1.79769e308
#	var _max_last_iterations:float = 0.0
	var _last_prices:Array = []
	var _all_prices:Array = []
	
	var _num_last_price_tops:Array = []
	var _num_last_price_bottoms:Array = []
	
	func reset():
		_iteration = 0
		_min_price = 1.79769e308
		_max_price = 0.0
#		_min_last_iterations = 1.79769e308
#		_max_last_iterations = 0.0
		_last_prices.clear()
	
	func are_prices_changing():
		if _all_prices.size()>1:
			if (0 ==_all_prices[_all_prices.size()-1] - _all_prices[_all_prices.size()-2]):
				return false
			else:
				return true
		else:
			return false
		
	func get_prices():
		return _last_prices
		
	func get_all_prices():
		return _all_prices
		
	func reset_last_prices():
		_last_prices.clear()
		
	func add_price_iteration(price_arg:float):
		_iteration += 1
		if price_arg<_min_price:
			_min_price = price_arg
		if price_arg>_max_price:
			_max_price = price_arg		
		if _last_prices.size()>_param_iterations_log:
			_last_prices.remove(0)
		
		_last_prices.push_back(price_arg)
		_all_prices.push_back(price_arg)
		
		_num_last_price_tops.push_back(_calculate_num_price_tops())
		_num_last_price_bottoms.push_back(_calculate_num_price_bottoms())
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

	func get_num_price_tops_array()->Array:
		return _num_last_price_tops
	
	func get_num_price_bottoms_array()->Array:
		return _num_last_price_bottoms
	

	func get_num_price_tops()->int:
		return _num_last_price_tops.back()
	
	func get_num_price_bottoms()->int:
		return _num_last_price_bottoms.back()
	
	
	func _calculate_num_price_tops()->int:
		
#		Estaría bien registrar esto, para poder verlo gráficamente
		var num_max_price_tops:int = 0
		var last_price:float = 0.0
		var last_price_going_up:bool = true
		var count:int = 0
		for price in _last_prices:
			if price>last_price:
				last_price_going_up = true;
			if price<last_price:
				if last_price_going_up and count>1:
					num_max_price_tops += 1
				last_price_going_up = false;
			last_price = price
			count += 1
		return num_max_price_tops
	
	
	func _calculate_num_price_bottoms()->int:
		var num_min_price_bottoms:int = 0
		var last_price:float = 0.0
		var last_price_going_up:bool = true
		var count:int = 0
		for price in _last_prices:
			if price>last_price:
				if false == last_price_going_up and count>1:
					num_min_price_bottoms += 1
				last_price_going_up = true;
			if price<last_price:
				last_price_going_up = false;
			last_price = price
			count += 1
		return num_min_price_bottoms
	
func _init():
	_prices_log_info = PricesLogInfo.new()
	_excess_products_dict.clear()
	

func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func init_default_example(satisf_calc_arg:Node):
	_excess_products_dict.clear()
	_persons.clear()
	_person_tradecalc.clear()
	_person_owned_dict.clear()
	var trade_calculator:TradeCalculator = TradeCalculator.new(satisf_calc_arg)
	add_person("Person 1", trade_calculator)
	add_person("Person 2", trade_calculator)
	
	_person_owned_dict = {"Person 1": {"candy":1,"chocolate":20,"nut":10
												},
									"Person 2": {"candy":1,"chocolate":40,"nut":10
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
		
func _calculate_best_combinations():
	for person in _persons:
		var best_combidict = self._calculate_best_combination_for_person(person)
		_person_best_combination_dict[person] = best_combidict

#func _calculate_best_combinations_using_func(best_comb_func_to_use_arg:String):
#	for person in _persons:
##		var best_combidict = self._calculate_best_combination_for_person(person)
#		var best_combidict = self._calculate_best_combination_for_person_using_func(best_comb_func_to_use_arg,person)
#		_person_best_combination_dict[person] = best_combidict
		
func get_trade_calculator(person_arg:String)->Node:
	var node:Node = null
	if _person_tradecalc.has(person_arg):
		return _person_tradecalc[person_arg]
	return node

func calculate_trades_with_current_best_combinations():
	
	for person in _person_best_combination_dict.keys():
		calculate_trade_for_person_with_current_best_combinations(person)
#		var best_option_combidict:Dictionary = _person_best_combination_dict[person]
#
#		var trade_calculator:TradeCalculator = get_trade_calculator(person)
#		if trade_calculator:
#			var satisfaction_calculator:SatisfactionCalculator = trade_calculator.get_satisfaction_calculator()
#			var best_product_combidict:Dictionary = satisfaction_calculator.get_product_combidict_from_option_combidict(best_option_combidict)
##			print(person)
##			print("best_option_combidict")
##			print(best_option_combidict)
##			print("best_product_combidict")
##			print(best_product_combidict)
#			var trade:Dictionary = self._calculate_trade_from_best_combination(person,best_product_combidict)
#			self._person_trade_combination_dict[person] = trade

func calculate_trade_for_person_with_current_best_combinations(person_arg:String)->Dictionary:
	var best_option_combidict:Dictionary = _person_best_combination_dict[person_arg]
		
	var trade_calculator:TradeCalculator = get_trade_calculator(person_arg)
	if trade_calculator:
		var satisfaction_calculator:SatisfactionCalculator = trade_calculator.get_satisfaction_calculator()
		var best_product_combidict:Dictionary = satisfaction_calculator.get_product_combidict_from_option_combidict(best_option_combidict)
#			print(person)
#			print("best_option_combidict")
#			print(best_option_combidict)
#			print("best_product_combidict")
#			print(best_product_combidict)
		var trade:Dictionary = self._calculate_trade_from_best_combination(person_arg,best_product_combidict)
		
		self._person_trade_combination_dict[person_arg] = trade
		return trade
	self._person_trade_combination_dict[person_arg] = {}
	return {}
	


func calculate_sum_of_trade():
	var sum:Dictionary = {}
	for person in _person_trade_combination_dict.keys():
		sum = Utils.sum_combidict(sum, _person_trade_combination_dict[person])
	_sum_of_trade = sum

func get_sum_of_trade():
	return _sum_of_trade		

func _calculate_trade_from_best_combination(person_arg:String, best_combination_arg:Dictionary)->Dictionary:
	var owned_combidict:Dictionary = {}
	if _person_owned_dict.has(person_arg):
		owned_combidict = _person_owned_dict[person_arg]
	var trade:Dictionary = Utils.calculate_combination_difference(best_combination_arg,owned_combidict)
	return trade
	
func _calculate_best_combination_for_person(person_arg:String)->Dictionary:
	if _person_owned_dict.has(person_arg):
#		var combidict:Dictionary = _person_owned_dict[person_arg]
#		var budget:float = Prices.calculate_combidict_price(combidict)
##		print("Budget for "+person_arg+": "+str(budget))
#		_person_value_of_owned[person_arg] = budget
		var budget:float = self.get_value_of_owned(person_arg)
		if self._person_tradecalc.has(person_arg):
			var trade_calc:TradeCalculator = self._person_tradecalc[person_arg]
			
			var best_combidict:Dictionary = trade_calc.calculate_best_combidict(budget)
			

#			El cálculo tendría que hacerse con pasos de precisión de decimales, y el metodo interpolaría para resultados intermedios
			return best_combidict
	var null_dictionary = {}
	return null_dictionary


func get_owned_products(person_arg:String)->Dictionary:
	var empty_dict:Dictionary = {}
	if _person_owned_dict.has(person_arg):
		return _person_owned_dict[person_arg]
	return empty_dict

func set_owned_products(person_arg:String, owned_product:Dictionary):
	if _person_owned_dict.has(person_arg):
		_person_owned_dict[person_arg]=owned_product.duplicate()

func add_owned_products(person_arg:String, owned_product_to_add:Dictionary):
	if _person_owned_dict.has(person_arg):
		var owned_prod_dict:Dictionary = _person_owned_dict[person_arg]
		for product in owned_product_to_add.keys():
			var amount_to_add:float = owned_product_to_add[product]
			if owned_prod_dict.has(product):
				var old_amount = owned_prod_dict[product]
				var total_amount:float = amount_to_add+old_amount
				owned_prod_dict[product] = total_amount
			else:
				assert(product in PriceCalculationGlobals._products)
				owned_prod_dict[product] = amount_to_add
		_person_owned_dict[person_arg] = owned_prod_dict

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

#func calculate_value_of_owned():
#	for person in self._persons:
#		if _person_owned_dict.has(person):
#			var combidict:Dictionary = _person_owned_dict[person]
#			var budget:float = Prices.calculate_combidict_price(combidict)
#			_person_value_of_owned[person] = budget

func get_value_of_owned(person_arg:String):
#	if _person_value_of_owned.has(person_arg):
#		return _person_value_of_owned[person_arg]
#	else:
#		return 0.0
#	for person in self._persons:
	if _person_owned_dict.has(person_arg):
		var combidict:Dictionary = _person_owned_dict[person_arg]
		var budget:float = Prices.calculate_combidict_price(combidict)
#			_person_value_of_owned[person] = budget
		return budget
	return 0

func calculate_new_prices():

	var exit:bool = false
	var count:int = 0
	var max_count:int = _param_max_steps_calculating_new_prices	
	var param_price_change_step:float = _param_initial_price_change_step #Tiene que ser < 1
	var param_price_precission:float = _param_price_precission
	
	while false==exit:
		count += 1
#		if 30==count:
#			print(count)
		var price_changed:bool = _change_prices(param_price_change_step)
		_prices_log_info.register_prices()
		var prices_evolving:bool = _prices_log_info.are_prices_evolving()
		_prices_log_info.add_pricechangestep_to_array(param_price_change_step)
		
#		assert(false)
#		Aquí falla algo. Esto tarda muchos pasos en llegar a unos precios precisos
		if false==prices_evolving:
			if param_price_change_step<param_price_precission:
				break
			elif false == price_changed:
				break
			else:
				param_price_change_step = param_price_change_step/2.0
				_prices_log_info.reset_last_prices()
		if count>max_count:
			break
			
	set_excess_products(_sum_of_trade)

#		if false == prices_evolving or count>max_count:
#			exit=true
		
func _change_prices(param_price_change_step_arg:float)->bool:
	var price_changed:bool = false
#	if (_param_initial_price_change_step<=param_price_change_step_arg):
##		La primera vez se llama a _calculate_best_combinations, y el resto de veces a _adjust_best_combinations
#		_calculate_best_combinations()
#	else:
	var budget_step = 0.01
	var max_num_steps = 5
	_adjust_best_combinations(budget_step,max_num_steps)
	
#
	calculate_trades_with_current_best_combinations()
	calculate_sum_of_trade()
	var new_prices_increment:Dictionary = _calculate_new_prices_increment(param_price_change_step_arg)

	for product in Prices.get_products():
		if product != Prices.get_currency():
			if new_prices_increment.has(product):
				var increment:float = new_prices_increment[product]
				if increment!=0:					
					var current_price:float = Prices.get_price_of_product(product)
					var new_price = current_price+current_price*increment

					Prices.set_price_of_product(product, new_price)
					price_changed = true
	return price_changed

func _calculate_new_prices_increment(param_price_change_step_arg:float):
#	var new_prices_increment:Dictionary = _sum_of_trade.duplicate() #Creo que esto sobra
	var new_prices_increment:Dictionary = {}
	
	var sum_of_trade_and_excess_trade = Utils.sum_combidict(_sum_of_trade,_excess_products_dict)
	
	var amount_of_currency_excess = 0.0
#	for product in _sum_of_trade.keys():
#		if product == Prices.get_currency():
#			amount_of_currency_excess = _sum_of_trade[product]
			
	if (sum_of_trade_and_excess_trade.has(Prices.get_currency())):
		amount_of_currency_excess = sum_of_trade_and_excess_trade[Prices.get_currency()]
				
	var excess_relative_to_currency:Dictionary = {}
	for product in sum_of_trade_and_excess_trade.keys():
		var amount = sum_of_trade_and_excess_trade[product]
		excess_relative_to_currency[product] = amount - amount_of_currency_excess
		#	Añadimos el _excess_products_dict
		
	#		
	
	var max_amount_of_product_excess=0.0
	for product in excess_relative_to_currency.keys():
		var amount = abs(excess_relative_to_currency[product])
		if amount > max_amount_of_product_excess:
			max_amount_of_product_excess = amount
	
	var param_min_product_excess_to_change_price = 0.0
	
	#Este parámetro deberían pasarse por argumento al método calculate_new_prices_increment():
	var param_price_change_step = param_price_change_step_arg 

	if (max_amount_of_product_excess > param_min_product_excess_to_change_price):
		for product in excess_relative_to_currency.keys():
			var amount = excess_relative_to_currency[product]

			new_prices_increment[product] = param_price_change_step*amount/max_amount_of_product_excess
		
	return new_prices_increment
	
		
func get_last_price_calculation_prices()->Dictionary:
	return _prices_log_info.get_product_pricesarray()

func get_all_price_calculation_prices()->Dictionary:
	return _prices_log_info.get_product_allpricesarray()

func get_all_price_change_step()->Array:
	return _prices_log_info.get_allpricechangesteparray()
	
func get_product_price_tops()->Dictionary:
	return _prices_log_info.get_product_price_tops()
		
func get_product_price_bottoms()->Dictionary:
	return _prices_log_info.get_product_price_bottoms()

func set_excess_products(excess_product_arg:Dictionary)->void:
	self._excess_products_dict = Utils.deep_copy(excess_product_arg)
	
	
#Código de prueba
#			TODO: Probar a usar 
#			func adjust_best_combidict(budget_arg:float, current_combidict:Dictionary, budget_step_arg):
#Hacer los siguientes métodos:
#func _adjust_best_combinations():
#func _adjust_best_combination_for_person(person_arg:String,current_best_combidict:Dictionary)->Dictionary:
#Cambiar el método:
#func calculate_trades():
#para que no se llame a calculate_best_combinations()
#Habría que llamar a calculate_best_combinations() o adjust_best_combinations antes de llamar a calculate_trades
#Fin del código de pruebaa

func _adjust_best_combinations(budget_step:float,max_num_steps:int):
	for person in _persons:
#		if _person_best_combination_dict.has(person)==false:
#			var empty_combidict:Dictionary = {}
#			_person_best_combination_dict[person] = empty_combidict
		self.adjust_best_combination_for_person_with_max_num_steps(person,budget_step,max_num_steps)

func _adjust_best_combinations_test(budget_step:float,max_num_steps:int):
	for person in _persons:
		self.adjust_best_combination_for_person_with_max_num_steps(person,budget_step,max_num_steps)
		


func adjust_best_combination_for_person_with_max_num_steps(person_arg:String, budget_step:float,max_num_steps:int)->Dictionary:
	if _person_owned_dict.has(person_arg):
#		var combidict:Dictionary = _person_owned_dict[person_arg]
#		var budget:float = Prices.calculate_combidict_price(combidict)
##		print("Budget for "+person_arg+": "+str(budget))
#		_person_value_of_owned[person_arg] = budget
#
#		var budget:float = self.get_value_of_owned(person_arg)
		if self._person_tradecalc.has(person_arg):
			var trade_calc:TradeCalculator = self._person_tradecalc[person_arg]
			
			if _person_best_combination_dict.has(person_arg)==false:
				var empty_combidict:Dictionary = {}
				_person_best_combination_dict[person_arg] = empty_combidict			
			var current_best_combidict = _person_best_combination_dict[person_arg]
#			var best_combidict:Dictionary = trade_calc.adjust_best_combidict(budget,current_best_combidict_arg,budget_step,max_num_steps)
#			TODO: Probar adjust_best_combidict_changing_step
#			var init_budget_step = budget_step*8
#			var best_combidict:Dictionary = trade_calc.adjust_best_combidict_changing_step(budget,current_best_combidict,init_budget_step,budget_step,max_num_steps)
#			_person_best_combination_dict[person_arg] = best_combidict
#
			var best_combidict:Dictionary = improve_combination(trade_calc,_person_owned_dict[person_arg], current_best_combidict,budget_step,max_num_steps)
			_person_best_combination_dict[person_arg] = best_combidict
#			El cálculo tendría que hacerse con pasos de precisión de decimales, y el metodo interpolaría para resultados intermedios
			return best_combidict
	var null_dictionary = {}
	_person_best_combination_dict[person_arg]=null_dictionary
	return null_dictionary

func improve_combination(trade_calc_arg:TradeCalculator, owned_combidict_arg:Dictionary, current_best_combidict_arg:Dictionary,budget_step:float,max_num_steps:int)->Dictionary:

	var budget:float = Prices.calculate_combidict_price(owned_combidict_arg)
	var init_budget_step = budget_step*8
	var best_combidict:Dictionary = trade_calc_arg.adjust_best_combidict_changing_step(budget,current_best_combidict_arg,init_budget_step,budget_step,max_num_steps)
#			El cálculo tendría que hacerse con pasos de precisión de decimales, y el metodo interpolaría para resultados intermedios
	return best_combidict


func calculate_trades():
	for person in self._persons:
		calculate_trade_for_person(person)

func adjust_best_combination_for_person(person_arg:String):
	var budget_step = 0.01
	var max_num_steps = 5
	adjust_best_combination_for_person_with_max_num_steps(person_arg,budget_step,max_num_steps)
		
func calculate_trade_for_person(person_arg:String)->Dictionary:
	adjust_best_combination_for_person(person_arg)
	return calculate_trade_for_person_with_current_best_combinations(person_arg)
	
func calculate_consumption_for_person_with_current_best_combinations(person_arg:String)->Dictionary:
	var best_option_combidict:Dictionary = _person_best_combination_dict[person_arg]
		
	var trade_calculator:TradeCalculator = get_trade_calculator(person_arg)
	if trade_calculator:
		var satisfaction_calculator:SatisfactionCalculator = trade_calculator.get_satisfaction_calculator()		
		var consumption_option_combidict:Dictionary = satisfaction_calculator.get_optidict_of_type_from_optidict(best_option_combidict, "consumption")		
		var consumption_product_combidict:Dictionary = satisfaction_calculator.get_product_combidict_from_option_combidict(consumption_option_combidict)
		
		return consumption_product_combidict
	
	return {}


