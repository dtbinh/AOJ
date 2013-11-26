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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

int main(){
  string pass;
  while(cin >> pass){
    int flag = 0;
    
    if(pass.size() >= 6) flag |= 1;

    for(int i=0;i<pass.size();i++){
      if(isdigit(pass[i])) flag |= (1<<1);
      if('A' <= pass[i] && pass[i] <= 'Z') flag |= (1<<2);
      if('a' <= pass[i] && pass[i] <= 'z') flag |= (1<<3);
    }

    printf("%s\n",flag == (1<<4)-1 ? "VALID" : "INVALID");
  }
}
