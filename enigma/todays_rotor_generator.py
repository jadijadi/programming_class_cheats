'''
Creates rotors
'''
import random
import pickle

ALPHABET = 'abcdefghijklmnopqrstuvwxyz '

ROTOR_1 = list(ALPHABET)
random.shuffle(ROTOR_1)
ROTOR_1 = ''.join(ROTOR_1)


ROTOR_2 = list(ALPHABET)
random.shuffle(ROTOR_2)
ROTOR_2 = ''.join(ROTOR_2)

ROTOR_3 = list(ALPHABET)
random.shuffle(ROTOR_3)
ROTOR_3 = ''.join(ROTOR_3)

FILE_ROTOR = open('./todays_rotor_state.enigma', 'wb')
pickle.dump((ROTOR_1, ROTOR_2, ROTOR_3), FILE_ROTOR)
FILE_ROTOR.close()
