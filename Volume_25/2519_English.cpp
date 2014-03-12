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
  
int tx[] = {+0,+1,+1,+1,+0,-1,-1,-1};
int ty[] = {-1,-1,+0,+1,+1,+1,+0,-1};

const int mask = (1<<16) - 1;

map<string,set<int> > route;

void dfs(int x,int y,
	 string str,
	 int bits,
	 char stage[4][4],
	 const set<string>& keywords){
  if(__builtin_popcount((bits & mask)) >= 8) return;
  
  if(keywords.count(str) > 0
     && route[str].count(bits) == 0){
    route[str].insert(bits);
  }

  for(int i=0;i<8;i++){
    int dx = x + tx[i];
    int dy = y + ty[i];
    if(dx < 0 || dx >= 4 || dy < 0 || dy >= 4) continue;
    int idx = dy * 4 + dx;
    if(bits & (1<<idx)) continue;
    string next = str;
    next.push_back(stage[dy][dx]);
    dfs(dx,dy,next,bits | (1<<idx),stage,keywords);
  }
}



int main(){
  int N;
  while(~scanf("%d",&N)){
    route.clear();
    char stage[4][4];

    set<string> keywords;
    vector<string> idx2keyword;
    map<string,int> score_table;
    int dp[10001];

    for(int i=0;i<N;i++){
      string word;
      int score;
      cin >> word >> score;
      score_table[word] = score;
      idx2keyword.push_back(word);
      keywords.insert(word);
    }
    for(int y=0;y<4;y++){
      string line;
      cin >> line;
      for(int x=0;x<4;x++){
	stage[y][x] = line[x];
      }
    }

    int time_limit;
    scanf("%d",&time_limit);
    memset(dp,-1,sizeof(dp));
    for(int y=0;y<4;y++){
      for(int x=0;x<4;x++){
	int bits = ((1<<(y*4+x)) << 16);
	string str = "";
	str.push_back(stage[y][x]);
	dfs(x,y,str,bits | (1<<(y*4+x)),stage,keywords);
      }
    }

    dp[0] = 0;
    for(int idx=0;idx<N;idx++){
      string key = idx2keyword[idx];

      for(int route_idx=0,size=route[key].size();
	  route_idx < size;
	  route_idx++){
	int cost = key.length();

	int tmp[10001];
	memset(tmp,0,sizeof(tmp));
	for(int next_time=0;next_time<=time_limit;next_time++){
	  int from_time = next_time - cost;
	  if(from_time < 0) continue;
	  if(dp[from_time] == -1) continue;
	  tmp[next_time] = max(dp[from_time] + score_table[key],dp[next_time]);
	}
	memcpy(dp,tmp,sizeof(int)*10001);
      }
    }

    int max_score = 0;
    for(int time = time_limit; time >=0; time--){
      max_score = max(dp[time],max_score);
    }
    printf("%d\n",max_score);
  }
}
