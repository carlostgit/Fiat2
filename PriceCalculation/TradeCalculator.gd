extends Control


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")

var _satisfaction_calculator:SatisfactionCalculator = null

#const PricesRes = preload("res://Pricecalculation/Prices.gd")

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

		var end_calculating = false
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
			break
		
		left_money -= best_product_price
		combination = best_product_combination
		best_previous_satisfaction = best_product_satisfaction

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


