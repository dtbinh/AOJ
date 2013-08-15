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

class Packet{
public:
  int time,src,dst;
  Packet(int _t,int _s,int _d) : time(_t),src(_s),dst(_d){}
  bool operator<(const Packet& p) const{
    return time < p.time;
  }
  bool operator>(const Packet& p) const{
    return time > p.time;
  }
};

int main(){
  int computer_num,send_list_num;
  while(~scanf("%d %d",&computer_num,&send_list_num)){
    if(computer_num == 0 && send_list_num == 0) break;

    vector<Packet> packets;
    for(int i=0;i<send_list_num;i++){
      int time,src,dst;
      scanf("%d %d %d",&time,&src,&dst);
      packets.push_back(Packet(time,src,dst));
    }

    sort(packets.begin(),packets.end());
    
    bool infected[20001];
    memset(infected,0,sizeof(infected));
    infected[1] = true;
    for(int i=0;i<packets.size();i++){
      if(infected[packets[i].src]){
	infected[packets[i].dst] = true;
      }
    }

    int res = 0;
    for(int i=1;i<=computer_num;i++){
      if(infected[i]) res++;
    }

    printf("%d\n",res);
  }
}
