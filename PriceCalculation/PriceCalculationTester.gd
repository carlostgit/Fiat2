extends Node


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")
const SatisfactionCurve = preload("res://PriceCalculation/SatisfactionCurve.gd")
const TradeCalculator = preload("res://PriceCalculation/TradeCalculator.gd")

#const Plotter = preload("res://Plotter/Plotter.gd")
var PlotterResource = preload("res://Plotter/Plotter.tscn")
#const PriceCalculationTesterSceneRes = preload("res:://PriceCalculation/PriceCalculationTesterScene.tscn")

const PriceCalculationTesterSceneRes = preload("res://PriceCalculation/PriceCalculationTesterScene.tscn")

const PriceCalculationInterface = preload("res://PriceCalculation/PriceCalculationInterface.gd")

const Polyline = preload("res://PriceCalculation/Polyline.gd")

# Called when the node enters the scene tree for the first time.
func _ready():	
	
#	Escena PriceCalculationTesterScene
	var price_calculation_tester_scene = PriceCalculationTesterSceneRes.instance()
	self.call_deferred("add_child",price_calculation_tester_scene)
#	

#	Plotter
#	var x_max:float = 10
#	var y_max:float = 10
#	var plotter:Plotter = Plotter.new(x_max,y_max)
#	plotter.set_size(Vector2(200,400))


#	self.call_deferred("add_child",plotter)
#

#	var test_funcref = funcref( plotter, "default_test_function")
#	plotter.add_func_ref(test_funcref,[],"test")
#

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
	satisfaction_calculator.set_complementary_combo("sweets_consumption",["candy_consumption","chocolate_consumption"])
	satisfaction_calculator.set_satisfaction_curve_for_complementary_combo("sweets_consumption",satisfaction_curve_for_sweets)
	
	var param_preference_at_0_for_candy_sav = 1.0
	var maximum_satisf_for_candy_sav = 10.0
	var satisfaction_curve_for_candy_sav:SatisfactionCurve = SatisfactionCurve.new(param_preference_at_0_for_candy_sav, maximum_satisf_for_candy_sav)
	satisfaction_calculator.set_satisfaction_curve("candy_savings",satisfaction_curve_for_candy_sav)

	var param_preference_at_0_for_chocolate_sav = 1.0
	var maximum_satisf_for_chocolate_sav = 10.0
	var satisfaction_curve_for_chocolate_sav:SatisfactionCurve = SatisfactionCurve.new(param_preference_at_0_for_chocolate_sav, maximum_satisf_for_chocolate_sav)
	satisfaction_calculator.set_satisfaction_curve("chocolate_savings",satisfaction_curve_for_chocolate_sav)
	
	
	satisfaction_calculator.set_option_product_dict(option_product_dict)
	
	
	var max_amount_of_money:float = 10
	var calc_step:float = 1
	var polyline_group = trade_calculator.precalculate_aprox_best_combidict_curves_for_a_budget_range(max_amount_of_money, calc_step)
	
	var polyline_group_dict:Dictionary = polyline_group.get_polyline_dict()
	
	satisfaction_calculator.check_integrity()
	
	pass # Replace with function body.

func test_satisfaction(amount_arg:float, option_arg:String, sat_calc_arg:SatisfactionCalculator)->float:
	return sat_calc_arg.calculate_satifaction_of_option(option_arg,amount_arg)

func test_combo_satisfaction(amount_arg:float, combo_arg:String, sat_calc_arg:SatisfactionCalculator)->float:
	return sat_calc_arg.calculate_satifaction_of_opt_combo(combo_arg,amount_arg)

	

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
