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

int main(){
  string str;
  while(cin >> str){
    string next_str = str;
    const string aid = "AIZUNYAN";

    for(int i=0;i<str.size();i++){
      string tmp = str.substr(i,8);
      int freq[256] = {};
      for(int j=0;j<8;j++) freq[tmp[j]]++;

      if(freq['A'] == 2
	 && freq['I'] == 1 
	 && freq['D'] == 1 
	 && freq['U'] == 1 
	 // && freq['N'] == 2
	 && freq['Y'] == 1
	 // && freq['A'] == 2
	 && freq['N'] == 2){ 
	for(int j=0;j<8;j++) next_str[i+j] = aid[j];
      }
    }
    cout << next_str << endl;
  }
}
