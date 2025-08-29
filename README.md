# Binary Values Library

This repository provides a simple binary table format with:

- A header-only C++ writer located in `include/bv/bv_writer.hpp`.
- A Python reader package located in `python/bv`.
- Example programs in `examples`.

## C++ usage

Add the `include` directory to your include path and include the header:

```cpp
#include <bv/bv_writer.hpp>
```

Example build and run:

```bash
g++ -std=c++17 -I include examples/write_bv.cpp -o write_bv
./write_bv out.bin
```

## Python usage

Install the reader directly from this repository:

```bash
pip install git+https://github.com/naoto-aoki-fy/bv.git
```

Alternatively, add the `python` directory to `PYTHONPATH` and import the `bv` package:

```bash
PYTHONPATH=python python examples/read_bv.py
```

From another project you can simply:

```python
from bv import read_bv
bv_file = read_bv("out.bin")
```

## Gnuplot usage

You can obtain the binary format information and a ready-to-use command directly from the Python interface:
```python
from bv import read_bv
bv = read_bv("out.bin")
print(bv.gnuplot_command())
```
If the file contains three `float64` fields starting at byte offset `104`, this prints:
```gnuplot
plot "out.bin" binary skip=104 format="%3double"
```
