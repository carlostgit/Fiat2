extends Control

var _draw_backround_rect:bool = true

const _param_view_test_graph = false

#TODO: valores mínimos
var _min_x:float = 0
var _min_y:float = 0
#

var _max_x:float = 5 
var _max_y:float = 100

var _left_margin:float = 20
var _top_margin:float = 30
var _bottom_margin:float = 40
var _right_margin:float = 60

var _height:float = 500
var _width:float = 200

var _total_num_of_calculated_points:int = 100

#Parámetros que se calcularán a partir de los anteriores
var _width_per_calculated_point:float = 6
var _x_zoom:float = 20
var _y_zoom:float = 40.0
var _step_between_calculated_points:float = 0.0
#

var _canvas_item:CanvasItem = self
var _font = load("res://Plotter/new_dynamicfont.tres")

#Cosas a dibujar
#Funciones:
var _func_array:Array = []
var _func_label_dict:Dictionary = {}
var _func_args_dict:Dictionary = {}
var _func_color_dict:Dictionary = {}
#

#Puntos sueltos
var _points_to_draw:Array = []

#Grupos de puntos
var _groupid_points:Dictionary = {}
var _groupid_color:Dictionary = {}
var _groupid_label:Dictionary = {}

#
# Called when the node enters the scene tree for the first time.
func _ready():

#	init(7,80)
#
#	Descomentar esto, para tener un ejeplo
	if _param_view_test_graph:
		test()

	pass
	
func test():
	
	var test_funcref = funcref( self, "default_test_function")
	add_func_ref(test_funcref,[],"test",Color(0,1,1))
	updated_size()
	
func recalculate_member_variables():

	_canvas_item = self
	var param_min_width = 10
	_width = self.get_rect().size.x - _left_margin - _right_margin
	
	if _width < param_min_width:
		_width = param_min_width
	
	_width_per_calculated_point = _width/float(_total_num_of_calculated_points)
	
	_x_zoom = self._width/(self._max_x - self._min_x)
	
	var y_max:float = _max_y
	_height = self.get_rect().size.y - _top_margin - _bottom_margin
	var param_min_height = 10
	if _height < param_min_height:
		_height = param_min_height

	_y_zoom = _height/(y_max-self._min_y)
	
	_step_between_calculated_points = float(_max_x-_min_x)/float(_total_num_of_calculated_points)

	update()


func clear():
	_func_array.clear()
	_func_label_dict.clear()
	_func_args_dict.clear()
	_points_to_draw.clear()
	_groupid_points.clear()
	
	_func_color_dict.clear()
	_groupid_color.clear()
	_groupid_label.clear()

	update()

	
func clear_group_of_points(groupid_arg:int):
	_groupid_points.erase(groupid_arg)
	_groupid_color.erase(groupid_arg)
	_groupid_label.erase(groupid_arg)
	
	update()

func add_func_ref(func_ref_arg:FuncRef, func_args_arg = [], label_arg:String = "", color_arg:Color = Color(0,1,1))->void:
	_func_array.append(func_ref_arg)
	_func_label_dict[func_ref_arg]=label_arg
	
	_func_args_dict[func_ref_arg]=func_args_arg
	
	_func_color_dict[func_ref_arg]=color_arg

	update()	

func default_test_function(x_arg:float) -> float:
	var y:float = x_arg*x_arg
	return y


func updated_size()->void:
	recalculate_member_variables()
	update()

func _init(x_max_arg:float=5, y_max_arg:float=10, left_margin_arg:float=40, right_margin_arg:float=40, top_margin_arg:float=40, bottom_margin_arg:float=80, points_calculated_arg=100):
	self.connect("item_rect_changed",self,"updated_size")
	init(x_max_arg, y_max_arg, left_margin_arg, right_margin_arg, top_margin_arg, bottom_margin_arg, points_calculated_arg)


func init(x_max_arg:float, y_max_arg:float, left_margin_arg:float=40, right_margin_arg:float=40, top_margin_arg:float=40, bottom_margin_arg:float=80, points_calculated_arg=100):

	_max_x = x_max_arg 
	_max_y = y_max_arg
	_left_margin = left_margin_arg
	_right_margin = right_margin_arg
	_top_margin = top_margin_arg
	_bottom_margin = bottom_margin_arg
	_total_num_of_calculated_points = points_calculated_arg
	
	_canvas_item = self
	var param_min_width = 10
	_width = self.get_rect().size.x - _left_margin - _right_margin
	
	if _width < param_min_width:
		_width = param_min_width
	
	_width_per_calculated_point = _width/float(points_calculated_arg)
	
	_x_zoom = self._width/(self._max_x - self._min_x)
	
	var y_max:float = _max_y
	_height = self.get_rect().size.y - _top_margin - _bottom_margin
	var param_min_height = 10
	if _height < param_min_height:
		_height = param_min_height

	_y_zoom = _height/(y_max-self._min_y)
	
	_step_between_calculated_points = float(_max_x-self._min_x)/float(_total_num_of_calculated_points)


