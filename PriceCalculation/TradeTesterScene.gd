extends Control


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

const SatisfactionCalculator = preload("res://PriceCalculation/SatisfactionCalculator.gd")
var _satisfaction_calculator_ref:SatisfactionCalculator = null
#var _satisfaction_calculator_copy:SatisfactionCalculator = null
const TradeCalculator = preload("res://PriceCalculation/TradeCalculator.gd")
var _trade_calculator:TradeCalculator = null

var name_of_model:String = ""


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func set_satisfaction_calculator_ref(satisf_calculator_arg):
	_satisfaction_calculator_ref = satisf_calculator_arg
	self.name_of_model = _satisfaction_calculator_ref.get_name()
	$SatisfModelNameLabel.set_text(self.name_of_model)
	_trade_calculator = TradeCalculator.new(_satisfaction_calculator_ref)

#	He creado un _init en SatisfactionCalculator, que hace de constructor de copia
#	_satisfaction_calculator_copy = SatisfactionCalculator.new(satisf_calculator_arg)
	_update_items()
	

#	_draw_test2()

func _on_OptionsItemList_item_selected(index):
#	Selecciono el producto asociado
	var option:String = $OptionsItemList.get_item_text(index)	
	var option_product_dict:Dictionary = _satisfaction_calculator_ref.get_option_product_dict()
	if option_product_dict.has(option):
		var product:String = option_product_dict[option]
		for prod_indx in $ProductsItemList.get_item_count():
			var item_text:String = $ProductsItemList.get_item_text(prod_indx)
			if item_text == product:
				$ProductsItemList.select(prod_indx)
	
		# Pongo el precio del producto
		var price:float = Prices.get_price_of_product(product)
		$PriceLabel.set_text(str(price))

func get_options_for_amount_of_currency(amount_arg:float)->Dictionary:
	var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict(amount_arg)
	return best_combidict

#func draw_test(max_amount_of_money_arg:float=50.0):
#
#	var option_info:Dictionary = {}
#	for option in _satisfaction_calculator_ref.get_options():
#		option_info[option]=Array()	
#
#	var i:float = 0
#	var step:float = 1.0
#	while  i <= max_amount_of_money_arg:
#
#		var money_quant:float = i
#		var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict(money_quant)
#
#		for option in _satisfaction_calculator_ref.get_options():
#			var amount_of_option:float = 0
#			if best_combidict.has(option):
#				amount_of_option = best_combidict[option]
#			option_info[option].append(Vector2(money_quant,amount_of_option))
#
#		i+=step	
#
#	var count:int = 0
#	for option_idx in $OptionsItemList.get_item_count(): 
#		count+=1
#		var option_text:String = $OptionsItemList.get_item_text(option_idx)
#
#		var red = float(count)/5.0+0.2
#		var green = float(count)/5.0+0.0
#		var blue = float(-count)/5.0+1.0
#		var color:Color = Color(red,green,blue)
#
#		$Plotter.add_point_group(option_idx, option_info[option_text], color, option_text)

func _draw_test1(max_amount_of_money_arg:float=50.0, step_arg:float=0.1):
	
		
	$Plotter.clear()
	var option_info:Dictionary = {}
	for option in _satisfaction_calculator_ref.get_options():
		option_info[option]=Array()	
	
	var i:float = 0
	var step:float = step_arg
#	var calculating_step:float = calculating_step_arg
#	var best_combidict_for_each_step:Dictionary = _trade_calculator.calculate_best_combidict_for_each_budget(max_amount_of_money_arg,calculating_step)	
	while  i <= max_amount_of_money_arg:
#	for i in best_combidict_for_each_step.keys():
		
		var money_quant:float = i
#		var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict(money_quant)
		var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict(money_quant)
		
		for option in _satisfaction_calculator_ref.get_options():
			var amount_of_option:float = 0
			if best_combidict.has(option):
				amount_of_option = best_combidict[option]
			option_info[option].append(Vector2(money_quant,amount_of_option))
		
		i+=step	

	var count:int = 0
	for option_idx in $OptionsItemList.get_item_count(): 
		count+=1
		var option_text:String = $OptionsItemList.get_item_text(option_idx)
		
		var red = float(count)/5.0+0.2
		var green = float(count)/5.0+0.0
		var blue = float(-count)/5.0+1.0
		var color:Color = Color(red,green,blue)
		
		$Plotter.add_point_group(option_idx, option_info[option_text], color, option_text)

	
