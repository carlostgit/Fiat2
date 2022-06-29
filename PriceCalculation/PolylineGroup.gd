extends Node


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

const Polyline = preload("res://PriceCalculation/Polyline.gd")

var _name_polyline_dict = {}

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func add_polyline(name_arg:String, polyline_arg):
	_name_polyline_dict[name_arg] = polyline_arg
	
func get_polyline(name_arg:String):
	if (_name_polyline_dict.has(name_arg)):
		return _name_polyline_dict[name_arg]
	else:
		return null

func add_point(name_arg:String,x_arg:float,y_arg:float):
	var polyline = get_polyline(name_arg)
	if polyline:
		polyline.add_point(x_arg,y_arg)
	else:
		var new_polyline:Polyline = Polyline.new()
		new_polyline.add_point(x_arg,y_arg)
		add_polyline(name_arg, new_polyline)

func get_polyline_dict()->Dictionary:
	return _name_polyline_dict
	
func get_groupname_points_dict()->Dictionary:
	var groupname_points_dict:Dictionary = {}
	var count:int = 0
	for name in _name_polyline_dict.keys():
		var polyline = _name_polyline_dict[name]
		var points_array = polyline.get_points_array()
		groupname_points_dict[name] = points_array
		
	return groupname_points_dict
		

func print_info():
	print("Polyline group:")
	for name in _name_polyline_dict.keys():
		print("Polyline: "+name)
		_name_polyline_dict[name].print_info()
	
	
