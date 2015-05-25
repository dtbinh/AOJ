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
#include <complex>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-12;

int main(){
  int total_test_cases;
  while(~scanf("%d",&total_test_cases)){
    for(int test_i = 0; test_i < total_test_cases; test_i++){
      int total_staff;
      int speech_duration,prohibited_duration;

      scanf("%d %d %d",&total_staff,
	    &speech_duration,&prohibited_duration);
      int customer_x,customer_y;
      scanf("%d %d",&customer_x,&customer_y);
      complex<int> customer(customer_x,customer_y);

      vector<complex<int> > staff;
      for(int staff_i = 0; staff_i < total_staff; staff_i++){
	int x,y;
	scanf("%d %d",&x,&y);
	staff.push_back(complex<int>(x,y));
      }
      
      int latest_speech_finished_time[1001];
      memset(latest_speech_finished_time,-1,sizeof(latest_speech_finished_time));
      queue<int> que;
      for(int staff_i = 0; staff_i < total_staff; staff_i++){
	if((staff[staff_i].real() - customer.real()) * (staff[staff_i].real() - customer.real())
	   + (staff[staff_i].imag() - customer.imag()) * (staff[staff_i].imag() - customer.imag()) > 100) continue;
	que.push(staff_i);
	latest_speech_finished_time[staff_i] = speech_duration;
      }
      
      vector<int> edges[1001];
      for(int staff_i = 0; staff_i < total_staff; staff_i++){
	for(int staff_j = 0; staff_j < total_staff; staff_j++){
	  if(staff_i == staff_j) continue;
	  if((staff[staff_i].real() - staff[staff_j].real()) * (staff[staff_i].real() - staff[staff_j].real())
	     + (staff[staff_i].imag() - staff[staff_j].imag()) * (staff[staff_i].imag() - staff[staff_j].imag()) > 2500) continue;
	  edges[staff_i].push_back(staff_j);
	}
      }

      bool isok = false;
      for(int round = 0; round < 100000; round++){
	queue<int> next;
	bool visited[1001] = {};
	while(!que.empty()){
	  int staff_i = que.front();
	  que.pop();
	  for(int i = 0; i < edges[staff_i].size(); i++){
	    int staff_j = edges[staff_i][i];
	    if(latest_speech_finished_time[staff_j] == -1 
	       || (latest_speech_finished_time[staff_j] + prohibited_duration
		   < latest_speech_finished_time[staff_i])){
	      if(visited[staff_j]) continue;
	      next.push(staff_j);
	      visited[staff_j] = true;
	      latest_speech_finished_time[staff_j]
		= latest_speech_finished_time[staff_i] + speech_duration;
	    }
	  }
	}
	if(next.empty()){
	  isok = true;
	  break;
	}
	que = next;
      }
      
      int res = 0;
      for(int i = 0; i < total_staff; i++){
	res = max(res,latest_speech_finished_time[i]);
      }
      if(isok){
	printf("%d\n",res);
      }
      else{
	printf("You're always welcome!\n");
      }
    }
  }
}
