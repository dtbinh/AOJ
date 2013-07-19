#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

#include <iostream>
#include <cstdio>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include <string>
#include <cstring>
#include <set>
#include <deque>
#include <bitset>
#include <list>
#include <cctype>
#include <utility>
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

class Button {
public:
  char vowel;
  char consonant;

  Button(int num){
    conv[1] = 'a';
    conv[2] = 'k';
    conv[3] = 's';
    conv[4] = 't';
    conv[5] = 'n';
    conv[6] = 'h';
    conv[7] = 'm';
    conv[8] = 'y';
    conv[9] = 'r';
    conv[0] = 'w';
    
    //aiueo
    //'T','L','U','R','D';
    flick['T'] = 'a';
    flick['L'] = 'i';
    flick['U'] = 'u';
    flick['R'] = 'e';
    flick['D'] = 'o';

    vowel = conv[num];
  }
  void push(char dir){
    if(vowel == 'w' && dir == 'U'){
      cout << "nn";
    }
    else if(vowel == 'a'){
      cout << flick[dir];
    }
    else{
      cout << vowel <<flick[dir];
    }
  }
private:
  map<int,char> conv;
  char flick[256];
};

int main(){
  string str;
  while(cin >> str){
    for(int i=0;i<str.size();i+=2){
      int num = str[i] - '0';
      char dir = str[i+1];
      Button button(num);
      button.push(dir);
    }
    cout << "\n";
  }
}
