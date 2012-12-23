
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
 
char table[5][6];
char latice[10][6];
char vline[5][6];
char hline[5][6];
char key[51];
 
void rotate_table(int angle,char arg_table[5][6]){
    double theta = ((double)angle / 180.0)*M_PI;
    char tmp[5][6];
    memset(tmp,'\0',sizeof(tmp));
    for(int y=0;y<5;y++){
        for(int x=0;x<5;x++){
            double dx = (double)x*cos(theta) - (double)y*sin(theta);
            double dy = (double)x*sin(theta) + (double)y*cos(theta);
 
            if(angle == 90) dx += 4.0;
            else if(angle == 180){
                dx += 4.0;
                dy += 4.0;
            }
            else if(angle == 270){
                dy += 4.0;
            }
            tmp[(int)(dy < 0 ? dy - EPS : dy + EPS)][(int)(dx < 0 ? dx - EPS : dx + EPS)] = arg_table[y][x];
        }
    }
 
    //printf("angle:%d\n",angle);
    //printf("orig:\n");
    //for(int y=0;y<5;y++){
    //  for(int x=0;x<5;x++){
    //      printf("%c",arg_table[y][x]);
    //  }
    //  printf("\n");
    //}
 
    //printf("rotate:\n");
    //for(int y=0;y<5;y++){
    //  for(int x=0;x<5;x++){
    //      printf("%c",tmp[y][x]);
    //  }
    //  printf("\n");
    //}
 
    memcpy(arg_table,tmp,sizeof(char)*30);
}
 
void mirror(char arg_vline[5][6]){
    char tmp[6];
    memset(tmp,'\0',sizeof(tmp));
    memcpy(tmp,arg_vline[4],sizeof(char)*6);
    memcpy(arg_vline[4],arg_vline[0],sizeof(char)*6);
    memcpy(arg_vline[0],tmp,sizeof(char)*6);
 
    memcpy(tmp,arg_vline[3],sizeof(char)*6);
    memcpy(arg_vline[3],arg_vline[1],sizeof(char)*6);
    memcpy(arg_vline[1],tmp,sizeof(char)*6);
}
 
