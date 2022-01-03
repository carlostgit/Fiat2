extends AcceptDialog

signal ok_pressed(text)

# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	self.register_text_enter($AddLineEdit) #Para que al dar al Enter se acepte el diálogo


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_AddPersonAcceptDialog_confirmed():
	var add_text:String = $AddLineEdit.get_text()
	emit_signal("ok_pressed",add_text)
	$AddLineEdit.clear()
		


func _on_AddPersonAcceptDialog_about_to_show():
#	Sin el call_defferred no funciona
	$AddLineEdit.call_deferred("grab_focus")
