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

Add the `python` directory to `PYTHONPATH` and import the `bv` package:

```bash
PYTHONPATH=python python examples/read_bv.py
```

From another project you can simply:

```python
from bv import read_bv
bv_file = read_bv("out.bin")
print(bv_file.gnuplot_command("1:2"))
```

This prints the field names, data type and a gnuplot command for plotting.
