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

bool is_prime[30001];

int main(){
  int side_sum;

  memset(is_prime,true,sizeof(is_prime));
  is_prime[0] = false;
  is_prime[1] = false;
  vector<int> prime;
  for(int i=0;i<=30000;i++){
    if(!is_prime[i]) continue;
    prime.push_back(i);
    for(int j=i+i;j<=30000;j+=i){
      is_prime[j] = false;
    }
  }

  while(~scanf("%d",&side_sum)){
    if(side_sum == 0) break;
    int res = 0;
    map<vector<int>,bool> visited;

    for(int prime_i = 0; prime_i < prime.size(); prime_i++){

      int center_side = prime[prime_i];
      if(center_side >= side_sum) break;

      int remainings = side_sum - center_side;
      if(remainings <= 0) break;
      
      for(int prime_j = 0; prime_j < prime.size(); prime_j++){
	int left_side = prime[prime_j];
	int right_side = remainings - left_side;

	if(right_side <= 0) continue;
	if(!is_prime[right_side]) continue;
	vector<int> used;
	used.push_back(center_side);
	used.push_back(left_side);
	used.push_back(right_side);
	sort(used.begin(),used.end());
	if(used[0] + used[1] <= used[2]) continue;

	if(visited.find(used) != visited.end()) continue;

	visited[used] = true;
	res++;
      }
    }
    printf("%d\n",res);
  }
}
