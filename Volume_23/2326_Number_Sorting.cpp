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

class BIT {
private:
  int n;
  ll* bit;
public:
  BIT(int _n) {
    n = _n;
    bit = new ll[n]();
  }
  
  ll sum(int i){
    ll s = 0;
    while(i > 0){
      s += bit[i];
      i -= i & -i;
    }
    return s;
  }
  
  void add(int i, ll x){
    while(i <= n){
      bit[i] += x;
      i += i & -i;
    }
  }
};

int main(){
  int first_num;
  int last_num;
  int mod;
  while(~scanf("%d %d %d",&first_num,&last_num,&mod)){
    if(first_num == 0 && last_num == 0 && mod == 0) break;
    
    vector<int> order_lexicon;
    vector<string> nums;
    
    for(int start = first_num; start <= last_num; start++){
      stringstream ss;
      ss << start;
      nums.push_back(ss.str());
    }
    sort(nums.begin(),nums.end());
    
    for(int num_i = 0; num_i < nums.size(); num_i++){
      order_lexicon.push_back(atoi(nums[num_i].c_str()));
    }
    
    ll res = 0;
    BIT bit(last_num - first_num + 2);
    for(int i = 0; i < order_lexicon.size();i++){
      ll tmp = (bit.sum(order_lexicon[i] - first_num + 1) + 1) % mod;
      res += tmp;
      res %= mod;
      bit.add(order_lexicon[i] - first_num + 1,tmp);
    }
    
    printf("%lld\n",res % mod);
  }
}
