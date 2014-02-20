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
  int N;
  while(~scanf("%d",&N)){
    priority_queue<int> carpets;
    int count = 0;
    for(int i=0;i<N;i++){
      int height;
      scanf("%d",&height);
      count++;

      while(!carpets.empty()){
	if(carpets.top() > height){
	  carpets.pop();
	}
	else if(carpets.top() == height){
	  count--;
	  break;
	}
	else{
	  break;
	}
      }
      carpets.push(height);
    }
    printf("%d\n",count);
  }
}
