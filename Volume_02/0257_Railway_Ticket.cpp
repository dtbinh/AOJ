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

static const double EPS = 1e-8;

int main(){
  int bits[3];
  for(int i=0;i<3;i++){
    scanf("%d",&bits[i]);
  }
  if(bits[0] == 1){
    if(bits[1] == 0){
      //100
      printf("Close\n");
    }
    else if(bits[1] == 1){
      //110
      printf("Open\n");
    }
  }
  else if(bits[0] == 0){
    if(bits[2] == 0){
      //010
      //000
      printf("Close\n");
    }
    else if(bits[2] == 1){
      //001
      printf("Open\n");
    }
  }
}
