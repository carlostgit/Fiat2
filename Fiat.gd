extends Node2D


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

#Testeo de scripts
#const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")


#var PriceCalculationTester = load("res://PriceCalculation/PriceCalculationTester.gd")
var PriceCalculationInterface = load("res://PriceCalculation/PriceCalculationInterface.gd")

#Fin de testeo de scripts

# Called when the node enters the scene tree for the first time.
func _ready():
	
	#Testeo de scripts	
#	var sat_calc:SatisfactionCalculator = SatisfactionCalculator.new()
#	var combi = {"chocolate": 10.0, "candy": 10.0}
#	var satisf:float = sat_calc.calculate_satisf_of_combidict(combi)
#	print(satisf)
#	var price_calc_tester:PriceCalculationTester = PriceCalculationTester.new()
#	self.add_child(price_calc_tester)
	
	#Fin de testeo de scripts
	
	
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_Button_pressed():
	var price_calculation_interface = PriceCalculationInterface.new()
	price_calculation_interface.init_default_scenario()
	price_calculation_interface.print_scenario_info()
	pass # Replace with function body.
