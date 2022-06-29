extends Control


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

#const Polyline = preload("res://PriceCalculation/Polyline.gd")
var PolylineGroup = load("res://PriceCalculation/PolylineGroup.gd")

const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")

var _satisfaction_calculator:SatisfactionCalculator = null

#const PricesRes = preload("res://Pricecalculation/Prices.gd")

#Cosas precalculadas:
var _precalculated_combination_for_each_step:Dictionary = {}
var _max_precalculated_budget:float = 0.0
var _step_used_for_precalculation:float = 0.0

#Curvas aproximadas precualculadas:
var _precalculated_aprox_curves = null
#

# Called when the node enters the scene tree for the first time.
func _ready():
#	testeo de calculate_combination_difference
	_satisfaction_calculator = SatisfactionCalculator.new()
	_satisfaction_calculator.init_default_satisfaction()
	
#	var combination_1:Dictionary = {"chocolate": 0, "candy": 0}
#	var combination_2:Dictionary = {"chocolate": 2, "candy": 1}
#	var combination_result = calculate_combination_difference(combination_1,combination_2)
#	print ("diff: "+ str(combination_result))

	#Hay que hacer Autoload de Pricees.gd
	Prices.set_amount_of_product("candy",10.0)
	Prices.set_amount_of_product("chocolate",1.0)
	Prices.set_currency("candy")
	
	var best_combidict:Dictionary = calculate_best_combidict(2.0)
	print("best combi: "+ str(best_combidict))
	print("cost: "+ str(Prices.calculate_combidict_price(best_combidict)))
	
	
#	var bad_combi_too_much_candy:Dictionary = {"chocolate": 2, "candy": 50}
#	var trade_result_too_much_candy:Dictionary = calculate_trade_for_combidict(bad_combi_too_much_candy)
#	print("Too much candy result:")
#	print (trade_result_too_much_candy)
	
	
	
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _init(satisf_calc_arg:SatisfactionCalculator=null):
	_satisfaction_calculator=satisf_calc_arg

func get_satisfaction_calculator()->SatisfactionCalculator:
	return _satisfaction_calculator

func calculate_trade_for_combidict(combidict_arg:Dictionary)->Dictionary:
	
	var satisfaction:float =_satisfaction_calculator.calculate_satisf_of_combidict(combidict_arg)
	#Prices está en autoload, por lo que lo puedo usar en cualquier lado
	var price:float = Prices.calculate_combidict_price(combidict_arg)
		
	var best_combination:Dictionary = calculate_best_combidict(price)
	var satisfaction_of_best_combination:float = _satisfaction_calculator.calculate_satisf_of_combidict(best_combination)
	
	var combination_diff:Dictionary = {}
	if (satisfaction_of_best_combination > satisfaction):
		combination_diff = calculate_combination_difference(best_combination,combidict_arg)

	return combination_diff

#
#
#
#TODO: probar estos métodos:
#	precalculate_best_combidict_for_each_budget
#	get_precalculated_best_combidict
#	
#
func get_step_used_for_precalculation():
	return self._step_used_for_precalculation
	
func get_max_precalculated_budget():
	return self._max_precualculated_budget
	
func precalculate_best_combidict_for_each_budget(max_budget_arg:float,step_length_arg:float=1.0):
	self._precalculated_combination_for_each_step = calculate_best_combidict_for_each_budget(max_budget_arg,step_length_arg)
	self._step_used_for_precalculation = step_length_arg
	self._max_precalculated_budget = max_budget_arg
		
func get_precalculated_best_combidict(budget_arg:float)->Dictionary:
	
	var budget = budget_arg
	if (budget_arg>self._max_precalculated_budget):
		assert("No se ha precalculado para tanto presupuesto")
		budget = self._max_precalculated_budget
	if budget_arg == 0.0:
		var empty_options:Dictionary = {}
		var options:Array = _satisfaction_calculator.get_options()				
		for option in options:
			empty_options[option] = 0
		return empty_options
			
	var previous_money_step = 0.0
	for money_step in self._precalculated_combination_for_each_step.keys():
		if budget==money_step:
			return _precalculated_combination_for_each_step[money_step]
		if budget<money_step:
