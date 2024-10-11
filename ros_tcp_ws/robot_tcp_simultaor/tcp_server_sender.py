import socket
import sys



def tcp_server(ip, port):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((ip, port))
    server.listen(5)
    print('waiting for connection...')
    conn, addr = server.accept()
    print('connected by', addr)
    while True:
        
    conn.close()