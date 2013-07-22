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

int main(){
  int old_film_price,semi_new_film_price,new_film_price;
  int num_threshold,price_threshold;
  int old_film_num,semi_new_film_num,new_film_num;
  
  while(~scanf("%d %d %d %d %d",
	       &old_film_price,&semi_new_film_price,&new_film_price,
	       &num_threshold,&price_threshold)){
    scanf("%d %d %d",&old_film_num,&semi_new_film_num,&new_film_num);
    
    int total_price = old_film_num * old_film_price 
      + semi_new_film_num * semi_new_film_price 
      + new_film_num * new_film_price;
    
    int res = total_price;
    if(num_threshold <= old_film_num + semi_new_film_num + new_film_num
       && total_price >= (old_film_num + semi_new_film_num + new_film_num) * price_threshold){
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
    printf("%d\n",res);
  }
}
