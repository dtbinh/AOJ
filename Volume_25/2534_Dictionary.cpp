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
    vector<P> dict;
    
    char mapping[256];
    bool used[256];
    memset(mapping,0,sizeof(mapping));
    memset(used,false,sizeof(used));

    for(int i=0;i<N;i++){
      string str;      
      cin >> str;

      for(int j=0;j<str.size();j++){
	if(mapping[str[j]] == 0){
	  for(char alter='a';alter<='z';alter++){
	    if(!used[alter]){
	      mapping[str[j]] = alter;
	      used[alter] = true;
	      break;
	    }
	  }
	}
      }
      
      string next = "";
      for(int j=0;j<str.size();j++){
	next.push_back(mapping[str[j]]);
      }
      dict.push_back(P(next,i));
    }

    stable_sort(dict.begin(),dict.end());

    bool isok = true;
    for(int i=0;i<dict.size();i++){
      if(dict[i].second != i){
      	isok = false;
      	break;
      }
    }

    printf("%s\n",isok ? "yes" : "no");
  }
}

