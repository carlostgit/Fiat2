extends Button


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

#onready var data = preload("res://simple.gdns").new()
onready var data = preload("res://PriceCalculatorGDNBind.gdns").new()

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_GDNativeTestButton_pressed():
#	data.set_and_get_data("Hello with set_data")
	#$Label.text = "Data = " + data.get_data()
	#$Label2.text = "Data2 = " + data.get_data2()
	#$Label.text = "get_num_args = " + data.get_num_args(5,3)
#	$Label2.text = "set_data = " + data.set_and_get_data("Kuku")
	
	var text_dict_arg:Dictionary = {"Persons": ["Peter","George"], "Products":["nut","chocolate","candy"], "Consumption":["nut_consumption","chocolate_consumption","candy_consumption"]}
	
	var text_dict_arg2:Dictionary = {"cucu": 5.0, "coco":"lulu", "caca":["a","b"]}
	
	#var text_dict_answ:Dictionary = data.get_and_set_dict(text_dict_arg)
#	var text_dict_answ:Dictionary = data.calc_info_from_market_test()
	
	$Label.text = ""
	$Label.text = "bla bla bla an5es de llamar a PriceCalculatorDll"
	#$Label2.text = "calc_info_from_market_test: "+ str(data.calc_info_from_market_test())
	$Label2.text = "calc_info_from_price_calculator_dll: "+ str(data.calc_info_from_price_calculator_dll(text_dict_arg,text_dict_arg2))
	
	$Label.text = "bla bla bla after calling"
	
	for text_key in text_dict_arg:
		$Label.text += " Key: "+text_key
		$Label.text += " Value: "+str(text_dict_arg[text_key])
	
#	for text_key in text_dict_answ:
#		$Label2.text += " Key: "+text_key
#		$Label2.text += " Value: "+str(text_dict_answ[text_key])
##		if "cucu"==text_key:
##			$Label2.text += " "+str(text_dict_answ[text_key])
##		else:
##			$Label2.text += " "+str(text_dict_answ[text_key])
	
	
	
	pass # Replace with function body.
