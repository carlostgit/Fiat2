extends Control


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

#var _param_preference_at_0 = {"chocolate": 2.16, "candy": 4.5}
#var _maximum_satisf = {"chocolate": 10.0, "candy": 4.0}

#const Combination = preload("res://Combination.gd")

var _complementary_combos:Dictionary = {"sweets":["chocolate","candy"]}

#Añadir _supplementary_combos
#Cambiar _complementary_combos de tal manera que se pueda ponderar cada opción
#Por ejemplo, que por cada unidad de sweet_savings tenga que haber 1 unidad de candy, y solo 0.5 unidades de chocolate
var _supplementary_combos:Dictionary = {	"savings":	{	"candy_savings":0.1, 
															"chocolate_savings":1.0,
															"nut_savings":0.2
														}
										}

#var _products = ["chocolate","candy"]
var _products = Globals._products


#const Plotter = preload("res://Plotter.gd")
const SatisfactionCurve = preload("res://PriceCalculation/SatisfactionCurve.gd")

var _option_satisf_curve_dict:Dictionary = {}
var _complementary_combo_satisf_curve_dict:Dictionary = {}
var _supplementary_combo_satisf_curve_dict:Dictionary = {}

var _options:Array = ["candy_savings","chocolate_savings","nut_savings",
						"candy_consumption","chocolate_consumption","nut_consumption"
						]

var _option_product_dict:Dictionary = { "candy_savings": "candy",
									"candy_consumption": "candy",
									"chocolate_savings": "chocolate",
									"chocolate_consumption": "chocolate",
									"nut_savings": "nut",
									"nut_consumption": "nut"
									}
									

var _name:String = "satisf_calc_default_name"

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
	return calculate_satifaction_of_opt_complementary_combo("sweets_consumption",quantity_arg)
##


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _init(satisfaction_calculator_arg:Control = null):
	init_default_satisfaction()
	if (satisfaction_calculator_arg):
		copy(satisfaction_calculator_arg)

		
func copy(satisfaction_calculator_arg:Control):
#	El método duplicate() de Object no hace bien la copia de mis variables miembro Dictionary
	_complementary_combos = (satisfaction_calculator_arg.get_complementary_combos()).duplicate()
	_supplementary_combos = (satisfaction_calculator_arg.get_supplementary_combos()).duplicate()
	_products = (satisfaction_calculator_arg.get_products()).duplicate()
	_option_satisf_curve_dict = (satisfaction_calculator_arg.get_satisfaction_curves_of_options()).duplicate()
	_complementary_combo_satisf_curve_dict = (satisfaction_calculator_arg.get_satisfaction_curves_of_complementary_combos()).duplicate()
	_supplementary_combo_satisf_curve_dict = (satisfaction_calculator_arg.get_satisfaction_curves_of_supplementary_combos()).duplicate()
	_options = (satisfaction_calculator_arg.get_options()).duplicate()
	_option_product_dict = (satisfaction_calculator_arg.get_option_product_dict()).duplicate()
	_name = str(satisfaction_calculator_arg.get_name())

func get_name()->String:
	return _name
	
func set_name(name_arg:String):
	_name = name_arg
	
func reset()->void:
	_option_satisf_curve_dict.clear()
	_complementary_combo_satisf_curve_dict.clear()
	_supplementary_combo_satisf_curve_dict.clear()

#func copy()->Control:
#
#	var satisfaction_calculator_copy = (self.get_script()).new()
#	satisfaction_calculator_copy.set_complementary = _complementary_combos.duplicate()
##	_supplementary_combos:Dictionary = {	"savings":	{	"candy_savings":0.1, 
##	_products = Globals._products
##
##	_option_satisf_curve_dict:Dictionary = {}
##	_complementary_combo_satisf_curve_dict:Dictionary = {}
##	_supplementary_combo_satisf_curve_dict:Dictionary = {}
##	_options:Array = ["candy_savings","chocolate_savings",
##	_option_product_dict:Dictionary = { "candy_savings": "candy",
#	return satisfaction_calculator_copy

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
	
