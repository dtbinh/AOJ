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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

string MakeSeq(int N){
  string res = "";
  for(int i=0;i<N;i++){
    int random_variable = std::rand() % 2; // 0 or 1
    res.push_back('0' + random_variable);
  }
  return res;
}

bool isClear(const vector<vector<int> >& cards,const string& bits,int N){
  for(int card_pos=0;card_pos < cards.size(); card_pos++){
    int sum = 0;
    for(int i=0;i<cards[card_pos].size();i++){
      if(bits[cards[card_pos][i]] == '1'){
	sum++;
      }
    }
    if(sum < N/8 || sum > 3*N/8) return false;
  }
  return true;
}

int main(){
  int N,K;
  srand(time(0)); // use current time as seed for random generator

  while(~scanf("%d %d",&N,&K)){
    vector<vector<int> > cards;
    for(int card_pos =0; card_pos < K; card_pos++){
      vector<int> card;
      for(int i = 0; i < N/2; i++){
	int seq_pos;
	scanf("%d",&seq_pos);
	card.push_back(seq_pos-1);
      }
      cards.push_back(card);
    }
    
    for(;;){
      string seq = MakeSeq(N);
      if(isClear(cards,seq,N)){
	printf("%s\n",seq.c_str());
	break;
      }
    }
  }
}
