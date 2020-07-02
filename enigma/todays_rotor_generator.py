import pickle
import random
import string

ALPHABET = string.ascii_lowercase + " "


def generate_rotors(chars=ALPHABET):
    rotor1 = list(chars)
    random.shuffle(list(chars))
    rotor1 = "".join(rotor1)

    rotor2 = list(chars)
    random.shuffle(rotor2)
    rotor2 = "".join(rotor2)

    rotor3 = list(chars)
    random.shuffle(rotor3)
    rotor3 = "".join(rotor3)

    return (rotor1, rotor2, rotor3)


def save_rotors_state(filename, rotor1, rotor2, rotor3):
    with open(filename, mode="wb") as binary_file:
        pickle.dump((rotor1, rotor2, rotor3), binary_file)


if __name__ == "__main__":
    rotor1, rotor2, rotor3 = generate_rotors()
    save_rotors_state("./todays_rotor_state.enigma", rotor1, rotor2, rotor3)
