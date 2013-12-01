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
  int total_toppings;
  while(~scanf("%d",&total_toppings)){
    int dough_price,topping_price;
    int dough_cal;
    int topping_cal[100];
    scanf("%d %d",&dough_price,&topping_price);
    scanf("%d",&dough_cal);
    for(int i=0;i<total_toppings;i++){
      scanf("%d",topping_cal+i);
    }

    sort(topping_cal,topping_cal+total_toppings,greater<int>());

    int total_cal = dough_cal;
    int res = total_cal/dough_price;
    for(int i=0;i<total_toppings;i++){
      total_cal += topping_cal[i];
      res = max(total_cal/(dough_price + topping_price * (i+1)),res);
    }
    printf("%d\n",res);
  }
}
