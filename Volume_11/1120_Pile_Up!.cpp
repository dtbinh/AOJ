
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
 
void printPile(deque<int>* pile,int n){
    for(int i=1;i<=n;i++){
        printf("%d:",i);
        for(int j=0;j<pile[i].size();j++){
            printf("%3d",pile[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
        deque<int> pile[101];
        for(int i=1;i<=n;i++){
            pile[i].push_back(i);
        }
        while(1){
            int from,to;
            scanf("%d %d",&from,&to);
 
            if(from == 0 && to == 0) break;
 
            if(from == to) continue;
 
            int fNum=0,fPos=0;
            int tNum=0,tPos=0;
 
            //search pick up cube pos
            for(int j=1;j<=n;j++){
                for(int k=0;k<pile[j].size();k++){
                    if(pile[j][k] == from){
                        fNum = j;
                        fPos = k;
                    }
 
                    if(pile[j][k] == to){
                        tNum = j;
                        tPos = k;
                    }
                }
            }
 
            if(tNum == fNum){
                if(fPos < tPos) continue;
            }
 
            if(to == 0 && fPos == pile[fNum].size() -1) continue;
 
            //pick up
            vector<int> tmp;
            for(int j=0;j<fPos;j++){
                tmp.push_back(pile[fNum][j]);
            }
            reverse(tmp.begin(),tmp.end());
 
 
            pile[fNum].erase(pile[fNum].begin(),pile[fNum].begin() + fPos + 1);
             
            for(int j=0;j<tmp.size();j++){
                pile[tmp[j]].push_front(tmp[j]);
            }
 
            for(int j=1;j<=n;j++){
                for(int k=0;k<pile[j].size();k++){
                    if(pile[j][k] == to){
                        tNum = j;
                        tPos = k;
                    }
                }
            }
 
            if(tNum == 0){
                tNum = from;
            }
 
            pile[tNum].push_front(from);
 
            //printPile(pile,n);
        }
 
        vector<int> h;
        for(int i=1;i<=n;i++){
            if(pile[i].size() >= 1) h.push_back(pile[i].size());
        }
 
        sort(h.begin(),h.end());
 
        for(int i=0;i<h.size();i++){
            printf("%d\n",h[i]);
        }
        printf("end\n");
    }
}