bool isVisited(map<string,bool>& visited_stage){  
    memset(key,'\0',sizeof(key));
    for(int i=0;i<5;i++) strcat(key,hline[i]);
    for(int i=0;i<5;i++) strcat(key,vline[i]);
 
    if(visited_stage.find(key) != visited_stage.end()) return true;
     
    //original
    visited_stage[key] = true;
 
    char tmp_hline[5][6];
    char tmp_vline[5][6];
    char tmp[5][6];
    memset(tmp_hline,'\0',sizeof(tmp_hline));
    memset(tmp_vline,'\0',sizeof(tmp_vline));
     
    memcpy(tmp_hline,hline,sizeof(char)*30);
    memcpy(tmp_vline,vline,sizeof(char)*30);
 
    //rotate 90 degrees
    rotate_table(90,hline);
    rotate_table(90,vline);
 
    memset(tmp,'\0',sizeof(tmp));
    memcpy(tmp,hline,sizeof(char)*30);
    memcpy(hline,vline,sizeof(char)*30);
    memcpy(vline,tmp,sizeof(char)*30);
 
    memset(key,'\0',sizeof(key));
    for(int i=0;i<5;i++) strcat(key,hline[i]);
    for(int i=0;i<5;i++) strcat(key,vline[i]);
 
    visited_stage[key] = true;
     
    memcpy(hline,tmp_hline,sizeof(char)*30);
    memcpy(vline,tmp_vline,sizeof(char)*30);
 
    //rotate 180 degrees
    rotate_table(180,hline);
    rotate_table(180,vline);
 
    memset(key,'\0',sizeof(key));
    for(int i=0;i<5;i++) strcat(key,hline[i]);
    for(int i=0;i<5;i++) strcat(key,vline[i]);
 
    visited_stage[key] = true;
 
    memcpy(hline,tmp_hline,sizeof(char)*30);
    memcpy(vline,tmp_vline,sizeof(char)*30);
 
    //rotate 270 degrees
    rotate_table(270,hline);
    rotate_table(270,vline);
 
    memset(tmp,'\0',sizeof(tmp));
    memcpy(tmp,hline,sizeof(char)*30);
    memcpy(hline,vline,sizeof(char)*30);
    memcpy(vline,tmp,sizeof(char)*30);
 
    memset(key,'\0',sizeof(key));
    for(int i=0;i<5;i++) strcat(key,hline[i]);
    for(int i=0;i<5;i++) strcat(key,vline[i]);
 
    visited_stage[key] = true;
     
    memcpy(hline,tmp_hline,sizeof(char)*30);
    memcpy(vline,tmp_vline,sizeof(char)*30);
 
     
 
    //mirror
    mirror(vline);
    mirror(hline);
 
    memset(key,'\0',sizeof(key));
    for(int i=0;i<5;i++) strcat(key,hline[i]);
    for(int i=0;i<5;i++) strcat(key,vline[i]);
 
    visited_stage[key] = true;
 
    char mirror_hline[5][6];
    char mirror_vline[5][6];
 
    memcpy(mirror_hline,hline,sizeof(char)*30);
    memcpy(mirror_vline,vline,sizeof(char)*30);
 
    //mirror rotate 90 degrees
    rotate_table(90,hline);
    rotate_table(90,vline);
 
    memset(tmp,'\0',sizeof(tmp));
    memcpy(tmp,hline,sizeof(char)*30);
    memcpy(hline,vline,sizeof(char)*30);
    memcpy(vline,tmp,sizeof(char)*30);
 
    memset(key,'\0',sizeof(key));
    for(int i=0;i<5;i++) strcat(key,hline[i]);
    for(int i=0;i<5;i++) strcat(key,vline[i]);
 
    visited_stage[key] = true;
     
    memcpy(hline,mirror_hline,sizeof(char)*30);
    memcpy(vline,mirror_vline,sizeof(char)*30);
 
    //mirror rotate 180 degrees
    rotate_table(180,hline);
    rotate_table(180,vline);
 
    memset(key,'\0',sizeof(key));
    for(int i=0;i<5;i++) strcat(key,hline[i]);
    for(int i=0;i<5;i++) strcat(key,vline[i]);
 
    visited_stage[key] = true;
 
    memcpy(hline,mirror_hline,sizeof(char)*30);
    memcpy(vline,mirror_vline,sizeof(char)*30);
 
 
    //mirror rotate 270 degrees
    rotate_table(270,hline);
    rotate_table(270,vline);
 
    memset(tmp,'\0',sizeof(tmp));
    memcpy(tmp,hline,sizeof(char)*30);
    memcpy(hline,vline,sizeof(char)*30);
    memcpy(vline,tmp,sizeof(char)*30);
 
    memset(key,'\0',sizeof(key));
    for(int i=0;i<5;i++) strcat(key,hline[i]);
    for(int i=0;i<5;i++) strcat(key,vline[i]);
 
    visited_stage[key] = true;
 
     
    memcpy(hline,tmp_hline,sizeof(char)*30);
    memcpy(vline,tmp_vline,sizeof(char)*30);
 
     
 
    //printf("vline:\n");
    //for(int i=0;i<5;i++){
    //  
    //  for(int j=0;j<5;j++){
    //      printf("%d",vline[i][j]);
    //  }
    //  printf("\n");
    //}
 
    //printf("hline:\n");
    //for(int i=0;i<5;i++){
    //  
    //  for(int j=0;j<5;j++){
    //      printf("%d",hline[i][j]);
    //  }
    //  printf("\n");
    //}
 
    return false;
}
 
