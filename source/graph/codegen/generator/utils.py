RIGHT_BORDER = 100

def get_cpp_type(attr):
    SIMPLE_TYPES = {
        "uint8_t"   : "uint8_t",   
        "uint16_t"  : "uint16_t",
        "uint32_t"  : "uint32_t", 
        "uint64_t"  : "uint64_t",
        "int8_t"    : "int8_t",     
        "int16_t"   : "int16_t", 
        "int32_t"   : "int32_t",   
        "int64_t"   : "int64_t",
        "float"     : "float", 
        "double"    : "double",
        "bool"      : "bool", 
        "string"    : "std::string",
    }
    
    def map_simple(type_name):
        return SIMPLE_TYPES.get(type_name, type_name)
    
    raw_type = attr["type"]
    
    if raw_type.startswith("vector<") and raw_type.endswith(">"):
        inner_type = raw_type[7:-1]
        return f"std::vector<{map_simple(inner_type)}>"
    
    if raw_type == "enum":
        enum_name = attr.get("enum_name")
        return f"{enum_name}"
    
    return map_simple(raw_type)

def get_default_value(attr):
    value = attr["default"]
    if value is None:
        return None
    if attr["type"] == "enum":
        return f"{attr['enum_name']}::{value}"
    if attr["type"] == "string":
        return f'"{value}"'
    if attr["type"].startswith("vector<"):
        return "{}" if value == "[]" else value
    return str(value)
    
def join_with_leading_sep(items, sep):
    return (sep + sep.join(items)) if items else ""

def get_attr_name(attr_type):
    SIMPLE_TYPES = {
        "int64_t": "Int",
        "uint64_t": "Int",
        "bool": "Int",
        "float": "Float",
        "string": "String",
        "enum": "String",
        "Tensor": "Tensor",
        "Graph": "Graph",
    }
    
    if attr_type.startswith("vector<") and attr_type.endswith(">"):
        inner_type = attr_type[7:-1] 
        if inner_type in SIMPLE_TYPES:
            return SIMPLE_TYPES[inner_type] + "s"
        raise ValueError(f"Неподдерживаемый тип вектора: vector<{inner_type}>")
    
    if attr_type in SIMPLE_TYPES:
        return SIMPLE_TYPES[attr_type]
    
    raise ValueError(f"Неподдерживаемый тип атрибута: {attr_type}")