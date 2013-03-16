
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
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
//int cost[30][30][30][30];
//int visited[30][30];
int W,H;
 
int main()
{
    int dx,dy;
    int x=0,y=0;
    int rx=0,ry=0;
    int maxv = 0;
    int N;
    scanf("%d",&N);
    while(~scanf("%d %d",&dx,&dy)){
        if(dx == dy && dy==0){
            printf("%d %d\n",rx,ry);
            x = 0;
            y = 0;
            rx = 0;
            ry = 0;
            maxv = 0;
        }
 
        x += dx;
        y += dy;
        if(maxv < x*x+y*y){
            maxv = x*x+y*y;
            rx = x;
            ry = y;
        }
        else if(maxv == x*x+y*y){
            if(x > rx){
                rx = x;
                ry = y;
            }
        }
    }
}

