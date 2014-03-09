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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

int main(){
  int total_hotels;
  int total_days;
  while(~scanf("%d %d",
	       &total_hotels,
	       &total_days)){
    int price_table[51][51];
    memset(price_table,0,sizeof(price_table));

    for(int hotel_idx=1;hotel_idx<=total_hotels;hotel_idx++){
      for(int day=1;day<=total_days;day++){
	int price;
	scanf("%d",&price);
	price_table[hotel_idx][day] = price;
      }
    }
  }
}
