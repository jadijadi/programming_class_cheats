import pickle
import string
import sys

ALPHABET = string.ascii_lowercase + " "
ALPHA_LEN = len(ALPHABET)


def load_rotors(filename="./todays_rotor_state.enigma"):
    with open(filename, mode="rb") as infile:
        r1, r2, r3 = pickle.load(infile)
    return (r1, r2, r3)


ROTOR1, ROTOR2, ROTOR3 = load_rotors()


def reflector(char):
    char_index = ALPHABET.find(char)
    return ALPHABET[::-1][char_index]


def shift(string):
    return string[1:] + string[0]


def rotate_rotors(state):
    global ROTOR1, ROTOR2, ROTOR3
    ROTOR1 = shift(ROTOR1)
    if state % ALPHA_LEN == 0:
        ROTOR2 = shift(ROTOR2)
    if state % (ALPHA_LEN ** 2) == 0:
        ROTOR3 = shift(ROTOR3)


def enigma_one_char(char):
    c1 = ROTOR1[ALPHABET.find(char)]
    c2 = ROTOR2[ALPHABET.find(c1)]
    c3 = ROTOR3[ALPHABET.find(c2)]

    reflected = reflector(c3)

    c3 = ALPHABET[ROTOR3.find(reflected)]
    c2 = ALPHABET[ROTOR2.find(c3)]
    c1 = ALPHABET[ROTOR1.find(c2)]

    return c1


def encipher(text):
    ciphered = ""
    for index, char in enumerate(text, start=1):
        ciphered += enigma_one_char(char)
        rotate_rotors(index)
    return ciphered


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Please enter your message.")
        sys.exit(1)
    text = sys.argv[1]
    ciphered = encipher(text)
    print(ciphered)
