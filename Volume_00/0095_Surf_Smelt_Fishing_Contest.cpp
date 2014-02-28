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
  int n;
  while(~scanf("%d",&n)){
    int fish_num[21];
    memset(fish_num,0,sizeof(fish_num));

    int max_fish = 0;
    for(int i=0;i<n;i++){
      int a,v;
      scanf("%d %d",&a,&v);
      fish_num[a] += v;
      max_fish = max(max_fish,fish_num[a]);
    }

    for(int a=1;a<=n;a++){
      if(fish_num[a] == max_fish){
	printf("%d %d\n",a,fish_num[a]);
	break;
      }
    }
  }
}
