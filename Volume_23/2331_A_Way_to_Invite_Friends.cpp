#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
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
 
static const double EPS = 1e-8;

class Condition{
public:
  int lower;
  int upper;
  Condition(int _l,int _u) : lower(_l), upper(_u) {}
  bool operator<(const Condition& c) const{
    if(lower != c.lower){
      return lower < c.lower;
    }else{
      return upper < c.upper;
    }
  }
  bool operator>(const Condition& c) const{
    if(lower != c.lower){
      return lower > c.lower;
    }else{
      return upper > c.upper;
    }
  }
};

int main(){
  int N;
  while(~scanf("%d",&N)){
    priority_queue<Condition,vector<Condition>,greater<Condition> > ppl;
    for(int i=0;i<N;i++){
      int lower,upper;
      scanf("%d %d",&lower,&upper);
      ppl.push(Condition(lower,upper));
    }
    int current = 1;

    int res = 0;
    int dp[100100];
    memset(dp,0,sizeof(dp));

    while(!ppl.empty()){
      Condition c = ppl.top();
      ppl.pop();
      if(current + 1 >= c.lower){
	current++;
	current -= dp[current];
	dp[c.upper + 1]++;
	res = max(current - 1,res);
      }
    }

    printf("%d\n",res);
  }
}
