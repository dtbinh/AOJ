#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <cstdio>
#include <iostream>
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
typedef pair <int,P > PP;
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};
 
static const double EPS = 1e-8;

static const char ranks[32] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};

int get_rank(char _c){
  for(int i=0;i<strlen(ranks);i++){
    if(ranks[i] == _c) return i;
  }
  return -1;
}

int main(){
  char Trump[2];

  while(~scanf("%s",Trump)){
    if(Trump[0] == '#') break;

    int led = 0;
    vector<vector<string> > cards;
    bool used[4][13];
    memset(used,false,sizeof(used));

    for(int dir=0;dir<4;dir++){
      vector<string> tmp_cards;
      for(int i=0;i<13;i++){
	string str;
	cin >> str;
	tmp_cards.push_back(str);
      }
      cards.push_back(tmp_cards);
    }

    int win[2] = {0,0};
    for(int turn=0;turn<13;turn++){

      int best_dir[3] = {-1,-1,-1}; //trump,led,other
      int best_rank[3] = {-1,-1,-1};//trump,led,other
      
      //search suit(SHDC)
      char led_suit = cards[led][turn][1];
      for(int dir=0;dir<4;dir++){
	int rank = get_rank(cards[dir][turn][0]);
	char suit = cards[dir][turn][1];

	if(suit == Trump[0]){
	  if(best_rank[0] < rank){
	    best_rank[0] = rank;
	    best_dir[0] = dir;
	  }
	}
	else if(suit == led_suit){
	  if(best_rank[1] < rank){
	    best_rank[1] = rank;
	    best_dir[1] = dir;
	  }
	}
	else if(suit != Trump[0]){
	  if(best_rank[2] < rank){
	    best_rank[2] = rank;
	    best_dir[2] = dir;
	  }
	}
      }
      
      for(int i=0;i<3;i++){
	if(best_dir[i] != -1){
	  win[best_dir[i] % 2]++;
	  // printf("%d\n",best_dir[i]);
	  led = best_dir[i];
	  break;
	}
      }
    }
    
    printf("%s %d\n",win[0] > win[1] ? "NS" : "EW",max(win[0],win[1])-6);
  }
}
