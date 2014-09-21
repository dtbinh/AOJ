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

int sigma(int j,int block_length,int bits[1001]){
  int res = 0;
  for(int i = j; i < j+block_length-1;i++){
    res += bits[i];
  }
  return res;
}

string bit2str(int bits,int len){
  string res = "";
  for(int i=len-1;i>=0;i--){
    res.push_back((bits & (1<<i) ? '1' : '0'));
  }
  return res;
}

string conv_log(const vector<string>& log){
  string res = "";
  for(int i=0;i<log.size()-1;i++){
    res.push_back(log[i][0]);
  }
  res += log[log.size()-1];
  return res;
}

int next[1001][1<<12];

int main(){
  int sequence_length;
  int block_length;
  while(~scanf("%d %d",&sequence_length,&block_length)){
    if(sequence_length == 0 && block_length == 0) break;
    
    int sequence[1001];
    for(int seq_i=0; seq_i < sequence_length; seq_i++){
      scanf("%d",&sequence[seq_i]);
    }

    memset(next,-1,sizeof(next));
    for(int pos = (sequence_length + block_length - 1) - block_length; pos - 1 >= 0; pos--){
      for(int S = 0; S < (1<<block_length); S++){
	if(sequence[pos] == __builtin_popcount(S)){
	  int inherit = S >> 1;

	  for(int header = 0; header <= 1; header++){
	    int prev = inherit | (header<<(block_length-1));
	    if(sequence[pos-1] == __builtin_popcount(prev)){
	      next[pos-1][prev] = S;
	    }
	  }
	}
      }
    }

    bool has_ans = false;
    for(int S = 0; S < (1<<block_length); S++){
      if(next[0][S] == -1) continue;
      bool isok = true;
      vector<string> log;
      int bit = S;
      for(int pos = 0; pos < sequence_length; pos++){
	log.push_back(bit2str(bit,block_length));
	if(bit == -1){
	  isok = false;
	  break;
	}
	bit = next[pos][bit];
      }
      
      if(isok){
	cout << conv_log(log) << endl;
	has_ans = true;
	break;
      }
    }

    if(!has_ans){
      printf("Goofy\n");
    }
  }
}
