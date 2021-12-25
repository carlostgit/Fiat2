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

func set_satisfaction_calculator_ref(satisf_calculator_arg, name_arg:String=""):
	_satisfaction_calculator_ref = satisf_calculator_arg
	self.name_of_model = name_arg
	
	_trade_calculator = TradeCalculator.new(_satisfaction_calculator_ref)

#	He creado un _init en SatisfactionCalculator, que hace de constructor de copia
#	_satisfaction_calculator_copy = SatisfactionCalculator.new(satisf_calculator_arg)
	update_items()
	

	draw_test2()

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

func draw_test(max_amount_of_money_arg:float=50.0):
	
	var option_info:Dictionary = {}
	for option in _satisfaction_calculator_ref.get_options():
		option_info[option]=Array()	
	
	var i:float = 0
	var step:float = 1.0
	while  i <= max_amount_of_money_arg:
		
		var money_quant:float = i
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


func draw_test2(max_amount_of_money_arg:float=50.0):
	
	var option_info:Dictionary = {}
	for option in _satisfaction_calculator_ref.get_options():
		option_info[option]=Array()	
	
#	var i:float = 0
	var step:float = 0.1
	var best_combidict_for_each_step:Dictionary = _trade_calculator.calculate_best_combidict_for_each_budget(max_amount_of_money_arg,step)	
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
		
		

func _on_XMaxSpinBox_value_changed(value):
	$Plotter.set_max_x_axis_value(value)
	

func _on_YMaxSpinBox_value_changed(value):
	$Plotter.set_max_y_axis_value(value)


func _on_RecalculateButton_pressed():
	draw_test2()

func update_items():
	$ProductsItemList.clear()
	for product in _satisfaction_calculator_ref.get_products():
		$ProductsItemList.add_item(product)
	
	$OptionsItemList.clear()
	for option in _satisfaction_calculator_ref.get_options():
		$OptionsItemList.add_item(option)
	
	$CurrencyLabel.set_text(Prices.get_currency())
	


func _on_Button_pressed():
	update_items()
	
