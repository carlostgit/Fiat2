extends Node


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
#{0.0€:0.0products, 10.0€:4.0products, 30€:4.4products}
var _points_x_y_dict:Dictionary = {}

func test():
	add_point(0, 20)
	add_point(10, 30)
	print("get_value(0)")
	print(get_value(0))
	print("get_value(5)")
	print(get_value(5))
	print("get_value(10)")
	print(get_value(10))
	print("get_value(30)")
	print(get_value(30))
	

# Called when the node enters the scene tree for the first time.
func _ready():
	test()
	pass # Replace with function body.

func add_point(x_arg:float, y_arg:float):
	_points_x_y_dict[x_arg]=y_arg
	
func get_value(x_arg:float):
	
	if (_points_x_y_dict.size()<2):
		return 0.0
	
	var x_ini = 0.0
	var x_end = 0.0
	var y_ini = 0.0
	var y_end = 0.0
	
	var x_point_over_x_arg_found = false
	var x_point_over_x_arg:float = 0
	var x_point_below_x_arg_found = false
	var x_point_below_x_arg:float = 0
	for point_x in _points_x_y_dict.keys():
		if (point_x >= x_arg):
			x_point_over_x_arg_found = true
			x_point_over_x_arg = point_x
			break
		if (point_x < x_arg):
			x_point_below_x_arg_found = true
			x_point_below_x_arg = point_x
			
	if (false==x_point_over_x_arg_found and 
		false==x_point_below_x_arg_found):
		return 0.0
	elif (true==x_point_over_x_arg_found and 
		true==x_point_below_x_arg_found):
	
		x_ini = x_point_below_x_arg
		x_end = x_point_over_x_arg
		y_ini = _points_x_y_dict[x_point_below_x_arg]
		y_end = _points_x_y_dict[x_point_over_x_arg]
	
	elif (true==x_point_over_x_arg_found and 
		false==x_point_below_x_arg_found):
#		El punto en argumento está antes del menor punto de esta polilinea
		x_ini = (_points_x_y_dict.keys())[0]
		x_end = (_points_x_y_dict.keys())[1]
		y_ini = _points_x_y_dict[x_ini]
		y_end = _points_x_y_dict[x_end]
	elif (false==x_point_over_x_arg_found and 
		true==x_point_below_x_arg_found):
#		El punto en argumento está más allá del mayor punto de esta polilinea
		x_ini = (_points_x_y_dict.keys())[_points_x_y_dict.size()-2]
		x_end = (_points_x_y_dict.keys()).back()
		y_ini = _points_x_y_dict[x_ini]
		y_end = _points_x_y_dict[x_end]
	else:
		assert(false)
		
	var x_step:float = x_end-x_ini
	if (x_step==0):
		return 
	var y_step:float = y_end-y_ini
	var slope:float = y_step/x_step
	var advance_towards_next_step:float = x_arg-x_ini
	 
	var y:float = y_ini+advance_towards_next_step*slope
		
	return y

func get_points()->Dictionary:
	return _points_x_y_dict	
	
func print_info():
	for x in _points_x_y_dict.keys():
		print("x: "+str(x))
		print("y: "+str(_points_x_y_dict[x]))
		

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
