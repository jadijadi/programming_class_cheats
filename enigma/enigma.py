'''
Code and decode enigma cipher
'''

import pickle
import click

ALPHABET = 'abcdefghijklmnopqrstuvwxyz '
PLUGBOARD = {'a':'a', 'b':'b'}
CIPHER = ''
STATE = 0

FILE_ROTOR = open('./todays_rotor_state.enigma', 'rb')
ROTOR_1, ROTOR_2, ROTOR_3 = pickle.load(FILE_ROTOR)
FILE_ROTOR.close()


def reflector(character):
    ''' Reflects character '''
    return ALPHABET[-(ALPHABET.find(character)+1)]

def enigma_one_char(character):
    ''' Code and decode enigma characters '''
    character_1 = ROTOR_1[ALPHABET.find(character)]
    character_2 = ROTOR_2[ALPHABET.find(character_1)]
    character_3 = ROTOR_3[ALPHABET.find(character_2)]
    reflected = reflector(character_3)
    character_3 = ALPHABET[ROTOR_3.find(reflected)]
    character_2 = ALPHABET[ROTOR_2.find(character_3)]
    character_1 = ALPHABET[ROTOR_1.find(character_2)]

    return character_1

def rotate_rotors():
    ''' Rotate rotors to make more secure cipher '''
    global ROTOR_1, ROTOR_2, ROTOR_3
    ROTOR_1 = ROTOR_1[1:] + ROTOR_1[0]
    if STATE % 26 == 0:
        ROTOR_2 = ROTOR_2[1:] + ROTOR_2[0]
    if STATE % (26*26) == 0:
        ROTOR_3 = ROTOR_3[1:] + ROTOR_3[0]



@click.command()
@click.option('-m', '--message', required=True,
              nargs=1, prompt=True, hide_input=True)
def cli(message):
    ''' Get message and Code/Decode it '''
    global CIPHER, STATE

    for character in message:
        if character in PLUGBOARD.keys():
            character = PLUGBOARD[character]
        STATE += 1
        CIPHER += enigma_one_char(character)
        rotate_rotors()

    click.secho(CIPHER, fg="green")

if __name__ == "__main__":
    cli()
