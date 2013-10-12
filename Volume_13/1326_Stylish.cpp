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

const char brackets[] = {'(','{','[',')','}',']'};

class Bracket {
public:
  int round_bracket_left;
  int round_bracket_right;
  int curly_bracket_left;
  int curly_bracket_right;
  int square_bracket_left;
  int square_bracket_right;
};

int main(){
  int P,Q;
  while(~scanf("%d %d",&P,&Q)){

    int indented_freq[10][256];
    int suspicious_freq[10][256];
    memset(indented_freq,0,sizeof(indented_freq));
    memset(suspicious_freq,0,sizeof(suspicious_freq));

    for(int i=0;i<P;i++){
      string line;
      cin >> line;
      bool found_char = false;
      for(int pos=0;pos<line.size();pos++){
	if(!found_char && line[pos] == '.'){
	  indented_freq[i]['.']++;
	}
	else if(line[pos] != '.'){
	  found_char = true;
	}

	for(int bracket_idx = 0;bracket_idx<6;bracket_idx++){
	  if(line[pos] == brackets[bracket_idx]){
	    indented_freq[i][brackets[bracket_idx]]++;
	    break;
	  }
	}
      }
    }

    for(int i=0;i<Q;i++){
      string line;
      cin >> line;
      for(int pos=0;pos<line.size();pos++){
	for(int bracket_idx = 0;bracket_idx<6;bracket_idx++){
	  if(line[pos] == brackets[bracket_idx]){
	    indented_freq[i][brackets[bracket_idx]]++;
	  }
	}
      }
    }
  }
}
