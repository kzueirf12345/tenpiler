from generator import \
    parse_arguments, \
    validate_paths, \
    load_json, \
    generate_hpp, \
    generate_cpp, \
    generate_node_onnx_creator_hpp, \
    generate_op_table_hpp, \
    generate_node_onnx_creator_cpp, \
    generate_node_dumb_hpp, \
    generate_node_dumb_cpp
    
        
if __name__ == "__main__":
    args = parse_arguments()

    input_path, node_header_path, node_source_path, \
        node_header_dumb_path, node_source_dumb_path, node_onnx_creator_dir_path \
            = validate_paths(args)

    data = load_json(input_path, args.verbose)
    
    if args.mode in ["all", "node_header"]:
        if args.verbose:
            print("Генерация заголовков операций...")
        generate_hpp(data, node_header_path, args.verbose)
        
    if args.mode in ["all", "node_sources"]:
        if args.verbose:
            print("Генерация сорцов операций...")
        generate_cpp(data, node_source_path, args.verbose)
        
    if args.mode in ["all", "node_onnx_creator"]:
        if args.verbose:
            print("Генерация фабрик ONNX...")
        generate_node_onnx_creator_hpp(
            data, 
            node_onnx_creator_dir_path / (node_onnx_creator_dir_path.name + ".hpp"),
            args.verbose
        )
        generate_op_table_hpp(
            data,
            node_onnx_creator_dir_path / ("MAP_" + node_onnx_creator_dir_path.name + ".hpp"),
            args.verbose
        )
        generate_node_onnx_creator_cpp(
            data,
            node_onnx_creator_dir_path / (node_onnx_creator_dir_path.name + ".cpp"),
            args.verbose
        )
        
    if args.mode in ["all", "node_dumb"]:
        if args.verbose:
            print("Генерация файлов дампа...")
        generate_node_dumb_hpp(data, node_header_dumb_path, args.verbose)
        generate_node_dumb_cpp(data, node_source_dumb_path, args.verbose)
        

    if args.verbose:
        print("Генерация завершена успешно!")