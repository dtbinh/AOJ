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

static const int FACT_MAX = 1500;

void multiply(int res[5001],int num){
  int carry = 0;
  for(int i=0;i<5001;i++){
    int sum = res[i] * num + carry;
    carry = sum / 10;
    res[i] = sum % 10;
  }
}

void add(int res[5001],int num){

  int tmp[5001];
  memset(tmp,0,sizeof(tmp));

  for(int i=0;i<5001;i++){
    tmp[i] = num % 10;
    num /= 10;
  }
  
  int carry = 0;
  for(int i=0;i<5001;i++){
    res[i] += tmp[i] + carry;
    carry = res[i] / 10;
    res[i] %= 10;
  }
}

void printNum(int res[5001]){
  bool flag = false;
  for(int i=5000;i>=0;i--){
    if(res[i] != 0){
      flag = true;
    }
    if(flag){
      printf("%d",res[i]);
    }
  }
  printf("\n");
}

int main(){

  int n;
  while(~scanf("%d",&n)){
    int res[5001];
    memset(res,0,sizeof(res));
    res[0] = 1;
    for(int i=1;i<=FACT_MAX;i++){
      multiply(res,i);
    }

    add(res,2);
    printNum(res);
    for(int i=0;i<n;i++){
      printf("%d\n",i+2);
    }
  }
}
