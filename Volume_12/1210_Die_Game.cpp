
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
 
class Dice{
    int top;
    int left;
    int right;
    int bottom;
    int front;
    int rear;
 
public:
    Dice(){
        top = 1;
        front = 2;
        left = 3;
        bottom = 6;
        right = 4;
        rear = 5;
    }
    void rotateDice(string dir){
        if(dir == "north"){
            //top2fr
            //fr2bot
            //bot2rear
            //rear2top
 
            int tmp_front = top;
            int tmp_bottom = front;
            int tmp_rear = bottom;
            int tmp_top = rear;
 
            front = tmp_front;
            bottom = tmp_bottom;
            rear = tmp_rear;
            top = tmp_top;
        }
 
        else if(dir == "south"){
            //top2fr
            //fr2bot
            //bot2rear
            //rear2top
 
            int tmp_front = bottom;
            int tmp_bottom = rear;
            int tmp_rear = top;
            int tmp_top = front;
 
            front = tmp_front;
            bottom = tmp_bottom;
            rear = tmp_rear;
            top = tmp_top;
        }
        else if(dir == "west"){
            int tmp_bottom = left;
            int tmp_top = right;
            int tmp_left = top;
            int tmp_right = bottom;
 
            bottom = tmp_bottom;
            top = tmp_top;
            left = tmp_left;
            right = tmp_right;
        }
 
        else if(dir == "east"){
            int tmp_bottom = right;
            int tmp_top = left;
            int tmp_left = bottom;
            int tmp_right = top;
 
            bottom = tmp_bottom;
            top = tmp_top;
            left = tmp_left;
            right = tmp_right;
        }
    }
 
    int tellTop() const{
        return top;
    }
};
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
        Dice d;
        for(int i=0;i<n;i++){
            char buf[8];
            scanf("%s",buf);
            d.rotateDice(buf);
        }
 
        printf("%d\n",d.tellTop());
    }
}

