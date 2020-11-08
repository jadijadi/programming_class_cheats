import random
import pickle

#Adding (),:;'' to current program to make it more user-friendly
alphabet = "abcdefghijklmnopqrstuvwxyz ''():;,"

def main():
  r1 = list(alphabet)
  random.shuffle(r1)
  r1 = ''.join(r1)

  r2 = list(alphabet)
  random.shuffle(r2)
  r2 = ''.join(r2)

  r3 = list(alphabet)
  random.shuffle(r3)
  r3 = ''.join(r3)

  f = open('./todays_rotor_state.enigma', 'wb')
  pickle.dump((r1, r2, r3), f)
  f.close()

  #Saving keys in form of .txt file in case we need them!!
  f1 = open("r1(keys).txt", "a")
  f1.write(R1)
  f1.close()

  f2 = open("r2(keys).txt", "a")
  f2.write(R2)
  f2.close()

  f3 = open("r3(keys).txt", "a")
  f3.write(r3)
  f3.close()
if __name__=="__main__":main()
