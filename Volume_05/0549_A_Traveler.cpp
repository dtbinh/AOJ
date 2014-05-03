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

int main(){
  int total_post_towns;
  int total_journey_days;
  while(~scanf("%d %d",
	       &total_post_towns,
	       &total_journey_days)){
    vector<int> path;

    int sum[100001];
    memset(sum,0,sizeof(sum));
    for(int i=0;i<total_post_towns-1;i++){
      int distance;
      scanf("%d",&distance);
      path.push_back(distance);
      sum[i+1] = distance + sum[i];
    }

    int sx = 0;
    int res = 0;
    for(int i=0;i<total_journey_days;i++){
      int dx;
      scanf("%d",&dx);
      if(dx < 0){
	res += sum[sx] - sum[sx+dx];
	res %= 100000;
	sx += dx;
      }
      else if(dx >= 0){
	res += sum[sx + dx] - sum[sx];
	res %= 100000;
	sx += dx;
      }
    }

    printf("%d\n",res % 100000);
  }
}
