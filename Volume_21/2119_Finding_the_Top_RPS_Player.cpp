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
  int player_num;
  int consective_win_num;
  int case_idx = 1;
  while(~scanf("%d %d",&player_num,&consective_win_num)){
    if(player_num == 0 && consective_win_num == 0) break;

    int winners[21];
    memset(winners,0,sizeof(winners));
    winners[0] = player_num;
    
    int res = 0;
    for(int turn = 1;winners[consective_win_num] < 1;turn++){

      int next_winners[21];
      memset(next_winners,0,sizeof(next_winners));

      for(int win=0;win<player_num;win++){
	next_winners[win+1] += winners[win] / 2;
	next_winners[win] += winners[win] % 2;
	next_winners[0] += winners[win] / 2;
      }

      memcpy(winners,next_winners,sizeof(int)*21);
      res = turn;
    }

    printf("Case %d: %d\n",case_idx,res);
    case_idx++;
  }
}
