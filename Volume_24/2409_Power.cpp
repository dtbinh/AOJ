
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
  
struct Data{
    int start;
    int end;
};
  
int main(){
    int N,M;
    while(~scanf("%d %d",&N,&M)){
        Data data[101];
        for(int i=0;i<M;i++){
            int s,e;
            scanf("%d %d",&s,&e);
            data[i].start = s;
            data[i].end = e;        
        }
  
        int stime = 1;
         
        bool used[101];
        memset(used,0,sizeof(used));
        int res = 0;
        while(1){
            int etime = stime;
            int idx = -1;
            for(int i=0;i<M;i++){
                if(!used[i] && data[i].start <= stime){
                    if(etime <= data[i].end){
                        etime = data[i].end;
                        idx = i;
                    }
                }
            }
  
            if(idx != -1 && etime < N) {
                used[idx] = true;
                stime = etime+1;
                res++;
            }
         
            else if(idx != -1 && etime >= N){
                res++;
                printf("%d\n",res);
                break;
            }
  
            else if(idx == -1){
                printf("Impossible\n");
                break;
            }
        }
  
    }
}