func _draw_test2(max_amount_of_money_arg:float=50.0, step_arg:float=0.1, calculating_step_arg:float=0.5):
	
	var usec_start = OS.get_ticks_usec()
	var countCalc:int = 0
	
	$Plotter.clear()
	var option_info:Dictionary = {}
	for option in _satisfaction_calculator_ref.get_options():
		option_info[option]=Array()	
	
#	var i:float = 0
	var step:float = step_arg
	var calculating_step:float = calculating_step_arg
	var best_combidict_for_each_step:Dictionary = _trade_calculator.calculate_best_combidict_for_each_budget(max_amount_of_money_arg,calculating_step)	
	countCalc += 1
	var usec_end = OS.get_ticks_usec()
#	while  i <= max_amount_of_money_arg:
	for i in best_combidict_for_each_step.keys():
		
		var money_quant:float = i
#		var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict(money_quant)
		var best_combidict:Dictionary = best_combidict_for_each_step[i]
		
		for option in _satisfaction_calculator_ref.get_options():
			var amount_of_option:float = 0
			if best_combidict.has(option):
				amount_of_option = best_combidict[option]
			option_info[option].append(Vector2(money_quant,amount_of_option))
		
		i+=step	

	var count:int = 0
	for option_idx in $OptionsItemList.get_item_count(): 
		count+=1
		var option_text:String = $OptionsItemList.get_item_text(option_idx)
		
		var red = float(count)/5.0+0.2
		var green = float(count)/5.0+0.0
		var blue = float(-count)/5.0+1.0
		var color:Color = Color(red,green,blue)
		
		$Plotter.add_point_group(option_idx, option_info[option_text], color, option_text)

	
	var usec_elapsed = usec_end-usec_start
	$CalcCostLabel.set_text(str(usec_elapsed/countCalc))


func _draw_test3_with_precalculation(max_amount_of_money_arg:float=50.0, step_arg:float=0.1):
#	Usando 	precalculate_best_combidict_for_each_budget
	
	
	$Plotter.clear()
	var option_info:Dictionary = {}
	for option in _satisfaction_calculator_ref.get_options():
		option_info[option]=Array()	
	
#	var i:float = 0
	var step:float = step_arg
#	var best_combidict_for_each_step:Dictionary = _trade_calculator.calculate_best_combidict_for_each_budget(max_amount_of_money_arg,step)	
	_trade_calculator.precalculate_best_combidict_for_each_budget(max_amount_of_money_arg,step)
#	while  i <= max_amount_of_money_arg:
	var i:float = 0
	while (i <= max_amount_of_money_arg*10):
		
		var money_quant:float = i/10.0
#		var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict(money_quant)
#		var best_combidict:Dictionary = best_combidict_for_each_step[i]
#		TODO: debugear que los resultados salgan bien. Creo que no están saliendo bien

		if money_quant >30.0:
			assert("debugea esto")

		var best_combidict:Dictionary = _trade_calculator.get_precalculated_best_combidict(money_quant)
		
		for option in _satisfaction_calculator_ref.get_options():
			var amount_of_option:float = 0
			if best_combidict.has(option):
				amount_of_option = best_combidict[option]
			option_info[option].append(Vector2(money_quant,amount_of_option))
		
		i+=step	

	var count:int = 0
	for option_idx in $OptionsItemList.get_item_count(): 
		count+=1
		var option_text:String = $OptionsItemList.get_item_text(option_idx)
		
		var red = float(count)/5.0+0.2
		var green = float(count)/5.0+0.0
		var blue = float(-count)/5.0+1.0
		var color:Color = Color(red,green,blue)
		
		$Plotter.add_point_group(option_idx, option_info[option_text], color, option_text)


func _draw_test5_simple_continuity(max_amount_of_money_arg:float=50.0, step_arg:float=0.1, calc_step_arg:float=1.0):
#	Usando 	precalculate_best_combidict_for_each_budget
	
#	var usec_start = OS.get_ticks_usec()
	
#	PerformanceUtils.reset()
	TimeMeasurement.reset()
