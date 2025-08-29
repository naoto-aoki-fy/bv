import os
from dataclasses import dataclass
from typing import List

import numpy as np

__all__ = ["BVFile", "read_bv"]
__version__ = "0.1.0"


@dataclass
class BVFile:
    path: str
    offset: int
    fields: List[str]
    dtype: np.dtype

    @property
    def data(self) -> np.memmap:
        num_fields = len(self.fields)
        itemsize = np.dtype(self.dtype).itemsize
        file_size = os.path.getsize(self.path)
        num_rows, remainder = divmod(file_size - self.offset, itemsize * num_fields)
        if remainder != 0:
            raise ValueError("File size does not match header information")
        return np.memmap(self.path, dtype=self.dtype, mode="r", offset=self.offset, shape=(num_rows, num_fields))

    def __getitem__(self, field: str):
        idx = self.fields.index(field)
        return self.data[:, idx]

    def gnuplot_format(self) -> str:
        dt_map = {
            np.float64: "double",
            np.float32: "float",
            np.int64: "int64",
            np.int32: "int32",
            np.int16: "int16",
            np.int8: "int8",
            np.uint64: "uint64",
            np.uint32: "uint32",
            np.uint16: "uint16",
            np.uint8: "uint8",
        }
        fmt = dt_map.get(self.dtype)
        if fmt is None:
            raise ValueError(f"Unsupported dtype {self.dtype} for gnuplot")
        return f"%{len(self.fields)}{fmt}"

    def gnuplot_command(self) -> str:
        fmt = self.gnuplot_format()
        return f'plot "{self.path}" binary skip={self.offset} format="{fmt}"'


def read_bv(path: str) -> BVFile:
    lines = []
    with open(path, "rb") as fp:
        while True:
            headchar = fp.read(1)
            if headchar != b"#":
                break
            line = fp.readline()
            lines.append(line)
        offset = fp.tell() - 1

    fields: List[str] = []
    dtype = None
    for line in lines:
        eq_pos = line.find(b"=")
        if eq_pos > 0:
            key = line[:eq_pos].strip()
            value = line[eq_pos + 1:].strip()
            if key == b"fields":
                fields = [f.strip().decode() for f in value.split(b",")]
            elif key == b"dtype":
                dtype = getattr(np, value.decode())
    if dtype is None or not fields:
        raise ValueError("Missing header information")
    return BVFile(path=path, offset=offset, fields=fields, dtype=dtype)
