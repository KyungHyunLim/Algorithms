/*
S/W 문제해결 기본] 4일차 - 길찾기

간단한 DFS 문제
원하는 도착지가 나오면 종료
*/
#include<iostream>
#include<cstring>
using namespace std;

int map[100][100];
bool visited[100];
bool ans;
int N;

void dfs(int x){
	visited[x] = true;
    if(x==99){
        ans = true;
        return;
    }
    for(int i=1; i<100; i++){
        if(!visited[i] && map[x][i]) 
            dfs(i);
    }	
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
    for(int i=0; i<10; i++){
        cin >>T >> N;

        ans = false;
        memset(visited, false, sizeof(visited));
        memset(map, 0, sizeof(map));

        for(int i=0; i<N; i++){
            int x, y;
            cin >> x >> y;
            map[x][y] = 1;
        }

        dfs(0);
      
        cout << "#" << T << " ";
        cout << (ans ? 1:0) << endl;
    }
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