#	PerformanceUtils.start("draw_test5_simple_continuity")
	
	$Plotter.clear()
	var option_info:Dictionary = {}
	for option in _satisfaction_calculator_ref.get_options():
		option_info[option]=Array()	
	
#	var i:float = 0
	var step:float = step_arg
	var calc_step:float = calc_step_arg
#	var best_combidict_for_each_step:Dictionary = _trade_calculator.calculate_best_combidict_for_each_budget(max_amount_of_money_arg,step)	
#	_trade_calculator.precalculate_best_combidict_for_each_budget(max_amount_of_money_arg,step)
#	while  i <= max_amount_of_money_arg:
#	var countCalc:int = 0
	var i:float = 0
	while (i <= max_amount_of_money_arg):
		
		var money_quant:float = i
#		var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict(money_quant)
#		var best_combidict:Dictionary = best_combidict_for_each_step[i]
#		TODO: debugear que los resultados salgan bien. Creo que no están saliendo bien

		if money_quant >30.0:
			assert("debugea esto")

#		PerformanceUtils.start("_trade_calculator.calculate_best_combidict_simple_with_continuity(money_quant)")
#		TimeMeasurement.start("calculate_best_combidict_simple_with_continuity")	
		var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict_simple_with_continuity_with_product_step(money_quant,calc_step)
#		countCalc+=1
#		TimeMeasurement.stop("calculate_best_combidict_simple_with_continuity")	
#		PerformanceUtils.stop("_trade_calculator.calculate_best_combidict_simple_with_continuity(money_quant)")
			
		for option in _satisfaction_calculator_ref.get_options():
			var amount_of_option:float = 0
			if best_combidict.has(option):
				amount_of_option = best_combidict[option]
			option_info[option].append(Vector2(money_quant,amount_of_option))
		
		i+=step	

	

	var count:int = 0
	for option_idx in $OptionsItemList.get_item_count(): 
		count+=1
		var option_text:String = $OptionsItemList.get_item_text(option_idx)
		
		var red = float(count)/5.0+0.2
		var green = float(count)/5.0+0.0
		var blue = float(-count)/5.0+1.0
		var color:Color = Color(red,green,blue)
		
		$Plotter.add_point_group(option_idx, option_info[option_text], color, option_text)

	
#	var usec_end = OS.get_ticks_usec()
#
#	var usec_elapsed = usec_end-usec_start
	
	
#	PerformanceUtils.stop("draw_test5_simple_continuity")
#	var elapsed = TimeMeasurement.get_average_time("draw_test5_simple_continuity")
	var elapsed = TimeMeasurement.get_total_time("calculate_best_combidict_simple_with_continuity")
	var num_calls = TimeMeasurement.get_num_measurements("calculate_best_combidict_simple_with_continuity")
	
	TimeMeasurement.print_info()
#	$CalcCostLabel.set_text(str(usec_elapsed/countCalc))
	$CalcCostLabel.set_text("calculate_best_combidict_simple_with_continuity: "+ str(elapsed))
	
	$CalcCostLabelExtraInfo.set_text("num calls:" +str(num_calls))
	
	
func _draw_test6_simple_continuity_budget_step(max_amount_of_money_arg:float=50.0, step_arg:float=0.1, calc_step_arg:float = 0.5):
#	Usando 	precalculate_best_combidict_for_each_budget
	
#	var usec_start = OS.get_ticks_usec()
	
#	PerformanceUtils.reset()
#	TimeMeasurement.reset()
#	PerformanceUtils.start("draw_test5_simple_continuity")
	
	$Plotter.clear()
	var option_info:Dictionary = {}
	for option in _satisfaction_calculator_ref.get_options():
		option_info[option]=Array()	
	
#	var i:float = 0
	var step:float = step_arg
	var calc_step:float = calc_step_arg
#	var best_combidict_for_each_step:Dictionary = _trade_calculator.calculate_best_combidict_for_each_budget(max_amount_of_money_arg,step)	
#	_trade_calculator.precalculate_best_combidict_for_each_budget(max_amount_of_money_arg,step)
#	while  i <= max_amount_of_money_arg:
#	var countCalc:int = 0
	var i:float = 0
	while (i <= max_amount_of_money_arg):
		
		var money_quant:float = i