bool isValid(int state){
    if(state == 0) return true;
 
    else if(state == 1){
        if(table[0][0] == '0'+'1') return true;
        else return false;
    }
 
    else if(state == 2){
        if(table[0][1] == '0'+'1') return true;
        else return false;
    }
 
    else if(state == 3){
        for(int x=0;x<2;x++){
            if(table[1][x] != '0'+'1') return false;
        }
        return true;
    }
 
    else if(state == 4){
        for(int y=0;y<2;y++){
            if(table[y][2] != '0'+'1') return false;
        }
        return true;
    }
 
    else if(state == 5){
        for(int x=0;x<3;x++){
            if(table[2][x] != '0'+'1') return false;
        }
        return true;
    }
 
    else if(state == 6){
        for(int y=0;y<3;y++){
            if(table[y][3] != '0'+'1') return false;
        }
        return true;
    }
 
    else if(state == 7){
        for(int x=0;x<4;x++){
            if(table[3][x] != '0'+'1') return false;
        }
        return true;
    }
 
    else if(state == 8){
        for(int y=0;y<4;y++){
            if(table[y][4] != '0'+'1') return false;
        }
        return true;
    }
 
    else if(state == 9){
        for(int x=0;x<5;x++){
            if(table[4][x] != '0'+'1') return false;
        }
        return true;
    }
 
    else return true;
}
 
 
 
int dfs(int state,int visited,map<string,bool>& visited_stage){
    if(state == 10 && !isVisited(visited_stage)) return 1;
 
    int res = 0;
 
    for(int i=0;i<10;i++){
        if(visited & (1<<i)) continue;
        if(state % 2){
            //state:1,3,5,7,9
            //fill horizonal
            for(int j=0;j<5;j++){
                table[state/2][j] += latice[i][j];
                hline[state/2][j] += latice[i][j];
            }
 
            if(isValid(state)) res += dfs(state+1,visited | (1<<i),visited_stage);
 
            for(int j=0;j<5;j++){
                table[state/2][j] -= latice[i][j];
                hline[state/2][j] -= latice[i][j];
            }
 
            for(int j=0,k=4;j<5;j++,k--){
                table[state/2][j] += latice[i][k];
                hline[state/2][j] += latice[i][k];
            }
 
            if(isValid(state)) res += dfs(state+1,visited | (1<<i),visited_stage);
 
            for(int j=0,k=4;j<5;j++,k--){
                table[state/2][j] -= latice[i][k];
                hline[state/2][j] -= latice[i][k];
            }
             
        }
        else{
            //state:0,2,4,6,8
            //fill vertical
            for(int j=0;j<5;j++){
                table[j][state/2] += latice[i][j];
                vline[j][state/2] += latice[i][j];
            }
 
            if(isValid(state)) res += dfs(state+1,visited | (1<<i),visited_stage);
 
            for(int j=0;j<5;j++){
                table[j][state/2] -= latice[i][j];
                vline[j][state/2] -= latice[i][j];
            }
 
            for(int j=0,k=4;j<5;j++,k--){
                table[j][state/2] += latice[i][k];
                vline[j][state/2] += latice[i][k];
            }
 
            if(isValid(state)) res += dfs(state+1,visited | (1<<i),visited_stage);
 
            for(int j=0,k=4;j<5;j++,k--){
                table[j][state/2] -= latice[i][k];
                vline[j][state/2] -= latice[i][k];
            }
        }
    }
 
    return res;
}
 
int main(){
    while(~scanf("%s",&latice[0])){
        if(strcmp(latice[0],"END")==0) break;
        for(int i=1;i<=9;i++){
            scanf("%s",latice+i);
        }
 
        map<string,bool> visited_stage;
        memset(table,'\0',sizeof(table));
        memset(hline,'\0',sizeof(hline));
        memset(vline,'\0',sizeof(vline));
        printf("%d\n",dfs(0,0,visited_stage));
    }
}