#			interpolamos entre los 2 pasos
			var previous_step_combi:Dictionary = {}
			if (0==previous_money_step): #Para presupuesto 0, hago una combinación con todo 0
				var options:Array = _satisfaction_calculator.get_options()				
				for option in options:
					previous_step_combi[option] = 0
			else:
				previous_step_combi = _precalculated_combination_for_each_step[previous_money_step]
				
			var next_step_combi:Dictionary = _precalculated_combination_for_each_step[money_step]
			var step_length:float = money_step-previous_money_step
			var weight_of_next:float = (budget_arg-previous_money_step)/step_length
			var weight_of_prev:float = (money_step-budget_arg)/step_length
			
			var interpolated_combi_dict:Dictionary = {}
			for product in next_step_combi.keys():
				var next_amount:float = next_step_combi[product]
				var prev_amount:float = 0.0
				if previous_step_combi.has(product):
					prev_amount = previous_step_combi[product]
					
				var interpolated_amount:float = (prev_amount*weight_of_prev)+(next_amount*weight_of_next)
				interpolated_combi_dict[product] = interpolated_amount
			
			return interpolated_combi_dict
		
		previous_money_step = money_step
	
	assert("algo ha fallado")
	return {}

#
#

func calculate_best_combidict_for_each_budget(max_budget_arg:float,step_length_arg:float=1.0)->Dictionary:
	#	Debería hacer una versión de este método, que solo recorriese una lista de combinaciones precalculadas
	
#	Prueba
	var combination_for_each_step:Dictionary = {}
#	

#	var best_combination:Dictionary = {}
	var step_length:float = step_length_arg
	
#	var products:Array = Prices.get_products()
	var options:Array = _satisfaction_calculator.get_options()
	var combination:Dictionary = {}
	for option in options:
		combination[option] = 0
	
	var left_money:float = max_budget_arg
	
#	var best_next_combination:Dictionary = combination.duplicate()
	var count = 0
	var best_previous_satisfaction = 0.0
	while true:
#		print ("left money: "+ str(left_money))	
		var end_calculating = false
		var best_product_combination:Dictionary = {}
		var best_product_satisfaction = 0.0
		var best_product_price = 0.0
		var best_increment_of_satisfaction_for_price:float = 0.0
#		print("count :"+str(count))
		var product_found = false
		for option in options:
			var trying_combination:Dictionary = combination.duplicate()
			trying_combination[option] += step_length
			var satisfaction_of_trying_combination:float = _satisfaction_calculator.calculate_satisf_of_combidict(trying_combination)
			
			var increment_of_satisfaction:float = satisfaction_of_trying_combination - best_previous_satisfaction
			
			var product:String = _satisfaction_calculator.get_product_from_option(option)
			
			var price = Prices.get_price_of_product(product)*step_length
			
#			print("product: "+ product)
#			print("satisf: "+ str(satisfaction_of_trying_combination))
			
			if price<=left_money and increment_of_satisfaction > 0.0:
				product_found = true
				
#				var satisfacton_of_trying_combination_for_price = satisfaction_of_trying_combination/price
				var increment_of_satisfaction_for_price:float = increment_of_satisfaction/price
#				print("satisf/price: "+ str(satisfacton_of_trying_combination_for_price))
#				print("satisf/price: "+ str(increment_of_satisfaction_for_price))
#				print("product: "+ product)
#				print(trying_combination)
#				print ("increment of satisf for price: " + str(increment_of_satisfaction_for_price))
				
				if increment_of_satisfaction_for_price > best_increment_of_satisfaction_for_price:
					best_product_satisfaction = satisfaction_of_trying_combination
					best_product_combination = trying_combination
					best_product_price = price
					best_increment_of_satisfaction_for_price = increment_of_satisfaction_for_price
		
		
		if false==product_found:
			
			break
		
		left_money -= best_product_price
		combination = best_product_combination
		best_previous_satisfaction = best_product_satisfaction
		
