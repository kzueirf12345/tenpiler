import argparse
import sys
import json
from pathlib import Path

def parse_arguments():
    parser = argparse.ArgumentParser(
        description="Ops header generator",
    )

    parser.add_argument(
        "-i", "--input",
        type=str,
        required=False,
        default="./source/graph/codegen/OpsTableGen.json",
        metavar="INPUT_FILE",
        help="Входной JSON файл с описанием классов операций "
             "(по умолчанию: ./source/graph/OpsTableGen.json)"
    )

    parser.add_argument(
        "-o", "--output",
        type=str,
        required=False,
        default="./source/graph/include/graph/Node/Ops.hpp",
        metavar="OUTPUT_FILE",
        help="Выходной файл .hpp для сгенерированного кода (по умолчанию: "
             "./source/graph/include/graph/Node/Ops.hpp)"
    )
    
    parser.add_argument(
        "-s", "--source_directory",
        type=str,
        required=False,
        default="./source/graph/src/Node",
        metavar="SOURCE_DIR",
        help="Выходная папка для .cpp реализаций операций (по умолчанию: "
             "./source/graph/src/Node)"
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
    output_path = Path(args.output)
    source_dir_path = Path(args.source_directory)

    if not input_path.exists():
        print(f"Ошибка: Входной файл не найден: {input_path}", file=sys.stderr)
        sys.exit(1)

    if not input_path.is_file():
        print(f"Ошибка: Входной путь не является файлом: {input_path}", file=sys.stderr)
        sys.exit(1)

    if input_path.suffix != ".json":
        print(f"Предупреждение: Входной файл не имеет расширения .json", file=sys.stderr)

    if output_path.suffix != ".hpp":
        print(f"Предупреждение: Выходной файл не имеет расширения .hpp", file=sys.stderr)

    output_dir = output_path.parent
    if not output_dir.exists():
        print(f"Ошибка: Директория для выходного файла не существует: {output_dir}", 
              file=sys.stderr)
        sys.exit(1)
        
    if not source_dir_path.is_dir():
        print(f"Ошибка: Путь к выходной директории не является директорией: {source_dir_path}", 
              file=sys.stderr)
        sys.exit(1)
        
    if not source_dir_path.exists():
        print(f"Ошибка: Выходная директория не существует: {source_dir_path}", 
              file=sys.stderr)
        sys.exit(1)

    return input_path, output_path, source_dir_path

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
