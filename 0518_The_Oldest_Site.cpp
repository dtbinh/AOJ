
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
 
class Point{
public:
    int x;
    int y;
    Point(int _x,int _y) : x(_x), y(_y) {}
};
 
bool isHere[5001][5001];
 
int main(){
    int n;  
    while(~scanf("%d",&n)){
        if(n==0) break;
 
         
        memset(isHere,0,sizeof(isHere));
 
        vector<Point> pos;
        for(int i=0;i<n;i++){
            int x,y;
            scanf("%d %d",&x,&y);
            isHere[y][x] = true;
            pos.push_back(Point(x,y));
        }
 
        int res = 0;
        for(int p1=0;p1<pos.size();p1++){
            for(int p2=p1+1;p2<pos.size();p2++){
                int dx = pos[p2].x - pos[p1].x;
                int dy = pos[p2].y - pos[p1].y;
                 
                dx = dx < 0 ? -dx : dx;
                dy = dy < 0 ? -dy : dy;
 
                int p3x = pos[p2].x + dy;
                int p3y = pos[p2].y + dx;
 
                int p4x = pos[p1].x + dy;
                int p4y = pos[p1].y + dx;
 
                if(p3x > 5000 || p3y > 5000
                    || p4x > 5000 || p4y > 5000) continue;
 
                if(isHere[p3y][p3x] 
                    && isHere[p4y][p4x]){
                    res = max(res,dx*dx+dy*dy);
                }
            }
        }
 
        printf("%d\n",res);
    }
}

