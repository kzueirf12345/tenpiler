from generator import \
    parse_arguments, \
    validate_paths, \
    load_json, \
    generate_hpp, \
    generate_cpp, \
    generate_node_onnx_creator_hpp
        
if __name__ == "__main__":
    args = parse_arguments()

    input_path, output_path, source_dir_path, node_onnx_creator_dir_path = validate_paths(args)

    data = load_json(input_path, args.verbose)
    
    if args.mode in ["all", "node_header"]:
        if args.verbose:
            print("Генерация заголовков операций...")
        generate_hpp(data, output_path, args.verbose)
        
    if args.mode in ["all", "node_sources"]:
        if args.verbose:
            print("Генерация исходных файлов операций...")
        generate_cpp(data, source_dir_path, args.verbose)
        
    if args.mode in ["all", "node_onnx_creator"]:
        if args.verbose:
            print("Генерация фабрик ONNX...")
        generate_node_onnx_creator_hpp(
            data, 
            node_onnx_creator_dir_path / (node_onnx_creator_dir_path.name + ".hpp"),
            args.verbose
        )

    if args.verbose:
        print("Генерация завершена успешно!")