func get_complementary_combo_max_satisfaction(combo_arg:String):
	if _complementary_combo_satisf_curve_dict.has(combo_arg):
		return _complementary_combo_satisf_curve_dict[combo_arg].get_maximum_satisf()	
	return 0

func get_supplementary_combo_max_satisfaction(combo_arg:String):
	if _supplementary_combo_satisf_curve_dict.has(combo_arg):
		return _supplementary_combo_satisf_curve_dict[combo_arg].get_maximum_satisf()	
	return 0
	
func get_option_preference_at_0(option_arg:String):
	if _option_satisf_curve_dict.has(option_arg):
		return _option_satisf_curve_dict[option_arg].get_preference_at_0()
	return 0
	
func get_complementary_combo_preference_at_0(combo_arg:String):
	if _complementary_combo_satisf_curve_dict.has(combo_arg):
		return _complementary_combo_satisf_curve_dict[combo_arg].get_preference_at_0()	
	return 0

func get_supplementary_combo_preference_at_0(combo_arg:String):
	if _supplementary_combo_satisf_curve_dict.has(combo_arg):
		return _supplementary_combo_satisf_curve_dict[combo_arg].get_preference_at_0()	
	return 0

func get_satisfaction_curve_of_option(option_arg:String):
	if _option_satisf_curve_dict.has(option_arg):
		return _option_satisf_curve_dict[option_arg]
	return null

func get_satisfaction_curve_of_comp_combo(option_arg:String):
	if _complementary_combo_satisf_curve_dict.has(option_arg):
		return _complementary_combo_satisf_curve_dict[option_arg]
	return null

func get_satisfaction_curve_of_sup_combo(option_arg:String):
	if _supplementary_combo_satisf_curve_dict.has(option_arg):
		return _supplementary_combo_satisf_curve_dict[option_arg]
	return null

func increase_max_satisfaction_of_option(option_arg:String):
	if _option_satisf_curve_dict.has(option_arg):
		var current_max_satisf = _option_satisf_curve_dict[option_arg].get_maximum_satisf()	
		current_max_satisf += 1
		_option_satisf_curve_dict[option_arg].set_maximum_satisf(current_max_satisf)

func increase_max_satisfaction_of_complementary_combo(combo_arg:String):
	if _complementary_combo_satisf_curve_dict.has(combo_arg):
		var current_max_satisf = _complementary_combo_satisf_curve_dict[combo_arg].get_maximum_satisf()	
		current_max_satisf += 1
		_complementary_combo_satisf_curve_dict[combo_arg].set_maximum_satisf(current_max_satisf)

func increase_max_satisfaction_of_supplementary_combo(combo_arg:String):
	if _supplementary_combo_satisf_curve_dict.has(combo_arg):
		var current_max_satisf = _supplementary_combo_satisf_curve_dict[combo_arg].get_maximum_satisf()	
		current_max_satisf += 1
		_supplementary_combo_satisf_curve_dict[combo_arg].set_maximum_satisf(current_max_satisf)


func set_max_satisfaction_of_option(option_arg:String,max_satisf_arg:float):
	if _option_satisf_curve_dict.has(option_arg):
		_option_satisf_curve_dict[option_arg].set_maximum_satisf(max_satisf_arg)

func set_max_satisfaction_of_complementary_combo(combo_arg:String,max_satisf_arg:float):
	if _complementary_combo_satisf_curve_dict.has(combo_arg):
		_complementary_combo_satisf_curve_dict[combo_arg].set_maximum_satisf(max_satisf_arg)

func set_max_satisfaction_of_supplementary_combo(combo_arg:String,max_satisf_arg:float):
	if _supplementary_combo_satisf_curve_dict.has(combo_arg):
		_supplementary_combo_satisf_curve_dict[combo_arg].set_maximum_satisf(max_satisf_arg)


