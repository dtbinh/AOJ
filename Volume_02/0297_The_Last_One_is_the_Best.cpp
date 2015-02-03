#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
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
  int total_games;
  while(~scanf("%d",&total_games)){
    for(int game_i = 0; game_i < total_games; game_i++){
      int num_of_stones;
      int num_of_players;
      scanf("%d %d",&num_of_stones,&num_of_players);
      if(num_of_stones < num_of_players){
	printf("%d\n",num_of_stones);
      }
      else{
	if(num_of_stones % num_of_players == 0){
	  printf("%d\n",num_of_players);
	}
	else{
	  printf("%d\n",num_of_stones % num_of_players);
	}
      }
    }
  }
}
