import ctypes
import easyocr

class OCRResult(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_int * 4),
        ("y", ctypes.c_int * 4),
        ("confidence", ctypes.c_double),
        ("text", ctypes.c_char_p),
    ]


lib = ctypes.CDLL("./libocr.dll")
lib.process_results.argtypes = [ctypes.POINTER(OCRResult), ctypes.c_int]
lib.process_results.restype = None

reader = easyocr.Reader(['ja'])
result = reader.readtext("C:/Users/djbik/Downloads/20260715_100617.jpeg")

count = len(result)
c_results = (OCRResult * count)()

text_buffers = []

for i, (bbox, text, conf) in enumerate(result):
    xs = [int(p[0]) for p in bbox]
    ys = [int(p[1]) for p in bbox]
    encoded = text.encode("utf-8")
    text_buffers.append(encoded)

    c_results[i].x[:] = xs
    c_results[i].y[:] = ys
    c_results[i].confidence = conf
    c_results[i].text = ctypes.c_char_p(encoded)

lib.process_results(c_results, count)