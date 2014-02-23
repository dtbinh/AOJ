#define _USE_MATH_DEFINES
#define INF 10000000
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
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

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

static const double EPS = 1e-8;

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N == 0) break;
    char cards[101];
    scanf("%s",cards);
    
    int card_idx = 0;
    int players[11];
    memset(players,0,sizeof(players));

    int field = 0;
    for(int round=0;round < 100; round++){
      for(int player_idx=0;player_idx < N; player_idx++){

	if(cards[card_idx] == 'M'){
	  players[player_idx]++;
	}
	else if(cards[card_idx] == 'S'){
	  field += (players[player_idx] + 1);
	  players[player_idx] = 0;
	}
	else if(cards[card_idx] == 'L'){
	  players[player_idx] += (field + 1);
	  field = 0;
	}
	card_idx++;
	if(card_idx >= 100) goto game_over;
      }
    }
    
  game_over:;

    sort(players,players + N);
    for(int player_idx=0;player_idx<N;player_idx++){
      printf("%d ",players[player_idx]);
    }
    printf("%d\n",field);
  }
}
