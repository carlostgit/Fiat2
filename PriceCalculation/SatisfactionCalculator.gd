extends Control


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

#var _param_preference_at_0 = {"chocolate": 2.16, "candy": 4.5}
#var _maximum_satisf = {"chocolate": 10.0, "candy": 4.0}

#const Combination = preload("res://Combination.gd")

var _combos:Dictionary = {"sweets":["chocolate","candy"]}
#var _param_combo_preference_at_0 = {"sweets":10.8}
#var _param_combo_maximum_quantity_satisf = {"sweets":3.0}

#var _products = ["chocolate","candy"]
var _products = Globals._products


#const Plotter = preload("res://Plotter.gd")
const SatisfactionCurve = preload("res://PriceCalculation/SatisfactionCurve.gd")

var _option_satisf_curve_dict:Dictionary = {}
var _combo_satisf_curve_dict:Dictionary = {}

var _options:Array = ["candy_savings","chocolate_savings",
						"candy_consumption","chocolate_consumption"]

var _option_product_dict:Dictionary = { "candy_savings": "candy",
									"candy_consumption": "candy",
									"chocolate_savings": "chocolate",
									"chocolate_consumption": "chocolate",}

# Called when the node enters the scene tree for the first time.
func _ready():

#	var test_combination:Dictionary = {"chocolate": 2, "candy": 2}	
#	print(calculate_satisf_of_combidict(test_combination))

#	var param_max_satisf:float = 10
#	var param_quantity:float = 10
#	var param_satisf_at_1:float = 5
#	var preference_at_0 = calculate_param_preference_at_0(param_max_satisf, param_satisf_at_1, param_quantity)
#	_param_preference_at_0["chocolate"] = preference_at_0
#	_maximum_satisf["chocolate"] = param_max_satisf

#	var plotter:Plotter = Plotter.new(10,15)
#	plotter.set_size(Vector2(300,300))
#	plotter.updated_size()
#	var dimin_ret_fact_func_ref:FuncRef = funcref( self, "get_diminishing_returns_factor")
#	plotter.add_func_ref(dimin_ret_fact_func_ref,"dimin_ret_fact")
#	self.call_deferred("add_child",plotter)
	
#	print(calculate_param_preference_at_0(10, 1, 1))

#	var satis_curve_chocolate:SatisfactionCurve = SatisfactionCurve.new(0.56,10)
#	var satis_curve_candy:SatisfactionCurve = SatisfactionCurve.new(10,4)
#	var satis_curve_sweets:SatisfactionCurve = SatisfactionCurve.new(10.8,15)
#
#	_product_satisf_curve_dict["chocolate"]=satis_curve_chocolate
#	_product_satisf_curve_dict["candy"]=satis_curve_candy
#	_combo_satisf_curve_dict["sweets"]=satis_curve_sweets

	#init_default_satisfaction()
#	init_candy_satisfaction()
	init_chocolate_satisfaction()
	
#	plotter.add_func_ref(funcref( self, "calculate_satifaction_of_chocolate"),"chocolate")
#	plotter.add_func_ref(funcref( self, "calculate_satifaction_of_candy"),"candy")
#	plotter.add_func_ref(funcref( self, "calculate_satifaction_of_sweets"),"sweets")

	var combi = {"chocolate": 10.0, "candy": 10.0}
	print("satisf_combi: " + str(self.calculate_satisf_of_combidict(combi)))
	var combi_2 = {"chocolate": 11.0, "candy": 9.0}
	print("satisf_combi_2: " + str(self.calculate_satisf_of_combidict(combi_2)))
	
	
##test funcs
func calculate_satifaction_of_chocolate_consumption(quantity_arg:float) -> float:
	return calculate_satifaction_of_option("chocolate_consumption",quantity_arg)
func calculate_satifaction_of_candy_consumption(quantity_arg:float) -> float:
	return calculate_satifaction_of_option("candy_consumption",quantity_arg)
func calculate_satifaction_of_sweets_consumption(quantity_arg:float) -> float:
	return calculate_satifaction_of_opt_combo("sweets_consumption",quantity_arg)
##


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _init():
	init_default_satisfaction()
	
