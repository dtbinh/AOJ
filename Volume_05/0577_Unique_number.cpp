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
  int total_players;
  while(~scanf("%d",&total_players)){
    int cards[200][3];
    int scores[200];
    memset(cards,0,sizeof(cards));
    memset(scores,0,sizeof(scores));
    for(int player_id = 0;player_id < total_players; player_id++){
      for(int turn = 0; turn < 3; turn++){
	scanf("%d",&cards[player_id][turn]);
      }
    }
    for(int turn = 0; turn < 3; turn++){
      int freq[101];
      memset(freq,0,sizeof(freq));

      for(int player_id = 0;player_id < total_players; player_id++){
	freq[cards[player_id][turn]]++;
      }

      for(int player_id = 0;player_id < total_players; player_id++){
	if(freq[cards[player_id][turn]] == 1){
	  scores[player_id] += cards[player_id][turn];
	}
      }
    }

    for(int player_id = 0; player_id < total_players; player_id++){
      printf("%d\n",scores[player_id]);
    }
  }
}
