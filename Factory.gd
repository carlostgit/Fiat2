extends Node2D

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

export(Texture) var _product_texture = preload("res://candy_small.png")
#export(String) var _demanded_product_type = "Chocolate"
export(bool) var _produce_candy = true

# Called when the node enters the scene tree for the first time.
func _ready():
	pass
# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
