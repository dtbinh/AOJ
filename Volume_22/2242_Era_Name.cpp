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

int main(){
  int N,Q;
  while(~scanf("%d %d",&N,&Q)){
    if(N==0 && Q==0) break;

    map<string,int> StartWestYear;
    map<int,string> StartWestYearName;
    map<string,int> EraBasedYearUpperBounds;
    vector<int> WesternBasedYears;
    for(int i=0;i<N;i++){
      string EraName;
      int EraBasedYear,WesternYear;
      cin >> EraName >> EraBasedYear >> WesternYear;
      StartWestYear[EraName] = WesternYear - EraBasedYear + 1;
      StartWestYearName[WesternYear - EraBasedYear + 1] = EraName;

      EraBasedYearUpperBounds[EraName] = max(EraBasedYear,EraBasedYearUpperBounds[EraName]);
      WesternBasedYears.push_back(WesternYear - EraBasedYear + 1);
    }

    WesternBasedYears.push_back(0);
    WesternBasedYears.push_back(INF);
    sort(WesternBasedYears.begin(),WesternBasedYears.end());

    for(int i=0;i<Q;i++){
      int year;
      cin >> year;

      string res = "Unknown";
      for(int year_idx=0;year_idx+1 < WesternBasedYears.size();year_idx++){

	// year := 2000
	// [1990(year_idx's year) ~ 2050)
	if(WesternBasedYears[year_idx] <= year && year < WesternBasedYears[year_idx+1]){
	  if(year_idx == 0) break;

	  if(StartWestYearName.find(WesternBasedYears[year_idx]) != StartWestYearName.end()){
	    ostringstream oss;

	    if(EraBasedYearUpperBounds[StartWestYearName[WesternBasedYears[year_idx]]]
	       < year - WesternBasedYears[year_idx] + 1) break;

	    oss << (StartWestYearName[WesternBasedYears[year_idx]])
		<< " " 
		<< (year - WesternBasedYears[year_idx] + 1);
	    res = oss.str();
	    break;
	  }
	}
      }

      printf("%s\n",res.c_str());
    }
  }
}
