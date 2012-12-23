
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
 
class Point{
public:
    double x;
    double y;
    Point() : x(0),y(0){}
    Point(double _x,double _y){
        x = _x;
        y = _y;
    }
};
 
class Region{
public:
    int larger_num;
    int smaller_num;
    double size;
    double x;
    double y;
    Region(double _x,double _y,double _size,int _larger_num,int _smaller_num){
        x = _x;
        y = _y;
        size = _size;
        larger_num = _larger_num;
        smaller_num = _smaller_num;
    }
 
    bool operator<(const Region& r) const{
        return larger_num < r.larger_num;
    }
};
 
void save(double x,double y,double size,const vector<Point>& points,priority_queue<Region>& que,int* maxv){
    int larger_num=0;
    int smaller_num=0;
    double cx = x + (size / 2.0);
    double cy = y + (size / 2.0);
 
    for(int i=0;i<points.size();i++){
        double d = sqrt((points[i].x - cx) * (points[i].x - cx)
            + (points[i].y - cy) * (points[i].y - cy));
        if(d <= 1.0) smaller_num++;
        if(d <= 1.0 + (size/2.0)*sqrt(2.0)) larger_num++;
    }
 
    if(*maxv >= larger_num) return;
    *maxv = max(*maxv,smaller_num);
 
    que.push(Region(x,y,size,larger_num,smaller_num));
}
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
        vector<Point> points;
        for(int i=0;i<n;i++){
            double x,y;
            scanf("%lf %lf",&x,&y);
            points.push_back(Point(x,y));
        }
 
        priority_queue<Region> que;
 
        int maxv = 1;
        save(0,0,10,points,que,&maxv);
 
        while(!que.empty()){
            Region re = que.top();
            int larger = re.larger_num;
            int smaller = re.smaller_num;
            double size = re.size;
            double x = re.x;
            double y = re.y;
 
            que.pop();
         
            save(x,y,size/2.0,points,que,&maxv);
            save(x+size/2.0,y,size/2.0,points,que,&maxv);
            save(x,y+size/2.0,size/2.0,points,que,&maxv);
            save(x+size/2.0,y+size/2.0,size/2.0,points,que,&maxv);
        }
 
        printf("%d\n",maxv);
    }
}

