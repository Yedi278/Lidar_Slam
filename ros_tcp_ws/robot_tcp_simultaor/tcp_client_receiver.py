import socket
import sys

def tcp_client(ip:str, port:int):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((ip, port))

    while True:
        try:
            data = client.recv(12)
            angle = int.from_bytes(data[0:2], byteorder='little')
            rpm = int.from_bytes(data[2:4], byteorder='little')
            dist = int.from_bytes(data[4:6], byteorder='little')
            wh1 = int.from_bytes(data[6:8], byteorder='little')
            wh2 = int.from_bytes(data[8:10], byteorder='little')
            othr = int.from_bytes(data[10:12], byteorder='little')
            print(f'{angle}\t{rpm}\t{dist}\t{wh1}\t{wh2}\t{othr}')

        except KeyboardInterrupt:
            client.close()
            sys.exit()
    
    
if __name__ == '__main__':
    ip = '192.168.1.169'
    port = 1234

    tcp_client(ip, port)