#		var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict(money_quant)
#		var best_combidict:Dictionary = best_combidict_for_each_step[i]
#		TODO: debugear que los resultados salgan bien. Creo que no están saliendo bien

#		if money_quant >30.0:
#			assert("debugea esto")

#		PerformanceUtils.start("_trade_calculator.calculate_best_combidict_simple_with_continuity(money_quant)")
#		TimeMeasurement.start("draw_test5_simple_continuity")	
		var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict_simple_with_continuity_budget_step(money_quant,calc_step)
#		countCalc+=1
#		TimeMeasurement.stop("draw_test5_simple_continuity")	
#		PerformanceUtils.stop("_trade_calculator.calculate_best_combidict_simple_with_continuity(money_quant)")
			
		for option in _satisfaction_calculator_ref.get_options():
			var amount_of_option:float = 0
			if best_combidict.has(option):
				amount_of_option = best_combidict[option]
			option_info[option].append(Vector2(money_quant,amount_of_option))
		
		i+=step	

	

	var count:int = 0
	for option_idx in $OptionsItemList.get_item_count(): 
		count+=1
		var option_text:String = $OptionsItemList.get_item_text(option_idx)
		
		var red = float(count)/5.0+0.2
		var green = float(count)/5.0+0.0
		var blue = float(-count)/5.0+1.0
		var color:Color = Color(red,green,blue)
		
		$Plotter.add_point_group(option_idx, option_info[option_text], color, option_text)

	
#	var usec_end = OS.get_ticks_usec()
#
#	var usec_elapsed = usec_end-usec_start
	
	
#	PerformanceUtils.stop("draw_test5_simple_continuity")
#	var elapsed = TimeMeasurement.get_average_time("draw_test5_simple_continuity")
#	var elapsed = TimeMeasurement.get_total_time("draw_test5_simple_continuity")
#	var num_calls = TimeMeasurement.get_num_measurements("draw_test5_simple_continuity")
	
#	TimeMeasurement.print_info()
#	$CalcCostLabel.set_text(str(usec_elapsed/countCalc))
#	$CalcCostLabel.set_text("draw_test5_simple_continuity: "+ str(elapsed))
	
#	$CalcCostLabelExtraInfo.set_text("num calls:" +str(num_calls))


func _draw_test7_simple_continuity_budget_product_max_step(max_amount_of_money_arg:float=50.0, step_arg:float=0.1, calc_step_arg:float = 0.5):	
#	var usec_start = OS.get_ticks_usec()
	
#	PerformanceUtils.reset()
#	TimeMeasurement.reset()
#	PerformanceUtils.start("draw_test5_simple_continuity")
	
	$Plotter.clear()
	var option_info:Dictionary = {}
	for option in _satisfaction_calculator_ref.get_options():
		option_info[option]=Array()	
	
#	var i:float = 0
	var step:float = step_arg
	var calc_step:float = calc_step_arg
#	var best_combidict_for_each_step:Dictionary = _trade_calculator.calculate_best_combidict_for_each_budget(max_amount_of_money_arg,step)	
#	_trade_calculator.precalculate_best_combidict_for_each_budget(max_amount_of_money_arg,step)
#	while  i <= max_amount_of_money_arg:
#	var countCalc:int = 0
	var i:float = 0
	while (i <= max_amount_of_money_arg):
		
		var money_quant:float = i
#		var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict(money_quant)
#		var best_combidict:Dictionary = best_combidict_for_each_step[i]
#		TODO: debugear que los resultados salgan bien. Creo que no están saliendo bien

#		if money_quant >30.0:
#			assert("debugea esto")

#		PerformanceUtils.start("_trade_calculator.calculate_best_combidict_simple_with_continuity(money_quant)")
#		TimeMeasurement.start("draw_test5_simple_continuity")	
		var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict_simple_with_continuity_budget_product_max_step(money_quant,calc_step)