func init_default_satisfaction():
	var satis_curve_chocolate:SatisfactionCurve = SatisfactionCurve.new(2.16,10)
	var satis_curve_candy:SatisfactionCurve = SatisfactionCurve.new(2.2,14)
	var satis_curve_sweets:SatisfactionCurve = SatisfactionCurve.new(1.8, 1)
	var satis_curve_savings:SatisfactionCurve = SatisfactionCurve.new(1.2, 1)
	
	_option_satisf_curve_dict["chocolate_consumption"]=satis_curve_chocolate
	_option_satisf_curve_dict["candy_consumption"]=satis_curve_candy
	_complementary_combo_satisf_curve_dict["sweets_consumption"]=satis_curve_sweets
	_supplementary_combo_satisf_curve_dict["savings"]=satis_curve_savings

func init_candy_satisfaction():
	var satis_curve_chocolate:SatisfactionCurve = SatisfactionCurve.new(2,5)
	var satis_curve_candy:SatisfactionCurve = SatisfactionCurve.new(2,30)
	var satis_curve_sweets:SatisfactionCurve = SatisfactionCurve.new(2, 3)
	var satis_curve_savings:SatisfactionCurve = SatisfactionCurve.new(1.2, 1)
	
	_option_satisf_curve_dict["chocolate_consumption"]=satis_curve_chocolate
	_option_satisf_curve_dict["candy_consumption"]=satis_curve_candy
	_complementary_combo_satisf_curve_dict["sweets_consumption"]=satis_curve_sweets
	_supplementary_combo_satisf_curve_dict["savings"]=satis_curve_savings

func init_chocolate_satisfaction():
	var satis_curve_chocolate:SatisfactionCurve = SatisfactionCurve.new(2,30)
	var satis_curve_candy:SatisfactionCurve = SatisfactionCurve.new(2,5)
	var satis_curve_nut:SatisfactionCurve = SatisfactionCurve.new(1.2, 10)
	var satis_curve_sweets:SatisfactionCurve = SatisfactionCurve.new(2, 3)
	var satis_curve_savings:SatisfactionCurve = SatisfactionCurve.new(1.2, 1)
	
	
	_option_satisf_curve_dict["chocolate_consumption"]=satis_curve_chocolate
	_option_satisf_curve_dict["candy_consumption"]=satis_curve_candy
	_option_satisf_curve_dict["nut_consumption"]=satis_curve_nut
	_complementary_combo_satisf_curve_dict["sweets_consumption"]=satis_curve_sweets
	_supplementary_combo_satisf_curve_dict["savings"]=satis_curve_savings

func get_satisfaction_curves_of_options():
	return _option_satisf_curve_dict

func get_satisfaction_curves_of_complementary_combos():
	return _complementary_combo_satisf_curve_dict

func get_satisfaction_curves_of_supplementary_combos():
	return _supplementary_combo_satisf_curve_dict


func set_satisfaction_curve(option_arg:String, satisfaction_curve_arg:SatisfactionCurve):
	_option_satisf_curve_dict[option_arg]=satisfaction_curve_arg
	assert(option_arg in _options)

func set_complementary_combo(combo_arg:String,options_arg:Array):
	for option in options_arg:
		assert(option in _options)
	_complementary_combos[combo_arg]=options_arg

func erase_complementary_combo(combo_arg:String):
	_complementary_combos.erase(combo_arg)

func erase_option_in_comp_combo(combo_arg:String,option_arg:String):
	if _complementary_combos.has(combo_arg):
		_complementary_combos[combo_arg].erase(option_arg)

func add_option_in_comp_combo(combo_arg:String,option_arg:String):
	if _complementary_combos.has(combo_arg):
		if (option_arg in _options):			
			_complementary_combos[combo_arg].append(option_arg)


func set_supplementary_combo(combo_arg:String,options_arg:Dictionary):
	for option in options_arg:
		assert(option in _options)
	_supplementary_combos[combo_arg]=options_arg

func erase_supplementary_combo(combo_arg:String):
	_supplementary_combos.erase(combo_arg)

func erase_option_in_sup_combo(combo_arg:String,option_arg:String):
	if _supplementary_combos.has(combo_arg):
		_supplementary_combos[combo_arg].erase(option_arg)


func set_satisfaction_curve_for_complementary_combo(combo_arg:String, satisfaction_curve_arg:SatisfactionCurve):
	assert(combo_arg in _complementary_combos)
	_complementary_combo_satisf_curve_dict[combo_arg]=satisfaction_curve_arg

