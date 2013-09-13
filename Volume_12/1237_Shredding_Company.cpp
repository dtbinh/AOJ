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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};

class Node{
private:
  vector<string> constituents;
  int score;
public:
  
  int get_score() const { return score; }
  void print_result() {
    
    printf("%d ",score);
    for(int i=0;i<constituents.size();i++){
      if(i==0){
	cout << constituents[i];
      }
      else{
	cout << " " <<constituents[i];
      }
    }
    printf("\n");
  }
  Node(const string& _c) {
    constituents.push_back(_c);
    score = atoi(_c.c_str());
  }
  
  Node(const string& _c,int _s) : score(_s) {
    constituents.push_back(_c);
  }
  
  void cat(const string& _c,int _s){
    constituents.push_back(_c);
    score = score + _s;
  }
  void erase_last (int last_score){
    score -= last_score;
    constituents.pop_back();
  }
  
};

int main(){
  int target_num;
  string card;
  while(cin >> target_num >> card){
    if(target_num == 0 && card == "0") break;

    //1 ^(1) 2 ^(2) 2 ^(3) 4 ^(4)
    vector<Node> dp[100];
    for(int i=0;i<card.size();i++){
      dp[i].push_back(Node(card.substr(0,i+1)));
      for(int j=0;j<i;j++){
	//0->j j->i
	for(int k=0;k<dp[j].size();k++){
	  int rear = atoi(card.substr(j+1,i-j).c_str());
	  dp[j][k].cat(card.substr(j+1,i-j),rear);
	  dp[i].push_back(dp[j][k]);
	  dp[j][k].erase_last(rear);
	  // printf("%d %d\n",dp[j][k],rear);
	}
      }
    }

    Node res("",-1);
    bool reject = false;
    for(int i=0;i<dp[card.size()-1].size();i++){
      if(target_num >= dp[card.size()-1][i].get_score()){
	if(res.get_score() < dp[card.size()-1][i].get_score()){
	  res = dp[card.size()-1][i];
	  reject = false;
	}
	else if(res.get_score() == dp[card.size()-1][i].get_score()){
	  reject = true;
	}
      }
      // printf("%d\n",dp[card.size()-1][i]);
    }
    
    if(res.get_score() == -1){
      printf("error\n");
    }
    else if(reject){
      printf("rejected\n");
    }
    else{
      res.print_result();
    }
  }
}
