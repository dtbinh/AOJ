#define _USE_MATH_DEFINES
#define INF 100000000
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

static int cards[256];

int compute_score(bool& has_ace11,const vector<string>& hands){
  int sum = 0;

  bool has_ace = false;
  for(int i = 0; i < hands.size();i++){
    int num = cards[hands[i][0]];
    if(num == 1) has_ace = true;
    sum += num;
  }
  if(has_ace){
    if(sum + 10 <= 21){
      has_ace11 = true;
      sum += 10;
    }
  }
  return sum;
}

int main(){
  int total_testcases;
  for(int i = 2; i < 10; i++){
    cards['0' + i] = i;
  }
  cards['A'] = 1;
  cards['T'] = 10;
  cards['J'] = 10;
  cards['Q'] = 10;
  cards['K'] = 10;

  while(~scanf("%d",&total_testcases)){
    for(int test_i = 0; test_i < total_testcases; test_i++){
      string lhs,rhs;
      vector<string> hands;
      cin >> lhs >> rhs;

      bool is_ace11 = false;
      hands.push_back(lhs);
      hands.push_back(rhs);

      int sum = 0;
      for(int pile_i = 0; pile_i < 8; pile_i++){

	string pile;
	cin >> pile;
	bool is_ace11 = false;
	sum = compute_score(is_ace11,hands);

	if(sum <= 16){
	  hands.push_back(pile);
	}
	else if(sum == 17 && is_ace11){
	  hands.push_back(pile);
	}
      }
      sum = compute_score(is_ace11,hands);
      
      if(sum > 21){
	printf("bust\n");
      }
      else if(sum == 21 && hands.size() == 2){
	printf("blackjack\n");
      }
      else{
	printf("%d\n",sum);
      }
    }
  }
}
