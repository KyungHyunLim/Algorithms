/*
마법사 상어와 파이어스톰

- 남아있는 얼음 A[r][c]의 합
- 남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수

1. 맵 재구성 (얼음 돌리기)
2. 얼음 녹는 것 반영

*/
#include <iostream>
#include <vector>
#include <queue>
 
#define MAX 70
#define endl "\n"
using namespace std;
 
int N, Q, Sum_Answer, Size_Answer;
int MAP[MAX][MAX];
bool Visit[MAX][MAX];
vector<int> Cmd;
 
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
 
int Max(int A, int B) { return A > B ? A : B; }
 
void Input()
{
    cin >> N >> Q;
    N = (1 << N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
            Sum_Answer += MAP[i][j];
        }
    }
    for (int i = 0; i < Q; i++)
    {
        int a; cin >> a;
        Cmd.push_back(a);
    }
}
 
void Turning(int a, int b, int Len)
{
    int Square = Len / 2;
    for (int Number = 0; Number < Square; Number++)
    {
        int Start_x = a + Number;
        int Start_y = b + Number;
        int End_x = a + Len - Number - 1;
        int End_y = b + Len - Number - 1;
 
        int x_Idx = End_x;
        int y_Idx = Start_y;
        int Idx = 0;
        vector<int> Temp;
        for (int i = Start_x; i < End_x; i++) Temp.push_back(MAP[i][Start_y]);
        for (int i = Start_x; i < End_x; i++) MAP[i][Start_y] = MAP[End_x][y_Idx++];
        for (int i = Start_y; i < End_y; i++) MAP[End_x][i] = MAP[x_Idx--][End_y];
        for (int i = End_x; i > Start_x; i--) MAP[i][End_y] = MAP[Start_x][y_Idx--];
        for (int i = End_y; i > Start_y; i--) MAP[Start_x][i] = Temp[Idx++];
    }
}
 
void Remake_MAP(int Len)
{
    for (int i = 0; i < N; i += Len)
    {
        for (int j = 0; j < N; j += Len)
        {
            Turning(i, j, Len);
        }
    }
}
 
void Melting_Ice()
{
    vector<pair<int, int>> V;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (MAP[i][j] == 0) continue;
 
            int Cnt = 0;
            for (int k = 0; k < 4; k++)
            {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
                if (MAP[nx][ny] == 0) continue;
                Cnt++;
            }
 
            if (Cnt < 3) V.push_back(make_pair(i, j));
        }
    }
 
    for (int i = 0; i < V.size(); i++)
    {
        int x = V[i].first;
        int y = V[i].second;
        MAP[x][y]--;
        Sum_Answer--;
    }
}
 
int BFS(int a, int b)
{
    queue<pair<int, int>> Q;
    Q.push(make_pair(a, b));
    Visit[a][b] = true;
    int Cnt = 1;
 
    while (Q.empty() == 0)
    {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
 
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < N && ny < N)
            {
                if (MAP[nx][ny] != 0 && Visit[nx][ny] == false)
                {
                    Visit[nx][ny] = true;
                    Q.push(make_pair(nx, ny));
                    Cnt++;
                }
            }
        }
    }
    return Cnt;
}
 
void Calculate_Ice_Size()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (MAP[i][j] == 0) continue;
            if (Visit[i][j] == true) continue;
            
            int Result = BFS(i, j);
            Size_Answer = Max(Size_Answer, Result);
        }
    }
}
 
void Solution()
{
    for (int i = 0; i < Q; i++)
    {
        int L = (1 << Cmd[i]);
        Remake_MAP(L);
        Melting_Ice();
    }
    Calculate_Ice_Size();
 
    cout << Sum_Answer << endl << Size_Answer << endl;
}
 
void Solve()
{
    Input();
    Solution();
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    //freopen("Input.txt", "r", stdin);
    Solve();
 
    return 0;
}
