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
  int n;
  while(~scanf("%d",&n)){
    deque<pair<char,int> > seq;
    for(int i=0;i<n;i++){
      char parentheses[2];
      int num;

      scanf("%s %d",parentheses,&num);
      seq.push_back(pair<char,int>(parentheses[0],num));
    }

    int max_round = seq.size();
    for(int round=0;round < max_round;round++){
      for(int i=0;i+1<seq.size();i++){
	if(seq[i].first == '(' && seq[i+1].first == ')'){
	  if(seq[i].second < seq[i+1].second){
	    seq[i+1].second -= seq[i].second;
	    seq.erase(seq.begin()+i);
	    break;
	  }
	  else if(seq[i].second > seq[i+1].second){
	    seq[i].second -= seq[i+1].second;
	    seq.erase(seq.begin()+i+1);
	    break;
	  }
	  else if(seq[i].second == seq[i+1].second){
	    seq.erase(seq.begin()+i,seq.begin()+i+2);
	    break;
	  }
	}
      }
    }

    printf("%s\n",seq.size() == 0 ? "YES" : "NO");
  }
}
