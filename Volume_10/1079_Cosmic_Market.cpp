#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdio>
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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
 
static const double EPS = 1e-8;

struct Order{
  int type;
  int pos;
  int action;
  Order(int _t,int _p,int _a) : type(_t),pos(_p),action(_a) {}
};

int main(){
  int total_rows,total_cols,total_queries;

  while(~scanf("%d %d %d",&total_rows,&total_cols,&total_queries)){
    if(total_rows == 0 && total_cols == 0 && total_queries == 0) break;

    vector<Order> orders;
    bool is_used_row[50001];
    bool is_used_col[50001];
    memset(is_used_row,false,sizeof(is_used_row));
    memset(is_used_col,false,sizeof(is_used_col));
    ll remaining_row = total_rows;
    ll remaining_col = total_cols;

    for(int query_idx = 0; query_idx < total_queries; query_idx++){

      int order_type;
      int pos;
      int action;
      scanf("%d %d %d",&order_type,&pos,&action);
      orders.push_back(Order(order_type,pos,action));
    }

    ll occupied_seats = 0;
    for(int query_idx = total_queries -1; query_idx >= 0; query_idx--){
      
      //row
      if(orders[query_idx].type == 0){
	if(is_used_row[orders[query_idx].pos]) continue;

	is_used_row[orders[query_idx].pos] = true;

	//0:sit 1:stand up
	if(orders[query_idx].action == 1) {
	  occupied_seats += remaining_row;
	}
	remaining_col--;
      }

      //col
      else if(orders[query_idx].type == 1){
	if(is_used_col[orders[query_idx].pos]) continue;

	is_used_col[orders[query_idx].pos] = true;

	//0:sit 1:stand up
	if(orders[query_idx].action == 1) {
	  occupied_seats += remaining_col;
	}
	remaining_row--;
      }
    }
    printf("%lld\n",occupied_seats);
  }
}
