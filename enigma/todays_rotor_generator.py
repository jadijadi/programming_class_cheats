import random
import pickle

def generate_rotors():
    alphabet = 'abcdefghijklmnopqrstuvwxyz '

    rotor_1 = list(alphabet)
    random.shuffle(rotor_1)
    rotor_1 = ''.join(rotor_1)


    rotor_2 = list(alphabet)
    random.shuffle(rotor_2)
    rotor_2 = ''.join(rotor_2)


    rotor_3 = list(alphabet)
    random.shuffle(rotor_3)
    rotor_3 = ''.join(rotor_3)

    f = open('./todays_rotor_state.enigma', 'wb')
    pickle.dump((rotor_1, rotor_2, rotor_3), f)
    f.close()

if __name__ == "__main__":
    generate_rotors()
