from pycparser import c_parser, c_ast

def check_c_syntax(statement):
    try:
        parser = c_parser.CParser()
        ast = parser.parse(statement)
        return True
    except c_parser.ParseError:
        return False

def print_lines_with_keywords(file_path, keywords):
    with open(file_path, 'r') as f:
        contents = f.read()
        lines = contents[::-1]
        for line in lines:
            if any(keyword in line.split() for keyword in keywords):
                print(line)
