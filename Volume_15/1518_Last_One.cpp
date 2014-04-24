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

int table[256];

void init_table(){
  int idx = 0;
  for(int i=0;i<=9;i++){
    table[ i + '0'] = idx;
    idx++;
  }
  for(int i='A';i<='Z';i++){
    table[i] = idx;
    idx++;
  }
  for(int i='a';i<='z';i++){
    table[i] = idx;
    idx++;
  }
}

int fast_pow(int x, int n){
  int res = 1;
  while(n > 0) {
    if (n & 1) res = res * x;
    x = x * x;
    n >>= 1;
  }
  return res;
}

int conv(int type,const string& num){
  int res = 0;
  for(int i=num.size()-1,j=0;i>=0;i--,j++){
    res += table[num[i]] * fast_pow(type,j);
  }
  return res;
}

int main(){
  init_table();

  int total_initial_subsets;
  while(~scanf("%d",&total_initial_subsets)){
    int freq[4];
    memset(freq,0,sizeof(freq));
      
    for(int subset_idx=0;subset_idx < total_initial_subsets;subset_idx++){
      int type;
      string num;
      cin >> type >> num;

      int dec = conv(type,num);
      int success = 0;
      for(int i=0;i<20;i++){
	if(dec & (1<<i)){
	  success++;
	}
	else{
	  if(success == 1) freq[1]++;
	  else if(success > 1) freq[2]++;
	  success=0;
	}
      }

      if(success == 1) freq[1]++;
      else if(success > 1) freq[2]++;
    }

    for(int i=1;i<=2;i++){
      cout << freq[i] << endl;
    }

    printf("%s\n",((freq[1] % 2) + freq[2]) % 2 == 0 ? "win" : "lose");
  }
}
