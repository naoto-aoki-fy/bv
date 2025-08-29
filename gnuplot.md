# Guide to use bv in gnuplot

Get format information with python. example output:
```
fpos=104
fieldname_list=['a', 'b', 'c']
dtype=<class 'numpy.float64'>
...
```
You find the offset is 104, the number of fields is 3, and dtype is float64.

Then, a gnuplot command for example is
```gnuplot
plot "out.bin" binary skip=104 format="%3double" using 1:2
```