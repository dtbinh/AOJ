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

string hex2bin(const char hex[256]){
  int parts[4];
  sscanf(hex,"%2x%2x%2x%2x",parts,parts+1,parts+2,parts+3);

  string res = "";
  for(int i = 0; i < 4; i++){
    string tmp = "";
    for(int j = 0; j < 8; j++){
      tmp.push_back((parts[i] % 2) ? '1' : '0');
      parts[i] /= 2;
    }
    reverse(tmp.begin(),tmp.end());
    res += tmp;
  }
  return res;
}

string bin2dec(const string& bin){
  double sign = (bin[0] == '1' ?  -1 : +1);

  double integers = 0.0;
  double mul = 1.0;
  for(int i = 1 + 24 - 1,j = 0; i >= 1; i--,j++){
    if(bin[i] == '1'){
      integers += mul;
    }
    mul *= 2.0;
  }

  mul = 0.5;
  double decimals = 0.0;
  for(int i = 25; i < 32; i++){
    if(bin[i] == '1'){
      decimals += mul;
    }
    mul *= 0.5;
  }

  string res = "";
  stringstream ss;
  ss << sign * (integers + decimals);
  res += ss.str();
  if(decimals == 0){
    res += ".0";
  }
  return res;
}

int main(){
  int N;
  while(~scanf("%d",&N)){
    for(int i = 0; i < N; i++){
      char hex[256];
      scanf("%s",hex);
      string bin = hex2bin(hex);
      cout << bin2dec(bin) << endl;
    }
  }
}
