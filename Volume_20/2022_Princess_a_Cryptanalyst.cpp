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
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int main(){
  int n;
  while(~scanf("%d",&n)){
    if(n==0) break;

    vector<int> order;
    for(int i=0;i<n;i++){
      order.push_back(i);
    }

    vector<string> constituents;
    for(int i=0;i<n;i++){
      string str;
      cin >> str;
      constituents.push_back(str);
    }

    string res = "";
    for(int i=0;i<=110;i++) res.push_back('z');
    sort(order.begin(),order.end());
    do{

      string catstr = constituents[order[0]];
      for(int i=1;i<order.size();i++){
	int idx = order[i];
	for(int smoothing = min(catstr.size(),constituents[idx].size());
	    smoothing >= 0 ;
	    smoothing--){
	  string front = catstr.substr(catstr.size()-smoothing,smoothing);
	  string rear = constituents[idx].substr(0,smoothing);

	  if(front == rear){
	    catstr += constituents[idx].substr(smoothing,constituents[idx].size()-smoothing);
	    break;
	  }
	}

	if(catstr.size() > res.size()) break;
      }

      if(res.size() > catstr.size()){
	res = catstr;
      }
      else if(res.size() == catstr.size() 
	      && res > catstr){
	res = catstr;
      }
    }while(next_permutation(order.begin(),order.end()));
    cout << res << endl;
  }
}
