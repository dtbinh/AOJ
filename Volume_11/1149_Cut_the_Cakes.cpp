
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
 
static const float EPS = 1e-8;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
class Cake{
public:
    int birth;
    int W;
    int H;
    Cake(int _W,int _H,int _b){
        W = _W;
        H = _H;
        birth = _b;
    }
    bool operator<(const Cake& c) const{
        if(birth != c.birth) return birth < c.birth;
        else return W*H < c.H*c.W;
    }
 
    bool operator>(const Cake& c) const{
        if(birth != c.birth) return birth > c.birth;
        else return W*H > c.H*c.W;
    }
};
 
class mycmp{
public:
    bool operator()(const Cake& c1,const Cake& c2) const{
        return c1.H*c1.W < c2.H*c2.W;
    }
};
 
int main(){
    int n,w,d;
    while(~scanf("%d %d %d",&n,&w,&d)){
        if(n==w && w==d && d==0) break;
        vector<Cake> cakes;
        cakes.push_back(Cake(w,d,0));
 
        for(int i=1;i<=n;i++){
             
            int id,dist;
            scanf("%d %d",&id,&dist);
 
            int wc=0,hc=0;
            int ry=0,rx=0;
            dist %= (cakes[id-1].W*2+cakes[id-1].H*2);
            while(1){
                dist -= cakes[id-1].W;
                if(dist < 0){
                    rx += abs(dist);
                    break;
                }
                wc++;
                dist -= cakes[id-1].H;
                if(dist < 0){
                    ry += abs(dist);
                    break;
                }
                hc++;
            }
 
            if(wc == 0 || (wc == 1 && hc == 1)){
                Cake c1(cakes[id-1].W-rx,cakes[id-1].H,i);
                Cake c2(rx,cakes[id-1].H,i);
                cakes.erase(cakes.begin()+id-1);
                cakes.push_back(c1);
                cakes.push_back(c2);
                sort(cakes.begin(),cakes.end());
 
            }
            else{
                Cake c1(cakes[id-1].W,cakes[id-1].H-ry,i);
                Cake c2(cakes[id-1].W,ry,i);
                cakes.erase(cakes.begin()+id-1);
                cakes.push_back(c1);
                cakes.push_back(c2);
                sort(cakes.begin(),cakes.end());
            }
        }
 
        sort(cakes.begin(),cakes.end(),mycmp());
 
        for(int i=0;i<cakes.size();i++){
            printf("%s%d",i==0 ? "" : " ",cakes[i].W*cakes[i].H);
        }
 
        printf("\n");
    }
}