func set_satisfaction_curve_for_supplementary_combo(combo_arg:String, satisfaction_curve_arg:SatisfactionCurve):
	assert(combo_arg in _supplementary_combos)
	_supplementary_combo_satisf_curve_dict[combo_arg]=satisfaction_curve_arg

	
#func calculate_satisf_of_combination(combination_arg:Combination):
#	if combination_arg as Combination:
#		var combination_dict:Dictionary = combination_arg.get_combidict()
#		return calculate_satisf_of_combidict(combination_dict)
#	else:
#		assert(false)

func calculate_satisf_of_combidict_from_individual_options(combidict_arg:Dictionary) -> float:
	
	var satisf_of_opt_individually = 0.0
	for option in self._options:
		if combidict_arg.has(option):
			var amount_of_option = combidict_arg[option]
			satisf_of_opt_individually += self.calculate_satifaction_of_option(option,amount_of_option)

	return satisf_of_opt_individually


func calculate_satisf_of_combidict_from_complementary_combos(combidict_arg:Dictionary) -> float:
	
	var satisf_of_combi = 0.0
	for combi_name in self._complementary_combos.keys():
		var amount_of_combi = 0
		var count = 0
		for option in _complementary_combos[combi_name]:
			var amount_of_option = 0.0
			if combidict_arg.has(option):
				amount_of_option = combidict_arg[option]
			if amount_of_option < amount_of_combi or 0 == count:
				amount_of_combi = amount_of_option
			if amount_of_option == 0:
				break
			count += 1
		
		satisf_of_combi += self.calculate_satifaction_of_opt_complementary_combo(combi_name,amount_of_combi)

	return satisf_of_combi


func calculate_satisf_of_combidict_from_supplementary_combos(combidict_arg:Dictionary) -> float:
#	Satisfacción de los supplementary combos
#var _supplementary_combos:Dictionary = {	"savings":	{	"candy_savings":0.1, 
#															"chocolate_savings":1.0
#														}
#										}
	var satisf_of_combi:float = 0.0
	for supp_combo_name in self._supplementary_combos.keys():
		var amount_of_supp_combo = 0.0
		var supplementary_combo_dict:Dictionary = self._supplementary_combos[supp_combo_name]
		for option in supplementary_combo_dict.keys():
			var weighting_of_option:float = supplementary_combo_dict[option]
			var amount_of_option:float = 0.0
			if combidict_arg.has(option):
				amount_of_option = combidict_arg[option]
			var weigted_amount_of_option:float = weighting_of_option*amount_of_option
			amount_of_supp_combo += weigted_amount_of_option
	
		satisf_of_combi += self.calculate_satifaction_of_opt_supplementary_combo(supp_combo_name,amount_of_supp_combo)

	return satisf_of_combi


func calculate_satisf_of_combidict(combidict_arg:Dictionary) -> float:
	
	var satisf_of_opt_individually = 0.0
	satisf_of_opt_individually = calculate_satisf_of_combidict_from_individual_options(combidict_arg)

	var satisf_of_complementary_combi = 0.0
	satisf_of_complementary_combi = calculate_satisf_of_combidict_from_complementary_combos(combidict_arg)

	var satisf_of_supplementary_combi = 0.0
	satisf_of_supplementary_combi = calculate_satisf_of_combidict_from_supplementary_combos(combidict_arg)

	var satisfaction_return = 0.0
	satisfaction_return = satisf_of_opt_individually+satisf_of_complementary_combi+satisf_of_supplementary_combi
		
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

func calculate_satifaction_of_opt_complementary_combo(combo_arg:String, quantity_arg:float) -> float:
	
	if false==self._complementary_combos.has(combo_arg):
		return 0.0
	
	if false==self._complementary_combo_satisf_curve_dict.has(combo_arg):
		return 0.0
	
	
	var ret_satisf = 0.0
#	var pref_at_0 = self._param_combo_preference_at_0[combi_arg]
#	var max_satisf = self._param_combo_maximum_quantity_satisf[combi_arg]
#
#	ret_satisf = max_satisf*get_diminishing_returns_factor(quantity_arg*pref_at_0/max_satisf)
#	
	
	var combo_satisf_curve:SatisfactionCurve = self._complementary_combo_satisf_curve_dict[combo_arg]
	ret_satisf = combo_satisf_curve.calculate_satifaction(quantity_arg)
	
	return ret_satisf
	
