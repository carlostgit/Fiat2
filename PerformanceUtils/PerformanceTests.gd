extends Node

const TimeMeasurement = preload("res://PerformanceUtils/TimeMeasurement.gd")

# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func default_test():
	var time_measurement = TimeMeasurement.new()
	time_measurement.reset()
	
	time_measurement.start("nothing")
	time_measurement.stop("nothing")
	
	time_measurement.start("1000 sum and division")
	var result:float = 0;
	for i in range(1,1000):
		result = (result+1)/i
	time_measurement.stop("1000 sum and division")
	
	time_measurement.start("1000 division")
	result = 10000000;
	for i in range(1,1000):
		result = result/i
	time_measurement.stop("1000 division")

	time_measurement.start("1000 sum")
	result = 10;
	for i in range(1,1000):
		result = result+i
	time_measurement.stop("1000 sum")
	
	time_measurement.start("1000 dictionary")
	var test_dict:Dictionary = {"aaaaaaaa":1,"baaaaaaaabaaaaaaaabaaaaaaaa":2,"caaaaaaaa":3,"daaaaaaaa":4}
	for i in range(1,1000):
		result = test_dict["baaaaaaaabaaaaaaaabaaaaaaaa"];
	time_measurement.stop("1000 dictionary")

	time_measurement.start("1000 combination")
	result = 0;
	var result_2:float = 0;
	for i in range(1,1000):
		result = (result*result+1)/i
		result_2 = (result_2*result_2+2)/i
	time_measurement.stop("1000 combination")
	
	
	time_measurement.print_info()
