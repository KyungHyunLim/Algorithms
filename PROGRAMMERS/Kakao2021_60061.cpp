#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

bool Pillar[102][102];
bool Bar[102][102];

bool checkPillar(int x, int y){
    if(y== 0 || Pillar[x][y-1]) return true;
    if((x > 0 && Bar[x-1][y]) || Bar[x][y]) return true;
    return false;
}

bool checkBar(int x, int y){
    if(Pillar[x][y-1] || Pillar[x+1][y-1]) return true;
    if (x > 0 && Bar[x-1][y] && Bar[x+1][y]) return true;  
    return false;
}

bool canDelete(int x, int y){
    for (int i=max(x-1, 0); i<= x+1; i++){
        for(int j=y; j<= y+1; j++){
            if(Pillar[i][j] && checkPillar(i, j) == false) return false;
            if(Bar[i][j] && checkBar(i, j)== false) return false;
        }
    }
    return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    
    memset(Pillar, 0, sizeof(Pillar));
    memset(Bar, 0, sizeof(Bar));
    
    for(auto build : build_frame){
        int x = build[0], y = build[1];
        int type = build[2], cmd = build[3];
        
        if (type == 0){
            if (cmd == 1){
                if (checkPillar(x,y))
                    Pillar[x][y] = true;
            } else{
                Pillar[x][y] = false;
                if (canDelete(x, y) == false) Pillar[x][y] = true;
            }
        } else{
            if (cmd == 1){
                if (checkBar(x,y))
                    Bar[x][y] = true;
            }else{
                Bar[x][y] = false;
                if (canDelete(x, y) == false) Bar[x][y] = true;
            }
        }
    }
    
    for (int x = 0; x <= n; x++){
        for (int y = 0; y <= n; y++){
            if(Pillar[x][y]) answer.push_back({x, y, 0});
            if(Bar[x][y]) answer.push_back({x,y,1});
        }
    }
    
    return answer;
}
