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

class Letter{
public:
  string letter;
  string number;
  Letter() : letter(""),number(""){}
  Letter(string _l,string _n) : letter(_l),number(_n) {}
};

bool matching_letters(int offset, const string& src,const string& dst){
  if(offset + src.size() > dst.size()) return false;

  for(int i=0;i<src.size();i++){
    if(dst[i+offset] != src[i]) return false;
  }
  return true;
}

int main(){
  int buttons[256];
  buttons['a'] = 2;
  buttons['b'] = 2;
  buttons['c'] = 2;

  buttons['d'] = 3;
  buttons['e'] = 3;
  buttons['f'] = 3;

  buttons['g'] = 4;
  buttons['h'] = 4;
  buttons['i'] = 4;

  buttons['j'] = 5;
  buttons['k'] = 5;
  buttons['l'] = 5;

  buttons['m'] = 6;
  buttons['n'] = 6;
  buttons['o'] = 6;

  buttons['p'] = 7;
  buttons['q'] = 7;
  buttons['r'] = 7;
  buttons['s'] = 7;

  buttons['t'] = 8;
  buttons['u'] = 8;
  buttons['v'] = 8;

  buttons['w'] = 9;
  buttons['x'] = 9;
  buttons['y'] = 9;
  buttons['z'] = 9;

  int N;
  while(~scanf("%d",&N)){
    if(N == 0) break;

    Letter dict[128];
    for(int dic_idx=0;dic_idx<N;dic_idx++){
      string str;
      cin >> str;

      string tmp_num = "";
      for(int i=0;i<str.size();i++){
	tmp_num.push_back(buttons[str[i]] + '0');
      }
      dict[dic_idx] = Letter(str,tmp_num);
    }

    vector<string> dp[5001]; //dp[end_pos] := term

    string numbers;
    cin >> numbers;
    
    for(int end_pos = 0; end_pos <= 3000; end_pos++){
      if(end_pos == 0){
	for(int dic_idx=0;dic_idx<N;dic_idx++){
	  if(matching_letters(end_pos,dict[dic_idx].number,numbers)){
	    dp[end_pos + dict[dic_idx].number.size()].push_back(dict[dic_idx].letter);
	  }
	}
      }
      if(dp[end_pos].size() == 0) continue;

      for(int dic_idx=0;dic_idx<N;dic_idx++){
	if(matching_letters(end_pos,dict[dic_idx].number,numbers)){
	  for(int i=0;i<dp[end_pos].size();i++){
	    dp[end_pos + dict[dic_idx].number.size()].push_back(dp[end_pos][i] + " " + dict[dic_idx].letter);
	  }
	}
      }
    }

    for(int i=0;i<dp[numbers.size()].size();i++){
      cout << dp[numbers.size()][i] << "." << endl;
    }
    cout << "--" << endl;
  }
}
