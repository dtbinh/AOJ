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

int R(int i,int S,int A,int C){
  if(i == 0) return S;
  return (A * R(i-1,S,A,C) + C) % 256;
}

int O(int* I,int i,int S,int A,int C){
  return (I[i] + R(i,S,A,C)) % 256;
}

double H(int* freq,int N){
  double sum = 0.0;
  for(int i=0;i<256;i++){
    if(freq[i] == 0) continue;
    sum += ((double)freq[i]/(double)N)*log((double)freq[i]/(double)N);
    // printf("%lf\n",sum);
    // printf("%lf\n",((double)freq[i]/(double)N)*log((double)freq[i]/(double)N));
  }
  return -sum;
}

int main(){
  int freq[256];
  int I[320];
  int N;

  while(~scanf("%d",&N)){
    if(N==0) break;

    for(int i=1;i<=N;i++){
      scanf("%d",I+i);
    }

    double min_H = 100000.0;
    int res_S = 0;
    int res_A = 0;
    int res_C = 0;
    for(int S=0;S<=15;S++){
      for(int A=0;A<=15;A++){
	for(int C=0;C<=15;C++){
	  memset(freq,0,sizeof(freq));
	  for(int i=1;i<=N;i++){
	    // printf("i=%d I[i]=%d S=%d A=%d C=%d O=%d\n",i,I[i],S,A,C,O(I,i,S,A,C));
	    freq[O(I,i,S,A,C)]++;
	  }
	  double tmp_H = H(freq,N);
	  if(min_H > tmp_H + EPS){
	    // printf("%lf\n",tmp_H);
	    min_H = tmp_H;
	    res_S = S;
	    res_A = A;
	    res_C = C;
	  }
	}
      }
    }
    printf("%d %d %d\n",res_S,res_A,res_C);
  }
}
