import socket               # Import socket module
import time 
import os

import pickle
import numpy as np

BUF_SIZE = 1024 ** 2
LOOP_NUM = int(10 * (1024 ** 3) / BUF_SIZE)

s = socket.socket(family=socket.AF_UNIX, type=socket.SOCK_STREAM) # Create a socket object with TCP/IP
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # if the port is in use, reclaim the port
# host = socket.gethostname() # Get local machine name
# port = 12345                # Reserve a port for your service.
# s.bind((host, port))        # Bind to the port
server_address = './uds_socket'
os.remove(server_address)
s.bind(server_address)

s.listen(5)                 # Now wait for client connection.
connected = False
while not connected:
    c, addr = s.accept()     # Establish connection with client.
    connected = True
    print('Got connection from', addr)
    # data = b'Data received'
    # print("Origin data: {}".format(data))

    start_t = time.time()
    while True:
        c.recv(BUF_SIZE)
    # c.close()  # Close the connection
    end_t = time.time()
    print("Time spent on server: {} seconds".format(end_t - start_t))
    size = (BUF_SIZE * LOOP_NUM) / (1024 ** 3)
    print("Throughput = {} GB/s".format(size / (end_t - start_t)))
