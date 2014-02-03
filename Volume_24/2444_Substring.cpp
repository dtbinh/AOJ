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
  int string_size;
  int total_queries;
  while(~scanf("%d %d",&string_size,&total_queries)){
    string str;
    cin >> str;
    int left[300000];
    int right[300000];
    memset(left,0,sizeof(left));
    memset(right,0,sizeof(right));
    left[0] = 1;
    right[0] = 1;
    set<string> visited;
    for(int query_idx = 1; query_idx <= total_queries; query_idx++){
      string query;
      cin >> query;
      if(query == "L--"){
	left[query_idx]=left[query_idx-1] - 1;
	right[query_idx]=right[query_idx-1];
      }
      else if(query == "L++"){
	left[query_idx]=left[query_idx-1] + 1;
	right[query_idx]=right[query_idx-1];
      }
      if(query == "R--"){
	left[query_idx]=left[query_idx-1];
	right[query_idx]=right[query_idx-1] - 1;
      }
      else if(query == "R++"){
	left[query_idx]=left[query_idx-1];
	right[query_idx]=right[query_idx-1] + 1;
      }

      visited.insert(str.substr(left[query_idx]-1,right[query_idx]-left[query_idx]+1));
    }
    printf("%d\n",visited.size());
  }
}
