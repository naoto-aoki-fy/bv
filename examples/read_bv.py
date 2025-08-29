from bv import read_bv

if __name__ == "__main__":
    bv = read_bv("out.bin")
    print(f"offset={bv.offset}")
    print(f"fields={bv.fields}")
    print(f"dtype={bv.dtype}")
    print(bv.data)
    print(bv["a"])
    print(bv.gnuplot_command())