func calculate_satifaction_of_opt_supplementary_combo(combo_arg:String, quantity_arg:float) -> float:
	
	if false==self._supplementary_combos.has(combo_arg):
		return 0.0
	
	if false==self._supplementary_combo_satisf_curve_dict.has(combo_arg):
		return 0.0
	
	
	var ret_satisf = 0.0
#	var pref_at_0 = self._param_combo_preference_at_0[combi_arg]
#	var max_satisf = self._param_combo_maximum_quantity_satisf[combi_arg]
#
#	ret_satisf = max_satisf*get_diminishing_returns_factor(quantity_arg*pref_at_0/max_satisf)
#	
	
	var combo_satisf_curve:SatisfactionCurve = self._supplementary_combo_satisf_curve_dict[combo_arg]
	ret_satisf = combo_satisf_curve.calculate_satifaction(quantity_arg)
	
	return ret_satisf

	
func get_options():
	return self._options
	
func get_products():
	return self._products
	
func add_product(product_arg:String):
	Globals.add_product(product_arg)
		
func remove_product(product_arg:String):
	Globals.remove_product(product_arg)
	
func get_product_from_option(product_arg:String):
	return _option_product_dict[product_arg]
	
func set_options(options_arg:Array):
	self._options=options_arg

func add_option(option_arg:String):
	self._options.append(option_arg)

func erase_option(option_arg:String):
	self._options.erase(option_arg)

func set_option_product_dict(option_product_dict_arg:Dictionary):

	self._option_product_dict = option_product_dict_arg

func set_product_for_option(product_arg:String,option_arg:String):
	if _option_product_dict.has(option_arg):
		if self._products.has(product_arg):
			_option_product_dict[option_arg] = product_arg

func get_option_product_dict():
	return self._option_product_dict

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

func get_complementary_combo_satisf_curve_dict()->Dictionary:
	return _complementary_combo_satisf_curve_dict

func get_supplementary_combo_satisf_curve_dict()->Dictionary:
	return _supplementary_combo_satisf_curve_dict

func get_complementary_combos()->Dictionary:
	return self._complementary_combos

func get_supplementary_combos()->Dictionary:
	return self._supplementary_combos
	
func get_options_from_complementary_combo(comp_combo_arg:String)->Array:
	var options:Array = []
	if self._complementary_combos.has(comp_combo_arg):
		options = self._complementary_combos[comp_combo_arg]
	return options

func get_options_from_supplementary_combo(sup_combo_arg:String)->Array:
	var options:Array = []
	if self._supplementary_combos.has(sup_combo_arg):
		options = self._supplementary_combos[sup_combo_arg].keys()
	return options

func get_weighted_options_from_supplementary_combo(sup_combo_arg:String)->Dictionary:
	var options_weight:Dictionary = {}
	if self._supplementary_combos.has(sup_combo_arg):
		options_weight = self._supplementary_combos[sup_combo_arg]
	return options_weight

func add_option_in_sup_combo(combo_arg:String,option_arg:String):
	add_option_with_weight_in_sup_combo(combo_arg,option_arg,1.0)
	
func add_option_with_weight_in_sup_combo(combo_arg:String,option_arg:String,weight_of_option_arg:float):
	if _supplementary_combos.has(combo_arg):
		if (option_arg in _options):
			var param_weigh_of_new_option:float = weight_of_option_arg
			if false == _supplementary_combos[combo_arg].has(option_arg):
				_supplementary_combos[combo_arg][option_arg] = param_weigh_of_new_option
				
func set_weight_of_option_in_sup_combo(combo_arg:String,option_arg:String,weight_of_option_arg:float):
	if _supplementary_combos.has(combo_arg):
		var param_weigh_of_new_option:float = weight_of_option_arg
		if _supplementary_combos[combo_arg].has(option_arg):
			_supplementary_combos[combo_arg][option_arg] = param_weigh_of_new_option

