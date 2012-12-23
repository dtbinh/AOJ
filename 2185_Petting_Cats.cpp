
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
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        for(int i=0;i<n;i++){
            int sx,sy,W,H;
            scanf("%d %d %d %d",&sx,&sy,&W,&H);
            int N;
            scanf("%d",&N);
            int count = 0;
            for(int j=0;j<N;j++){
                int x,y;
                scanf("%d %d",&x,&y);
                if(x < sx || x > sx+W
                    || y < sy || y > sy+H){
                        continue;
                }
 
                count++;
            }
 
            printf("%d\n",count);
        }
    }
}

