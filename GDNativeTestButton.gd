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
	
	var output_dict:Dictionary = {
		"Persons": ["Peter","George"], 
		"Products":["nut","chocolate","candy"], 
		"Consumption":["nut_consumption","chocolate_consumption","candy_consumption"],
		"Owned": {
			"Peter":
					{"nut":1,"chocolate":2,"candy":3},
			"George":
					{"nut":4,"chocolate":5,"candy":6}
		},
		"OptionProduct":{"nut_consumption":"nut","chocolate_consumption":"chocolate","candy_consumption":"candy"},
		"Currency":"nut"
	}
	
	#var input_dict:Dictionary = {"cucu": 5.0, "coco":"lulu", "caca":["a","b"]}
	var input_dict:Dictionary = {}
	
	#var text_dict_answ:Dictionary = data.get_and_set_dict(text_dict_arg)
#	var text_dict_answ:Dictionary = data.calc_info_from_market_test()
	
	$OutputLabel.text = str(output_dict)
	#$Label2.text = "calc_info_from_market_test: "+ str(data.calc_info_from_market_test())
	$ReturnLabel.text = "calc_info_from_price_calculator_dll: "+ str(data.calc_info_from_price_calculator_dll(output_dict,input_dict))
	
	$InputLabel.text = str(input_dict)
	
	print("input dict:")
	print(input_dict)
	
	$InputTextEdit.text = str(input_dict)
	
#	for text_key in output_dict:
#		$Label.text += " Key: "+text_key
#		$Label.text += " Value: "+str(output_dict[text_key])
	
#	for text_key in text_dict_answ:
#		$Label2.text += " Key: "+text_key
#		$Label2.text += " Value: "+str(text_dict_answ[text_key])
##		if "cucu"==text_key:
##			$Label2.text += " "+str(text_dict_answ[text_key])
##		else:
##			$Label2.text += " "+str(text_dict_answ[text_key])
	
	
	
	pass # Replace with function body.
