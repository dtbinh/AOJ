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

map<string,int> freq;

void dfs(int x,int y,
	 string str,
	 int visited,
	 char stage[4][4],
	 const set<string>& keywords){
  str += stage[y][x];
  visited |= (1<<(4*y+x));
  if(keywords.count(str) > 0){
    freq[str]++;
  }

  if(__builtin_popcount((visited)) >= 8) return;

  for(int i=0;i<8;i++){
    int dx = x + tx[i];
    int dy = y + ty[i];
    if(dx < 0 || dx >= 4 || dy < 0 || dy >= 4) continue;
    int idx = dy * 4 + dx;
    if(visited & (1<<idx)) continue;
    dfs(dx,dy,str,visited,stage,keywords);
  }
}



int main(){
  int N;
  while(~scanf("%d",&N)){
    freq.clear();
    char stage[4][4];

    set<string> keywords;
    vector<string> keywords_v;
    map<string,int> score_table;
    int dp[10001];

    for(int i=0;i<N;i++){
      string word;
      int score;
      cin >> word >> score;
      score_table[word] = score;
      keywords.insert(word);
      keywords_v.push_back(word);
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
	dfs(x,y,"",0,stage,keywords);
      }
    }

    dp[0] = 0;
    for(int key_idx=0;key_idx < keywords_v.size();key_idx++){
      const string& key = keywords_v[key_idx];
      int cost = key.length();
      int score = score_table[key];

      int scalar = 1;
      int capacity = freq[key];
      for(;
	  scalar <= capacity;
	  capacity -= scalar,scalar *= 2){

	for(int next_time=time_limit;next_time - cost * scalar>=0;next_time--){
	  int from_time = next_time - cost * scalar;
	  if(dp[from_time] == -1) continue;
	  dp[next_time] = max(dp[from_time] + score * scalar,
			      dp[next_time]);
	}
      }

      if(capacity){
	for(int next_time=time_limit;next_time - cost * capacity>=0;next_time--){
	  int from_time = next_time - cost * capacity;
	  if(dp[from_time] == -1) continue;
	  dp[next_time] = max(dp[from_time] + score * capacity,
			      dp[next_time]);
	}
      }
    }

    int max_score = 0;
    for(int time = time_limit; time >=0; time--){
      max_score = max(dp[time],max_score);
    }
    printf("%d\n",max_score);
  }
}
