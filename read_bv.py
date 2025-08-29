import numpy
import os

fn = "out.bin"

lines = []
fp = open(fn, "rb")
while True:
    headchar = fp.read(1)
    if headchar != b'#':
        break
    line = fp.readline()
    lines.append(line)
# print(lines)
fpos = fp.tell() - 1
fp.close()


fieldname_list = None
dtype = None

for line in lines:
    eq_pos = line.find(b"=")
    if eq_pos > 0:
        key = line[:eq_pos].strip()
        value = line[eq_pos + 1:].strip()
        if key == b"fields":
            fieldname_list = [field_name.strip().decode() for field_name in value.split(b",")]
        elif key == b"dtype":
            dtype = getattr(numpy, value.strip().decode())
        else:
            raise Exception(f"unknown key: {key}")
    elif b'padding' in line:
        pass

print(f"{fpos=}")
print(f"{fieldname_list=}")
print(f"{dtype=}")

num_fields = len(fieldname_list)
num_rows, remainder = divmod(os.path.getsize(fn) - fpos, 8 * num_fields)
print(f"{remainder=}")
assert remainder==0

import numpy
data = numpy.memmap(fn, dtype=numpy.float64, mode='r', offset=fpos, shape=(num_rows, num_fields))

for fieldidx, fieldname in enumerate(fieldname_list):
    globals()[fieldname] = data[:, fieldidx]

print(data)