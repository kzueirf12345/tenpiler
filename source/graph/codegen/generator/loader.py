import argparse
import sys
import json
from pathlib import Path

def parse_arguments():
    parser = argparse.ArgumentParser(
        description="Node description generator",
    )

    # === Режим генерации ===
    parser.add_argument(
        "-m", "--mode",
        type=str,
        required=False,
        default="all",
        choices=["all", "node_header", "node_onnx_creator", "node_source", "node_dumb", "node_attr"],
        metavar="MODE",
        help="Режим генерации: all, node_header, node_onnx_creator, node_source, node_dumb, node_attr "
             "(по умолчанию: all)"
    )

    parser.add_argument(
        "-i", "--input",
        type=str,
        required=False,
        default="./source/graph/codegen/OpsTableGen.json",
        metavar="INPUT_FILE",
        help="Входной JSON файл с описанием классов операций "
             "(по умолчанию: ./source/graph/codegen/OpsTableGen.json)"
    )

    parser.add_argument(
        "-nh", "--node_header",
        type=str,
        required=False,
        default="./source/graph/include/graph/Node/Ops.hpp",
        metavar="OUTPUT_FILE",
        help="Выходной файл .hpp для сгенерированного кода (по умолчанию: "
             "./source/graph/include/graph/Node/Ops.hpp)"
    )
    
    parser.add_argument(
        "-ns", "--node_source",
        type=str,
        required=False,
        default="./source/graph/src/Node/Node.cpp",
        metavar="OUTPUT_FILE",
        help="Выходной файл .cpp c реализацией операций (по умолчанию: "
             "./source/graph/src/Node/Node.cpp)"
    )
    
    parser.add_argument(
        "-f", "--node_onnx_creator",
        type=str,
        required=False,
        default="./source/graph/src/NodeOnnxCreator/",
        metavar="OUTPUT_DIR",
        help="Выходная директория для .cpp и .hpp файлов создания узлов из ONNX "
             "(по умолчанию: ./source/graph/src/GENERATE_NodeOnnxCreator/)"
    )
    
    parser.add_argument(
        "-dnh", "--node_header_dumb",
        type=str,
        required=False,
        default="./source/graph/include/graph/Node/OpsDumb.hpp",
        metavar="OUTPUT_FILE",
        help="Выходной файл функций дампа .hpp для сгенерированного кода (по умолчанию: "
             "./source/graph/include/graph/Node/OpsDumb.hpp)"
    )
    
    parser.add_argument(
        "-dns", "--node_source_dumb",
        type=str,
        required=False,
        default="./source/graph/src/Node/OpsDumb.cpp",
        metavar="OUTPUT_FILE",
        help="Выходной файл функций дампа .cpp c реализацией (по умолчанию: "
             "./source/graph/src/Node/OpsDumb.cpp)"
    )
    
    parser.add_argument(
        "-anh", "--node_header_attr",
        type=str,
        required=False,
        default="./source/graph/include/graph/Node/OpsAttr.hpp",
        metavar="OUTPUT_FILE",
        help="Выходной файл геттеров аттрибутов .hpp для сгенерированного кода (по умолчанию: "
             "./source/graph/include/graph/Node/OpsAttr.hpp)"
    )
    
    parser.add_argument(
        "-ans", "--node_source_attr",
        type=str,
        required=False,
        default="./source/graph/src/Node/OpsAttr.cpp",
        metavar="OUTPUT_FILE",
        help="Выходной файл геттеров аттрибутов .cpp c реализацией (по умолчанию: "
             "./source/graph/src/Node/OpsAttr.cpp)"
    )
    
    parser.add_argument(
        "-v", "--verbose",
        action="store_true",
        help="Включить подробный вывод процесса генерации"
    )
    
    args = parser.parse_args()

    return args

