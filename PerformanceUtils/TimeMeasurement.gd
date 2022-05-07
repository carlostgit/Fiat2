extends Node


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

var _measurement_start:Dictionary
var _measurement_times:Dictionary

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func reset():
	_measurement_start.clear()
	_measurement_times.clear()

func start(name_arg:String):
	
	_measurement_start[name_arg] = OS.get_ticks_usec()

func stop(name_arg:String):
	
#	usec_stop = OS.get_ticks_usec()
#	var has_name= _measurement_start.has(name_arg)
#	var multip = 5* 8
#	var has_name2= _measurement_start.has(name_arg)
#	var has_name3= _measurement_start.has(name_arg)
#	var has_name4 = has_name2+has_name2+has_name3
	var usec_stop = OS.get_ticks_usec()
	if _measurement_start.has(name_arg):
		
		var usec_start = _measurement_start[name_arg]
		var elapsed_time = usec_stop - usec_start
		
		if false == _measurement_times.has(name_arg):
			_measurement_times[name_arg] = []
			
		_measurement_times[name_arg].append(elapsed_time)
		_measurement_start.erase(name_arg)
	
func get_num_measurements(name_arg:String)->int:
	if _measurement_times.has(name_arg):
		return _measurement_times[name_arg].size()
	return 0

func get_total_time(name_arg:String)->float:
	var total_time:float = 0.0
	if _measurement_times.has(name_arg):
		for time in _measurement_times[name_arg]:
			total_time += time
	return total_time
	
func get_average_time(name_arg:String)->float:
	var num_measurements:float = get_num_measurements(name_arg)
	var total_time:float = get_total_time(name_arg)
	return total_time/num_measurements

func get_last_time(name_arg:String)->float:
	if _measurement_times.has(name_arg):
		return _measurement_times[name_arg].back()
	return 0.0

func print_info()->void:
	for name in _measurement_times.keys():
		print("") #Un espacio
		print(name)
		print("total time: "+str(get_total_time(name)))
		print("average time: "+str(get_average_time(name)))
		print("calls: "+str(get_num_measurements(name)))
		
