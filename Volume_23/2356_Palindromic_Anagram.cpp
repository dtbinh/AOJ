#define _USE_MATH_DEFINES
#include <cstdio>
#include <iostream>
#include <sstream>
#include <cmath>
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

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

static const double eps = 10e-8;

ll nCr(int n,int r){
  return (r==0 || n==r) ? 1 : nCr(n-1,r) + nCr(n-1,r-1);
}

int main(){
  string str;
  while(cin>>str){
    map<char,int> freq;
    for(int i=0;i<str.size();i++){
      freq[str[i]]++;
    }
    
    bool isok = true;
    ll sum=1;
    if(str.size() % 2 == 0){	
      int size = str.size() / 2;
      for(map<char,int>::iterator it = freq.begin(); it != freq.end(); it++){
	if(it->second % 2 != 0){
	  isok = false;
	  break;
	}
	else{
	  sum *= nCr(size,it->second / 2);
	  size -= it->second / 2;
	}
      }
    }
    else{
      int size = str.size() / 2;
      int c = 0;
      for(map<char,int>::iterator it = freq.begin(); it != freq.end(); it++){
	if(it->second % 2 != 0){
	  c++;
	  if(c>=2) isok = false;
	  if(it->second > 2){
	    sum *= nCr(size,(it->second - 1) / 2);
	    size -= (it->second - 1) / 2;
	  }
	}
	else{
	  sum *= nCr(size,it->second / 2);
	  size -= it->second / 2;
	}
      }
    }
    printf("%lld\n",isok ? sum : 0);
  }	
}