#		Prueba:
		combination_for_each_step[max_budget_arg-left_money]=best_product_combination
#		

		count += 1

	return combination_for_each_step

func calculate_best_combidict_simple_with_continuity_with_product_step(money_arg:float,step_arg:float)->Dictionary:
	return calculate_best_combidict_simple_with_continuity(money_arg,step_arg)

func calculate_best_combidict_simple_with_continuity(money_arg:float, step_arg:float=1.0)->Dictionary:

	TimeMeasurement.start("calculate_best_combidict_simple_with_continuity")
	
	var step_length:float = step_arg
	
	var options:Array = _satisfaction_calculator.get_options()
	var combination:Dictionary = {}
	for option in options:
		combination[option] = 0
	
	var left_money:float = money_arg
	
	var count = 0
	var max_count = 10000 #En caso de error
	var best_previous_satisfaction = 0.0
	while true:

		var best_product_combination:Dictionary = {}
		var best_product_satisfaction = 0.0
		var best_product_price = 0.0
		var best_increment_of_satisfaction_for_price:float = 0.0

		var product_found = false
		var run_out_of_money = false
		for option in options:
#			PerformanceUtils.start("duplicate")
			var trying_combination:Dictionary = combination.duplicate()
#			PerformanceUtils.stop("duplicate")
			trying_combination[option] += step_length
			TimeMeasurement.start("_satisfaction_calculator.calculate_satisf_of_combidict")
			var satisfaction_of_trying_combination:float = _satisfaction_calculator.calculate_satisf_of_combidict(trying_combination)
			TimeMeasurement.stop("_satisfaction_calculator.calculate_satisf_of_combidict")
			var increment_of_satisfaction:float = satisfaction_of_trying_combination - best_previous_satisfaction
			var product:String = _satisfaction_calculator.get_product_from_option(option)
			var price = Prices.get_price_of_product(product)*step_length
			
			if increment_of_satisfaction > 0.0:
				product_found = true
				
				var increment_of_satisfaction_for_price:float = increment_of_satisfaction/price

				if increment_of_satisfaction_for_price > best_increment_of_satisfaction_for_price:
					
					if left_money<price:
						var portion_payable:float = left_money/price
						var portion_non_payable:float = 1-(left_money/price)
						trying_combination[option] -= portion_non_payable*step_length
						increment_of_satisfaction *= portion_payable
						satisfaction_of_trying_combination *= portion_payable
						price *= portion_payable		
					
					best_product_satisfaction = satisfaction_of_trying_combination
					best_product_combination = trying_combination
					best_product_price = price
					best_increment_of_satisfaction_for_price = increment_of_satisfaction_for_price		
			
		if product_found:
			left_money -= best_product_price
			combination = best_product_combination
			best_previous_satisfaction = best_product_satisfaction
			if left_money<=0:
				break
		else:
			break
		count += 1
		if count>max_count:
			 break
			
	TimeMeasurement.stop("calculate_best_combidict_simple_with_continuity")
	return combination	


func calculate_best_combidict_simple_with_continuity_budget_step(money_arg:float, step_arg:float)->Dictionary:
#	TODO: Mejorar el nombre de este método
#	TODO: pasar el paso en el argumento
#	
#	TODO: hacer que el paso constanto sea en la cantidad de dinero

#	PerformanceUtils.start("calculate_best_combidict_simple_with_continuity")
	
	var step_length:float = step_arg
	
	var options:Array = _satisfaction_calculator.get_options()
	var combination:Dictionary = {}
	for option in options:
		combination[option] = 0
	
	var left_money:float = money_arg
	
	var count = 0
	var max_count = 10000 #En caso de error
	var best_previous_satisfaction = 0.0
	while true:

		var best_product_combination:Dictionary = {}
		var best_product_satisfaction = 0.0
		var best_product_amount_of_money = 0.0
		var best_increment_of_satisfaction_for_price:float = 0.0

		var product_found = false
		var run_out_of_money = false
		for option in options:
			var amount_of_money_to_spend = step_length
			var product:String = _satisfaction_calculator.get_product_from_option(option)
			var amount_of_option = amount_of_money_to_spend/Prices.get_price_of_product(product)
