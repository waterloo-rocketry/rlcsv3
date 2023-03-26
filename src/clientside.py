import struct
import serial

DATA_POINTS = 10

s = serial.Serial("/dev/ttyUSB0", 115200)

state = False
t = 0

try:
    while True:
        while s.read(1).decode('ascii') != "W":
            pass
        raw = s.read(DATA_POINTS*2 + 2)
        if raw[-2:] != b"R\n":
            print("Invalid data:", raw)
        print(raw)
        data = []
        for i in range(DATA_POINTS):
            data.append(struct.unpack("<H", raw[2*i:2*i+2])[0])
        print(data)

        t += 1
        if t > 30:
            t = 0
            state = not state

        if state:
            s.write(b"W\1\1\1\1\1\1R")
        else:
            s.write(b"W\0\0\0\0\0\0R")
finally:
    s.close()
