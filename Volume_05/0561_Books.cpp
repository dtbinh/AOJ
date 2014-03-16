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
  int total_books;
  int total_sell_books;
  while(~scanf("%d %d",
	       &total_books,
	       &total_sell_books)){
    vector<int> books[11];
    for(int book_idx=0;book_idx<total_books;book_idx++){
      int price,category;
      scanf("%d %d",&price,&category);
      books[category].push_back(price);
    }

    for(int category=1;category<=10;category++){
      sort(books[category].begin(),books[category].end(),greater<int>());
    }

    int dp[2001];
    memset(dp,0,sizeof(dp));
    for(int category=1;category<=10;category++){
      for(int sell=total_sell_books;sell>=0;sell--){
	int sum = 0;
	for(int book_idx=0;book_idx<books[category].size();book_idx++){
	  if(sell + (book_idx+1) > total_sell_books) continue;
	  int price = books[category][book_idx];
	  sum += price;
	  dp[sell+(book_idx+1)] = max(dp[sell] + sum + (book_idx+1)*book_idx,
				      dp[sell+(book_idx+1)]);
	}
      }
    }
    printf("%d\n",dp[total_sell_books]);
  }
}