func get_weight_of_option_in_sup_combo(combo_arg:String,option_arg:String)->float:
	if _supplementary_combos.has(combo_arg):
#			var param_weigh_of_new_option:float = weight_of_option_arg
			if _supplementary_combos[combo_arg].has(option_arg):
				return _supplementary_combos[combo_arg][option_arg]
	return 0.0


func calculate_productdict_from_optiondict(option_dict_arg:Dictionary)->Dictionary:
	var product_dict:Dictionary = {}
	for option in option_dict_arg:
		if _option_product_dict.has(option):
			var product = _option_product_dict[option]
			if (product_dict.has(product)):
				product_dict[product] += option_dict_arg[option]
			else:
				product_dict[product] = option_dict_arg[option]
		
		else:
	#	No sé si está bien que pueda haber products entre las options
			if _products.has(option):
				if (product_dict.has(option)):
					product_dict[option] += option_dict_arg[option]
				else:
					product_dict[option] = option_dict_arg[option]
		
	return product_dict


func get_product_combidict_from_option_combidict(option_combidict:Dictionary)->Dictionary:
	var product_combidict:Dictionary = {}
	for option in option_combidict.keys():
		var product:String = self.get_product_from_option(option)
		var amount:float = option_combidict[option]
		if product_combidict.has(product):
			product_combidict[product] += amount
		else:
			product_combidict[product] = amount
	
	return product_combidict


func print_info():
	print("Supplementary combos:")
	print(self._supplementary_combos)
	print("Complementary combos:")
	print(self._complementary_combos)
	print("Options:")
	print(self._options)
	print("Products:")
	print(self._products)
	print("Option->Product map:")
	for option in self._option_satisf_curve_dict.keys():
		var satis_curve:SatisfactionCurve  = _option_satisf_curve_dict[option]
		var max_satisf:float = satis_curve.get_maximum_satisf()
		var pref_at_0:float = satis_curve.get_preference_at_0()
		print("Option: " + option)
		print("Max satisf: " +str(max_satisf))
		print("Pref at 0: " + str(pref_at_0))
	for option in self._complementary_combo_satisf_curve_dict.keys():
		var satis_curve:SatisfactionCurve  = _complementary_combo_satisf_curve_dict[option]
		var max_satisf:float = satis_curve.get_maximum_satisf()
		var pref_at_0:float = satis_curve.get_preference_at_0()
		print("Compl Option: " + option)
		print("Max satisf: " +str(max_satisf))
		print("Pref at 0: " + str(pref_at_0))
	for option in self._supplementary_combo_satisf_curve_dict.keys():
		var satis_curve:SatisfactionCurve  = _supplementary_combo_satisf_curve_dict[option]
		var max_satisf:float = satis_curve.get_maximum_satisf()
		var pref_at_0:float = satis_curve.get_preference_at_0()
		print("Suppl Option: " + option)
		print("Max satisf: " +str(max_satisf))
		print("Pref at 0: " + str(pref_at_0))

func check_integrity():

	print("Have all options a product?:")
	var num_errors_all_options_with_product:int = 0
	for option in _options:
		if false ==_option_product_dict.has(option):
			print("ERROR: missing option "+option+" in _option_product_dict")
			num_errors_all_options_with_product +=1
	
	if 0==num_errors_all_options_with_product:
		print("OK: All options with product")
	
	print("Are options in satisf curves in options array?:")
	var num_errors_saisf_curve_options_in_options_array:int = 0
	for option in _option_satisf_curve_dict:
		if false == _options.has(option):
			num_errors_saisf_curve_options_in_options_array +=1
			print("ERROR: missing option "+option+" from _option_satisf_curve_dict in _options")
#	for option in _complementary_combo_satisf_curve_dict:
#		if false == _options.has(option):
			num_errors_saisf_curve_options_in_options_array +=1
#			print("ERROR: missing option "+option+" from _complementary_combo_satisf_curve_dict in _options")
#	for option in _supplementary_combo_satisf_curve_dict:
#		if false == _options.has(option):
			num_errors_saisf_curve_options_in_options_array +=1
