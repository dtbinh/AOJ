
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
 
int par[1001];
int curr[1001];
 
void init(){
    for(int i=0;i<=1000;i++){
        par[i] = i;
        curr[i] = -1;
    }
}
 
bool isSat(string question,map<int,string>& name,map<string,int>& num){
    string str;
    stringstream ss(question);
    vector<string> v;
    while(ss >> str){
        v.push_back(str);
    }
 
    string X = v[0];
    string Y = v[5].substr(0,v[5].size()-1);
 
    //X is a child of Y.
    //X is the parent of Y.
    //X is a sibling of Y.
    //X is a descendant of Y.
    //X is an ancestor of Y.
 
    if(v[3] == "child"){
        return (par[num[X]] == num[Y] && num[Y] != -1);
    }
    else if(v[3] == "parent"){
        return (par[num[Y]] == num[X] && num[X] != -1);
    }
    else if(v[3] == "sibling"){
        return (par[num[Y]] == par[num[X]] && par[num[X]] != -1);
    }
    else if(v[3] == "ancestor"){
        while(par[num[Y]] != -1){
            Y = name[par[num[Y]]];
            if(X == Y) return true;
        }
        return false;
    }
    else if(v[3] == "descendant"){
        while(par[num[X]] != -1){
            X = name[par[num[X]]];
            if(X == Y) return true;
        }
 
        return false;
    }
 
    return false;
}
 
int main(){
    string str;
 
    while(getline(cin,str)){
        init();
        stringstream ss(str);
        ss >> str;
        int n = atoi(str.c_str());
        ss >> str;
        int m = atoi(str.c_str());
 
 
        if(n==0 && m==0) break;
 
        map<int,string> name;
        map<string,int> num;
 
        for(int i=0;i<n;i++){
            getline(cin,str);
 
             
            int j=0;
            while(str[j] == ' ') j++;
            name[i] = str.substr(j,str.size()-j);
            num[str.substr(j,str.size()-j)] = i;
 
            if(j==0){
                par[i] = -1;
            }
            else par[i] = curr[j-1];
            //cout << str << endl;
 
            curr[j] = i;
        }
 
        for(int i=0;i<m;i++){
            getline(cin,str);
            if(isSat(str,name,num)){
                printf("True\n");
            }
            else{
                printf("False\n");
            }
        }
        printf("\n");
    }
}

