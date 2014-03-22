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

int pos;

int digits(const string& str){
  int scalar = 1;
  string num_str="";
  while(isdigit(str[pos])){
    num_str += str[pos];
    pos++;
  }

  return atoi(num_str.c_str());
}

int equation(const string& str){
  int res = 0;
  vector<int> nums;
  if(pos < str.size() && str[pos] == '['){
    pos++;

    while(str[pos] != ']'){
      int num = equation(str);
      nums.push_back(num);
    }

    pos++;
    sort(nums.begin(),nums.end());
    for(int i=0;i<(nums.size()+1)/2;i++){
      res += nums[i];
    }
    return res;
  }
  else if(pos < str.size() && isdigit(str[pos])){
    int num = digits(str);
    return num / 2 + 1;
  }
  else{
    return res;
  }
}



int main(){
  int N;
  
  scanf("%d",&N);
  for(int i=0;i<N;i++){
    string str;
    cin >> str;
    pos=0;
    printf("%d\n",equation(str));
  }
}
