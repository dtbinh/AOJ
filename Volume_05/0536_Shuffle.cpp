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
  int total_cards;
  while(~scanf("%d",&total_cards)){
    int total_shuffles;
    int first,last,upper;

    scanf("%d",&total_shuffles);
    scanf("%d %d %d",&first,&last,&upper);
    
    vector<P> cards;
    cards.push_back(P(1,total_cards));

    for(int i=0;i<total_shuffles;i++){
      int x,y;
      scanf("%d %d",&x,&y);
      //x -> none
      //y -> 1
      //n -> x+1
      //C -> B -> A
      vector<P> A;
      vector<P> B;
      vector<P> C;

      int sum = 0;
      int prev_sum = 0;
      for(int j=0;j<cards.size();j++){
	prev_sum = sum;
	sum += cards[j].second - cards[j].first + 1;
	if(prev_sum < x){
	  if(sum <= x){
	    A.push_back(cards[j]);
	  }
	  else if(sum > x && sum <= y){
	    A.push_back(P(cards[j].first,cards[j].first + (x - prev_sum)));
	    B.push_back(P(cards[j].first + (x - prev_sum + 1),
			  cards[j].second));
	  }
	  else if(sum > y){
	    A.push_back(P(cards[j].first,cards[j].first + (x - prev_sum)));
	    B.push_back(P(cards[j].first + (x - prev_sum + 1),
			  cards[j].first + (x - prev_sum + 1) + (y - x)));
	    B.push_back(P(cards[j].first + (x - prev_sum + 1) + (y - x) + 1,
			  cards[j].second));
	  }
	}
	else if(prev_sum >= x){
	  if(sum <= y){
	    B.push_back(P(cards[j].first,cards[j].second));
	  }
	  else if(sum > y){
	    B.push_back(P(cards[j].first,cards[j].first + (y - prev_sum)));
	    C.push_back(P(cards[j].first + (y - prev_sum + 1),cards[j].second));
	  }
	}

	for(int i=0;i<A.size();i++){
	  cout << "A<f,s>=" << A[i].first << "," << A[i].second << endl;
	}
	for(int i=0;i<B.size();i++){
	  cout << "B<f,s>=" << B[i].first << "," << B[i].second << endl;
	}
	for(int i=0;i<C.size();i++){
	  cout << "C<f,s>=" << C[i].first << "," << C[i].second << endl;
	}
      }
    }
  }
}
