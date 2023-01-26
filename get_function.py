def print_lines_with_keywords(file_path, keywords):
    with open(file_path, 'r') as f:
        contents = f.read()
        lines = contents[::-1]
        for line in lines:
            if any(keyword in line.split() for keyword in keywords):
                print(line)
