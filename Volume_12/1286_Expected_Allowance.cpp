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
 
const static int tx[] = {0,1,0,-1};
const static int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int prev[1000000];
int next[1000000];

int main(){
  int dice_num,side_num,cutback;
  
  while(~scanf("%d %d %d",&dice_num,&side_num,&cutback)){
    if(dice_num == 0) break;
    memset(prev,0,sizeof(prev));
    memset(next,0,sizeof(next));
    
    for(int i=1;i<=side_num;i++) prev[i] = 1;

    for(int i=1;i<dice_num;i++){
      for(int from=1;from<=side_num*dice_num;from++){
	for(int spots=1;spots<=side_num;spots++){
	  next[from+spots] += prev[from];
	}
      }
      memcpy(prev,next,sizeof(int)*1000000);
      memset(next,0,sizeof(next));
    }

    int sum = 0;
    for(int i=0;i<=side_num*dice_num;i++){
      sum += prev[i];
    }

    double exp = 0.0;
    for(int i=0;i<=side_num*dice_num;i++){
      double prob = (double)prev[i]/(double)sum;
      if(i-cutback <= 0){
	exp += 1.0 * prob;
      }
      else{
	exp += (double)(i-cutback) * prob;
      }
    }

    printf("%.8lf\n",exp);
  }
}

