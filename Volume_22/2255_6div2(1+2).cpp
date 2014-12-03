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
 
const int tx[] = {+0,+1,+0,-1};
const int ty[] = {-1,+0,+1,+0};
 
static const double EPS = 1e-8;

int main(){
  string str;
  while(cin >> str){
    if(str == "#") break;
    vector<string> elems;

    vector<char> ope;
    vector<int> nums;
    vector<int> ope_depth;

    int depth = 0; 
    for(int i = 0; i < str.size(); i++){
      if(str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*'){
	ope.push_back(str[i]);
	ope_depth.push_back(depth);
      }
      else if(str[i] == '('){
	depth++;
      }
      else if(str[i] == ')'){
	depth--;
      }
      else if(isdigit(str[i])){
	int sum = 0;
	while(i < str.size() && isdigit(str[i])){
	  sum *= 10;
	  sum += str[i] - '0';
	  i++;
	}
	nums.push_back(sum);
	i--;
      }
    }

    vector<int> order;
    for(int i = 0; i < ope.size(); i++){
      order.push_back(i);
    }
    
    set<int> res;
    vector<int> orig = nums;

    do {
      nums = orig;
      int min_depth = INF;
      bool used[12];
      memset(used,false,sizeof(used));
      for(int i = 0; i < order.size(); i++){
	if(min_depth < ope_depth[order[i]]){
	  goto over;
	}
	min_depth = min(min_depth,ope_depth[order[i]]);
      }

      for(int i = 0; i < order.size(); i++){
	int ans = 0;
	if(ope[order[i]] == '+') ans = nums[order[i]] + nums[order[i]+1];
	else if(ope[order[i]] == '-') ans = nums[order[i]] - nums[order[i]+1];
	else if(ope[order[i]] == '*') ans = nums[order[i]] * nums[order[i]+1];

	else if(ope[order[i]] == '/'){
	  if(nums[order[i]+1] == 0){
	    goto over;
	  }
	  ans = nums[order[i]] / nums[order[i]+1];
	}

	for(int j = order[i] + 1; j <= order.size() ; j++){
	  nums[j] = ans;
	  if(!used[j]) break;
	}
	for(int j = order[i]; j >= 0; j--){
	  nums[j] = ans;
	  if(j == 0 || !used[j-1]) break;
	}
	used[order[i]] = true;
      }

      res.insert(nums[0]);
    over:;
    }while(next_permutation(order.begin(),order.end()));
    cout << res.size() << endl;
  }
}