func reset()->void:
	_option_satisf_curve_dict.clear()
	_combo_satisf_curve_dict.clear()

func set_preference_for_chocolate():
	reset()
	init_chocolate_satisfaction()

func set_preference_for_candy():
	reset()
	init_candy_satisfaction()

func set_default_preference():
	reset()
	init_default_satisfaction()

func get_option_max_satisfaction(option_arg:String):
	if _option_satisf_curve_dict.has(option_arg):
		return _option_satisf_curve_dict[option_arg].get_maximum_satisf()	
	return 0
	
func get_combo_max_satisfaction(combo_arg:String):
	if _combo_satisf_curve_dict.has(combo_arg):
		return _combo_satisf_curve_dict[combo_arg].get_maximum_satisf()	
	return 0
	
func get_option_preference_at_0(option_arg:String):
	if _option_satisf_curve_dict.has(option_arg):
		return _option_satisf_curve_dict[option_arg].get_preference_at_0()
	return 0
	
func get_combo_preference_at_0(combo_arg:String):
	if _combo_satisf_curve_dict.has(combo_arg):
		return _combo_satisf_curve_dict[combo_arg].get_preference_at_0()	
	return 0

func increase_max_satisfaction_of_option(option_arg:String):
	if _option_satisf_curve_dict.has(option_arg):
		var current_max_satisf = _option_satisf_curve_dict[option_arg].get_maximum_satisf()	
		current_max_satisf += 1
		_option_satisf_curve_dict[option_arg].set_maximum_satisf(current_max_satisf)

func increase_max_satisfaction_of_combo(combo_arg:String):
	if _combo_satisf_curve_dict.has(combo_arg):
		var current_max_satisf = _combo_satisf_curve_dict[combo_arg].get_maximum_satisf()	
		current_max_satisf += 1
		_combo_satisf_curve_dict[combo_arg].set_maximum_satisf(current_max_satisf)


func set_max_satisfaction_of_option(option_arg:String,max_satisf_arg:float):
	if _option_satisf_curve_dict.has(option_arg):
		_option_satisf_curve_dict[option_arg].set_maximum_satisf(max_satisf_arg)

func set_max_satisfaction_of_combo(combo_arg:String,max_satisf_arg:float):
	if _combo_satisf_curve_dict.has(combo_arg):
		_combo_satisf_curve_dict[combo_arg].set_maximum_satisf(max_satisf_arg)



func init_default_satisfaction():
	var satis_curve_chocolate:SatisfactionCurve = SatisfactionCurve.new(2.16,10)
	var satis_curve_candy:SatisfactionCurve = SatisfactionCurve.new(2.2,14)
	var satis_curve_sweets:SatisfactionCurve = SatisfactionCurve.new(1.8, 1)
	
	_option_satisf_curve_dict["chocolate_consumption"]=satis_curve_chocolate
	_option_satisf_curve_dict["candy_consumption"]=satis_curve_candy
	_combo_satisf_curve_dict["sweets_consumption"]=satis_curve_sweets

func init_candy_satisfaction():
	var satis_curve_chocolate:SatisfactionCurve = SatisfactionCurve.new(2,5)
	var satis_curve_candy:SatisfactionCurve = SatisfactionCurve.new(2,30)
	var satis_curve_sweets:SatisfactionCurve = SatisfactionCurve.new(2, 3)
	
	_option_satisf_curve_dict["chocolate_consumption"]=satis_curve_chocolate
	_option_satisf_curve_dict["candy_consumption"]=satis_curve_candy
	_combo_satisf_curve_dict["sweets_consumption"]=satis_curve_sweets

func init_chocolate_satisfaction():
	var satis_curve_chocolate:SatisfactionCurve = SatisfactionCurve.new(2,30)
	var satis_curve_candy:SatisfactionCurve = SatisfactionCurve.new(2,5)
	var satis_curve_sweets:SatisfactionCurve = SatisfactionCurve.new(2, 3)
	
	_option_satisf_curve_dict["chocolate_consumption"]=satis_curve_chocolate
	_option_satisf_curve_dict["candy_consumption"]=satis_curve_candy
	_combo_satisf_curve_dict["sweets_consumption"]=satis_curve_sweets

