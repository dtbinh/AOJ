
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
 
class Data{
public:
    double x;
    double y;
    double r;
    Data(double _x,double _y,double _r){
        x = _x;
        y = _y;
        r = _r;
    }
};
 
bitset<10000> found; 
bool filled[400][400];
int main(){
    int n;
    int idx = 1;
    while(~scanf("%d",&n)){
        if(n==0) break;
 
        vector<Data> Points;
        memset(filled,0,sizeof(filled));
 
        for(int i=0;i<n;i++){
            double x,y,r;
            scanf("%lf %lf %lf",&x,&y,&r);
            Points.push_back(Data(x,y,r));
 
            //x=200; cx=20000;
            //x=0 cx=0;
            //r=200 ra=20000;
            //-20000<square<20000
 
            int cx = x*100.0;
            int cy = y*100.0;
            int ra = r*100.0; 
             
            for(int y=0;y<40000;y+=100){
                for(int x=0;x<40000;x+=100){
                    if(cx - ra + 20000 <= x && x+100 < cx+ra + 20000
                    && cy - ra + 20000 <= y && y+100 < cy+ra + 20000){
                        filled[y/100][x/100] = true;
                        continue;
                    }
                }
            }
        }
 
 
        int res=0;
 
 
        for(int y=0;y<40000;y+=100){
            for(int x=0;x<40000;x+=100){
                if(filled[y/100][x/100]){
                    res+= 10000;
                    continue;
                }
                else{
 
                    found.reset();
                    for(int i=0;i<Points.size();i++){
                        int cx = Points[i].x*100.0 + 20000;
                        int cy = Points[i].y*100.0 + 20000;
                        int ra = Points[i].r*100.0;
 
 
                        if(cx+ra < x || x+100 <= cx - ra) continue;
                        if(cy+ra < y || y+100 <= cy - ra) continue;
                        for(int dy= max(cy-ra,y);dy<min(cy+ra,y+100);dy++){
                            for(int dx = max(cx-ra,x);dx < min(cx+ra,x+100); dx++){
                                found[(dy-y)*100+(dx-x)] = true;
                            }
                        }
 
                    }
 
                    res += found.count();
 
                }
 
            }
        }
 
        printf("%d %.2lf\n",idx++,res/(double)10000);       
    }
}

