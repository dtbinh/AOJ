#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <cstdio>
#include <iostream>
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
typedef pair <int,P > PP;
 
const static int mx[] = {1,-1,1,-1};
const static int my[] = {1,-1,-1,1};

int main(){
  int N;
  
  while(~scanf("%d",&N)){
    if(N==0) break;
    int inheritance[50];
    for(int i=0;i<N;i++){
      int total_days;
      scanf("%d",&total_days);
      
      int mask = 0;
      for(int j=0;j<total_days;j++){
	int day;
	scanf("%d",&day);
	mask |= (1<<day);
      }
      inheritance[i] = mask;
    }
  }
}
