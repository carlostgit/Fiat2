
class_name Utils


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

static func sum_combidict(dict_1:Dictionary,dict_2:Dictionary)->Dictionary:
	var answer:Dictionary = {}
	for key in dict_1.keys():
		if false==dict_2.has(key):
			answer[key] = dict_1[key]
		else:
			answer[key] = dict_1[key]+dict_2[key]
	
	for key in dict_2.keys():
		if false==dict_1.has(key):
			answer[key] = dict_2[key]
	
	return answer

static func calculate_combination_difference(combination_1_arg:Dictionary, combination_2_arg:Dictionary)->Dictionary:
	#1-2
	var return_dict:Dictionary = combination_1_arg.duplicate()
	for product_2 in combination_2_arg.keys():
		if return_dict.has(product_2):
			return_dict[product_2] = return_dict[product_2] - combination_2_arg[product_2]
		else:
			return_dict[product_2] =  - combination_2_arg[product_2]

	return return_dict

static func compare_dictionaries(dict_1:Dictionary,dict_2:Dictionary)-> bool:
	#Este método casero es necesario, porque en la versión de gdscript actual
	#no funciona bien la comparación (operador==) entre objetos Dictionary
	if(dict_1.size()!=dict_2.size()):
		return false
		
	for key in dict_1.keys():
		if false==dict_2.has(key):
			return false
		if dict_1[key] != dict_2[key]:
			return false
		
	return true
	
static func find_value_in_dictionary_with_dictionary_key(dict_with_dictionary_key_arg:Dictionary,dict_key_arg:Dictionary):
	#Este método casero es necesario, porque en la versión de gdscript actual
	#no funciona bien la comparación (operador==) entre objetos Dictionary
		
	for dictionary_key in dict_with_dictionary_key_arg:
		if compare_dictionaries(dictionary_key, dict_key_arg):
			return dict_with_dictionary_key_arg[dictionary_key]
	
	return null
	
static func get_ordered_combidicts(combination_satisfaction_arg:Dictionary) -> Array:
	#Se ordenano de menor a mayor satisfacción
	
	var satisfactions_ordered:Array = combination_satisfaction_arg.values()
	satisfactions_ordered.sort()
	var combi_satisf_left = combination_satisfaction_arg.duplicate(true) #copia
	var combinations_ordered:Array = Array()
	for satisfaction in satisfactions_ordered:
		for combination in combi_satisf_left:
			if satisfaction == combi_satisf_left[combination]:
				combinations_ordered.append(combination)
				combi_satisf_left.erase(combination)
				break	
	assert(combination_satisfaction_arg.size()==combinations_ordered.size())

	return combinations_ordered
