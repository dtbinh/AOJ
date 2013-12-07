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
    int num[3];
    int max_num = 0;
    for(int i=0;i<n;i++){
      scanf("%d",num+i);
      max_num = max(max_num,num[i]);
    }

    vector<int> divisors;
    for(int div=1;div*div<=1e9;div++){
      bool isok = true;
      vector<int> candidates;
      for(int i=0;i<n;i++){
	if(num[i] % div != 0) isok = false;
	if(num[i] % div ==0) {
	  candidates.push_back(num[i]/div);
	}
      }
      if(isok){
	divisors.push_back(div);

	for(int i=0;i<candidates.size();i++){
	  bool isok2 = true;
	  for(int j=0;j<n;j++){
	    if(num[j] % candidates[i] != 0) isok2 = false;
	  }
	  if(isok2){
	    divisors.push_back(candidates[i]);
	  }
	}
      }
    }

    sort(divisors.begin(),divisors.end());
    vector<int>::iterator it = unique (divisors.begin(), divisors.end());
    divisors.resize(distance(divisors.begin(),it) );
    
    for(int i=0;i<divisors.size();i++){
      printf("%d\n",divisors[i]);
    }
  }
}