#		countCalc+=1
#		TimeMeasurement.stop("draw_test5_simple_continuity")	
#		PerformanceUtils.stop("_trade_calculator.calculate_best_combidict_simple_with_continuity(money_quant)")
			
		for option in _satisfaction_calculator_ref.get_options():
			var amount_of_option:float = 0
			if best_combidict.has(option):
				amount_of_option = best_combidict[option]
			option_info[option].append(Vector2(money_quant,amount_of_option))
		
		i+=step	

	

	var count:int = 0
	for option_idx in $OptionsItemList.get_item_count(): 
		count+=1
		var option_text:String = $OptionsItemList.get_item_text(option_idx)
		
		var red = float(count)/5.0+0.2
		var green = float(count)/5.0+0.0
		var blue = float(-count)/5.0+1.0
		var color:Color = Color(red,green,blue)
		
		$Plotter.add_point_group(option_idx, option_info[option_text], color, option_text)

	
#	var usec_end = OS.get_ticks_usec()
#
#	var usec_elapsed = usec_end-usec_start
	
	
#	PerformanceUtils.stop("draw_test5_simple_continuity")
#	var elapsed = TimeMeasurement.get_average_time("draw_test5_simple_continuity")
#	var elapsed = TimeMeasurement.get_total_time("draw_test5_simple_continuity")
#	var num_calls = TimeMeasurement.get_num_measurements("draw_test5_simple_continuity")
	
#	TimeMeasurement.print_info()
#	$CalcCostLabel.set_text(str(usec_elapsed/countCalc))
#	$CalcCostLabel.set_text("draw_test5_simple_continuity: "+ str(elapsed))
	
#	$CalcCostLabelExtraInfo.set_text("num calls:" +str(num_calls))


func _draw_test4_simple(max_amount_of_money_arg:float=50.0, step_arg:float=0.1):
#	Usando 	precalculate_best_combidict_for_each_budget
	
	$Plotter.clear()
	var option_info:Dictionary = {}
	for option in _satisfaction_calculator_ref.get_options():
		option_info[option]=Array()	
	
#	var i:float = 0
	var step:float = step_arg
#	var best_combidict_for_each_step:Dictionary = _trade_calculator.calculate_best_combidict_for_each_budget(max_amount_of_money_arg,step)	
#	_trade_calculator.precalculate_best_combidict_for_each_budget(max_amount_of_money_arg,step)
#	while  i <= max_amount_of_money_arg:
	var i:float = 0
	while (i <= max_amount_of_money_arg):
		
		var money_quant:float = i
#		var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict(money_quant)
#		var best_combidict:Dictionary = best_combidict_for_each_step[i]
#		TODO: debugear que los resultados salgan bien. Creo que no están saliendo bien

		if money_quant >30.0:
			assert("debugea esto")

		var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict_simple(money_quant)
		
		for option in _satisfaction_calculator_ref.get_options():
			var amount_of_option:float = 0
			if best_combidict.has(option):
				amount_of_option = best_combidict[option]
			option_info[option].append(Vector2(money_quant,amount_of_option))
		
		i+=step	

	var count:int = 0
	for option_idx in $OptionsItemList.get_item_count(): 
		count+=1
		var option_text:String = $OptionsItemList.get_item_text(option_idx)
		
		var red = float(count)/5.0+0.2
		var green = float(count)/5.0+0.0
		var blue = float(-count)/5.0+1.0
		var color:Color = Color(red,green,blue)
		
		$Plotter.add_point_group(option_idx, option_info[option_text], color, option_text)


func _draw_option(option_arg:String, max_amount_of_money_arg:float=50.0,step_arg:float = 0.1):
	$Plotter.clear()
	var option_info:Array = []
	
#	var i:float = 0
	var step:float = step_arg
	var best_combidict_for_each_step:Dictionary = _trade_calculator.calculate_best_combidict_for_each_budget(max_amount_of_money_arg,step)	
#	while  i <= max_amount_of_money_arg:
	for i in best_combidict_for_each_step.keys():
		
		var money_quant:float = i
#		var best_combidict:Dictionary = _trade_calculator.calculate_best_combidict(money_quant)
		var best_combidict:Dictionary = best_combidict_for_each_step[i]
		
		for option in _satisfaction_calculator_ref.get_options():
			if option == option_arg:
				var amount_of_option:float = 0
				if best_combidict.has(option):
					amount_of_option = best_combidict[option]
				option_info.append(Vector2(money_quant,amount_of_option))
		
		i+=step	

	var count:int = 0
	for option_idx in $OptionsItemList.get_item_count(): 
		count+=1
		var option_text:String = $OptionsItemList.get_item_text(option_idx)
		
		if option_text == option_arg:
		
			var red = 1
			var green = 1
			var blue = 1
			var color:Color = Color(red,green,blue)
			
			$Plotter.add_point_group(option_idx, option_info, color, option_text)

		

