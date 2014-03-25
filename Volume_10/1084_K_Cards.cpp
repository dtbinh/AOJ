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

using namespace std;

typedef long long ll;
typedef pair <int,int> P;

static const double EPS = 1e-8;

int main(){
  int total_cards;
  int continuous_range;
  while(~scanf("%d %d",&total_cards,&continuous_range)){
    if(total_cards == 0) break;
    int cards[101];
    for(int card_idx=0;card_idx<total_cards;card_idx++){
      scanf("%d",cards + card_idx);
    }

    int org_max = 0;
    for(int start=0;start + continuous_range<=total_cards;start++){
      int sum = 1;
      for(int cr=0;cr<continuous_range;cr++){
	sum *= cards[start+cr];
      }
      org_max = max(sum,org_max);
    }
    int next_max = 0;
    for(int from_idx=0;from_idx<total_cards;from_idx++){
      for(int to_idx=from_idx+1;to_idx<total_cards;to_idx++){
	swap(cards[from_idx],cards[to_idx]);
	for(int start=0;start + continuous_range<=total_cards;start++){
	  int sum = 1;
	  for(int cr=0;cr<continuous_range;cr++){
	    sum *= cards[start+cr];
	  }
	  next_max = max(sum,next_max);
	}
	swap(cards[from_idx],cards[to_idx]);
      }
    }

    if(next_max - org_max >= 0){
      printf("%d\n",next_max - org_max);
    }
    else{
      printf("NO GAME\n");
    }

  }
}
