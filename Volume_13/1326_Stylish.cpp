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

int ComputeIndents(int R,int C,int S,int freq[11][256],int i){
  int white_space
    = R * (freq[i-1][brackets[0]]-freq[i-1][brackets[3]])
    + C * (freq[i-1][brackets[1]]-freq[i-1][brackets[4]])
    + S * (freq[i-1][brackets[2]]-freq[i-1][brackets[5]]);

  return white_space;
}

class RCS{
public:
  RCS(int _r,int _c,int _s) : R(_r),C(_c),S(_s){}
  int R;
  int C;
  int S;
};

int main(){
  int P,Q;
  while(~scanf("%d %d",&P,&Q)){
    if(P == 0 && Q == 0) break;

    vector<RCS> candidates;
    int indented_freq[11][256];
    int suspicious_freq[11][256];
    memset(indented_freq,0,sizeof(indented_freq));
    memset(suspicious_freq,0,sizeof(suspicious_freq));

    for(int i=1;i<=P;i++){
      string line;
      cin >> line;
      bool found_char = false;

      //add previous freq
      for(int bracket_idx = 0;bracket_idx<6;bracket_idx++){
	indented_freq[i][brackets[bracket_idx]]
	  = indented_freq[i-1][brackets[bracket_idx]];
      }

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

    for(int i=1;i<=Q;i++){
      string line;
      cin >> line;

      //add previous freq
      for(int bracket_idx = 0;bracket_idx<6;bracket_idx++){
	suspicious_freq[i][brackets[bracket_idx]]
	  = suspicious_freq[i-1][brackets[bracket_idx]];
      }

      for(int pos=0;pos<line.size();pos++){
	for(int bracket_idx = 0;bracket_idx<6;bracket_idx++){
	  if(line[pos] == brackets[bracket_idx]){
	    suspicious_freq[i][brackets[bracket_idx]]++;
	  }
	}
      }
    }

    
    for(int R=1;R<=20;R++){
      for(int C=1;C<=20;C++){
	for(int S=1;S<=20;S++){
	  bool isok = true;
	  for(int i=1;i<=P;i++){
	    int white_space
	      = ComputeIndents(R,C,S,indented_freq,i);
	    if(white_space != indented_freq[i]['.']){
	      isok = false;
	      break;
	    }
	  }

	  if(isok){
	    candidates.push_back(RCS(R,C,S));
	  }
	}
      }
    }
    
    for(int i=1;i<=Q;i++){
      set<int> indents;
      for(int candidate_idx = 0; candidate_idx < candidates.size(); candidate_idx++){
	int R = candidates[candidate_idx].R;
	int C = candidates[candidate_idx].C;
	int S = candidates[candidate_idx].S;
	int white_space = ComputeIndents(R,C,S,suspicious_freq,i);
	indents.insert(white_space);
      }
      
      if(indents.size() == 0 || indents.size() > 1){
	printf("%s-1",i==1 ? "" : " ");
      }
      else{
	printf("%s%d",i==1 ? "" : " ",*indents.begin());
      }
    }

    printf("\n");
  }
}

