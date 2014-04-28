#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
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

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

int main(){
  char route[256][2];
  memset(route,0,sizeof(route));

  route['A'][0] = 'X';
  route['A'][1] = 'Y';

  route['X'][1] = 'Z';

  route['Y'][0] = 'X';

  route['Z'][0] = 'W';
  route['Z'][1] = 'B';

  route['W'][0] = 'B';
  route['W'][1] = 'Y';

  route['B'][0] = 'Y';  
  route['B'][1] = 'X';

  string str;
  while(cin >> str){
    if(str == "#") break;

    char current = 'A';
    for(int i=0;i<str.size();i++){
      current = route[current][str[i]-'0'];
    }
    if(current == 'B'){
      cout << "Yes" << endl;
    }
    else {
      cout << "No" << endl;
    }
  }
}
