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
typedef pair <string,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
const static int tx[] = {0,1,0,-1};
const static int ty[] = {-1,0,1,0};

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N == 0) break;
    vector<string> dict;
    int prior[256][256]; // prior[A][B] ::= A is prior to B or not
    memset(prior,-1,sizeof(prior));

    bool isok = true;
    bool res = true;
    for(int current_idx = 0;current_idx<N;current_idx++){
      string current;
      cin >> current;

      for(int prev_idx=0;prev_idx<dict.size();prev_idx++){
	for(int char_idx=0;
	    char_idx < current.size() && char_idx < dict[prev_idx].size();
	    char_idx++){
	  if(current[char_idx] == dict[prev_idx][char_idx]) continue;

	  if(prior[dict[prev_idx][char_idx]][current[char_idx]] == 1){
	    break;
	  }

	  if(prior[dict[prev_idx][char_idx]][current[char_idx]] == -1){
	    prior[dict[prev_idx][char_idx]][current[char_idx]] = 1;
	    prior[current[char_idx]][dict[prev_idx][char_idx]] = 0;
	    break;
	  }
	}

	bool isok = true;
	bool is_first = true;
	for(int char_idx=0;
	    char_idx < current.size() && char_idx < dict[prev_idx].size();
	    char_idx++){
	  if(current[char_idx] == dict[prev_idx][char_idx]) continue;
	  if(is_first && prior[current[char_idx]][dict[prev_idx][char_idx]] == 1){
	    isok = false;
	    break;
	  }
	  is_first = false;
	}

	if(isok){
	  if(current.size() < dict[prev_idx].size()
	     && dict[prev_idx].substr(0,current.size()) == current){
	    isok = false;
	  }
	}

	res &= isok;
	if(!res){
	  current_idx++;
	  for(;current_idx < N;current_idx++){
	    cin >> current;
	  }
	  goto found;
	}
      }

      dict.push_back(current);
    }
  found:;
    printf("%s\n",res ? "yes" : "no");
  }
}