#			PerformanceUtils.start("duplicate")
			var trying_combination:Dictionary = combination.duplicate()
#			PerformanceUtils.stop("duplicate")
			trying_combination[option] += amount_of_option
			TimeMeasurement.start("_satisfaction_calculator.calculate_satisf_of_combidict")
			var satisfaction_of_trying_combination:float = _satisfaction_calculator.calculate_satisf_of_combidict(trying_combination)
			TimeMeasurement.stop("_satisfaction_calculator.calculate_satisf_of_combidict")
			var increment_of_satisfaction:float = satisfaction_of_trying_combination - best_previous_satisfaction
			
			if increment_of_satisfaction > 0.0:
				product_found = true
				
				var increment_of_satisfaction_for_price:float = increment_of_satisfaction/amount_of_money_to_spend

				if increment_of_satisfaction_for_price > best_increment_of_satisfaction_for_price:
					
					if left_money<amount_of_money_to_spend:
						var portion_payable:float = left_money/amount_of_money_to_spend
						var portion_non_payable:float = 1-(left_money/amount_of_money_to_spend)
						trying_combination[option] -= portion_non_payable*amount_of_option
						increment_of_satisfaction *= portion_payable
						satisfaction_of_trying_combination *= portion_payable
						amount_of_money_to_spend *= portion_payable		
					
					best_product_satisfaction = satisfaction_of_trying_combination
					best_product_combination = trying_combination
					best_product_amount_of_money = amount_of_money_to_spend
					best_increment_of_satisfaction_for_price = increment_of_satisfaction_for_price		
			
		if product_found:
			left_money -= best_product_amount_of_money
			combination = best_product_combination
			best_previous_satisfaction = best_product_satisfaction
			if left_money<=0:
				break
		else:
			break
		count += 1
		if count>max_count:
			 break
			
#	PerformanceUtils.stop("calculate_best_combidict_simple_with_continuity")
	return combination


func precalculate_aprox_best_combidict_curves_for_a_budget_range(max_amount_of_money_arg:float, calc_step_arg:float):

	var polyline_group = PolylineGroup.new()

	var combination_for_each_budget:Dictionary = {}

	var step_length:float = calc_step_arg

	var options:Array = _satisfaction_calculator.get_options()
	var combination:Dictionary = {}
	for option in options:
		combination[option] = 0
		polyline_group.add_point(option, 0, 0)

	var left_money:float = max_amount_of_money_arg

	var count = 0
	var max_count = 10000 #En caso de error
	var best_previous_satisfaction = 0.0
	while true:

		var best_product_combination:Dictionary = {}
		var best_product_satisfaction = 0.0
		var best_product_amount_of_money = 0.0
		var best_increment_of_satisfaction_for_price:float = 0.0
		var best_option = ""

		var product_found = false
		var current_product_selected = ""
		var current_amount_of_option:float = 0 
		var run_out_of_money = false
		for option in options:
			var amount_of_money_to_spend = step_length
			var product:String = _satisfaction_calculator.get_product_from_option(option)
			var amount_of_option = amount_of_money_to_spend/Prices.get_price_of_product(product)

			var trying_combination:Dictionary = combination.duplicate()

			trying_combination[option] += amount_of_option

			var satisfaction_of_trying_combination:float = _satisfaction_calculator.calculate_satisf_of_combidict(trying_combination)

			var increment_of_satisfaction:float = satisfaction_of_trying_combination - best_previous_satisfaction

			if increment_of_satisfaction > 0.0:
				product_found = true
				current_product_selected = option
				current_amount_of_option = amount_of_option

				var increment_of_satisfaction_for_price:float = increment_of_satisfaction/amount_of_money_to_spend

				if increment_of_satisfaction_for_price > best_increment_of_satisfaction_for_price:

					if left_money<amount_of_money_to_spend:
						var portion_payable:float = left_money/amount_of_money_to_spend
						var portion_non_payable:float = 1-(left_money/amount_of_money_to_spend)
						trying_combination[option] -= portion_non_payable*amount_of_option
						increment_of_satisfaction *= portion_payable
						satisfaction_of_trying_combination *= portion_payable
						amount_of_money_to_spend *= portion_payable		

					best_product_satisfaction = satisfaction_of_trying_combination
					best_product_combination = trying_combination
					best_product_amount_of_money = amount_of_money_to_spend
					best_increment_of_satisfaction_for_price = increment_of_satisfaction_for_price
					best_option = option

		if product_found:
			left_money -= best_product_amount_of_money
			var previous_amount_of_best_option = combination[best_option]
			combination = best_product_combination
			best_previous_satisfaction = best_product_satisfaction

			var current_budget = max_amount_of_money_arg-left_money

			var whole_amount_for_best_option = combination[best_option]
			var half_increment_for_best_option = (whole_amount_for_best_option+previous_amount_of_best_option)/2.0

			polyline_group.add_point(best_option, current_budget, half_increment_for_best_option)

			if left_money<=0:
				break
		else:
			break
		count += 1

		if count>max_count:
			 break
			
	_adjust_polyline_group_to_prices(polyline_group)

	return polyline_group

