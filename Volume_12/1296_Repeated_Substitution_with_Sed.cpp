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

struct Operation{
  string from;
  string to;
};

string modify(const string& src,const Operation& opr){
  string res="";
  int f_size = opr.from.size();
  string f_str = opr.from;
  string t_str = opr.to;
  
  for(int i=0;i<src.size();){
    if(src.substr(i,f_size) == f_str){
      res += t_str;
      i+=f_size;
      continue;
    }
    res.push_back(src[i]);
    i++;
  }
  return res;
}

void dfs(string src,int N,
	 Operation modify_operations[10],
	 map<string,int>& from_orig_cost,
	 const string& target){
  for(int i=0;i<N;i++){
    string dst = modify(src,modify_operations[i]);
    if(src==dst) continue;
    if(dst.size() > target.size()) continue;
    if(from_orig_cost.find(dst) == from_orig_cost.end()
       || from_orig_cost[dst] > from_orig_cost[src]+1){
      from_orig_cost[dst] = from_orig_cost[src]+1;
      dfs(dst,N,modify_operations,from_orig_cost,target);
    }
  }
}


int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N==0) break;

    Operation modify_operations[10];
    for(int i=0;i<N;i++){
      string from,to;
      cin >> from >> to;
      Operation tmp = {from,to};
      modify_operations[i] = tmp;
    }

    map<string,int> from_orig_cost;

    string original;
    string target;
    cin >> original >> target;

    from_orig_cost[original] = 0;
    
    dfs(original,N,modify_operations,
	from_orig_cost,target);
    
    if(from_orig_cost.find(target) == from_orig_cost.end()){
      printf("-1\n");
    }
    else{
      printf("%d\n",from_orig_cost[target]);
    }
  }
}