func _draw():
	draw_background()
	draw_points()
	draw_point_groups()

	#Se dibujan todos las funciones que hay en _func_array
	#Esas funciones pueden estar en objetos que pueden desaparecer sin aviso
	#Por eso uso el método FuncRef::is_valid()
	
	var count:int = 0
	var index_of_not_valid_func:int = -1
	var not_valid_func
	for func_to_draw in _func_array:
		var label:String = self._func_label_dict[func_to_draw]
		var func_args = self._func_args_dict[func_to_draw]
		var color:Color = self._func_color_dict[func_to_draw]
		if func_to_draw.is_valid():
			draw(func_to_draw,label,func_args,color)
		else:
			index_of_not_valid_func=count
			not_valid_func = func_to_draw
		count +=1
	
	if index_of_not_valid_func >=0:
		_func_label_dict.erase(not_valid_func)
		_func_array.remove(index_of_not_valid_func)


func draw_background():
	
	var rect_width:float = self.get_rect().size.x
	var rect_height:float = self.get_rect().size.y
	
	#Rectángulo opaco
	if(_draw_backround_rect):
		_canvas_item.draw_rect(Rect2(Vector2(0,0),Vector2(rect_width,rect_height)),Color(0,0,0,1),true)
	
	#Bordes del Control:
	_canvas_item.draw_line(Vector2(0,rect_height),Vector2(rect_width,rect_height), Color(0,1,1))
	_canvas_item.draw_line(Vector2(0,0),Vector2(rect_width,0), Color(0,1,1))
	_canvas_item.draw_line(Vector2(0,0),Vector2(0,rect_height), Color(0,1,1))
	_canvas_item.draw_line(Vector2(rect_width,0),Vector2(rect_width,rect_height), Color(0,1,1))
	#
	#Márgenes
	_canvas_item.draw_line(Vector2(_left_margin,rect_height-_bottom_margin),Vector2(rect_width-_right_margin,rect_height-_bottom_margin), Color(1,0,1))
	_canvas_item.draw_line(Vector2(_left_margin,_top_margin),Vector2(rect_width-_right_margin,_top_margin), Color(1,0,1))
	_canvas_item.draw_line(Vector2(_left_margin,_top_margin),Vector2(_left_margin,rect_height-_bottom_margin), Color(1,0,1))
	_canvas_item.draw_line(Vector2(rect_width-_right_margin,_top_margin),Vector2(rect_width-_right_margin,rect_height-_bottom_margin), Color(1,0,1))
	#
	
	#Línea y
	_canvas_item.draw_line(Vector2(_left_margin,_height+_top_margin),Vector2(_left_margin,_top_margin), Color(1,1,1))

	#Dibujo la linea del y=1
#	_canvas_item.draw_line(Vector2(_left_margin,_height+_top_margin-1*_y_zoom),Vector2(_width+_left_margin,_height+_top_margin-1*_y_zoom), Color(1,1,1)) #Value of 1 line

	#Dibujo de líneas horizontales
#	Primero calculo cuántas líneas quiero dibujar. No quiero dibujar más de 100 líneas
	
	var num_hor_lines_to_draw:float = self._max_y - self._min_y
	var ten_times_reductions_in_hor_lines:int = 0
	while num_hor_lines_to_draw>100:
		num_hor_lines_to_draw = num_hor_lines_to_draw/(10)
		ten_times_reductions_in_hor_lines += 1
	
	for value_y_of_line in range(self._min_y, self._max_y, pow(10,ten_times_reductions_in_hor_lines)):
		if (value_y_of_line>0 and value_y_of_line < self._max_y):
			_canvas_item.draw_line(Vector2(_left_margin,_height+_top_margin-(value_y_of_line-self._min_y)*_y_zoom),Vector2(_width+_left_margin,_height+_top_margin-(value_y_of_line-self._min_y)*_y_zoom), Color(1,1,1,0.5)) #Value of 1 line

	#10 líneas verticales
