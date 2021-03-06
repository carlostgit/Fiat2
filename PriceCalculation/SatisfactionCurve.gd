#extends Control

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

var _param_preference_at_0 = 2.16
var _maximum_satisf = 10.0

#const Plotter = preload("res://Plotter.gd")

# Called when the node enters the scene tree for the first time.
func _ready():

#	var test_combination:Dictionary = {"chocolate": 2, "candy": 2}	
#	print(calculate_satisf_of_combidict(test_combination))

#	var param_max_satisf:float = 10
#	var param_quantity:float = 10
#	var param_satisf_at_1:float = 5
#	var preference_at_0 = calculate_param_preference_at_0(param_max_satisf, param_satisf_at_1, param_quantity)
#
#	_param_preference_at_0 = preference_at_0
#	_maximum_satisf = param_max_satisf
#
#	var plotter:Plotter = Plotter.new(100,10)
#	plotter.set_size(Vector2(300,300))
#	plotter.updated_size()
#	var dimin_ret_fact_func_ref:FuncRef = funcref( self, "get_diminishing_returns_factor")
#	plotter.add_func_ref(dimin_ret_fact_func_ref,"dimin_ret_fact")
#	self.call_deferred("add_child",plotter)
#	plotter.add_func_ref(funcref( self, "calculate_satifaction"),"satisfaction")	

#	print(calculate_param_preference_at_0(10, 1, 1))
	pass
	
# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _init(param_preference_at_0_arg:float = 1, maximum_satisf_arg:float = 1):
	_param_preference_at_0 = param_preference_at_0_arg
	_maximum_satisf = maximum_satisf_arg


func get_diminishing_returns_factor_old(quantity_arg:float) -> float:
	#Voy a llamar al termino "1-(1/(0.25*x+1)^2)" Diminishing Returns Factor
	#Esta ecuación tendría un máximo en 1, y tendría pendiente 1 en 0
	#Es como una ecuación y = x, pero que se va haciendo más y más horizontal hasta q ya no crece la y
	
#	PerformanceUtils.start(1)
#	PerformanceUtils.stop(1)
	
	var result = 0.0
	var denominator_square_root = 0.25*quantity_arg + 1.0;
	var denominator = denominator_square_root*denominator_square_root
	
	result = 1.0 - (1.0/denominator)
	if result < 0:
		result = 0
	
	
	
	return result
	
func _get_diminishing_returns_factor(quantity_arg:float) -> float:
	#Voy a llamar al termino "1-(1/(x+1))" Diminishing Returns Factor
	#Esta ecuación tendría un máximo en 1, y tendría pendiente 1 en 0
	#Es como una ecuación y = x, pero que se va haciendo más y más horizontal hasta q ya no crece la y
	
#	TimeMeasurement.start("get_diminishing_returns_factor")
	
	var result = 0.0
#	var denominator_square_root = 0.25*quantity_arg + 1.0;
#	var denominator = denominator_square_root*denominator_square_root
	var denominator = quantity_arg+1.0
	
	result = 1.0 - (1.0/denominator)
	if result < 0:
		result = 0
	
#	TimeMeasurement.stop("get_diminishing_returns_factor")
	
	
	return result


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

func calculate_satifaction(quantity_arg:float) -> float:
	
#	TimeMeasurement.start("calculate_satifaction")
		
	var ret_satisf = 0.0
	var pref_at_0 = _param_preference_at_0
	var max_satisf = _maximum_satisf
	
	if max_satisf==0:
		return max_satisf
	
	
	ret_satisf = max_satisf*_get_diminishing_returns_factor(quantity_arg*pref_at_0/max_satisf)
	
#	TimeMeasurement.stop("calculate_satifaction")
	
	return ret_satisf


func get_preference_at_0() -> float:
	return _param_preference_at_0

func set_preference_at_0(param_preference_arg:float):
	_param_preference_at_0 = param_preference_arg

func get_maximum_satisf() -> float:
	return _maximum_satisf

func set_maximum_satisf(maximum_satisf_arg:float):
	_maximum_satisf = maximum_satisf_arg

func to_dict()->Dictionary:
	var dict:Dictionary = {}
	dict["_param_preference_at_0"] = _param_preference_at_0
	dict["_maximum_satisf"] = _maximum_satisf
	return dict

func from_dict(dict_arg:Dictionary):
	_param_preference_at_0 = dict_arg["_param_preference_at_0"]
	_maximum_satisf = dict_arg["_maximum_satisf"]
