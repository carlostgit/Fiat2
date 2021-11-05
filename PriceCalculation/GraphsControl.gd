extends Control

#Controla las gráficas que se tienen que ver en Plotter

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

var _name_funcref_dict:Dictionary = {}
var _highlighted_graph:String = ""

const _plotter_node_path:NodePath = @"../../Plotter"

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func add_graph(funcref_arg:FuncRef, name_arg:String):
	_name_funcref_dict[name_arg] = funcref_arg
	update_plotter()
	update_graph_item_list()

func update_plotter():
	var plotter_node = get_node(_plotter_node_path)
	plotter_node.clear()
	for name in _name_funcref_dict.keys():
		var func_ref = _name_funcref_dict[name]
		
		if _highlighted_graph == name:
			var highlight_color:Color = Color(1,1,1)
			plotter_node.add_func_ref(func_ref,[],name, highlight_color)
		else:
			plotter_node.add_func_ref(func_ref,[],name)
			

func clear():
	_name_funcref_dict.clear()
	update_plotter()
	update_graph_item_list()
	_highlighted_graph = ""

func _on_ClearButton_pressed():
	clear()
	
func update_graph_item_list():
	$GraphsItemList.clear()
	for graph_name in _name_funcref_dict.keys():		
		$GraphsItemList.add_item(graph_name)


func _on_GraphsItemList_item_selected(index):
	var graph_name = $GraphsItemList.get_item_text(index)
	_highlighted_graph = graph_name
	update_plotter()
	
