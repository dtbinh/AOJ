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

void ComputeKakezan(const string& lhs,const string& rhs,string& result){
  ll a = strtol(lhs.c_str(),NULL,10);
  ll b = strtol(rhs.c_str(),NULL,10);

  char str[32];
  sprintf(str,"%ld",a*b);
  result = str;
}

int main(){
  int n;
  while(~scanf("%d",&n)){
    for(int i=0;i<n;i++){
      int count = 0;
      string seed;
      cin >> seed;
      
      map<string,bool> visited;
      visited[seed] = true;

      string current_max = seed;

      while(current_max.size() > 1){
	ll tmp_max = 0;
	for(int i=0;i<current_max.size()-1;i++){
	  string lhs = current_max.substr(0,i+1);
	  string rhs = current_max.substr(i+1,current_max.size()-(i+1));

	  string result;
	  ComputeKakezan(lhs,rhs,result);

	  ll result_ll = strtol(result.c_str(),NULL,10);
	  tmp_max = max(result_ll,tmp_max);
	  
	  // cout << lhs <<"\n";
	  // cout << rhs <<"\n";
	}
	
	char tmp[100];
	sprintf(tmp,"%ld",tmp_max);
	current_max = tmp;
	// cout << current_max << "\n";
	count++;
	if(visited.find(current_max) != visited.end()){
	  if(current_max.size() != 1) count = -1;
	  break;
	}
	visited[current_max] = true;
      }

      printf("%d\n",count);
    }
  }
}
