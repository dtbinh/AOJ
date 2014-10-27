#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
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
#include <cstdio>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <P,P> PP;
typedef pair <int,PP> PPP;

static const double eps = 1e-8;

bool cards[300001];

int main(){
  int total_cards;
  int total_questions;

  while(~scanf("%d %d",
	       &total_cards,
	       &total_questions)){

    memset(cards,false,sizeof(cards));
    
    int tmp_max = 0;
    for(int card_i = 0; card_i < total_cards; card_i++){
      int card;
      scanf("%d",&card);
      cards[card] = true;
    }

    for(int question_i = 0; question_i < total_questions; question_i++){
      int divisor;
      scanf("%d",&divisor);
      int res = 0;
      for(int target = divisor - 1; target >= 0; target--){
	for(int i = target; i <= 300000; i+= divisor){
	  if(cards[i]){
	    res = target;
	    goto found;
	  }
	}
      }
    found:;
      printf("%d\n",res);
    }
  }
}
