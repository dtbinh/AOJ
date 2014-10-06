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

vector<string> split(string delim,string str){
  vector<string> res;
  str += delim;
  for(int i=0;i<str.size();i++){
    for(int j=1;i+j<=str.size();j++){
      if(str.substr(i,j).find(delim) != string::npos){
	if(str.substr(i,j-1).size() >0 ) res.push_back(str.substr(i,j-1));
	i+=j-1;
	break;
      }
    }
  }
  return res;
}

bool is_leap_year(int year){
  if(year % 4 == 0){
    if(year % 100 != 0) return true;
    if(year % 400 == 0) return true;
  }
  return false;
}

int main(){
  string str;
  while(cin >> str){
    if(str == "#") break;
    int total_dots = count(str.begin(),str.end(),'.');
    if(total_dots == 2){
      //after christ
      vector<string> elements = split(".",str);
      int year = atoi(elements[0].c_str());
      int month = atoi(elements[1].c_str());
      int day = atoi(elements[2].c_str());

      int passed_day = 0;
      const int days_per_month[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
      for(int prev = 2012; prev < year; prev++){
	passed_day += (is_leap_year(prev) ? 366 : 365);
      }

      for(int prev = 1; prev < month; prev++){
	if(is_leap_year(year) && prev == 2){
	  passed_day++;
	}
	passed_day += days_per_month[prev];
      }
      for(int prev = 1; prev < day; prev++){
	passed_day++;
      }
      passed_day -= 355; //2012.01.01 - 2012.12.20
      cout << passed_day << endl;
    }
    else{
      //maya
      vector<string> elements = split(".",str);
      int b = atoi(elements[0].c_str());
      int ka = atoi(elements[1].c_str());
      int t = atoi(elements[2].c_str());
      int w = atoi(elements[3].c_str());
      int ki = atoi(elements[4].c_str());

      int passed_day = b * (20*18*20) + ka * (18*20) + w * 20 + ki;
      cout << passed_day << endl;
    }
  }
}
