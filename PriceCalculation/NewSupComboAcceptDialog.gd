extends AcceptDialog

signal ok_pressed(text)

# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	self.register_text_enter($NewSupComboLineEdit)
	$NewSupComboLineEdit.grab_focus()
#	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _on_NewSupComboAcceptDialog_visibility_changed():
	if self.is_visible():
		$NewSupComboLineEdit.grab_focus()

func _on_NewSupComboAcceptDialog_confirmed():
	var option_text:String = $NewSupComboLineEdit.get_text()
	emit_signal("ok_pressed",option_text)
	$NewSupComboLineEdit.clear()

