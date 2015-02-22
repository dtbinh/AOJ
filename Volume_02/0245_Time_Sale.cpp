#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
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

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

int main(){
  int W,H;
  while(~scanf("%d %d",&W,&H)){
    for(int y = 0; y < H; y++){
      for(int x = 0; x < W; x++){
	char cell[2];
	scanf("%s",cell);
      }
    }
    int total_time_sales;
    scanf("%d",&total_time_sales);
    for(int i = 0; i < total_time_sales; i++){
      int item_id;
      int discounted_price;
      int sale_start_time;
      int sale_end_time;
      scanf("%d %d %d %d",
	    &item_id,
	    &discounted_price,
	    &sale_start_time,
	    &sale_end_time);
    }
  }
}
