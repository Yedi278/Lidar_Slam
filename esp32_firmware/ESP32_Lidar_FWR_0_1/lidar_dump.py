import sys
import numpy as np
import serial
from packet_lib import packet
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore

esp32 = serial.Serial(port='COM8', baudrate=115200)

if esp32.isOpen():
    print("Serial port opened succesfully!")
else:
    print("Error opening the Serial port!")
    sys.exit()

app = pg.mkQApp("Lidar View")
win = pg.GraphicsLayoutWidget(show=True, title="Basic plotting examples")
win.resize(600,600)
win.setWindowTitle('pyqtgraph example: Plotting')

plot = win.addPlot(title="Lidar Data")
curve = plot.plot(pen=None, symbol='o', symbolPen=None, symbolSize=5, symbolBrush='r')
c2 = plot.plot(pen='b', symbol='o')
c2.setData([0],[0])

plot.setXRange(-3000,3000)
plot.setYRange(-3000,3000)

buffer = []

def update():
  global curve,buffer

  buffer.append(esp32.readline(1).hex())
  
  if buffer[-1] == 'a0' and buffer[-2] == 'fa':
    buffer.pop(-1)
    buffer.pop(-1)

    pck = packet(buffer)
    if pck.verify():
      pck.process()
    else:
       buffer.clear()
       print("Invalid packet")

    x,y = [],[]

    if pck.verify():
      for i in pck.processed:
        r = i["distance"]
        a = -i["angle"] * 4* np.pi/180
        x.append(r * np.cos(a))
        y.append(r * np.sin(a))

    curve.setData(x,y)
    
    buffer.clear()
    buffer.append('fa')
    buffer.append('a0')

timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start()

if __name__ == '__main__':
    pg.exec()