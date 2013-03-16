
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
 
class Card{
public:
    string color;
    int num;
 
    Card() : color(""),num(0){}
    bool operator<(const Card& c) const{
        if(color == c.color){
            return num < c.num;
        }
        return color < c.color;
    }
};
 
int main(){
    int n;
 
    while(~scanf("%d",&n)){
 
        for(int idx=0;idx<n;idx++){
            vector<Card> cards;
            int num[10];
            for(int j=0;j<9;j++){
                scanf("%d",&num[j]);
            }
 
            string str;
            for(int j=0;j<9;j++){
                cin >> str;
                Card c;
                c.color = str;
                c.num = num[j];
 
                cards.push_back(c);
            }
 
            sort(cards.begin(),cards.end());
 
            bool fail = false;
 
            for(int i=0;i<9;){
                int prev_num = cards[i].num;
                string prev_c = cards[i].color;
 
                bool isok = true;
                //3つ連続
                for(int j=0;j<2;j++){            
                    if(cards[i+j+1].num == prev_num
                        && cards[i+j+1].color == prev_c){
 
                    }
                    else{
                        isok = false;
                        break;
                    }
                    prev_num = cards[i+j+1].num;
                    prev_c = cards[i+j+1].color;
 
                }
 
                if(isok) {
                    i+=3;
                    continue;
                }
 
                isok = true;
 
                //昇順
                for(int j=0;j<2;j++){
                    if(cards[i+j+1].num == prev_num + 1
                        && cards[i+j+1].color == prev_c){
 
                    }
                    else{
                        isok = false;
                        break;
                    }
 
                    prev_num = cards[i+j+1].num;
                    prev_c = cards[i+j+1].color;
                }
 
                if(isok){
                    i+=3;
                    continue;
                }
 
                isok = true;
 
                if(i+6 >= 9){
                    fail = true;
                    break;
                }
 
                //七対子           
                for(int j=0;j<6;j+=2){
                    if(cards[i+j].color == cards[i+j+1].color
                        && cards[i+j].num == cards[i+j+1].num){
 
                    }
                    else{
                        isok = false;
                    }
                }
 
                if(isok){
                    i+=6;
                    continue;
                }
 
                fail = true;
                break;
            }
 
            printf("%d\n",fail ? 0 : 1);
        }
 
    }
}

