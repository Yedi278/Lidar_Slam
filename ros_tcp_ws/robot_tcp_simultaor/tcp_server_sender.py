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

def decode_data(data):
    if len(data)%2 != 0:
        return Exception("Data length is not even")
    data = b''.join(data)
    data_decoded = []
    for i in range(0, len(data), 2):
        data_decoded.append(int.from_bytes(data[i:i+2], byteorder='little'))

    return data_decoded

def accept_conn(server,conn):
    try:
        conn, addr = server.accept()
        print('connected by', addr)
    except (KeyboardInterrupt, SystemExit):
        conn.close()
        server.close()
        sys.exit()

def send_data(server, conn):
    
    data = generate_data()
    print('sending data...')

    while True:
        for i in data:
            conn.send(i)
            time.sleep(.0001)

def receive_data(conn:socket, buff_size:int=4):
    while True:
        try:
            data = []
            while len(data)<buff_size:
                data.append(conn.recv(1))
            
            data_decoded = decode_data(data)
            for i in data_decoded:
                print(i, end='\t')
            print()
        except (KeyboardInterrupt, SystemExit):
            conn.close()
            sys.exit()
        
def tcp_server(ip:str, port:int):

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    server.bind((ip, port))
    server.listen(2)
    print('waiting for connection...')

    conn, addr = server.accept()
    print('connected by', addr)

    return conn,addr


if __name__ == '__main__':

    ip = "192.168.1.169"
    port = 1234

    client_soc, cleint_addr = tcp_server(ip, port)

    receive_data_thread = threading.Thread(target=receive_data, args=(client_soc,))
    receive_data_thread.start()
    
    while True:
        try:
            send_data(client_soc, client_soc)
        except (KeyboardInterrupt, SystemExit) as e:
            print(e)
            client_soc.close()
            sys.exit()