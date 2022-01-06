extends Control


# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	$PriceSpinBox.hide()
	$SetCurrencyButton.hide()
	
	for product in Prices.get_products():
		$ProductItemList.add_item(product)
	
	$CurrencyLabel.set_text(Prices.get_currency())
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_ProductItemList_item_selected(index):
	$PriceSpinBox.show()
	$SetCurrencyButton.show()
	var product:String = $ProductItemList.get_item_text(index)
	var price:float = Prices.get_price_of_product(product)
	$PriceSpinBox.disconnect("value_changed",self,"_on_PriceSpinBox_value_changed")
	$PriceSpinBox.set_value(price)
	$PriceSpinBox.connect("value_changed",self,"_on_PriceSpinBox_value_changed")
	if product==Prices.get_currency():
		$PriceSpinBox.set_editable(false)
	else:
		$PriceSpinBox.set_editable(true)
		
func _on_SetCurrencyButton_pressed():
	var selected_items:Array = $ProductItemList.get_selected_items()
	if selected_items.size() > 0:
		var index:int = selected_items.front()
		var product:String = $ProductItemList.get_item_text(index)
		Prices.set_currency(product)
		$CurrencyLabel.set_text(Prices.get_currency())	

func _on_PriceSpinBox_value_changed(value):
	var selected_items:Array = $ProductItemList.get_selected_items()
	if selected_items.size() > 0:
		var index:int = selected_items.front()
		var product:String = $ProductItemList.get_item_text(index)
		Prices.set_price_of_product(product,value)
	


func _on_PricesEditor_gui_input(event):
	if event as InputEventScreenDrag:
		var input_event_screen_drag:InputEventScreenDrag = event as InputEventScreenDrag
		self.set_position(self.get_position()+input_event_screen_drag.relative)
