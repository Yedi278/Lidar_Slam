import sys
import numpy as np
import serial
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore
import threading

esp32 = serial.Serial(port='COM7', baudrate=115200)

if esp32.isOpen():
    print("Serial port opened succesfully!")
else:
    print("Error opening the Serial port!")
    sys.exit()

app = pg.mkQApp("Lidar View")
win = pg.GraphicsLayoutWidget(show=True, title="Basic plotting examples")
win.resize(600,600)
win.setWindowTitle('Lidar Data Plotter')

plot = win.addPlot(title="Lidar Data")
curve = plot.plot(pen=None, symbol='o', symbolPen=None, symbolSize=5, symbolBrush='r')
c2 = plot.plot(pen='b', symbol='o')
c2.setData([0],[0])

plot.setXRange(-3000,3000)
plot.setYRange(-3000,3000)

x,y = [],[]

def plot_data():
    global curve,x,y
    curve.setData(x,y)

def update():
    global curve,x,y

    plotting_thread = threading.Thread(target=plot_data)
    plotting_thread.start()

    data = esp32.readline().strip().decode().split(',')

    if(len(data) < 3): return

    try:
        angle = int(data[0])
        distance = int(data[2])
    except: return

    x.append(distance * np.cos(angle*3.14/180))
    y.append(distance * np.sin(angle*3.14/180))

    if(len(x) > 1000):
        x.pop(0)
        y.pop(0)

    plotting_thread.join()

timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start()

if __name__ == '__main__':

    pg.exec()
    esp32.close()
    sys.exit()