#define _USE_MATH_DEFINES
#define INF 10000000
#include <cstdio>
#include <iostream>
#include <sstream>
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
typedef pair <int,int> P;
typedef pair <int,P> PP;
typedef pair <int,PP> PPP;

static const double eps = 1e-8;

int main(){
  int duration;
  while(~scanf("%d",&duration)){
    int current_cars;
    scanf("%d",&current_cars);
    
    int max_cars = current_cars;
    bool isok = true;
    for(int i=0;i<duration;i++){
      int in,out;
      scanf("%d %d",&in,&out);
      max_cars = max(current_cars + (in-out),max_cars);
      current_cars += (in-out);
      if(current_cars < 0){
	isok = false;
      }
    }
    printf("%d\n",isok ? max_cars : 0);
  }
}
