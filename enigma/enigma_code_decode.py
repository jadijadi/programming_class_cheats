import pickle
import sys
import click
import schedule

from todays_rotor_generator import generate_rotors

alphabet = 'abcdefghijklmnopqrstuvwxyz '
plugboard = {'a':'a','b':'b'}

f = open('./todays_rotor_state.enigma', 'rb')
rotor_1, rotor_2, rotor_3 = pickle.load(f)
f.close()

schedule.every().days.do(generate_rotors)

def reflector(character: str) -> str:
    return alphabet[-(alphabet.find(character)+1)]


def enigma_one_char(character: str) -> str:
    character_1 = rotor_1[alphabet.find(character)]
    character_2 = rotor_2[alphabet.find(character_1)]
    character_3 = rotor_3[alphabet.find(character_2)]
    reflected = reflector(character_3)
    character_3 = alphabet[rotor_3.find(reflected)]
    character_2 = alphabet[rotor_2.find(character_3)]
    character_1 = alphabet[rotor_1.find(character_2)]

    return character_1


def rotate_rotors():
    global rotor_1, rotor_2, rotor_3
    rotor_1 = rotor_1[1:] + rotor_1[0]
    if state % 26 == 0:
        rotor_2 = rotor_2[1:] + rotor_2[0]
    if state % (26*26) == 0:
        rotor_3 = rotor_3[1:] + rotor_3[0]


@click.command()
@click.option('-m', '--message', required=True, nargs=1, prompt=True, hide_input=True, help="Get message and Code/Decode it.")
@click.option('-r', '--restart', is_flag=True, help="Generate new rotors for encryption and decryption")
def enigma(message, restart):
    if restart:
        generate_rotors()

    global cipher
    cipher = ''
    global state
    state = 0

    for character in message.lower():
        if character in plugboard.keys():
            character = plugboard[character]
        state += 1
        cipher += enigma_one_char(character)
        rotate_rotors()

    click.secho(cipher, fg="green")

if __name__ == "__main__":
    enigma()
