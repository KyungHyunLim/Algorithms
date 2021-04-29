/*
게임 맵 최단거리

간단한 bfs 문제
*/

#include<vector>
#include<cstring>
#include<queue>
#include<algorithm>
#include<iostream>
using namespace std;

int N, M;
int ans;
bool visited[101][101];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

void bfs(vector<vector<int>>& map, int x, int y){
    queue<pair<int, pair<int,int>>> q;
    q.push(make_pair(1,make_pair(x,y)));
    visited[x][y] = true;

    while(!q.empty()){
        int depth = q.front().first;
        int cx = q.front().second.first;
        int cy = q.front().second.second;
        q.pop();
        
        if(cx == N-1 && cy == M-1) {
            ans = depth;
            return;
        }
        
        for(int i=0; i<4; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            // 맵밖으로 못나감
            if(nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
            // 벽으로는 못감
            if(map[nx][ny] == 0) continue;
            // 이미 방문한 곳은 갈 필요 없음
            if(visited[nx][ny]) continue;
            visited[nx][ny] = true;
            q.push(make_pair(depth+1, make_pair(nx,ny)));
        }
    }
}

int solution(vector<vector<int> > maps)
{
    ans = 987654321;
    memset(visited, false, sizeof(visited));
    N = maps.size();
    M = maps[0].size();
    
    bfs(maps, 0, 0);
    if(ans == 987654321) return -1;
    return ans;
}
