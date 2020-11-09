import random
import pickle

#Adding (),:;'' to current program to make it more user-friendly,CAPITAL WORDS!!!!
alphabet="abcdefghijklmnopqrstuvwxyz;: ''?!$%^&*+-/().ABCDEFGHIJKLMNOPQRSTUVWXYZ"

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

  f = open('./todays_rotor_state.enigma',"w")
  pickle.dump((r1, r2, r3), f)
  f.close()

  #Saving keys in form of .txt file in case we need them!!
  f1 = open("r1(keys).txt","w")
  f1.write(r1)
  f1.close()

  f2 = open("r2(keys).txt","w")
  f2.write(r2)
  f2.close()

  f3 = open("r3(keys).txt","w")
  f3.write(r3)
  f3.close()
  
  #in case we need a .txt that contains all keys
  r4="All keys are this!!\nKeep Them safe\n"+r1+"\n"+r2+"\n"+r3
  f4 = open("r(All-keys).txt","w")
  f4.write(r4)
  f4.close()
  print("Keys Succesfully Generated")
if __name__=="__main__":main()
