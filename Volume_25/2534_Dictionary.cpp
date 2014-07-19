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
  
const static int tx[] = {0,1,0,-1};
const static int ty[] = {-1,0,1,0};

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N == 0) break;
    vector<string> dict;
    vector<string> asc;
    vector<string> desc;

    for(int i=0;i<N;i++){
      string str;      
      cin >> str;
      dict.push_back(str);
      asc.push_back(str);
      desc.push_back(str);
    }

    sort(asc.begin(),asc.end());
    sort(desc.begin(),desc.end(),greater<string>());

    int flag = 0;
    for(int i=0;i<N;i++){
      if(asc[i] != dict[i]) flag |= (1<<0);
      if(desc[i] != dict[i]) flag |= (1<<1);
    }

    printf("%s\n",(flag != (1<<2)-1) ? "yes" : "no");

  }
}

