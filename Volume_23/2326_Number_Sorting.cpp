#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
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
 
const static int tx[] = {+0,+1,+0,-1};
const static int ty[] = {-1,+0,+1,+0};
 
static const double EPS = 1e-8;

ll patterns[100001];

int main(){
  ll first_num;
  ll last_num;
  ll mod;

  patterns[0] = 0;
  patterns[1] = 1;
  for(int range = 1; range < 100000; range++){
    patterns[range+1] += (2LL * patterns[range]) % 1000000007LL;
  }

  while(~scanf("%lld %lld %lld",&first_num,&last_num,&mod)){
    if(first_num == 0 && last_num == 0 && mod == 0) break;


    map<ll,ll> dp;
    map<ll,ll> order_lexicon;
    vector<string> nums;
    for(int start = first_num; start <= last_num; start++){
      stringstream ss;
      ss << start;
      nums.push_back(ss.str());
    }
    sort(nums.begin(),nums.end());

    for(int num_i = 0; num_i < nums.size(); num_i++){
      order_lexicon[atol(nums[num_i].c_str())] = num_i;
    }

    ll res = 0;
    for(ll start = first_num; start <= last_num; start++){
      ll lhs = start;
      ll rhs = last_num;
      
      for(int round = 0; round < 20; round++){
	ll mid = lhs + (rhs - lhs) / 2;
	ll range = order_lexicon[mid] - order_lexicon[start] + 1;
	if(range == mid - start + 1){
	  lhs = mid;
	}
	else {
	  rhs = mid;
	}
      }
      
      printf("start:%lld range:%lld patterns:%lld\n",start,lhs - start + 1,patterns[lhs - start + 1 - 1] + 1);
      res += patterns[lhs-start+1 - 1] + 1;
      res %= mod;
    }

    printf("%lld\n",res);
  }
}