func _adjust_polyline_group_to_prices(polyline_group_arg)->void:
	var all_budget_points_array:Array = []
	var polyline_group_dict = polyline_group_arg.get_polyline_dict()
	for option in polyline_group_dict.keys():
		var points:Array = polyline_group_dict[option].get_points_array()
		for point in points:
			all_budget_points_array.append(point.x)
	
	for budget in all_budget_points_array:
		var sum_of_price:float = 0.0
		for option in polyline_group_dict.keys():
			var polyline = polyline_group_dict[option]
			var amount_of_option = polyline.get_value(budget)
			var price_of_this_amount = Prices.get_price_of_product(option)
			sum_of_price += price_of_this_amount
		
		var correcting_factor:float = 1
		if (sum_of_price!=0):
			correcting_factor = budget/sum_of_price
		for option in polyline_group_dict.keys():
			var polyline = polyline_group_dict[option]
			var amount_of_option = polyline.get_value(budget)
			polyline.set_point(budget,correcting_factor*amount_of_option)
	

func calculate_best_combidict_from_precalculated_aprox_curves(money_quant_arg:float, polyline_group_arg):
#	
	var option_amount_dict:Dictionary = {}
	var points_group_dict = polyline_group_arg.get_polyline_dict()
	for option in points_group_dict:
		var polyline = points_group_dict[option]
		var amount = polyline.get_value(money_quant_arg)
		option_amount_dict[option]=amount
		
	return option_amount_dict

func calculate_best_combidict_simple(money_arg:float)->Dictionary:

	var step_length:float = 1.0
	
	var options:Array = _satisfaction_calculator.get_options()
	var combination:Dictionary = {}
	for option in options:
		combination[option] = 0
	
	var left_money:float = money_arg
	
	var count = 0
	var max_count = 10000 #En caso de error
	var best_previous_satisfaction = 0.0
	while true:

		var best_product_combination:Dictionary = {}
		var best_product_satisfaction = 0.0
		var best_product_price = 0.0
		var best_increment_of_satisfaction_for_price:float = 0.0

		var product_found = false
		for option in options:
			var trying_combination:Dictionary = combination.duplicate()
			trying_combination[option] += step_length
			var satisfaction_of_trying_combination:float = _satisfaction_calculator.calculate_satisf_of_combidict(trying_combination)
			var increment_of_satisfaction:float = satisfaction_of_trying_combination - best_previous_satisfaction
			var product:String = _satisfaction_calculator.get_product_from_option(option)
			var price = Prices.get_price_of_product(product)*step_length
			
			if price<=left_money and increment_of_satisfaction > 0.0:
				product_found = true
				
				var increment_of_satisfaction_for_price:float = increment_of_satisfaction/price
				
				if increment_of_satisfaction_for_price > best_increment_of_satisfaction_for_price:
					best_product_satisfaction = satisfaction_of_trying_combination
					best_product_combination = trying_combination
					best_product_price = price
					best_increment_of_satisfaction_for_price = increment_of_satisfaction_for_price		
				
		
		if false==product_found:
			for option in options:
				var price:float = left_money
				var product:String = _satisfaction_calculator.get_product_from_option(option)
				var last_step_length:float = price/Prices.get_price_of_product(product)
				var trying_combination:Dictionary = combination.duplicate()
				trying_combination[option] += last_step_length
				var satisfaction_of_trying_combination:float = _satisfaction_calculator.calculate_satisf_of_combidict(trying_combination)
				var increment_of_satisfaction:float = satisfaction_of_trying_combination - best_previous_satisfaction
