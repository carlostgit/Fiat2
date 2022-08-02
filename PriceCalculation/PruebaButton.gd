extends Button

#Para probar cualquier cosa

const Polyline = preload("res://PriceCalculation/Polyline.gd")

const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")
const SatisfactionCurve = preload("res://PriceCalculation/SatisfactionCurve.gd")
const TradeCalculator = preload("res://PriceCalculation/TradeCalculator.gd")

var PlotterResource = preload("res://Plotter/Plotter.tscn")
#const PriceCalculationTesterSceneRes = preload("res:://PriceCalculation/PriceCalculationTesterScene.tscn")

#const PriceCalculationTesterSceneRes = preload("res://PriceCalculation/PriceCalculationTesterScene.tscn")

const PriceCalculationInterface = preload("res://PriceCalculation/PriceCalculationInterface.gd")


# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	
	
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_PruebaButton_pressed():
	var objectPolyline:Polyline = Polyline.new()
	objectPolyline.test()
	
	
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
	
#	
	var budget = 10.0
	var budget_step = 0.01
	var current_combidict:Dictionary = {"candy_savings":1,"chocolate_savings":1,
						"candy_consumption":1,"chocolate_consumption":1}

	var adjusted_combidict:Dictionary = trade_calculator.adjust_best_combidict(budget, current_combidict, budget_step)
	print(adjusted_combidict)

	var max_amount_of_money:float = 10
	var calc_step:float = 1
	var polyline_group = trade_calculator.precalculate_aprox_best_combidict_curves_for_a_budget_range(max_amount_of_money, calc_step)
	
	#	Plotter
	var polyline_group_dict = polyline_group.get_polyline_dict()
	
	
#	var plotter_scene_resource = load(Plotter_path)
	var plotter_scene = PlotterResource.instance()
	self.add_child(plotter_scene)
#	var plotter = plotter_scene.get_script()
	plotter_scene.add_point(Vector2(0,0))
	plotter_scene.add_point(Vector2(5,5))
	plotter_scene.draw_points()
	var points_array:Array = []
	points_array.append(Vector2(0,1))
	points_array.append(Vector2(5,2))
	plotter_scene.add_point_group(1,points_array)
	
	var points_group_dict = polyline_group.get_groupname_points_dict()
	
	plotter_scene.add_point_groups(points_group_dict)
	
#	for idgroup in points_group_dict:
#		var points = points_group_dict[idgroup]
#		plotter_scene.add_point_group(idgroup,points)
#
		
	
#	var x_max:float = 10
#	var y_max:float = 10
#	var plotter:Plotter = Plotter.new(x_max,y_max)
#	plotter.set_size(Vector2(600,400))
#	self.add_child(plotter)

	
	polyline_group.print_info()
	
#	comprobar y corregir los errores que saca check_integrity()
	satisfaction_calculator.check_integrity()

	
	
	
	pass # Replace with function body.
