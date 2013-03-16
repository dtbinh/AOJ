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
 
class Data{
public:
  string lhs;
  string rhs;
  int power;
  Data(string _l,string _r, int _p){
    lhs = _l;
    rhs = _r;
    power = _p;
  }
};
 
map<string,int> gUnit;
int gCount = 0;
 
int dp[101][101];
 
int unit2num(string str){
  if(gUnit.find(str) == gUnit.end()){
    gUnit[str]=gCount++;
  }
 
  return gUnit[str];
}
 
int main(){
  int n;
 
  while(~scanf("%d",&n)){
    if(n==0) break;
    gCount = 0;
    gUnit.clear();
    memset(dp,0x3f,sizeof(dp));
 
    vector<Data> relations;
    for(int i=0;i<n;i++){
      int num;
      string lhs;
      string eq;
      string rhs;
      string tmp;
 
      cin >> num >> lhs >> eq >> tmp >> rhs;
      int base,pow;
      sscanf(tmp.c_str(),"%d^%d",&base,&pow);
      relations.push_back(Data(lhs,rhs,pow));
    }
 
    for(int i=0;i<relations.size();i++){
      dp[unit2num(relations[i].lhs)][unit2num(relations[i].rhs)] = -relations[i].power;
      dp[unit2num(relations[i].rhs)][unit2num(relations[i].lhs)] = relations[i].power;
    }
 
    for(int k=0;k<gCount;k++){
      for(int i=0;i<gCount;i++){
	for(int j=0;j<gCount;j++){
	  dp[i][j] = min(dp[i][k] + dp[k][j],dp[i][j]);
	}
      }
    }
 
    bool isok = true;
    for(int i=0;i<gCount;i++){
      if(dp[i][i] != 0) isok = false;
    }
    printf("%s\n",isok ? "Yes" : "No");
  }
}
