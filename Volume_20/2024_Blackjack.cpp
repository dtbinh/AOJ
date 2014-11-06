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

int main(){
  int total_testcases;
  for(int i = 1; i < 10; i++){
    cards['0' + i] = i;
  }
  cards['A'] = 11;
  cards['T'] = 10;
  cards['J'] = 10;
  cards['Q'] = 10;
  cards['K'] = 10;

  while(~scanf("%d",&total_testcases)){
    for(int test_i = 0; test_i < total_testcases; test_i++){
      string lhs,rhs;
      cin >> lhs >> rhs;
      int numA = cards[lhs[0]];
      int numB = cards[rhs[0]];
      
      int sum = numA + numB;
      bool has_ace;
      bool is_blackjack = false;
      bool is_ace1 = false;
      if(numA + numB == 21){
	is_blackjack = true;
      }
      if(numA == 11 || numB == 11){
	has_ace = true;
	is_ace1 = false;
      }

      for(int pile_i = 0; pile_i < 8; pile_i++){
	string pile;
	cin >> pile;
	if(is_blackjack) continue;

	int num = cards[pile[0]];
	if(sum <= 16){
	   // || (sum > 16 && has_ace && !is_ace1 && sum - 10 <= 16)){
	  if(num == 11){
	    has_ace = true;

	    if(sum + num > 21){
	      is_ace1 = true;
	      sum += 1;
	    }
	    else{
	      sum += num;
	    }
	  }
	  else{
	    sum += num;
	  }
	}
	else if(sum == 17 && is_ace1){
	  sum += num;
	}
      }
      
      if(sum > 21){
	printf("bust\n");
      }
      else if(is_blackjack){
	printf("blackjack\n");
      }
      else{
	printf("%d\n",sum);
      }
    }
  }
}
