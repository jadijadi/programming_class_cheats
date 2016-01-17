# by Jadi under MIT license. 
# Published at https://github.com/jadijadi/programming_class_cheats

import socket
import sys

# Create the socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the localhost:10001
server_address = ('localhost', 10001)
sock.bind(server_address)
print 'starting up on %s port %s' % server_address

# Listen
sock.listen(1)

while True:
    # Wait for an incomming connection
    print >>sys.stderr, 'waiting...'
    connection, client_addr = sock.accept()

    try:
        print 'A request came! IP is ', client_addr

        # Read data
        while True:
            data = connection.recv(150) #or any other number
            print 'request is:', data
            if data:
                try:
                    answer = str(eval(data))
                except:
                    answer = 'error!'
                connection.sendall(answer)
                print 'Hooraay.... Answered this one.'
            else:
                print 'No data recived from', client_addr
                break

    finally:
        # Clean up the connection
        connection.close()
