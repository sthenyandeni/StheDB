import sys

if len(sys.argv) != 3:
    print("Usage: python3 file_creator.py <input_file_name> <output_file_name>")
    sys.exit(1)

input_file_name = sys.argv[1]
output_file_name = sys.argv[2]

file = open(f'./helper/{input_file_name}', 'r')
raw_text = file.read()
file.close()
raw_byte_array = [raw_text[i:i+2] for i in range(0, len(raw_text), 2)]
byte_array = []
for i in raw_byte_array:
    byte_array.append(bytes((int(i, 16),)))
print(byte_array)
byte_string = b''.join(byte_array)

new_file = open(f'./helper/{output_file_name}', 'wb')
new_file.write(byte_string)