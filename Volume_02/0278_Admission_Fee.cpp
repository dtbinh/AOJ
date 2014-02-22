#define _USE_MATH_DEFINES
#define INF 10000000
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
  int N;
  while(~scanf("%d",&N)){
    for(int day=0;day<N;day++){
      int x,y,b,p;
      scanf("%d %d %d %d",&x,&y,&b,&p);

      int min_money = INF;
      for(int i=0;i<=6;i++){
	for(int j=0;j<=6;j++){
	  if(i < b || j < p) continue;
	  
	  int money = INF;
	  if(i >= 5 && j >= 2){
	    money = (int)((double)i * (double)x * 0.8 + (double)j * (double)y * 0.8 + EPS);
	  }
	  else{
	    money = i * x + j * y;
	  }
	  min_money = min(money,min_money);
	}
      }
      printf("%d\n",min_money);
    }
  }
}
