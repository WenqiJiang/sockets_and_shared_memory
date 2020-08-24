import socket               # Import socket module
import time
import pickle
import numpy as np

BUF_SIZE = 1024

s = socket.socket()         # Create a socket object
host = socket.gethostname() # Get local machine name
port = 12345                # Reserve a port for your service.

print("hostname: {}\tport: {}".format(host, port))
s.connect((host, port))
# c = socket.create_connection((host, port))
while True:
  data = pickle.loads(s.recv(BUF_SIZE))
  print(data)
  data = data + np.ones(data.shape)
  s.send(pickle.dumps(data))
  time.sleep(1)

s.close()                     # Close the socket when done