#			print("ERROR: missing option "+option+" from _supplementary_combo_satisf_curve_dict in _options")

	if 0==num_errors_saisf_curve_options_in_options_array:
		print("OK: All saisf curve options in options array")

	print("Are options without satisf curve?:")
	var num_errors_options_without_satisf_curve:int = 0
	for option in _options:
		if (false == _option_satisf_curve_dict.has(option) and 
			false == _complementary_combo_satisf_curve_dict.has(option) and
			false == _supplementary_combo_satisf_curve_dict.has(option)):
				print("WARNING: missing satisf curve for option "+option)

	if 0==num_errors_options_without_satisf_curve:
		print("OK: All options with satisf curve")
	
func to_dict()->Dictionary:
	var save_dict:Dictionary = {}
	
	save_dict["_options"] = _options
	save_dict["_option_product_dict"] = _option_product_dict
	save_dict["_complementary_combos"] = _complementary_combos
	save_dict["_supplementary_combos"] = _supplementary_combos

	var otion_satisf_curv:Dictionary={}
	for option in _option_satisf_curve_dict.keys():
		var sat_curv_dict:Dictionary = _option_satisf_curve_dict[option].to_dict()
		otion_satisf_curv[option] = sat_curv_dict
	save_dict["_option_satisf_curve_dict"] = otion_satisf_curv

	var comp_combo_satisf_curv:Dictionary={}
	for option in _complementary_combo_satisf_curve_dict.keys():
		var sat_curv_dict:Dictionary = _complementary_combo_satisf_curve_dict[option].to_dict()
		comp_combo_satisf_curv[option] = sat_curv_dict
	save_dict["_complementary_combo_satisf_curve_dict"] = comp_combo_satisf_curv

	var sup_combo_satisf_curv:Dictionary={}
	for option in _supplementary_combo_satisf_curve_dict.keys():
		var sat_curv_dict:Dictionary = _supplementary_combo_satisf_curve_dict[option].to_dict()
		sup_combo_satisf_curv[option] = sat_curv_dict
	save_dict["_supplementary_combo_satisf_curve_dict"] = sup_combo_satisf_curv
	
	save_dict["_name"] = _name
#	print(to_json(save_dict))
	
	return save_dict


func save()->Dictionary:	
	return to_dict()

func from_dict(saved_dict:Dictionary):
	for dic_key in saved_dict:

		if dic_key == "_options":
			_options.clear()
			_options = saved_dict[dic_key]

		if dic_key == "_option_product_dict":
			_option_product_dict.clear()
			_option_product_dict = saved_dict[dic_key]

		if dic_key == "_complementary_combos":
			_complementary_combos.clear()
			_complementary_combos = saved_dict[dic_key]

		if dic_key == "_supplementary_combos":
			_supplementary_combos.clear()
			_supplementary_combos = saved_dict[dic_key]

		if dic_key == "_option_satisf_curve_dict":
			_option_satisf_curve_dict.clear()
			var option_satisf:Dictionary = saved_dict[dic_key]
			for option in option_satisf.keys():
				var satisf_curve:SatisfactionCurve = SatisfactionCurve.new()
				satisf_curve.from_dict(option_satisf[option])
				_option_satisf_curve_dict[option] = satisf_curve

		if dic_key == "_complementary_combo_satisf_curve_dict":
			_complementary_combo_satisf_curve_dict.clear()
			var option_satisf:Dictionary = saved_dict[dic_key]
			for option in option_satisf.keys():
				var satisf_curve:SatisfactionCurve = SatisfactionCurve.new()
				satisf_curve.from_dict(option_satisf[option])
				_complementary_combo_satisf_curve_dict[option] = satisf_curve

		if dic_key == "_supplementary_combo_satisf_curve_dict":
			_supplementary_combo_satisf_curve_dict.clear()
			var option_satisf:Dictionary = saved_dict[dic_key]
			for option in option_satisf.keys():
				var satisf_curve:SatisfactionCurve = SatisfactionCurve.new()
				satisf_curve.from_dict(option_satisf[option])
				_supplementary_combo_satisf_curve_dict[option] = satisf_curve

		if dic_key == "_name":
			self._name = saved_dict[dic_key]

