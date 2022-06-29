extends Node


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
#{0.0€:0.0products, 10.0€:4.0products, 30€:4.4products}
#var _points_x_y_dict:Dictionary = {} #A eliminar
#Lo anterior tiene que ser sustituido por lo siguiente
var _points_array:Array = []
#todo
#TODO: CAMBIAR TODO ESTO PARA USAR UN ARRAY EN VEZ DE UN DICTIONARY. Y USAR bsearch_custom PARA insertar elementos

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
#	_points_x_y_dict[x_arg]=y_arg

	
#	_points_array.push_back(Vector2(0,0))
#	_points_array.push_back(Vector2(1,1))
#	_points_array.push_back(Vector2(3,3))
#	_points_array.push_back(Vector2(4,4))
	
#	_points_array
	var new_point = Vector2(x_arg,y_arg)
	var find_x_result = self.find_point_with_same_x_in_array(_points_array,new_point.x)
	if -1==find_x_result:
		var insertion_index:int = 0
		insertion_index = self._points_array.bsearch_custom(new_point, CPointsSorter, "points_sorter", false)
		print("old _points_array:")
		print(_points_array)
		print("old _points_array.size(): "+str(_points_array.size()))
		print("new_point: "+str(new_point))
		print("insertion_index: "+str(insertion_index))
		_points_array.insert(insertion_index,new_point)
		
		print("new _points_array:")
		print(_points_array)
#		for point in _points_array:
#			print (point)
		print("end")
	else:
		_points_array[find_x_result]=new_point
		
func set_point(x_arg:float, y_arg:float):
	add_point(x_arg, y_arg)
	
func get_value(x_arg:float):
	
#	TODO
#	TODO:REHACER ESTE MÉTODO CON _points_array en vez de _points_x_y_dict
	if (self._points_array.size()<2):
		return 0.0
	
	var x_ini = 0.0
	var x_end = 0.0
	var y_ini = 0.0
	var y_end = 0.0
	
	var x_point_over_x_arg_found = false
	var point_over_x_arg:Vector2 = Vector2()
	var x_point_below_x_arg_found = false
	var point_below_x_arg:Vector2 = Vector2()
	for point in _points_array:
		var point_x:float = point.x
		if (point_x >= x_arg):
			x_point_over_x_arg_found = true
			point_over_x_arg = point
			break
		if (point_x < x_arg):
			x_point_below_x_arg_found = true
			point_below_x_arg = point
	if (false==x_point_over_x_arg_found and 
		false==x_point_below_x_arg_found):
		return 0.0
	elif (true==x_point_over_x_arg_found and 
		true==x_point_below_x_arg_found):
		x_ini = point_below_x_arg.x
		x_end = point_over_x_arg.x
		y_ini = point_below_x_arg.y
		y_end = point_over_x_arg.y
		
	elif (true==x_point_over_x_arg_found and 
		false==x_point_below_x_arg_found):
#		El punto en argumento está antes del menor punto de esta polilinea
		x_ini = _points_array[0].x
		x_end = _points_array[1].x
		y_ini = _points_array[0].y
		y_end = _points_array[1].y
	elif (false==x_point_over_x_arg_found and 
		true==x_point_below_x_arg_found):
#		El punto en argumento está más allá del mayor punto de esta polilinea
		x_ini = _points_array[_points_array.size()-2].x
		x_end = _points_array.back().x
		y_ini = _points_array[_points_array.size()-2].y
		y_end = _points_array.back().y
	else:
		assert(false)
	

	var x_step:float = x_end-x_ini
	if (x_step==0):
		return y_ini
	var y_step:float = y_end-y_ini
	var slope:float = y_step/x_step
	var advance_towards_next_step:float = x_arg-x_ini
	 
	var y:float = y_ini+advance_towards_next_step*slope
		
	return y	
#
#
#	if (_points_x_y_dict.size()<2):
#		return 0.0
#
#	var x_ini = 0.0
#	var x_end = 0.0
#	var y_ini = 0.0
#	var y_end = 0.0
#
#	var x_point_over_x_arg_found = false
#	var x_point_over_x_arg:float = 0
#	var x_point_below_x_arg_found = false
#	var x_point_below_x_arg:float = 0
#	for point_x in _points_x_y_dict.keys():
#		if (point_x >= x_arg):
#			x_point_over_x_arg_found = true
#			x_point_over_x_arg = point_x
#			break
#		if (point_x < x_arg):
#			x_point_below_x_arg_found = true
#			x_point_below_x_arg = point_x
#
#	if (false==x_point_over_x_arg_found and 
#		false==x_point_below_x_arg_found):
#		return 0.0
#	elif (true==x_point_over_x_arg_found and 
#		true==x_point_below_x_arg_found):
#
#		x_ini = x_point_below_x_arg
#		x_end = x_point_over_x_arg
#		y_ini = _points_x_y_dict[x_point_below_x_arg]
#		y_end = _points_x_y_dict[x_point_over_x_arg]
#
#	elif (true==x_point_over_x_arg_found and 
#		false==x_point_below_x_arg_found):
##		El punto en argumento está antes del menor punto de esta polilinea
#		x_ini = (_points_x_y_dict.keys())[0]
#		x_end = (_points_x_y_dict.keys())[1]
#		y_ini = _points_x_y_dict[x_ini]
#		y_end = _points_x_y_dict[x_end]
#	elif (false==x_point_over_x_arg_found and 
#		true==x_point_below_x_arg_found):
##		El punto en argumento está más allá del mayor punto de esta polilinea
#		x_ini = (_points_x_y_dict.keys())[_points_x_y_dict.size()-2]
#		x_end = (_points_x_y_dict.keys()).back()
#		y_ini = _points_x_y_dict[x_ini]
#		y_end = _points_x_y_dict[x_end]
#	else:
#		assert(false)
#
#	var x_step:float = x_end-x_ini
#	if (x_step==0):
#		return 
#	var y_step:float = y_end-y_ini
#	var slope:float = y_step/x_step
#	var advance_towards_next_step:float = x_arg-x_ini
#
#	var y:float = y_ini+advance_towards_next_step*slope
#
#	return y

#func get_points_dict()->Dictionary:
#	return _points_x_y_dict	

func get_points_array()->Array:
#	var pointsarray:PoolVector2Array = []
#	for x in _points_x_y_dict.keys():
#		pointsarray.append(Vector2(x,_points_x_y_dict[x]))
#	return pointsarray
	return self._points_array
	
func print_info():
	for point in _points_array:
		print("x: "+str(point))
		print("y: "+str(point))
		
class CPointsSorter:
	static func points_sorter(a:Vector2, b:Vector2):
		if a.x < b.x:
			return true
		return false
	
static func find_point_with_same_x_in_array(points_array_arg:Array,searching_x_arg:float)->int:
	if (points_array_arg.empty()):
		return -1	
	
	var index:int = points_array_arg.bsearch_custom(Vector2(searching_x_arg,0), CPointsSorter, "points_sorter", true)	
	if (index == -1 or index > points_array_arg.size()-1):
		return -1
		
	if (points_array_arg[index].x == searching_x_arg):
		return index;
	return -1
# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
