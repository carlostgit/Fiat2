extends AcceptDialog

signal ok_pressed(text)

# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	self.register_text_enter($NewOptionOfCompComboLineEdit)
	$NewOptionOfCompComboLineEdit.grab_focus()

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_NewOptionOfCompComboAcceptDialog_visibility_changed():
	if self.is_visible():
		$NewOptionOfCompComboLineEdit.grab_focus()


func _on_NewOptionOfCompComboAcceptDialog_confirmed():
	var option_text:String = $NewOptionOfCompComboLineEdit.get_text()
	emit_signal("ok_pressed",option_text)
	$NewOptionOfCompComboLineEdit.clear()
