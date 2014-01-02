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
#include <complex>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-10;

bool is_prime[1000001];

int compute_key_number(int num){
  int sum = 0;
  int last_prime = 0;
  for(int i=2;i<=num;i++){
    if(!is_prime[i]) continue;
    if(num % i == 0){
      sum += i;
      last_prime = i;
    }
  }
  return last_prime - (sum-last_prime);
}

int main(){
  memset(is_prime,true,sizeof(is_prime));

  is_prime[0] = false;
  is_prime[1] = false;

  for(int i=2;i*i<=1000000;i++){
    if(!is_prime[i]) continue;
    for(int j=i+i;j<=1000000;j+=i){
      is_prime[j] = false;
    }
  }

  int doors[2];
  while(~scanf("%d %d",doors,doors+1)){
    if(doors[0] == 0 && doors[1] == 0) break;
    printf("%c\n",compute_key_number(doors[0]) > compute_key_number(doors[1]) ? 'a' : 'b');
  }
}
