#include<iostream>
#include<vector>

#define endl "\n"
#define MAX 8
using namespace std;

int N, M, CCTV_Num, Answer;
int MAP[MAX][MAX];
int C_MAP[MAX][MAX];

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

vector<pair<pair<int, int>, pair<int, int>>> V;

int Min(int A, int B) { if (A < B) return A; return B; }

void Input()
{
    Answer = 99999999;
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
            if (1 <= MAP[i][j] && MAP[i][j] <= 5)
            {
                V.push_back(make_pair(make_pair(i, j), make_pair(MAP[i][j], -1)));
            }
        }
    }
    CCTV_Num = V.size();
}

void Copy_MAP()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            C_MAP[i][j] = MAP[i][j];
        }
    }
}

void Right(int x, int y)
{
    for (int i = y + 1; i < M; i++)
    {
        if (C_MAP[x][i] == 6) break;
        if (1 <= C_MAP[x][i] && C_MAP[x][i] <= 5) continue;

        C_MAP[x][i] = -1;
    }
}

void Left(int x, int y)
{
    for (int i = y - 1; i >= 0; i--)
    {
        if (C_MAP[x][i] == 6) break;
        if (1 <= C_MAP[x][i] && C_MAP[x][i] <= 5) continue;

        C_MAP[x][i] = -1;
    }
}

void Down(int x, int y)
{
    for (int i = x + 1; i < N; i++)
    {
        if (C_MAP[i][y] == 6) break;
        if (1 <= C_MAP[i][y] && C_MAP[i][y] <= 5) continue;

        C_MAP[i][y] = -1;
    }
}

void Up(int x, int y)
{
    for (int i = x - 1; i >= 0; i--)
    {
        if (C_MAP[i][y] == 6) break;
        if (1 <= C_MAP[i][y] && C_MAP[i][y] <= 5) continue;

        C_MAP[i][y] = -1;
    }
}

void Check_CCTV_Area()
{
    Copy_MAP();
    for (int i = 0; i < V.size(); i++)
    {
        if (V[i].second.first == 1)
        {
            if (V[i].second.second == 0) Right(V[i].first.first, V[i].first.second);
            else if (V[i].second.second == 1) Left(V[i].first.first, V[i].first.second);
            else if (V[i].second.second == 2) Down(V[i].first.first, V[i].first.second);
            else if (V[i].second.second == 3) Up(V[i].first.first, V[i].first.second);
        }
        else if (V[i].second.first == 2)
        {
            if (V[i].second.second == 0 || V[i].second.second == 1)
            {
                Right(V[i].first.first, V[i].first.second);
                Left(V[i].first.first, V[i].first.second);
            }
            else if (V[i].second.second == 2 || V[i].second.second == 3)
            {
                Up(V[i].first.first, V[i].first.second);
                Down(V[i].first.first, V[i].first.second);
            }
        }
        else if (V[i].second.first == 3)
        {
            if (V[i].second.second == 0)
            {
                Up(V[i].first.first, V[i].first.second);
                Right(V[i].first.first, V[i].first.second);
            }
            else if (V[i].second.second == 1)
            {
                Right(V[i].first.first, V[i].first.second);
                Down(V[i].first.first, V[i].first.second);
            }
            else if (V[i].second.second == 2)
            {
                Down(V[i].first.first, V[i].first.second);
                Left(V[i].first.first, V[i].first.second);
            }
            else if (V[i].second.second == 3)
            {
                Left(V[i].first.first, V[i].first.second);
                Up(V[i].first.first, V[i].first.second);
            }
        }
        else if (V[i].second.first == 4)
        {
            if (V[i].second.second == 0)
            {
                Left(V[i].first.first, V[i].first.second);
                Up(V[i].first.first, V[i].first.second);
                Right(V[i].first.first, V[i].first.second);
            }
            else if (V[i].second.second == 1)
            {
                Up(V[i].first.first, V[i].first.second);
                Right(V[i].first.first, V[i].first.second);
                Down(V[i].first.first, V[i].first.second);
            }
            else if (V[i].second.second == 2)
            {
                Right(V[i].first.first, V[i].first.second);
                Down(V[i].first.first, V[i].first.second);
                Left(V[i].first.first, V[i].first.second);
            }
            else if (V[i].second.second == 3)
            {
                Down(V[i].first.first, V[i].first.second);
                Left(V[i].first.first, V[i].first.second);
                Up(V[i].first.first, V[i].first.second);
            }
        }
        else if (V[i].second.first == 5)
        {
            Right(V[i].first.first, V[i].first.second);
            Left(V[i].first.first, V[i].first.second);
            Up(V[i].first.first, V[i].first.second);
            Down(V[i].first.first, V[i].first.second);
        }
    }
}

int NumOfSecretArea()
{
    int Sum = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (C_MAP[i][j] == 0) Sum++;
        }
    }
    return Sum;
}

void Set_CCTV_Direction(int Cnt)
{
    if (Cnt == CCTV_Num)
    {
        Check_CCTV_Area();
        Answer = Min(Answer, NumOfSecretArea());
        return;
    }

    V[Cnt].second.second = 0;
    Set_CCTV_Direction(Cnt + 1);

    V[Cnt].second.second = 1;
    Set_CCTV_Direction(Cnt + 1);

    V[Cnt].second.second = 2;
    Set_CCTV_Direction(Cnt + 1);

    V[Cnt].second.second = 3;
    Set_CCTV_Direction(Cnt + 1);
}

void Solution()
{
    Set_CCTV_Direction(0);
}

void Solve()
{
    Input();
    Solution();

    cout << Answer << endl;
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