func get_satisfaction_curves_of_options():
	return _option_satisf_curve_dict

func get_satisfaction_curves_of_combos():
	return _combo_satisf_curve_dict

func set_satisfaction_curve(option_arg:String, satisfaction_curve_arg:SatisfactionCurve):
	_option_satisf_curve_dict[option_arg]=satisfaction_curve_arg
	assert(option_arg in _options)

func set_combo(combo_arg:String,options_arg:Array):
	for option in options_arg:
		assert(option in _options)
	_combos[combo_arg]=options_arg

func set_satisfaction_curve_for_combo(combo_arg:String, satisfaction_curve_arg:SatisfactionCurve):
	assert(combo_arg in _combos)
	_combo_satisf_curve_dict[combo_arg]=satisfaction_curve_arg

	
#func calculate_satisf_of_combination(combination_arg:Combination):
#	if combination_arg as Combination:
#		var combination_dict:Dictionary = combination_arg.get_combidict()
#		return calculate_satisf_of_combidict(combination_dict)
#	else:
#		assert(false)


func calculate_satisf_of_combidict(combidict_arg:Dictionary) -> float:
	var satisfaction_return = 0.0
	
	var satisf_of_opt_individually = 0.0
	for option in self._options:
		var amount_of_option = combidict_arg[option]
		satisf_of_opt_individually += self.calculate_satifaction_of_option(option,amount_of_option)
#		var satisf_curve:SatisfactionCurve = _product_satisf_curve_dict[product]
#		satisf_of_prod_individually += satisf_curve.calculate_satifaction(amount_of_product)

	var satisf_of_combi = 0.0
	for combi_name in self._combos.keys():
		var amount_of_combi = 0
		var count = 0
		for option in _combos[combi_name]:
			var amount_of_option = combidict_arg[option]
			if amount_of_option < amount_of_combi or 0 == count:
				amount_of_combi = amount_of_option
			count += 1
		satisf_of_combi += self.calculate_satifaction_of_opt_combo(combi_name,amount_of_combi)

	satisfaction_return = satisf_of_opt_individually+satisf_of_combi		
		
#	print("indiv: "+str(satisf_of_prod_individually))
#	print("combi: "+str(satisf_of_combi))
	
	return satisfaction_return

#func calculate_satisfaction_of_combination(combination:Dictionary) -> float:
#	#Satisfaction of individual products
#	#{candy:3, chocolate:0}
#	var satisfaction:float = 0.0
#
#	for prod in combination.keys():
#		var num_of_prod:float = combination[prod]
#		if num_of_prod > 0.0:
#			var satisf_of_prod = calculate_satifaction_of_product(prod,num_of_prod)
#			satisfaction += satisf_of_prod
#
#	#Satisfaction of combos
#	var satisf_combos:float = calculate_satisfaction_of_prod_combos_in_combination(combination)
#
#	return satisfaction+satisf_combos

#func calculate_satisfaction_of_prod_combos_in_combination(combidict:Dictionary) -> float:
#	#Satisfaction of individual products
#	#{candy:3, chocolate:0}
#	var satisfaction:float = 0.0
#
#	#var _combo = {"sweets":["chocolate","candy"]}
#	for combo in self._combos.keys():
#		var dict_prod_of_combo_repetitions:Dictionary = Dictionary()
#		var prods_in_combo:Array = _combos[combo]
#		for prod in prods_in_combo:
#			dict_prod_of_combo_repetitions[prod] = 0.0
#
##		print ("dict_prod_of_combo_repetitions:")
##		print (dict_prod_of_combo_repetitions)
#
#		for prod in combidict.keys():
#			var num_of_prod:float = combidict[prod]
#			if num_of_prod > 0.0:
#				if dict_prod_of_combo_repetitions.has(prod):
#					dict_prod_of_combo_repetitions[prod] = num_of_prod
#
##		print ("dict_prod_of_combo_repetitions 2:")
##		print (dict_prod_of_combo_repetitions)
#
#
#		var min_of_comb_in_combination:float = 0.0
#		if (dict_prod_of_combo_repetitions.size()>0):
#			var first_prod:bool = true
#			for prod in dict_prod_of_combo_repetitions.keys():
#				var num_of_repet = dict_prod_of_combo_repetitions[prod]
#				if first_prod:
#					min_of_comb_in_combination = num_of_repet
#					first_prod = false
#				if num_of_repet < min_of_comb_in_combination:
#					min_of_comb_in_combination = num_of_repet
#		else:
#			min_of_comb_in_combination = 0.0
#
##		print ("min_of_comb_in_combination:")
##		print (min_of_comb_in_combination)
#
#
#		if min_of_comb_in_combination > 0.0:
#			var satisf_of_combo_in_combination = calculate_satifaction_of_prod_combo(combo, min_of_comb_in_combination)
#			satisfaction += satisf_of_combo_in_combination
#
#	return satisfaction

