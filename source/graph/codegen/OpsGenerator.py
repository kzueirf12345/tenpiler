from generator import parse_arguments, validate_paths, load_json, generate_hpp, generate_cpp
        
if __name__ == "__main__":
    args = parse_arguments()

    input_path, output_path, source_dir_path = validate_paths(args)

    data = load_json(input_path, args.verbose)

    generate_hpp(data, output_path, args.verbose)
    generate_cpp(data, source_dir_path, args.verbose)

    if args.verbose:
        print("Генерация завершена успешно!")