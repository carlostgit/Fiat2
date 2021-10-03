extends Node


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")
const SatisfactionCurve = preload("res://PriceCalculation/SatisfactionCurve.gd")
const TradeCalculator = preload("res://PriceCalculation/TradeCalculator.gd")

const Plotter = preload("res://Plotter/Plotter.gd")

const PriceCalculationInterface = preload("res://PriceCalculation/PriceCalculationInterface.gd")

# Called when the node enters the scene tree for the first time.
func _ready():	
	
	var x_max:float = 10
	var y_max:float = 15
	var plotter:Plotter = Plotter.new(x_max,y_max)
	plotter.set_size(Vector2(400,400))
	plotter.set_size(Vector2(400,500))

	self.call_deferred("add_child",plotter)
	
	var test_funcref = funcref( plotter, "default_test_function")
	plotter.add_func_ref(test_funcref,[],"test")
#
#	TODO (pseudocódigo)
	var price_calc_interf:PriceCalculationInterface = PriceCalculationInterface.new()
	var products:Array = ["candy","chocolate"]	
	price_calc_interf.set_products(products)
	price_calc_interf.set_currency("candy")
	
	var options_array:Array = ["candy_savings","chocolate_savings",
						"candy_consumption","chocolate_consumption"]

	
	var trade_calculator:TradeCalculator = price_calc_interf.create_trade_calculator()
	var satisfaction_calculator:SatisfactionCalculator = trade_calculator.get_satisfaction_calculator()

	satisfaction_calculator.set_options(options_array)
	
	var option_product_dict:Dictionary = { "candy_savings": "candy",
									"candy_consumption": "candy",
									"chocolate_savings": "chocolate",
									"chocolate_consumption": "chocolate",}

	
	var param_preference_at_0_for_candy_consu = 1.0
	var maximum_satisf_for_candy_consu = 10.0
	var satisfaction_curve_for_candy_consu:SatisfactionCurve = SatisfactionCurve.new(param_preference_at_0_for_candy_consu, maximum_satisf_for_candy_consu)
	satisfaction_calculator.set_satisfaction_curve("candy_consumption",satisfaction_curve_for_candy_consu)

	var param_preference_at_0_for_chocolate_consu = 1.0
	var maximum_satisf_for_chocolate_consu = 10.0
	var satisfaction_curve_for_chocolate_consu:SatisfactionCurve = SatisfactionCurve.new(param_preference_at_0_for_chocolate_consu, maximum_satisf_for_chocolate_consu)
	satisfaction_calculator.set_satisfaction_curve("chocolate_consumption",satisfaction_curve_for_chocolate_consu)
	
	var param_preference_at_0_for_sweets = 1.0
	var maximum_satisf_for_sweets = 10.0
	var satisfaction_curve_for_sweets:SatisfactionCurve = SatisfactionCurve.new(param_preference_at_0_for_sweets, maximum_satisf_for_sweets)
	satisfaction_calculator.set_combo("sweets_consumption",["candy_consumption","chocolate_consumption"])
	satisfaction_calculator.set_satisfaction_curve_for_combo("sweets_consumption",satisfaction_curve_for_sweets)
	
	var param_preference_at_0_for_candy_sav = 1.0
	var maximum_satisf_for_candy_sav = 10.0
	var satisfaction_curve_for_candy_sav:SatisfactionCurve = SatisfactionCurve.new(param_preference_at_0_for_candy_sav, maximum_satisf_for_candy_sav)
	satisfaction_calculator.set_satisfaction_curve("candy_savings",satisfaction_curve_for_candy_sav)

	var param_preference_at_0_for_chocolate_sav = 1.0
	var maximum_satisf_for_chocolate_sav = 10.0
	var satisfaction_curve_for_chocolate_sav:SatisfactionCurve = SatisfactionCurve.new(param_preference_at_0_for_chocolate_sav, maximum_satisf_for_chocolate_sav)
	satisfaction_calculator.set_satisfaction_curve("chocolate_savings",satisfaction_curve_for_chocolate_sav)
	
	#TODO. seguir haciendo lo mismo con las versiones savings, para las que no habrá combos
		
	
	satisfaction_calculator.set_option_product_dict(option_product_dict)
	
	
	#TODO
	var options_result = satisfaction_calculator.get_options()
	print (options_result)
	var products_result = satisfaction_calculator.get_products()
	print (products_result)
	var combos_result = satisfaction_calculator.get_combos()
	print (combos_result)
	
#	
#	TODO: Preparar en Plotter un método add_func_ref_with_args para poder hacer lo siguiente
	var func_calc_satisf = funcref(self,"test_satisfaction")
#	var func_args_array = ["candy",satisfaction_calculator]
	var func_args_array = ["candy_consumption",satisfaction_calculator]
	plotter.add_func_ref(func_calc_satisf, func_args_array, "test_candy_consumption_sat",Color(1,0,0) )
	
#	Tests de nuevas funciones de Plotter
	for i in range(100):
		plotter.add_point(Vector2(i,i))
		plotter.add_point(Vector2(i,i))	
#
	var point_group_id:int = 23
	var point_group_array:Array = []
	for k in range(100):
		point_group_array.append(Vector2(k,k))
		
	plotter.add_point_group(23,point_group_array, Color (1,0,0))
	
	
	var option_satisf_curve_dict:Dictionary = satisfaction_calculator.get_option_satisf_curve_dict()
	var combo_satisf_curve_dict:Dictionary = satisfaction_calculator.get_combo_satisf_curve_dict()

	for option in option_satisf_curve_dict:
		var func_calc_satisf2 = funcref(self,"test_satisfaction")
	#	var func_args_array = ["candy",satisfaction_calculator]
		var func_args_array2 = [option,satisfaction_calculator]
		plotter.add_func_ref(func_calc_satisf2, func_args_array2, option,Color(1,0,0) )

	for combo in combo_satisf_curve_dict:
		var func_calc_satisf2 = funcref(self,"test_combo_satisfaction")
	#	var func_args_array = ["candy",satisfaction_calculator]
		var func_args_array2 = [combo,satisfaction_calculator]
		plotter.add_func_ref(func_calc_satisf2, func_args_array2, combo,Color(0,1,0) )
	
	
		
#	TODO
#	Modificar parametros en funcion de calidad del producto como ahorro

#	Tengo que crear un moddelo de consumo/ahorro, que tenga en cuenta:
#		ingresos
#		ahorro actual
#		estabilidad de ingresos?
#		calidad del mejor ahorro posible?

#	Tengo que crear un selector de ahorro, que tenga en cuenta:
#		la depreciación del producto como moneda
#		el coste del uso como moneda
	
	
#	var consumption_options:Array = ["candy_consumption", "chocolate_consumption"]
#	var savings_options_array:Array = ["candy_savings", "chocolate_savings"]
	


#	var param_candy_saving_2:float = product_savings_quality_dict["candy_savings"]
#	price_calc_interf.set_satisfaction_params("candy_savings",param_candy_saving_1, param_candy_saving_2)
#
	
#	var income:float = 20.0
#	var income_currency = "candy"
#	price_calc_interf.set_income(income,income_currency)
	
	
	
	pass # Replace with function body.

func test_satisfaction(amount_arg:float, option_arg:String, sat_calc_arg:SatisfactionCalculator)->float:
	return sat_calc_arg.calculate_satifaction_of_option(option_arg,amount_arg)

func test_combo_satisfaction(amount_arg:float, combo_arg:String, sat_calc_arg:SatisfactionCalculator)->float:
	return sat_calc_arg.calculate_satifaction_of_opt_combo(combo_arg,amount_arg)

	

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
