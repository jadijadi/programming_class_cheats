// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;


// I THINK THIS PROGRAM SHOULD WORK FASTER THAN THIS

map<int,int> dict;
map<int,int>::iterator it;
// vector<int> numbers;


//the weird thing about this loop is that it work way faster by array instead of map
int func(unsigned int x) {
    cout << "strat for "<<x<<endl; 
    int count=0;
    int j;
    int k;
     for (auto const& [key, val] : dict){
       j = key;
       k = x - j;
       if (k==j||j>k||k<0)
          continue;
          it = dict.find(k);
        if(it != dict.end())
            count++;
     }
  return count;
}

string get_flag(vector<unsigned int> res){
  
  string flag="";
    for(int i=0;i< size(res); i++){
        flag+=char(func(res[i]));
        }
    return flag;
  }

int main () {
  string line;
  vector<unsigned int> res ={751741232, 519127658, 583555720, 3491231752, 3333111256, 481365731, 982100628, 1001121327, 3520999746,
           915725624, 3218509573, 3621224627, 3270950626, 3321456817, 3091205444, 999888800, 475855017, 448213157,
           3222412857, 820711846, 3710211491, 3119823672, 3333211607, 812955676, 971211391, 3210953872, 289789909,
           781213400, 578265122, 910021887, 653886578, 3712776506, 229812345, 582319118, 1111276998, 1151016390,
           700123328, 1074521304, 3210438183, 817210125, 501231350, 753244584, 3240911853, 415234677, 469125436,
           592610671, 612980665, 291821367, 344199617, 1011100412, 681623864, 897219249, 3132267885, 565913000,
           301203203, 3100544737, 432812663, 1012813485, 510928797, 671553831, 3216409218, 3191288433, 698777123,
           3512778698, 810476845, 3102989588, 3621432709, 812321695, 526486561, 378912454, 3316207359, 623111580,
           344209171, 537454826, 691277475, 2634678623, 1112182335, 792111856, 762989676, 666210267, 871278369,
           581009345, 391231132, 921732469, 717217468, 3101412929, 3101217354, 831912337, 532666530, 701012510,
           601365919, 492699680, 2843119525};
  ifstream myfile ("numbers.txt");
  if (myfile.is_open())
  {
    while (getline (myfile,line))
    {
      dict[stoi(line)]=1;
    }
    myfile.close();
  }
  else {
    cout << "Unable to open file"; 
    return 0;
  }
  string flag=get_flag(res);
  cout << "The flag is" << flag <<endl;
  return 1;
}