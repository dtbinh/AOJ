
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
 
class Node{
public:
    int x;
    int y;
    Node(int _x,int _y){
        x = _x;
        y = _y;
    }
};
 
bool check(const vector<Node>& s1,const vector<Node>& s2){
    if(s1.size() != s2.size()) return false;
 
    int isok = 0;
    int dX = s2.begin()->x - s1.begin()->x;
    int dY = s2.begin()->y - s1.begin()->y;
 
 
    for(int i=0;i<s1.size();i++){
        if((s2[i].x - s1[i].x) != dX || (s2[i].y - s1[i].y) != dY) isok |= 1;
    }
 
    dX = (s2.begin())->x - (s1.end()-1)->x;
    dY = (s2.begin())->y - (s1.end()-1)->y;
 
    for(int i=0,j=s1.size()-1;i<s1.size();i++,j--){
        if((s2[i].x - s1[j].x) != dX || (s2[i].y - s1[j].y) != dY) isok |= (1<<1);
    }
 
    return (isok != (1<<2)-1);
}
int main(){
 
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
        int m;
        scanf("%d",&m);
 
        vector<Node> L0;
        for(int i=0;i<m;i++){
            int x,y;
            scanf("%d %d",&x,&y);
            L0.push_back(Node(x,y));
        }
 
        vector< vector<Node> > Ls;
 
        Ls.push_back(L0);
 
        for(int i=1;i<=3;i++){
            vector<Node> L;
            for(int j=0;j<L0.size();j++){
                double dx = L0[j].x * cos(i*90.0*(M_PI/180.0)) - L0[j].y * sin(i*90.0*(M_PI/180.0));
                double dy = L0[j].x * sin(i*90.0*(M_PI/180.0)) + L0[j].y * cos(i*90.0*(M_PI/180.0));
                dx = (dx <= 0 ? dx - EPS : dx + EPS);
                dy = (dy <= 0 ? dy - EPS : dy + EPS);
                L.push_back(Node(dx,dy));
            }
            Ls.push_back(L);
        }
 
         
        for(int i=0;i<n;i++){
            vector<Node> L;
            scanf("%d",&m);
            for(int j=0;j<m;j++){
                int x,y;
                scanf("%d %d",&x,&y);
                L.push_back(Node(x,y));
            }
 
            for(int j=0;j<4;j++){
                if(check(Ls[j],L)){
                    printf("%d\n",i+1);
                    break;
                }
            }
 
        }
        printf("+++++\n");
    }
}