func _on_XMaxSpinBox_value_changed(value):
	$Plotter.set_max_x_axis_value(value)
	

func _on_YMaxSpinBox_value_changed(value):
	$Plotter.set_max_y_axis_value(value)



func _update_items():
	$ProductsItemList.clear()
	for product in _satisfaction_calculator_ref.get_products():
		$ProductsItemList.add_item(product)
	
	$OptionsItemList.clear()
	for option in _satisfaction_calculator_ref.get_options():
		$OptionsItemList.add_item(option)
	
	$CurrencyLabel.set_text(Prices.get_currency())
	


func _on_Button_pressed():
	_update_items()
	


func _on_UpdateItemsButton_pressed():
	_update_items()


func _on_DrawAllButton_pressed():
	var max_to_draw:float = $MaxToDrawSpinBox.get_value()
	var step:float = $StepOfGraphSpinBox.get_value()
	_draw_test2(max_to_draw,step,step)

func _on_DrawSelected_pressed():
	var max_to_draw:float = $MaxToDrawSpinBox.get_value()
	var step:float = $StepOfGraphSpinBox.get_value()

	var selected_items = $OptionsItemList.get_selected_items()
	if (selected_items.size()):
				
		var first_select_index = selected_items[0]
		var name = $OptionsItemList.get_item_text(first_select_index)
		_draw_option(name,max_to_draw,step)
	

func _on_TradeTesterScene_gui_input(event):
	if event as InputEventScreenDrag:
		var input_event_screen_drag:InputEventScreenDrag = event as InputEventScreenDrag
		self.set_position(self.get_position()+input_event_screen_drag.relative)


#func _on_CalculateTest1Button_pressed():
#	var max_to_draw:float = $MaxToDrawSpinBox.get_value()
##	var step:float = $StepOfGraphSpinBox.get_value()
#	draw_test(max_to_draw)

func _on_CalculateTest2Button_pressed():
	var max_to_draw:float = $MaxToDrawSpinBox.get_value()
	var step:float = $StepOfGraphSpinBox.get_value()
	var calc_step:float = $StepOfCalcSpinBox.get_value()
	_draw_test2(max_to_draw,step,calc_step)

func _on_CalculateTest3Button_pressed():
	var max_to_draw:float = $MaxToDrawSpinBox.get_value()
	var step:float = $StepOfGraphSpinBox.get_value()
	_draw_test3_with_precalculation(max_to_draw,step)

func _on_CalculateTest4Button_pressed():
	var max_to_draw:float = $MaxToDrawSpinBox.get_value()
	var step:float = $StepOfGraphSpinBox.get_value()
	_draw_test4_simple(max_to_draw,step)


func _on_CalculateTest1Button_pressed():
	var max_to_draw:float = $MaxToDrawSpinBox.get_value()
	var step:float = $StepOfGraphSpinBox.get_value()
#	var calc_step:float = $StepOfCalcSpinBox.get_value()
	_draw_test1(max_to_draw,step)


#calculate_best_combidict_simple_with_continuity


func _on_CalculateTest5Button_pressed():
	var max_to_draw:float = $MaxToDrawSpinBox.get_value()
	var step:float = $StepOfGraphSpinBox.get_value()
	var calc_step:float = $StepOfCalcSpinBox.get_value()
	_draw_test5_simple_continuity(max_to_draw,step,calc_step)


func _on_CalculateTest6Button_pressed():
	var max_to_draw:float = $MaxToDrawSpinBox.get_value()
	var step:float = $StepOfGraphSpinBox.get_value()
	var calc_step:float = $StepOfCalcSpinBox.get_value()
	_draw_test6_simple_continuity_budget_step(max_to_draw,step,calc_step)


func _on_CalculateTest7Button_pressed():
	var max_to_draw:float = $MaxToDrawSpinBox.get_value()
	var step:float = $StepOfGraphSpinBox.get_value()
	var calc_step:float = $StepOfCalcSpinBox.get_value()
	_draw_test7_simple_continuity_budget_product_max_step(max_to_draw,step,calc_step)
