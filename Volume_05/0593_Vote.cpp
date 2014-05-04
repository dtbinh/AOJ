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
  int total_competitions;
  int total_committee;
  while(~scanf("%d %d",
	       &total_competitions,
	       &total_committee)){
    
    int cost[1001];
    memset(cost,0,sizeof(cost));
    for(int competition_idx=1; competition_idx<=total_competitions; competition_idx++){
      scanf("%d",cost + competition_idx);
    }

    int votes[1001];
    memset(votes,0,sizeof(votes));
    
    int res = 0;
    int max_votes = 0;
    for(int committee_idx = 1; committee_idx <= total_committee; committee_idx++){
      int criteria;
      scanf("%d",&criteria);
      for(int competition_idx=1; competition_idx<=total_competitions; competition_idx++){
	if(cost[competition_idx] <= criteria){
	  votes[competition_idx]++;

	  if(max_votes < votes[competition_idx]){
	    res = competition_idx;
	    max_votes = votes[competition_idx];
	  }
	  break;
	}
      }
    }

    printf("%d\n",res);
  }
}
