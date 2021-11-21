extends AcceptDialog

signal ok_pressed(text)

# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	self.register_text_enter($NewOptionLineEdit)
	$NewOptionLineEdit.grab_focus()
#	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass



func _on_NewOptionWindowDialog_visibility_changed():
	if self.is_visible():
		$NewOptionLineEdit.grab_focus()
#		pass # Replace with function body.


func _on_NewOptionAcceptDialog_confirmed():
	var option_text:String = $NewOptionLineEdit.get_text()
	emit_signal("ok_pressed",option_text)
	$NewOptionLineEdit.clear()
