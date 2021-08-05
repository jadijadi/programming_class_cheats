# by Jadi under MIT license. 
# Published at https://github.com/jadijadi/programming_class_cheats

import socket
import sys
import click

# Create the socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

@click.command()
@click.option('-h', '--host', default='localhost')
@click.option('-p', '--port', default=10001)
def client(host, port):
    server_address = (host, port)
    click.secho(f"Connecting to {host}: {port} ...", fg="green")
    sock.connect(server_address)

    message = ''

    try:
        while message != 'done':
            # read the request
            message = input('\nWhat is your math question? [sample: 4*7+6] ')
            # send the query
            sock.sendall(message.encode('UTF-8'))

            # read the answer from the server
            data = sock.recv(100) #it should not be more than 100 chars
            click.secho(f"The answer of {message} is {data.decode('UTF-8')}.", fg="green" if data.decode('UTF-8') != 'error!' else "red")

    finally:
        print('closing socket', file=sys.stderr)
        sock.close()

if __name__ == "__main__":
    client()
