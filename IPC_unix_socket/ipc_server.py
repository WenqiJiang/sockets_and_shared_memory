import socket               # Import socket module
import time 
import pickle
import numpy as np

BUF_SIZE = 1024

s = socket.socket(family=socket.AF_UNIX, type=socket.SOCK_STREAM) # Create a socket object with TCP/IP
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # if the port is in use, reclaim the port
# host = socket.gethostname() # Get local machine name
# port = 12345                # Reserve a port for your service.
# s.bind((host, port))        # Bind to the port
server_address = './wenqi_socket'
s.bind(server_address)

s.listen(5)                 # Now wait for client connection.
while True:
    c, addr = s.accept()     # Establish connection with client.
    print('Got connection from', addr)
    data = np.random.randn(2,3)
    print("Origin data: {}".format(data))

    while True: 
        c.send(pickle.dumps(data))
        data = pickle.loads(c.recv(BUF_SIZE))
        print(data)
        time.sleep(1)
    c.close()  # Close the connection