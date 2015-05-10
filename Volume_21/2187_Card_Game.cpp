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
  int total_test_cases;
  while(~scanf("%d",&total_test_cases)){
    for(int test_i = 0; test_i < total_test_cases; test_i++){
      vector<int> gates;
      vector<int> jukky;
      for(int i = 0; i < 9; i++){
	int card;
	scanf("%d",&card);
	gates.push_back(card);
      }
      for(int i = 0; i < 9; i++){
	int card;
	scanf("%d",&card);
	jukky.push_back(card);
      }

      sort(gates.begin(),gates.end());
      int jukky_win = 0;
      int gates_win = 0;
      int total_games = 0;
      do {
	int jukky_score = 0;
	int gates_score = 0;

	for(int i = 0; i < gates.size(); i++){
	  if(jukky[i] > gates[i]){
	    jukky_score += jukky[i] + gates[i];
	  }
	  else if(jukky[i] < gates[i]){
	    gates_score += jukky[i] + gates[i];
	  }
	}

	if(jukky_score > gates_score){
	  jukky_win++;
	}
	else if(jukky_score < gates_score){
	  gates_win++;
	}
	total_games++;
      }while(next_permutation(gates.begin(),gates.end()));

      printf("%.5lf %.5lf\n",
	     (double)gates_win/(double)total_games,
	     (double)jukky_win/(double)total_games);
    }
  }
}