#				var product:String = _satisfaction_calculator.get_product_from_option(option)
#				var price = Prices.get_price_of_product(product)*step_length
				
				if price<=left_money and increment_of_satisfaction > 0.0:
					product_found = true
					var increment_of_satisfaction_for_price:float = increment_of_satisfaction/price
					
					if increment_of_satisfaction_for_price > best_increment_of_satisfaction_for_price:
						best_product_satisfaction = satisfaction_of_trying_combination
						best_product_combination = trying_combination
						best_product_price = price
						best_increment_of_satisfaction_for_price = increment_of_satisfaction_for_price		
						
		if product_found:
			left_money -= best_product_price
			combination = best_product_combination
			best_previous_satisfaction = best_product_satisfaction
		else:
			break
		count += 1
		if count>max_count:
			 break
			
	return combination	
	
func calculate_best_combidict(money_arg:float)->Dictionary:
#	Debería hacer una versión de este método, que solo recorriese una lista de combinaciones precalculadas
	
#	Prueba
#	var combination_for_each_step:Dictionary = combination_for_each_step_arg
#	

#	var best_combination:Dictionary = {}
	var step_length:float = 1.0
	
#	var products:Array = Prices.get_products()
	var options:Array = _satisfaction_calculator.get_options()
	var combination:Dictionary = {}
	for option in options:
		combination[option] = 0
	
	var left_money:float = money_arg
	
#	var best_next_combination:Dictionary = combination.duplicate()
	var count = 0
	var max_count = 10000 #En caso de error
	var best_previous_satisfaction = 0.0
	while true:
#		print ("left money: "+ str(left_money))	
		var end_calculating = false
		var best_product_combination:Dictionary = {}
		var best_product_satisfaction = 0.0
		var best_product_price = 0.0
		var best_increment_of_satisfaction_for_price:float = 0.0
#		print("count :"+str(count))
		var product_found = false
		for option in options:
			var trying_combination:Dictionary = combination.duplicate()
			trying_combination[option] += step_length 
			var satisfaction_of_trying_combination:float = _satisfaction_calculator.calculate_satisf_of_combidict(trying_combination)
			
			var increment_of_satisfaction:float = satisfaction_of_trying_combination - best_previous_satisfaction
			
			var product:String = _satisfaction_calculator.get_product_from_option(option)
			
			var price = Prices.get_price_of_product(product)*step_length
			
#			print("product: "+ product)
#			print("satisf: "+ str(satisfaction_of_trying_combination))
			
			if price<=left_money and increment_of_satisfaction > 0.0:
				product_found = true
				
#				var satisfacton_of_trying_combination_for_price = satisfaction_of_trying_combination/price
				var increment_of_satisfaction_for_price:float = increment_of_satisfaction/price
