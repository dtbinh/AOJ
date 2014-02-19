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
    map<int,bool> has_carpet;
    int count = 0;
    for(int i=0;i<N;i++){
      int height;
      scanf("%d",&height);
      count++;

      for(map<int,bool>::iterator it = has_carpet.begin();
	  it != has_carpet.end();
	  it++){
	if(it->first > height){
	  it->second = false;
	}
	if(it->first == height && it->second == true){
	  count--;
	}
      }
      has_carpet[height] = true;
    }
    printf("%d\n",count);
  }
}
