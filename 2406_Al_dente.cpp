
#define _USE_MATH_DEFINES
#define INF 100000000
  
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
    int N,T,E;
    while(~scanf("%d %d %d",&N,&T,&E)){
        int clock[101];
        for(int i=0;i<N;i++){        
            scanf("%d",clock+i);        
        }
  
        bool isok = false;
        for(int i=0;i<N;i++){
            for(int j=clock[i];j<=T+E;j+=clock[i]){
                if(T-E<=j && j<=T+E){
                    printf("%d\n",i+1);
                    isok = true;
                    goto next;
                }
            }
        }
  
        if(!isok) printf("%d\n",-1);
next:;
    }
    return 0;
}

