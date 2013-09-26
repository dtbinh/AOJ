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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};

class Link{
public:
  Link() : parent("") {}
  string parent;
  vector<string> childlen;
};

int dfs(map<string,Link>& nodes,const string& node_name){
  if(nodes[node_name].childlen.size() == 0){
    return 1;
  }
  int res = 0;
  for(int i=0;i<nodes[node_name].childlen.size();i++){
    res += dfs(nodes,nodes[node_name].childlen[i]);
  }
  return res;
}

int main(){
  int N;
  while(~scanf("%d",&N)){
    string str;
    map<string,Link> nodes;
    string first_group = "";
    for(int i=0;i<N;i++){
      cin >> str;
      string parent = "";
      
      int scan_idx = 0;
      for(;scan_idx<str.size() && str[scan_idx] != ':';
	  scan_idx++){
	parent.push_back(str[scan_idx]);
      }
      if(i==0) first_group = parent;

      string child = "";
      for(scan_idx++;scan_idx<str.size();scan_idx++){
	if(str[scan_idx] == ','
	|| str[scan_idx] == '.'){
	  nodes[child].parent = parent;
	  nodes[parent].childlen.push_back(child);
	  // cout << child << "\n";
	  child = "";
	  continue;
	}
	child.push_back(str[scan_idx]);
      }
    }

    printf("%d\n",dfs(nodes,first_group));
  }
}
