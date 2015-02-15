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
  int parts[8];
  sscanf(hex,"%2x%2x%2x%2x",
	 parts,parts+1,parts+2,parts+3);

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
  int sign = (bin[0] == '1' ?  -1 : +1);

  int integers = 0;;
  int int_mul = 1;
  for(int i = 1 + 24 - 1,j = 0; i >= 1; i--,j++){
    if(bin[i] == '1'){
      integers += int_mul;
    }
    int_mul *= 2;
  }

  double dec_mul = 0.5;
  double decimals = 0.0;
  for(int i = 25; i < 32; i++){
    if(bin[i] == '1'){
      decimals += dec_mul;
    }
    dec_mul *= 0.5;
  }

  char tmp_decimals[10];
  sprintf(tmp_decimals,"%.10lf",decimals);
  int r_pos = 10;
  int l_pos = 1;
  for(int i = 10; i >= 0; i--){
    if(tmp_decimals[i] != '0'){
      r_pos = i;
      break;
    }
    r_pos = i;
  }
  
  string res = "";
  stringstream ss;
  res += (sign < 0 ? "-" : "");
  ss << integers;
  res += ss.str();
  if(l_pos == r_pos) r_pos++;
  for(int i = l_pos; i <= r_pos; i++){
    res.push_back(tmp_decimals[i]);
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
