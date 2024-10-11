import socket
import sys

def generate_data():
    data = []
    for i in range(360):
        data.append(f"{i},200")
    return data

def tcp_server(ip, port):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((ip, port))
    server.listen(5)
    print('waiting for connection...')

    conn, addr = server.accept()
    print('connected by', addr)

    data = generate_data()
    print('sending data...')
    i=0
    while True:
        if i == 360:
            i = 0
        conn.write(data[i])
        i += 1

if __name__ == '__main__':
    ip = '192.168.1.169'
    port = 1234

    tcp_server(ip, port)