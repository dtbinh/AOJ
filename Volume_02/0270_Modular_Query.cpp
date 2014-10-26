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
    for(int card_i = 0; card_i < total_cards; card_i++){
      int card;
      scanf("%d",&card);
      cards[card] = true;
    }
    sort(cards,cards + total_cards);

    for(int question_i = 0; question_i < total_questions; question_i++){
      int question;
      scanf("%d",&question);
      int max_card = 0;
      for(int target = question - 1; target >= 1; target--){
	for(int i = target; i <= 300000; i+= question){
	  if(cards[i]){
	    max_card = i;
	    goto found;
	  }
	}
      }
    found:;
      printf("%d\n",max_card % question);
    }
  }
}