#	for line in range(1,10):
#		_canvas_item.draw_line(Vector2((line*_total_num_of_calculated_points/10)*_width_per_calculated_point+_left_margin,_height+_top_margin),Vector2((line*_total_num_of_calculated_points/10)*_width_per_calculated_point+_left_margin,_top_margin), Color(1,1,1)) #Cuantity of 50 line
	
	#Dibujo de líneas verticales
#	Primero calculo cuántas líneas quiero dibujar. No quiero dibujar más de 100 líneas
	var num_vert_lines_to_draw = self._max_x-self._min_x
	var ten_times_reductions_in_vert_lines:int = 0
	while num_vert_lines_to_draw>100:
		num_vert_lines_to_draw = num_vert_lines_to_draw/(10)
		ten_times_reductions_in_vert_lines += 1
	
#	for line_x in self._max_x:
	for value_x_of_line in range(self._min_x, self._max_x ,pow(10,ten_times_reductions_in_vert_lines)):		
		if (value_x_of_line>0 and value_x_of_line<self._max_x):
			_canvas_item.draw_line(Vector2((value_x_of_line-self._min_x)*_x_zoom+_left_margin,_height+_top_margin),Vector2((value_x_of_line-self._min_x)*_x_zoom+_left_margin,_top_margin), Color(1,1,1,0.5)) 

	#Línea x
	_canvas_item.draw_line(Vector2(_left_margin,_height+_top_margin),Vector2(_left_margin+_width,_height+_top_margin), Color(1,1,1)) #Cuantity of 100 line

	var font_size_y:float = _font.get_string_size("0").y
	
	#_max_x Etiqueta con el máximo en X
	_canvas_item.draw_string(_font,Vector2(_total_num_of_calculated_points*_width_per_calculated_point+_left_margin,_height+_top_margin+font_size_y),String(_max_x),Color(1,1,1))
	
	#Etiqueta con el mínimo en x
	_canvas_item.draw_string(_font,Vector2(_left_margin,_height+_top_margin+font_size_y),String(self._min_x),Color(1,1,1))
	
	#Dibujo la etiqueta del y=1
	#_canvas_item.draw_string(_font,Vector2(0,_height+_top_margin-1*_y_zoom),"1",Color(1,1,1))

	#_max_y Etiqueta con el máximo en Y
	_canvas_item.draw_string(_font,Vector2(0,_top_margin),str(_max_y),Color(1,1,1))
	
	#Etiqueta con el mínimo en y
	_canvas_item.draw_string(_font,Vector2(0,_height+_top_margin),str(self._min_y),Color(1,1,1))


func draw(var myfunc, var label_arg:String, func_args_arg = [], color_arg:Color = Color(0,1,0)):

	var last_y:float = 0
	var last_x:float = 0
	for i in range(0,_total_num_of_calculated_points):	

		var x1:float = _width_per_calculated_point*float(i)
		var x2:float = _width_per_calculated_point*float(i+1)
#		var y1:float = _y_zoom*myfunc.call_func(func_arg,i*_calculated_points_per_unit)
#		var y2:float = _y_zoom*myfunc.call_func(func_arg,(i+1)*_calculated_points_per_unit)
		var arguments_array1:Array = []
		arguments_array1.append(i*_step_between_calculated_points + self._min_x)
		var arguments_array2:Array = []
		arguments_array2.append((i+1)*_step_between_calculated_points + self._min_x)
		for extra_arg in func_args_arg:
			arguments_array1.append(extra_arg)
			arguments_array2.append(extra_arg)
#		var y1:float = _y_zoom*myfunc.call_func(i*_calculated_points_per_unit)
		var debug = myfunc.call_funcv(arguments_array1)
		var y1:float = _y_zoom*(myfunc.call_funcv(arguments_array1)-self._min_y)
		var y2:float = _y_zoom*(myfunc.call_funcv(arguments_array2)-self._min_y)
	
		_canvas_item.draw_line(Vector2((_left_margin+x1),_height+_top_margin-y1), Vector2((_left_margin+x2), _height+_top_margin-y2), color_arg, 1)

		last_x = _left_margin+x2
		last_y = _height+_top_margin-y2
		
	
	var label_pos:Vector2 = Vector2(last_x,last_y)	
	var font_size_y:float = _font.get_string_size("0").y
	if (last_y<font_size_y):
		label_pos.y=font_size_y;
