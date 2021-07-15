import pickle
import sys

alphabet = 'abcdefghijklmnopqrstuvwxyz '
plugboard = {'a':'a','b':'b'}

f = open('./todays_rotor_state.enigma', 'rb')
r1, r2, r3 = pickle.load(f)
f.close()


def reflector(c):
    return alphabet[len(alphabet)-alphabet.find(c)-1]

def enigma_one_char(c):
    c1 = r1[alphabet.find(c)]
    c2 = r2[alphabet.find(c1)]
    c3 = r3[alphabet.find(c2)]
    reflected = reflector(c3)
    c3 = alphabet[r3.find(reflected)]
    c2 = alphabet[r2.find(c3)]
    c1 = alphabet[r1.find(c2)]

    return c1

def rotate_rotors():
    global r1, r2, r3
    r1 = r1[1:] + r1[0]
    if state % 26 == 0:
        r2 = r2[1:] + r2[0]
    if state % (26*26) == 0:
        r3 = r3[1:] + r3[0]

if not len(sys.argv) == 2:
    print("Please enter your message.")

else:
    plain = sys.argv[1]
    cipher = ''
    state = 0

    for c in plain:
        if c in plugboard.keys():
            c = plugboard[c]
        state += 1
        cipher += enigma_one_char(c)
        rotate_rotors()

    print(cipher)
