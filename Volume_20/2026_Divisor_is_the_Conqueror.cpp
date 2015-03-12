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
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

map<vector<int>,bool> visited;
vector<int> answer;

bool dfs(int sum,int total_rank,vector<int>& cards,vector<int>& order){
  if(sum == total_rank){
    answer = order;
    return true;
  }
  bool res = false;
  if(visited.find(cards) != visited.end()) return false;

  visited[cards] = true;
  for(int i = 1; i <= 13; i++){
    if(cards[i] > 0 && sum % i == 0){
      cards[i]--;
      order.push_back(i);
      res |= dfs(sum + i,total_rank,cards,order);
      order.pop_back();
      cards[i]++;
    }
  }
  return res;
}

int main(){
  int num_of_cards;
  while(~scanf("%d",&num_of_cards)){
    if(num_of_cards == 0) break;

    vector<int> cards(14);
    int total_rank = 0;
    for(int i = 0; i < num_of_cards; i++){
      int rank;
      scanf("%d",&rank);
      cards[rank]++;
      total_rank += rank;
    }
    vector<int> order;
    bool isok = dfs(0,total_rank,cards,order);
    bool is_first = true;

    if(isok){
      for(int i = 0; i < answer.size(); i++){
	printf("%s%d",is_first ? "" : " ",answer[i]);
	is_first = false;
      }
      printf("\n");
    }
    else{
      printf("No\n");
    }
  }
}
