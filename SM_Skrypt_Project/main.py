from typing import Union

from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import tkinter as tk
import numpy as np
import serial
import time

from serial import Serial

'''variables'''
data = np.array([])
cond = True
'''plot data'''


def plot_data():
    global cond, data
    if(cond == True):

        # s = serial.Serial("/dev/cu.usbmodem1412203", baudrate = 9600)

        # s.write(b'050')

        # print('PLOTING THE DATA')
        a = s.readline()
        a = a.decode()
        s.reset_input_buffer()

        try:
            a_int = [int(x[-4:]) for x in a[:-3].split(',')]
            print(a)
            print(a_int)

            if(len(a_int) == 3):
                if(len(data) < 100):
                    data = np.append(data, a_int[1])
                    # data = np.append(data, 1.0)
                else:
                    data[0:99] = data[1:100]
                    data[-1] = a_int[1]
                    # data[99] = 1.0
                lines.set_xdata(np.arange(0, len(data)))
                lines.set_ydata(data)

                canvas.draw()
        except:
            print('error')
        # s.reset_input_buffer()
        root.after(1, plot_data)

def plot_start():
    global cond
    cond = True
    print('START PRESSED, ', 'cond = ', cond)
    # s.reset_input_buffer()
    root.after(1, plot_data)


def plot_stop():
    global cond
    cond = False
    print('STOP PRESSED, ', 'cond = ', cond)
'''main GUI code'''
root = tk.Tk()
root.title('Real time plot')
root.configure(background = 'light blue')
root.geometry('900x500')

'''create plot object'''
# add figure
fig = Figure()
ax = fig.add_subplot(111)


ax.set_title('Response')
ax.set_xlabel('Sample')
ax.set_ylabel('Speed rev/s')
ax.set_xlim(0, 100)
ax.set_ylim(0, 120)
lines = ax.plot([], [])[0]

canvas = FigureCanvasTkAgg(fig, master = root) #tk.DrawingArea
canvas.get_tk_widget().place(x=10, y=10, width = 600, height =400)
canvas.draw()



'''buttons'''
root.update()
start = tk.Button(root, text = 'Start', font = ('calibri',12), command = lambda: plot_start())
start.place(x=200, y= 450)

root.update()
stop = tk.Button(root, text = 'Stop', font = ('calibri', 12), command = lambda: plot_stop())
stop.place(x=400, y = 450)



'''Serial port'''
# global s
s = serial.Serial("/dev/cu.usbmodem1412203", baudrate=9600)
# s.reset_input_buffer()
# s.write(b'050')

'''value button'''
def entry_command():
    text = entry.get()
    # print(text)
    if(len(text)==3):
        s.write(str(text).encode())
    return None

entry = tk.Entry(root, width=3, borderwidth=2)
entry.pack
entry.insert(0, 'set')
entry.place(x = 600, y = 450)

button = tk.Button(root, text='Setpoint', command=entry_command)
button.pack()
button.place(x = 640, y = 450)



root.after(1, plot_data)
root.mainloop()