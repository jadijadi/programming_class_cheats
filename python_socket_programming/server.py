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
def server(host, port):
    # Bind the socket to the localhost:10001
    server_address = ('localhost', 10001)
    sock.bind(server_address)
    click.secho(f"Starting up on {host} port {port} ...", fg="green")

    # Listen
    sock.listen(1)

    while True:
        # Wait for an incomming connection
        click.echo('Waiting ...', file=sys.stderr)
        connection, client_addr = sock.accept()

        try:
            click.secho(f"A request came! IP is {client_addr[0]}: {client_addr[1]}", fg="cyan")
            # Read data
            while True:
                data = connection.recv(150) #or any other number
                click.echo('request is: ', nl=False)
                click.secho(f"{data.decode('UTF-8')}", fg="green")
                # print('request is:', data.decode('UTF-8'))
                if data:
                    try:
                        answer = str(eval(data))
                    except:
                        answer = 'error!'
                    connection.sendall(answer.encode('UTF-8'))
                    click.echo('Hooraay.... Answered this one.')
                else:
                    click.secho(f"No data recived from {client_addr[0]}: {client_addr[1]}", fg="red")
                    break

        finally:
            # Clean up the connection
            connection.close()

if __name__ == "__main__":
    server()