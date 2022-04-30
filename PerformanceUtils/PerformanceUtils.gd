extends Node2D

const PerformanceTests = preload("res://PerformanceUtils/PerformanceTests.gd")
# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_TestButton_pressed():
	var performance_tests = PerformanceTests.new()
	performance_tests.default_test()
	pass # Replace with function body.
