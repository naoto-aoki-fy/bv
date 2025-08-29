# Guide to use bv in gnuplot

You can obtain the binary format information and a ready-to-use command directly from the Python interface:
```python
from bv import read_bv
bv = read_bv("out.bin")
print(bv.gnuplot_command("1:2"))
```
If the file contains three `float64` fields starting at byte offset `104`, this prints:
```gnuplot
plot "out.bin" binary skip=104 format="%3double" using 1:2
```
You may adjust the column indices in the `using` clause to plot different fields.
