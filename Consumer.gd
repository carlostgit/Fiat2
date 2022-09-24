extends Sprite


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

var _to_be_consumed_dict:Dictionary = {"bill":0.0,
								"candy":0.0,
								"chocolate":0.0}

var _current_consumption_dict:Dictionary = {"bill":0.0,
								"candy":0.0,
								"chocolate":0.0}

signal send_products_to_consume_signal(to_be_consumed_dict)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func reset():
	_to_be_consumed_dict["bill"]=0.0
	_to_be_consumed_dict["candy"]=0.0
	_to_be_consumed_dict["chocolate"]=0.0
	_current_consumption_dict["bill"]=0.0
	_current_consumption_dict["candy"]=0.0
	_current_consumption_dict["chocolate"]=0.0
	

func update_labels():
	if _to_be_consumed_dict.has("bill"):
		var amount:float = _to_be_consumed_dict["bill"]
		$Bill/BillsToEatLabel.set_text(str(amount))
	if _to_be_consumed_dict.has("candy"):
		var amount:float = _to_be_consumed_dict["candy"]
		$Candy/CandiesToEatLabel.set_text(str(amount))
	if _to_be_consumed_dict.has("chocolate"):
		var amount:float = _to_be_consumed_dict["chocolate"]
		$Chocolate/ChocolatesToEatLabel.set_text(str(amount))	


func calculated_consumption_of_person(consumpt_dict):
	_to_be_consumed_dict = consumpt_dict.duplicate()
	update_labels()




func _on_ConsumeButton_pressed():
	reset()
	update_labels()

func _on_SendToConsumeButton_pressed():
#	#De momento, se consume todo lo que se había calculado
	#Pero tal vez habría que comprobar que hay suficientes productos
	_current_consumption_dict = _to_be_consumed_dict
	emit_signal("send_products_to_consume_signal",_to_be_consumed_dict)
