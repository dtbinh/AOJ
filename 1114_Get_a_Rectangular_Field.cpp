
#define _USE_MATH_DEFINES
#define INF 100000000
 
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
 
 
static const double EPS = 1e-8;
 
int tx[] = {-1,0,1,0};
int ty[] = {0,1,0,-1};
 
int stage[5][5];
 
bool isFull(int x1,int y1,int x2,int y2){
    for(int y=y1;y<=y2;y++){
        for(int x=x1;x<=x2;x++){
            if(stage[y][x] != 1) return false; 
        }
    }
 
    return true;
}
 
int main()
{
    int n;
    while(~scanf("%d",&n)){
 
        for(int i=0;i<n;i++){
            for(int y=0;y<5;y++){
                for(int x=0;x<5;x++){
                    scanf("%d",&stage[y][x]);
                }
            }
            int res = 0;
            for(int y1=0;y1<5;y1++){
                for(int x1=0;x1<5;x1++){
                    for(int y2=y1;y2<5;y2++){
                        for(int x2=x1;x2<5;x2++){
                            if(isFull(x1,y1,x2,y2)){
                                res = max(res,(x2-x1+1)*(y2-y1+1));
                            }
                        }
                    }
                }
            }
            printf("%d\n",res);
        }
    }
 
}

