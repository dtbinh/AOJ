
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
    double x;
    double y;
    double z;
    Point(double _x,double _y,double _z) : x(_x),y(_y),z(_z){}
};
 
bool diff(double a,double b){
    return abs(a-b) < 0.1;
}
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        for(int i=0;i<n;i++){
            double QR,RP,PQ;
            scanf("%lf %lf %lf",&QR,&RP,&PQ);
 
            int c;
            scanf("%d",&c);
            vector<Point> points;
            for(int j=0;j<c;j++){
                double x,y,z;
                scanf("%lf %lf %lf",&x,&y,&z);
                points.push_back(Point(x,y,z));
            }
 
            double minv = numeric_limits<double>::max();
            int resP,resQ,resR;
            for(int p=0;p<points.size();p++){
                for(int q=0;q<points.size();q++){
                    if(p==q) continue;
                    for(int r=0;r<points.size();r++){
                        if(q==r || r== p) continue;
 
                        double cQRx = abs(points[q].x - points[r].x);
                        double cQRy = abs(points[q].y - points[r].y);
                        double cQRz = abs(points[q].z - points[r].z);
                        double cQR = sqrt(cQRx * cQRx +  cQRy * cQRy + cQRz * cQRz);
 
                        double cRPx = abs(points[r].x - points[p].x);
                        double cRPy = abs(points[r].y - points[p].y);
                        double cRPz = abs(points[r].z - points[p].z);
                        double cRP = sqrt(cRPx * cRPx +  cRPy * cRPy + cRPz * cRPz);
 
                        double cPQx = abs(points[p].x - points[q].x);
                        double cPQy = abs(points[p].y - points[q].y);
                        double cPQz = abs(points[p].z - points[q].z);
                        double cPQ = sqrt(cPQx * cPQx +  cPQy * cPQy + cPQz * cPQz);
 
                        if(diff(cRP/RP,cQR/QR) && diff(cPQ/PQ,cQR/QR) && diff(cPQ/PQ,cRP/RP)){
                            printf("%d %d %d\n",p+1,q+1,r+1);
                            goto next;
                        }
                    }
                }
            }
next:;
 
        }
    }
}