#				print("satisf/price: "+ str(satisfacton_of_trying_combination_for_price))
#				print("satisf/price: "+ str(increment_of_satisfaction_for_price))
#				print("product: "+ product)
#				print(trying_combination)
#				print ("increment of satisf for price: " + str(increment_of_satisfaction_for_price))
				
				if increment_of_satisfaction_for_price > best_increment_of_satisfaction_for_price:
					best_product_satisfaction = satisfaction_of_trying_combination
					best_product_combination = trying_combination
					best_product_price = price
					best_increment_of_satisfaction_for_price = increment_of_satisfaction_for_price
		
		
		if false==product_found:
			
			break
		
		left_money -= best_product_price
		combination = best_product_combination
		best_previous_satisfaction = best_product_satisfaction
		
#		Prueba:
#		combination_for_each_step[money_arg-left_money]=best_product_combination
#		

		count += 1
		if count>max_count:
			 break
			
	if left_money > 0:
#		Ya no se puede añadir ningún producto, pero puede que quede dinero para intercambiar productos
		var count2:int = 0
		while true:
			count2 += 1
			if count2>100:
				break			
			var change_made = false
			for option_in_combi in options:
				for new_option in options:
					if new_option!=option_in_combi:
						if combination[option_in_combi]>=step_length:
							var trying_combination:Dictionary = combination.duplicate()
						
							trying_combination[option_in_combi] -= step_length
							trying_combination[new_option] += step_length
							var satisfaction_of_trying_combination:float = _satisfaction_calculator.calculate_satisf_of_combidict(trying_combination)
			
							var increment_of_satisfaction:float = satisfaction_of_trying_combination - best_previous_satisfaction
							
							var new_product:String = _satisfaction_calculator.get_product_from_option(new_option)
							var product_in_combi:String = _satisfaction_calculator.get_product_from_option(option_in_combi)
							
							var price = (Prices.get_price_of_product(new_product)-Prices.get_price_of_product(product_in_combi))*step_length
							var almost_zero = 0.000001 
							if left_money-price >= -almost_zero and increment_of_satisfaction > 0.0:
								combination = trying_combination
								change_made = true
								left_money -= price
					if change_made:
						break
				if change_made:
					break	
			
			if false==change_made:
				break
		
	return combination
	
	
func calculate_combination_difference(combination_1_arg:Dictionary, combination_2_arg:Dictionary)->Dictionary:
	#1-2
	var return_dict:Dictionary = combination_1_arg.duplicate()
	for product_2 in combination_2_arg.keys():
		if return_dict.has(product_2):
			return_dict[product_2] = return_dict[product_2] - combination_2_arg[product_2]
		else:
			return_dict[product_2] =  - combination_2_arg[product_2]

	return return_dict


func calculate_best_combidict_from_list(money_available_arg:float, combidicts_arg:Array,combidict_satisfaction_arg:Dictionary, combidict_price_arg:Dictionary)->Dictionary:

	var best_satisfaction = -1.0
	var best_combidict:Dictionary = {}
	
	for combidict in combidict_satisfaction_arg.keys():
		var satisfaction:float = combidict_satisfaction_arg[combidict]
		if combidict_price_arg.has(combidict):

			var price:float = combidict_price_arg[combidict]
			if (money_available_arg >= price):
				if (satisfaction > best_satisfaction):
					best_combidict = combidict
					best_satisfaction = satisfaction
	
#	assert("falta esto")
	return best_combidict
	

func calculate_better_combidicts_from_list(money_available_arg:float, combidicts_arg:Array,combidict_satisfaction_arg:Dictionary, combidict_price_arg:Dictionary, satisf_of_owned_arg:float)->Array:

#	var best_satisfaction = -1.0
#	var best_combidict:Dictionary = {}
	var better_combidicts:Array = []
	
	for combidict in combidict_satisfaction_arg.keys():
		var satisfaction:float = combidict_satisfaction_arg[combidict]
		if combidict_price_arg.has(combidict):

			var price:float = combidict_price_arg[combidict]
			if (money_available_arg >= price):
				if (satisfaction > satisf_of_owned_arg):
					better_combidicts.append(combidict)
#					best_combidict = combidict
#					best_satisfaction = satisfaction
	
#	assert("falta esto")
	return better_combidicts


