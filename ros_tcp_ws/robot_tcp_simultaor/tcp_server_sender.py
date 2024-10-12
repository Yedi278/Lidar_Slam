import socket
import sys
import threading
import time

def generate_data():
    data = []
    for i in range(360):
        angle = int(i).to_bytes(2, byteorder='little')
        rpm = int(1000).to_bytes(2, byteorder='little')
        dist = int(2000).to_bytes(2, byteorder='little')
        wh1 = int(37).to_bytes(2, byteorder='little')
        wh2 = int(25).to_bytes(2, byteorder='little')
        othr = int(0).to_bytes(2, byteorder='little')

        data.append(angle)
        data.append(rpm)
        data.append(dist)
        data.append(wh1)
        data.append(wh2)
        data.append(othr)
    return data

def accept_conn(server,conn):
    try:
        conn, addr = server.accept()
        print('connected by', addr)
    except KeyboardInterrupt:
        conn.close()
        server.close()
        sys.exit()

def send_data(server, conn):
    
    data = generate_data()
    print('sending data...')

    while True:
        for i in data:
            conn.send(i)

def tcp_server(ip:str, port:int):

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    server.bind((ip, port))
    server.listen(2)
    print('waiting for connection...')

    conn, addr = server.accept()
    print('connected by', addr)

    try:
        send_data(server, conn)
    except Exception as e:
        print(e)
        server.close()
        conn.close()
        sys.exit()

if __name__ == '__main__':

    ip = "192.168.1.169"
    port = 1234

    tcp_server(ip, port)