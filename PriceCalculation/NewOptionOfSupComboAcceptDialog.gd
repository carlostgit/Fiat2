extends AcceptDialog

signal ok_pressed(text)

# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	self.register_text_enter($NewOptionOfSupComboLineEdit)
	$NewOptionOfSupComboLineEdit.grab_focus()

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_NewOptionOfSupComboAcceptDialog_visibility_changed():
	if self.is_visible():
		$NewOptionOfSupComboLineEdit.grab_focus()


func _on_NewOptionOfSupComboAcceptDialog_confirmed():
	var option_text:String = $NewOptionOfSupComboLineEdit.get_text()
	emit_signal("ok_pressed",option_text)
	$NewOptionOfSupComboLineEdit.clear()