#
	_canvas_item.draw_string(_font,label_pos,label_arg,color_arg)


func add_point(point_arg:Vector2):
	_points_to_draw.append(point_arg)
	
	update()

func add_point_group(group_id:int, points_arg:Array, color_arg:Color = Color(0,1,1), label_arg = ""):
	
	_groupid_points[group_id] = points_arg
	_groupid_color[group_id] = color_arg
	_groupid_label[group_id] = label_arg

	update()

func draw_points(color_arg:Color = Color(0,1,0)):
	
	for point in _points_to_draw:
		var x:float = point.x
		var y:float = point.y
		
		var y1:float = _y_zoom*y
		var y_canvas:float = _height+_top_margin-y1
		
		var x1:float = _x_zoom*x
		var x_canvas:float = _left_margin+x1
		
		_canvas_item.draw_line(Vector2(x_canvas,y_canvas),Vector2(x_canvas+10,y_canvas+10),color_arg)
		_canvas_item.draw_line(Vector2(x_canvas,y_canvas),Vector2(x_canvas-10,y_canvas-10),color_arg)
		_canvas_item.draw_line(Vector2(x_canvas,y_canvas),Vector2(x_canvas-10,y_canvas+10),color_arg)
		_canvas_item.draw_line(Vector2(x_canvas,y_canvas),Vector2(x_canvas+10,y_canvas-10),color_arg)


func draw_point_groups():
	
	for id in _groupid_points.keys():
		var points:Array = _groupid_points[id]
		var color:Color = _groupid_color[id]
		if points.empty():
			continue
		
		var last_point_position:Vector2 = Vector2()
		var previous_point:Vector2 = points.front()
		var count:int = 0
		for point in points:
			count += 1
			if 1==count:
				continue
			
			var x_prev:float = previous_point.x
			var y_prev:float = previous_point.y
			
			var y1:float = _y_zoom*(y_prev-self._min_y)
			var y_canvas_prev:float = _height+_top_margin-y1
			
			var x1:float = _x_zoom*(x_prev-self._min_x)
			var x_canvas_prev:float = _left_margin+x1
			
			var x:float = point.x
			var y:float = point.y
			
			var y2:float = _y_zoom*(y-self._min_y)
			var y_canvas:float = _height+_top_margin-y2
			
			var x2:float = _x_zoom*(x-self._min_x)
			var x_canvas:float = _left_margin+x2
		
			_canvas_item.draw_line(Vector2(x_canvas_prev,y_canvas_prev),Vector2(x_canvas,y_canvas),color)
			
			last_point_position = Vector2(x_canvas,y_canvas)
			
			previous_point = point
		
		var label_point_position:Vector2 = last_point_position
		var label:String = self._groupid_label[id]
		
		var font_size_y:float = _font.get_string_size("0").y
		if (label_point_position.y<font_size_y):
			label_point_position.y=font_size_y;
#
		_canvas_item.draw_string(_font,label_point_position,label,color)
		

func set_max_x_axis_value(max_value:float):
	_max_x = max_value
	updated_size()

func set_max_y_axis_value(max_value:float):
	_max_y = max_value
	updated_size()

func set_func_color(func_ref_arg:FuncRef, color_arg:FuncRef):
	if self._func_color_dict.has(func_ref_arg):
		self._func_color_dict[func_ref_arg] = color_arg
		
func set_min_x_axis_value(min_value:float):
	_min_x = min_value
	updated_size()

func set_min_y_axis_value(min_value:float):
	_min_y = min_value
	updated_size()


func _on_XMaxSpinBox_value_changed(value):
	if (value>self._min_x):
		set_max_x_axis_value(value)

func _on_XMinSpinBox_value_changed(value):
	if (value<self._max_x):
		set_min_x_axis_value(value)

func _on_YMaxSpinBox_value_changed(value):
	if (value>self._min_y):
		set_max_y_axis_value(value)

func _on_YMinSpinBox_value_changed(value):
	if (value<self._max_y):
		set_min_y_axis_value(value)


func _on_ShowControlsButton_toggled(button_pressed):
	if button_pressed:
		$XMaxSpinBox.show()
		$XMinSpinBox.show()
		$YMaxSpinBox.show()
		$YMinSpinBox.show()
	else:
		$XMaxSpinBox.hide()
		$XMinSpinBox.hide()
		$YMaxSpinBox.hide()
		$YMinSpinBox.hide()
#	pass # Replace with function body.