func calculate_satifaction_of_option(option_arg:String, quantity_arg:float) -> float:
	
	if false==_options.has(option_arg):
		return 0.0
	
	var ret_satisf = 0.0
#	var pref_at_0 = _param_preference_at_0[product_arg]
#	var max_satisf = _maximum_satisf[product_arg]
#
#	ret_satisf = max_satisf*get_diminishing_returns_factor(quantity_arg*pref_at_0/max_satisf)
	
	var option_satisf_curve:SatisfactionCurve = self._option_satisf_curve_dict[option_arg]
	ret_satisf = option_satisf_curve.calculate_satifaction(quantity_arg)
	
	return ret_satisf

func calculate_satifaction_of_opt_combo(combo_arg:String, quantity_arg:float) -> float:
	
	if false==self._combos.has(combo_arg):
		return 0.0
	
	var ret_satisf = 0.0
#	var pref_at_0 = self._param_combo_preference_at_0[combi_arg]
#	var max_satisf = self._param_combo_maximum_quantity_satisf[combi_arg]
#
#	ret_satisf = max_satisf*get_diminishing_returns_factor(quantity_arg*pref_at_0/max_satisf)
#
	var combo_satisf_curve:SatisfactionCurve = self._combo_satisf_curve_dict[combo_arg]
	ret_satisf = combo_satisf_curve.calculate_satifaction(quantity_arg)
	
	return ret_satisf
	
func get_options():
	return self._options
	
func get_products():
	return self._products
	
func get_product_from_option(product_arg:String):
	return _option_product_dict[product_arg]
	
func set_options(options_arg:Array):
	self._options=options_arg

func set_option_product_dict(option_product_dict_arg:Dictionary):

	self._option_product_dict = option_product_dict_arg

#func get_diminishing_returns_factor(quantity_arg:float) -> float:
#	#Voy a llamar al termino "1-(1/(0.25*x+1)^2)" Diminishing Returns Factor
#	#Esta ecuación tendría un máximo en 1, y tendría pendiente 1 en 0
#	#Es como una ecuación y = x, pero que se va haciendo más y más horizontal hasta q ya no crece la y
#	var result = 0.0
#	var denominator_square_root = 0.25*quantity_arg + 1.0;
#	var denominator = denominator_square_root*denominator_square_root
#	result = 1.0 - (1.0/denominator)
#	if result < 0:
#		result = 0
#	return result

#static func calculate_param_preference_at_0(max_satisfaction_arg:float, param_point_satisfaction_arg:float, param_point_quantity_arg:float)->float:
#	#
#	var coefficient_q:float = 0.25*param_point_quantity_arg/max_satisfaction_arg
#	var coefficient_z:float = param_point_satisfaction_arg-max_satisfaction_arg
#	var coefficient_qq:float = coefficient_q*coefficient_q
#
#	var coefficient_sqrt:float = sqrt(-4*coefficient_qq*max_satisfaction_arg/coefficient_z)
#
#	var preference_at_0:float = (-2*coefficient_q+coefficient_sqrt)/(2*coefficient_qq)
#
#	return preference_at_0

func get_option_satisf_curve_dict()->Dictionary:
	return _option_satisf_curve_dict

func get_combo_satisf_curve_dict()->Dictionary:
	return _combo_satisf_curve_dict

func get_combos()->Dictionary:
	return self._combos
