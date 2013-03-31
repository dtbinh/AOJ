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

struct Coin{
  int num10;
  int num50;
  int num100;
  int num500;
};

struct Coin ChangeCoinNum(int sum){
  int num500yen = (sum >= 500 ? sum/500 : 0);
  sum %= 500;

  int num100yen = (sum >= 100 ? sum/100 : 0);
  sum %= 100;

  int num50yen = (sum >= 50 ? sum/50 : 0);
  sum %= 50;

  int num10yen = (sum >= 10 ? sum/10 : 0);
  sum %= 10;

  Coin res = {num10yen,num50yen,num100yen,num500yen};
  return res;
}

int main(){
  int price;
  int num10yen,num50yen,num100yen,num500yen;
  bool is_1st = true;
  while(~scanf("%d",&price)){
    if(price == 0) break;
    scanf("%d %d %d %d",&num10yen,&num50yen,&num100yen,&num500yen);

    struct Coin res;
    
    int min_c = numeric_limits<int>::max();
    for(int i=0;i<=num10yen;i++){
      for(int j=0;j<=num50yen;j++){
	for(int k=0;k<=num100yen;k++){
	  for(int l=0;l<=num500yen;l++){
	    int sum = 10*i + 50*j + 100*k + 500*l;
	    if(sum - price < 0) continue;

	    struct Coin each_coin_num = ChangeCoinNum(sum - price);
	    if(i && each_coin_num.num10) continue;
	    if(j && each_coin_num.num50) continue;
	    if(k && each_coin_num.num100) continue;
	    if(l && each_coin_num.num500) continue;

	    int total_coin_num = 
	      +num10yen -i + each_coin_num.num10
	      +num50yen -j + each_coin_num.num50
	      +num100yen -k + each_coin_num.num100
	      +num500yen -l + each_coin_num.num500;

	    if(min_c > total_coin_num){
	      min_c = total_coin_num;
	      struct Coin tmp 
		= {i,j,k,l};
	      res = tmp;
	    }
	  }
	}
      }
    }
    if(!is_1st){
      printf("\n");
    }
    if(res.num10 > 0) printf("10 %d\n",res.num10);
    if(res.num50 > 0) printf("50 %d\n",res.num50);
    if(res.num100 > 0) printf("100 %d\n",res.num100);
    if(res.num500 > 0) printf("500 %d\n",res.num500);
    is_1st = false;
  }
}
