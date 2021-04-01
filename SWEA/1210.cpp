/*
[S/W 문제해결 기본] 2일차 - Ladder1

도착지에서 거꾸로 이동 출발지 
dfs -> 왼쪽/오른쪽의 경우 우선 적으로 이동, 위로 이동

*/
#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

int map[100][100];
bool visited[100][100];
int target[2];

int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };
int ans;

bool isok(int x, int y) {
	if (x < 0 || x >= 100 || y < 0 || y >= 100) {
		return true;
	}
	return false;
}

void search(int i, int j) {
	visited[i][j] = true;
	if (i == 0) {
		ans = j;
		return;
	}
	else {
    // 반복문으로 표현 가능
    /*
    for(int z=0; z<3; z++){
      int nx = i + dx[z];
      int ny = j + dy[z];
      
      if(isok(nx,ny)) continue;
      if(map[nx][ny] && !visited[nx][ny]){
        visited[nx][ny] = true;
        search(nx, ny);
        return;
      }
    }
    */
		int rightx = i + dx[0];
		int righty = j + dy[0];
		int leftx = i + dx[1];
		int lefty = j + dy[1];
		int upx = i + dx[2];
		int upy = j + dy[2];
		
		if (!isok(rightx, righty) && map[rightx][righty] == 1 && !visited[rightx][righty]) {
			visited[rightx][righty] = true;
			search(rightx, righty);
			return;
		}
		if (!isok(leftx, lefty) && map[leftx][lefty] == 1 && !visited[leftx][lefty]) {
			visited[leftx][lefty] = true;
			search(leftx, lefty);
			return;
		}
		if (!isok(upx, upy) && map[upx][upy] == 1 && !visited[upx][upy]) {
			visited[upx][upy] = true;
			search(upx, upy);
			return;
		}
	}
}

int main(int argc, char** argv)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int T;

	for (int test_case = 1; test_case <= 10; ++test_case)
	{
		ans = -1;
		memset(visited, false, sizeof(visited));
		cin >> T;

		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				cin >> map[i][j];
				if (map[i][j] == 2) {
					target[0] = i;
					target[1] = j;
				}
			}
		}

		search(target[0], target[1]);
	
		cout << "#" << test_case << " " << ans << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
