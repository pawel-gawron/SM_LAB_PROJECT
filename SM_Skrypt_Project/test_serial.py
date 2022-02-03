import serial
import numpy as np
import time


value = 1
s = serial.Serial(port='COM7', baudrate = 9600)
# s.write(b'075')
setpoint = '095'
s.write(setpoint.encode())
print('polaczono')
while True:
# if(True):
    s.reset_input_buffer()
    a = s.readline()
    a = a.decode()
    print(a)
    try:
        a_int = [int(x[-3:]) for x in a[:-3].split(',')]
        print(a_int)
    except:
        print('error')

    # s.write(b'065')
    # if (value<100):
    #     value = value +1
    # else:
    #     value = 0
    # time.sleep(1)
    # print(f'value: {value}')


    # a_int[0] - sterowanie
    # a_int[1] - predkosc
    # a_int[2] - wartosc zadana


