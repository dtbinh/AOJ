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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};
 
static const double EPS = 1e-12;

int total_nights;
double mistake_probability,reference_diff,optimal_sleep_time;

double dfs(double R,double L,int count){
  double H = (R+L)/2.0;
  if(count >= total_nights){
    if(fabs(optimal_sleep_time - H) <= reference_diff + EPS){
      return 1.0;
    }
    else {
      return 0.0;
    }
  }

  if(L <= optimal_sleep_time + reference_diff
     && optimal_sleep_time - reference_diff <= R){
    return 1.0;
  }

  if(optimal_sleep_time + reference_diff < R
     || L < optimal_sleep_time - reference_diff){
    return 0.0;
  }

  double res = 0.0;

  if(H + EPS >= optimal_sleep_time){
    res += (1.0-mistake_probability) * dfs(R,H,count+1); //correct
    res += mistake_probability * dfs(H,L,count+1); //wrong
  }
  else{
    res += (1.0-mistake_probability) * dfs(H,L,count+1); //correct
    res += mistake_probability * dfs(R,H,count+1); //wrong
  }
  return res;
}

int main(){

  int R,L;
  while(~scanf("%d %d %d",&total_nights,&R,&L)){
    scanf("%lf %lf %lf",&mistake_probability,&reference_diff,&optimal_sleep_time);
    printf("%.9lf\n",dfs(R,L,0));
  }
}
