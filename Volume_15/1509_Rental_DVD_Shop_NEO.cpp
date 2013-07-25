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
     && total_price >= (old_film_num + semi_new_film_num + new_film_num) * price_threshold){
    res = (old_film_num + semi_new_film_num + new_film_num) * price_threshold;
  }
  else if(num_threshold > old_film_num + semi_new_film_num + new_film_num
	  && total_price >= num_threshold * price_threshold
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

    int res = old_film_num * old_film_price
      + semi_new_film_num * semi_new_film_price
      + new_film_num * new_film_price;

    for(int i=0;i<=old_film_num + semi_new_film_num;i++){
      int b = min(semi_new_film_num,i);
      int a = i - b;
      //      printf("a:%d b:%d\n",a,b);
      int p1 = (old_film_num - a) * old_film_price 
	+ (semi_new_film_num - b) * semi_new_film_price;

      int p2 = ComputePrice(
	a,
	b,
	new_film_num,
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
