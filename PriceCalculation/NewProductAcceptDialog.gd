extends AcceptDialog

signal ok_pressed(text)

# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	self.register_text_enter($NewProductLineEdit)
	$NewProductLineEdit.grab_focus()
#	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass



func _on_NewProductAcceptDialog_confirmed():
	var product_text:String = $NewProductLineEdit.get_text()
	emit_signal("ok_pressed",product_text)
	$NewProductLineEdit.clear()


func _on_NewProductAcceptDialog_visibility_changed():
	if self.is_visible():
		$NewProductLineEdit.grab_focus()
#		pass # Replace with function body.
