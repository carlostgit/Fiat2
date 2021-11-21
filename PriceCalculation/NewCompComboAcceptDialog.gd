extends AcceptDialog

signal ok_pressed(text)

# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	self.register_text_enter($NewCompComboLineEdit)
	$NewCompComboLineEdit.grab_focus()
#	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_NewCompComboAcceptDialog_visibility_changed():
	if self.is_visible():
		$NewCompComboLineEdit.grab_focus()

func _on_NewCompComboAcceptDialog_confirmed():
	var option_text:String = $NewCompComboLineEdit.get_text()
	emit_signal("ok_pressed",option_text)
	$NewCompComboLineEdit.clear()
