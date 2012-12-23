
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
 
class Pos{
public:
    int x;
    int y;
    Pos(int _x,int _y) : x(_x),y(_y){}  
};
 
bool used[500];
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
        memset(used,0,sizeof(used));
        vector<Pos> flags;
 
        for(int i=0;i<n;i++){
            int x,y;
            scanf("%d %d",&x,&y);
            flags.push_back(Pos(x,y));
        }
 
 
        double dist = 0.0;
        Pos mdir(0,1);
        Pos prev(0,0);
 
        for(int i=0;i<n;i++){
 
            double minv = 100.0;
            int next = -1;
 
            double lineDist = numeric_limits<double>::max();
 
            for(int j=0;j<n;j++){
                if(used[j]) continue;
                int line_dirx = flags[j].x-prev.x;
                int line_diry = flags[j].y-prev.y;
 
                double tmpDist = sqrt((double)(flags[j].x-prev.x)*(flags[j].x-prev.x) 
                + (double)(flags[j].y-prev.y)*(flags[j].y-prev.y));
 
                //double na = sqrt((double)mdir.x*mdir.x+(double)mdir.y*mdir.y);
                //double nb = sqrt((double)line_dirx*line_dirx+(double)line_diry*line_diry);
 
                double ab = mdir.x*line_dirx + mdir.y*line_diry;
                double axb = mdir.x*line_diry - mdir.y*line_dirx;
   
                double angle = atan2(axb,ab);
 
                if(angle <= 0.0 + EPS & abs(angle) < abs(minv)){
                    next = j;
                    minv = angle;   
                    lineDist = tmpDist;
                }
 
                else if(minv - EPS < angle && angle < minv + EPS){
                    if(tmpDist < lineDist){
                        next = j;
                        lineDist = tmpDist;
                    }                           
                }
            }
 
            if(next==-1) break;
 
            dist += sqrt((double)(flags[next].x-prev.x)*(flags[next].x-prev.x) 
                + (double)(flags[next].y-prev.y)*(flags[next].y-prev.y));
            mdir = Pos(flags[next].x-prev.x,flags[next].y-prev.y);
 
            prev = Pos(flags[next].x,flags[next].y);        
            used[next] = true;
        }
        //dist *= 10.0;
        //dist = floor(dist);
        //dist /= 10;
        printf("%.1lf\n",dist);
    }
}

