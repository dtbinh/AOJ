#define _USE_MATH_DEFINES
#define INF 100000000
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

using namespace std;

typedef long long ll;
typedef pair <int,int> P;

static const double EPS = 1e-8;

int main(){
  int agent_num;
  while(~scanf("%d",&agent_num)){
    if(agent_num == 0) break;
    vector<int> agent_info[101];
    for(int i=1;i<=agent_num;i++){
      int node_num;
      scanf("%d",&node_num);
      
      int to_node;
      for(int j=0;j<node_num;j++){
	scanf("%d",&to_node);
	agent_info[i].push_back(to_node);
      }
    }
    int leaked_num;
    int leak[101];
    scanf("%d",&leaked_num);
    for(int j=0;j<leaked_num;j++){
      scanf("%d",leak+j);
    }

    int criminal_num = 0;
    int criminal_idx = 0;
    for(int i=1;i<=agent_num;i++){
      int count = 0;
      for(int j=0;j<agent_info[i].size();j++){
	for(int k=0;k<leaked_num;k++){
	  if(leak[k] == agent_info[i][j]){
	    count++;
	    break;
	  }
	}
	
      }
      if(count >= leaked_num){
	criminal_idx = i;
	criminal_num++;
      }
    }

    printf("%d\n",criminal_num != 1 ? -1: criminal_idx);
  }
}
