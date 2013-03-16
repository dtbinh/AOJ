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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
 
static const int MAX_N = 1000000;
bool isPrime[MAX_N];
 
class Ticket{
public:
  int mMoney;
  string mNumber;
  Ticket(int _m, string _num){
    mMoney = _m;
    mNumber = _num;
  }
};
 
int main(){
  int n,m;
 
  while(~scanf("%d %d",&n,&m)){
    if(n==0) break;
    vector<Ticket> tickets;
    for(int i=0;i<n;i++){
      string number;
      int money;
      cin >> number >> money;
      tickets.push_back(Ticket(money,number));
    }
 
    int sum = 0;
    for(int i=0;i<m;i++){
      string str;
      cin >> str;       
      int prize = 0;
      for(int j=0;j<tickets.size();j++){       
	bool isok = true;
	for(int k=tickets[j].mNumber.size()-1;k>=0;k--){                 
	  if(tickets[j].mNumber[k] != str[k]
	     && tickets[j].mNumber[k] != '*'){
	    isok = false;
	    break;
	  }
	}
 
	if(isok) prize = max(tickets[j].mMoney,prize);
      }
 
      sum += prize;
    }
 
    printf("%d\n",sum);
  }
}
