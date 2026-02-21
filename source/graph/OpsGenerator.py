import json 
from pathlib import Path
from jinja2 import Template
import sys
from colorama import Fore

REL_PATH_FROM_THIS = Path("./include/graph/Node/GENERATE_Ops.hpp")
THIS_FILE_PATH = Path(__file__)

def GetOpsHeaderPath():
    ops_header_path = THIS_FILE_PATH.parent.joinpath(REL_PATH_FROM_THIS)
    
    if len(sys.argv) == 2:
        ops_header_path = Path(sys.argv[1])
        
        if not ops_header_path.is_absolute():
            ops_header_path = THIS_FILE_PATH.parent.joinpath(REL_PATH_FROM_THIS)
    elif len(sys.argv) == 3:
        if sys.argv[1].lower() != "-n" and sys.argv[1].lower() != "--name":
            raise RuntimeError(f"Unknown mode '{sys.argv[1]}'")
        
        ops_header_path = ops_header_path.with_name(sys.argv[2])
    elif len(sys.argv) > 3:
        raise RuntimeError("Too many argv")
    
    if not ops_header_path.parent.exists():
        raise RuntimeError("Incorrect path " + str(ops_header_path))
    
    return ops_header_path

try:
    if __name__ == "__main__":
        
        ops_header_path = GetOpsHeaderPath()
        
        ops_header_path.touch()
        
        print(ops_header_path)
    
except RuntimeError as e:
    print(Fore.RED + "EXCEPTION!!!"  + Fore.RESET)
    print(e)
except:
    print(Fore.RED + "EXCEPTION!!!"  + Fore.RESET)
    print("Something went wrond")