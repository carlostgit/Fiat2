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
#	var sat_calc:SatisfactionCalculator = SatisfactionCalculator.new()
	
	
	var x_max:float = 10
	var y_max:float = 15
	var plotter:Plotter = Plotter.new(x_max,y_max)
	plotter.set_size(Vector2(400,400))
	plotter.set_size(Vector2(400,500))
#	plotter.updated_size()

	self.call_deferred("add_child",plotter)
	
	var test_funcref = funcref( plotter, "default_test_function")
#	add_func_ref(func_ref_arg:FuncRef, label_arg:String = "")->void:
	plotter.add_func_ref(test_funcref,[],"test")
#	_func_array.append(test_funcref)
#	_label_array.append("test")
#	var func_calc_satisf_of_candy = funcref(sat_calc,"calculate_satifaction_of_candy")
#	plotter.add_func_ref(func_calc_satisf_of_candy,"test_satisf_candy")

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
	satisfaction_calculator.set_combo("sweets",["candy_consumption","chocolate_consumption"])
	satisfaction_calculator.set_satisfaction_curve_for_combo("sweets",satisfaction_curve_for_sweets)
	
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
	
	
#	var func_calc_satisf_candy = funcref(satisfaction_calculator,"calculate_satifaction_of_candy")
#	plotter.add_func_ref(func_calc_satisf_candy,"test_satisf_candy")
	
#	TODO: Preparar en Plotter un método add_func_ref_with_args para poder hacer lo siguiente
	var func_calc_satisf = funcref(self,"test_satisfaction")
#	var func_args_array = ["candy",satisfaction_calculator]
	var func_args_array = ["candy_consumption",satisfaction_calculator]
	plotter.add_func_ref(func_calc_satisf, func_args_array, "test_candy_consumption_sat",Color(1,0,0) )
	
#	var func_calc_satisf_2 = funcref(self,"test_satisfaction")
#	var func_args_array_2 = ["candy",satisfaction_calculator]
#	plotter.add_func_ref(func_calc_satisf_2, func_args_array_2, "test_candy_sat", Color(1,0,1) )
	
##	var test:float = test_satisfaction(100.0, "candy_consumption", satisfaction_calculator)
#	var test:float = test_satisfaction(5,"candy_consumption",satisfaction_calculator)
#	print("print_test")
#	print(test)
	
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

func test_satisfaction(amount_arg:float, product_arg:String, sat_calc_arg:SatisfactionCalculator)->float:
	return sat_calc_arg.calculate_satifaction_of_product(product_arg,amount_arg)
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
