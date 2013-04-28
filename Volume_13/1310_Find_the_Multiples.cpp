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

void GenerateSequence(int N,int S,int W,char* seq){
  int g = S;
  for(int i=0; i<N; i++) {
    seq[i] = ((g/7) % 10) + '0';
    if( g%2 == 0 ) { g = (g/2); }
    else           { g = (g/2) ^ W; }
  }
}

int ComputePatterns(const char* seq,int N,int Q){
  int remainder = 0;
  map<int,int> dp;
  dp[0] = 1;

  int res = 0;
  int pow = 1;

  for(int i=0;i<N;i++){
    remainder += ((seq[i]-'0') * pow) % Q;
    remainder %= Q;
    pow *= 10;
    pow %= Q;
    if(seq[i]-'0') res += dp[remainder];
    dp[remainder]++;
  }

  return res;
}

int ComputePatterns25(const char* seq,int N,int Q){
  int non_zero_num = 0;

  int res = 0;
  for(int i=N-1;i>=0;i--){
    if(seq[i]-'0') non_zero_num++;
    if((seq[i]-'0')%Q==0) res += non_zero_num;
  }
  return res;
}


char seq[100001];
int main(){
  int N,S,W,Q;
  while(~scanf("%d %d %d %d",&N,&S,&W,&Q)){
    if(N==0 && S==0 && W==0 && Q==0) break;

    memset(seq,'\0',sizeof(seq));
    GenerateSequence(N,S,W,seq);

    reverse(seq,seq+strlen(seq));
    
    printf("%d\n",(Q == 2 || Q == 5) 
	   ? ComputePatterns25(seq,N,Q)
	   : ComputePatterns(seq,N,Q));
  }
}
