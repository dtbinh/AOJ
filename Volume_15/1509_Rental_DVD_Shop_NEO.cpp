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

int ComputePrice(
  int old_film_num,
  int semi_new_film_num,
  int new_film_num,
  int num_threshold,
  int price_threshold,
  int old_film_price,
  int semi_new_film_price,
  int new_film_price){

  int total_price = old_film_num * old_film_price 
    + semi_new_film_num * semi_new_film_price
    + new_film_num * new_film_price;

  int res = total_price;

  if(num_threshold <= old_film_num + semi_new_film_num + new_film_num
     && total_price > (old_film_num + semi_new_film_num + new_film_num) * price_threshold){
    res = (old_film_num + semi_new_film_num + new_film_num) * price_threshold;
  }
  else if(num_threshold > old_film_num + semi_new_film_num + new_film_num
	  && total_price > num_threshold * price_threshold
  ){
    res = num_threshold * price_threshold;
  }
  else{
    //nothing to do
  }
  return res;
}

int main(){
  int old_film_price,semi_new_film_price,new_film_price;
  int num_threshold,price_threshold;
  int old_film_num,semi_new_film_num,new_film_num;
  
  while(~scanf("%d %d %d %d %d",
	       &old_film_price,&semi_new_film_price,&new_film_price,
	       &num_threshold,&price_threshold)){
    if(num_threshold == 0) break;
    scanf("%d %d %d",&old_film_num,&semi_new_film_num,&new_film_num);

    int res = INF;
    for(int bit=0;bit<=(1<<3)-1;bit++){
      bool f1 = (bit & (1<<0));
      bool f2 = (bit & (1<<1));
      bool f3 = (bit & (1<<2));

      int p1 = ComputePrice(
	old_film_num * f1,
	semi_new_film_num  * f2,
	new_film_num  * f3,
	num_threshold,
	price_threshold,
	old_film_price,
	semi_new_film_price,
	new_film_price);

      int p2 = ComputePrice(
	old_film_num * !f1,
	semi_new_film_num  * !f2,
	new_film_num  * !f3,
	num_threshold,
	price_threshold,
	old_film_price,
	semi_new_film_price,
	new_film_price);

        res = min(p1+p2,res);
    }
    printf("%d\n",res);
  }
}