def validate_paths(args):
    input_path = Path(args.input)
    node_header_path = Path(args.node_header)
    node_source_path = Path(args.node_source)
    node_header_dumb_path = Path(args.node_header_dumb)
    node_source_dumb_path = Path(args.node_source_dumb)
    node_header_attr_path = Path(args.node_header_attr)
    node_source_attr_path = Path(args.node_source_attr)
    node_onnx_creator_dir_path = Path(args.node_onnx_creator)

    if not input_path.exists():
        print(f"Ошибка: Входной файл не найден: {input_path}", file=sys.stderr)
        sys.exit(1)

    if not input_path.is_file():
        print(f"Ошибка: Входной путь не является файлом: {input_path}", file=sys.stderr)
        sys.exit(1)

    if input_path.suffix != ".json":
        print(f"Предупреждение: Входной файл не имеет расширения .json", file=sys.stderr)

    if args.mode in ["all", "node_header"]:
        if node_header_path.suffix != ".hpp":
            print(f"Предупреждение: Выходной файл не имеет расширения .hpp", file=sys.stderr)

        output_dir = node_header_path.parent
        if not output_dir.exists():
            print(f"Ошибка: Директория для выходного файла не существует: {output_dir}", 
                  file=sys.stderr)
            sys.exit(1)
        
    if args.mode in ["all", "node_source"]:
        if node_source_path.suffix != ".cpp":
            print(f"Предупреждение: Выходной файл не имеет расширения .cpp", file=sys.stderr)

        output_dir = node_source_path.parent
        if not output_dir.exists():
            print(f"Ошибка: Директория для выходного файла не существует: {output_dir}", 
                  file=sys.stderr)
            sys.exit(1)
            
    if args.mode in ["all", "node_header_dumb"]:
        if node_header_dumb_path.suffix != ".hpp":
            print(f"Предупреждение: Выходной файл не имеет расширения .hpp", file=sys.stderr)

        output_dir = node_header_dumb_path.parent
        if not output_dir.exists():
            print(f"Ошибка: Директория для выходного файла не существует: {output_dir}", 
                  file=sys.stderr)
            sys.exit(1)
        
    if args.mode in ["all", "node_source_dumb"]:
        if node_source_dumb_path.suffix != ".cpp":
            print(f"Предупреждение: Выходной файл не имеет расширения .cpp", file=sys.stderr)

        output_dir = node_source_dumb_path.parent
        if not output_dir.exists():
            print(f"Ошибка: Директория для выходного файла не существует: {output_dir}", 
                  file=sys.stderr)
            sys.exit(1)
            
    
    if args.mode in ["all", "node_header_attr"]:
        if node_header_attr_path.suffix != ".hpp":
            print(f"Предупреждение: Выходной файл не имеет расширения .hpp", file=sys.stderr)

        output_dir = node_header_attr_path.parent
        if not output_dir.exists():
            print(f"Ошибка: Директория для выходного файла не существует: {output_dir}", 
                  file=sys.stderr)
            sys.exit(1)
        
    if args.mode in ["all", "node_source_attr"]:
        if node_source_attr_path.suffix != ".cpp":
            print(f"Предупреждение: Выходной файл не имеет расширения .cpp", file=sys.stderr)

        output_dir = node_source_attr_path.parent
        if not output_dir.exists():
            print(f"Ошибка: Директория для выходного файла не существует: {output_dir}", 
                  file=sys.stderr)
            sys.exit(1)
    
        
    if args.mode in ["all", "node_onnx_creator"]:
        if not node_onnx_creator_dir_path.is_dir():
            print("Ошибка: Путь к выходной директории onnx_creator не является директорией: "
                  f"{node_onnx_creator_dir_path}", file=sys.stderr)
            sys.exit(1)
            
        if not node_onnx_creator_dir_path.exists():
            print("Ошибка: Выходная директория onnx_creator не существует: "
                  f"{node_onnx_creator_dir_path}", file=sys.stderr)
            sys.exit(1)

    return input_path, node_header_path, node_source_path, node_header_dumb_path, \
        node_source_dumb_path, node_onnx_creator_dir_path, node_header_attr_path, \
        node_source_attr_path

def load_json(path, verbose=False):
    if verbose:
        print(f"Чтение JSON из: {path}")

    try:
        with open(path, "r", encoding="utf-8") as f:
            data = json.load(f)
        
        if verbose:
            print(f"Успешно загружено {len(data['operations'])} операций")
        
        return data
    except json.JSONDecodeError as e:
        print(f"Ошибка парсинга JSON: {e}", file=sys.stderr)
        sys.exit(1)
    except Exception as e:
        print(f"Ошибка чтения файла: {e}", file=sys.stderr)
        sys.exit(1)
