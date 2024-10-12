import socket
import sys
from tcp_server_sender import *
import threading
import time


def tcp_client(ip:str, port:int):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print('connecting to server...')
    client.connect((ip, port))
    print('connected to server')
    
    return client

def send_data(conn:socket):
    data = b'X',b'F',b'Y',b'F'
    print('sending data...')
    
    while True:
        try:
            for i in data:
                conn.send(i)
            time.sleep(1)
        except (KeyboardInterrupt, SystemExit):
            conn.close()
            sys.exit()
        except Exception as e:
            print(e)
            conn.close()
            sys.exit()

if __name__ == '__main__':

    ip = '192.168.1.169'
    port = 1234

    client_soc = tcp_client(ip, port)
    send_data_thread = threading.Thread(target=send_data, args=(client_soc,))
    send_data_thread.start()
    
    while True:
        try:
            receive_data(client_soc, 12)
        except (KeyboardInterrupt, SystemExit):
            client_soc.close()
            sys.exit()
        except Exception as e:
            print(e)
            client_soc.close()
            sys.exit()