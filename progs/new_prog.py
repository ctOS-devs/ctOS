from simple_term_menu import TerminalMenu
from os import system, get_terminal_size

name = ""
file_name = ""
lang = ""

print("Project creator".center(get_terminal_size().columns))

name = input("Enter prog name: ")

print("\nSelect language:")
langs = ["C", "Python"]
menu = TerminalMenu(langs)
sel_index = menu.show()
if sel_index != None:
	lang = langs[sel_index]

#name = input("Enter prog name: ")
#lang = input("Enter programming language: ")

match lang:
	case "C":
		folder = name + "_C"
		file_name = f"{name}.c"
		system(f"mkdir {folder}")
		system(f"touch {folder}/{file_name}")
		system(f"echo 'musl-gcc --static {file_name} -o {name}; cp {name} ../binary_files;' > {folder}/build.sh")
		system(f"chmod +x {folder}/build.sh")
		system(f"echo '{name}' > {folder}/.gitignore")
	case "Python":
		folder = name + "_PY"
		file_name = f"{name}.py"
		system(f"mkdir {folder}")
		system(f"touch {folder}/{file_name}")
		system(f"echo 'python3 -m nuitka {file_name} -o {name}; cp {name} ../binary_files;' > {folder}/build.sh")
		system(f"chmod +x {folder}/build.sh")
		system(f"echo '{name}' > {folder}/.gitignore")
	case default:
		print("Language not selected, exit...")

print(f"""\n---------------------
Language: {lang}
Main file: {file_name}

In path: {folder}
---------------------""")
