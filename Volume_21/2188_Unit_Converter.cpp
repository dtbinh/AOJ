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

const static char unit_prefix_name[][12] = {
  "yotta",
  "zetta",
  "exa",
  "peta",
  "tera",
  "giga",
  "mega",
  "kilo",
  "hecto",
  "deca",
  "deci",
  "centi",
  "milli",
  "micro",
  "nano",
  "pico",
  "femto",
  "ato",
  "zepto",
  "yocto",
};

const static int unit_prefix_powers[] = {
  24,
  21,
  18,
  15,
  12,
  9,
  6,
  3,
  2,
  1,
  -1,
  -2,
  -3,
  -6,
  -9,
  -12,
  -15,
  -18,
  -21,
  -24
};

void conv(const string& original,const string& unit){
  int power = 1;
  for(int i = 0; i < sizeof(unit_prefix_name)/(sizeof(char)*12); i++){
    if(string(unit_prefix_name[i]) == unit){
      power = unit_prefix_powers[i];
    }
  }

  int dot_pos = original.size();
  for(int i = 0; i < original.size(); i++){
    if(original[i] == '.'){
      dot_pos = i;
      break;
    }
  }
  int first_number_pos = 0;
  for(int i = 0; i < original.size(); i++){
    if(original[i] != '.' && original[i] != '0'){
      first_number_pos = i;
      break;
    }
  }

  cout << "dot_pos: " << dot_pos << endl;
  cout << "fn: " << first_number_pos << endl;
  cout << "pow: " <<power << endl;
  cout << "result: " << (dot_pos - first_number_pos - (dot_pos > first_number_pos ? 1 : 0)) + power << endl;
}

int main(){
  string str;
  while(getline(cin,str)){
    int total_test_cases = atoi(str.c_str());
    for(int test_i = 0; test_i < total_test_cases; test_i++){
      string line;
      getline(cin,line);
      vector<string> elements = split(" ",line);
      if(elements.size() == 3){
	conv(elements[0],elements[1]);
      }
      else{
	
      }
    }
  }
}
