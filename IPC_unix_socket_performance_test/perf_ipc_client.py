import socket               # Import socket module
import time
import pickle
import numpy as np

BUF_SIZE = 1024 ** 2
LOOP_NUM = int(10 * (1024 ** 3) / BUF_SIZE)

s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)         # Create a socket object
# host = socket.gethostname() # Get local machine name
# port = 12345                # Reserve a port for your service.
server_address = './uds_socket'

# print("hostname: {}\tport: {}".format(host, port))

# s.connect((host, port))
s.connect(server_address)

data = b'0' * (BUF_SIZE - 1)
# c = socket.create_connection((host, port))
# sending 1 GB data (packet size = 1024 B, loop num = 1024 ** 2)
start_t = time.time()
for i in range(LOOP_NUM):
  # data = s.recv(BUF_SIZE)
  # print(data)
  # data = data + np.ones(data.shape)
  # s.send(pickle.dumps(data))
  s.send(data)
  # time.sleep(1)

s.close()                     # Close the socket when done

end_t = time.time()
print("Time spent on client side: {} seconds".format(end_t - start_t))
size = (BUF_SIZE * LOOP_NUM) / (1024 ** 3)
print("Throughput = {} GB/s".format(size / (end_t - start_t)))