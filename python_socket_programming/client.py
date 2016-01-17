import socket
import sys

# Create the socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the localhost:10001
server_address = ('localhost', 10001)
print 'connecting to %s:%s' % server_address
sock.connect(server_address)

message = ''

try:
    while message != 'done':
        # read the request
        message = raw_input('\nWhat is your math question? [sample: 4*7+6] ')
        # send the query
        sock.sendall(message)

        # read the answer from the server
        data = sock.recv(100) #it should not be more than 100 chars
        print 'The answer of %s is %s.' % (message, data)

finally:
    print >>sys.stderr, 'closing socket'
    sock.close()
