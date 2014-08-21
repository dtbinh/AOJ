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

class Info {
public:
  int _fare;
  int _time;
  int _company_id;
  Info() : _fare(0),_time(0),_company_id(0) {}
  Info(int fare,int time,int company_id)
    : _fare(fare),_time(time),_company_id(company_id) {}
};

Info lines[501][501];

int main(){
  int num_of_stations;
  int num_of_lines;
  int time_limit;
  int num_of_JAG_companies;
  while(~scanf("%d %d %d %d",
	       &num_of_stations,
	       &num_of_lines,
	       &time_limit,
	       &num_of_JAG_companies)){
    if(num_of_stations == 0
       && num_of_lines == 0 
       && time_limit == 0
       && num_of_JAG_companies == 0) break;

    for(int line_idx = 0; line_idx < num_of_lines; line_idx++){
      int from,to;
      int fare,time,company_id;
      scanf("%d %d %d %d %d",
	    &from,&to,&fare,&time,&company_id);
      lines[to][from] = lines[from][to] = Info(fare,time,company_id);
    }

    int station_near_S;
    int station_near_A;
    scanf("%d %d",&station_near_S,&station_near_A);

    int num_of_passports;
    scanf("%d",&num_of_passports);

    int passports[10];
    memset(passports,0x3f,sizeof(passports));
    for(int passport_idx = 0; passport_idx < num_of_passports; passport_idx++){
      int num_of_companies;
      int fare;
      scanf("%d %d",&num_of_companies,&fare);
      for(int company_idx=0; company_idx < num_of_companies; company_idx++){
	int company_id;
	scanf("%d",&company_id);
	passports[company_id] = fare;
      }
    }
  }
}
