#include<iostream>
#include<vector>

#define endl "\n"
#define MAX 20
using namespace std;

int N, M, Answer;
char MAP[MAX][MAX];

vector<pair<int, int>> Coin;

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

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
            if (MAP[i][j] == 'o') Coin.push_back(make_pair(i, j));    // ������ ��ǥ�� Vector�� ��
        }
    }
}

bool Range_Over(int a, int b)     // ������ �� ������ ������ ��� false�� ��ȯ, �ݴ��� ��� true�� ��ȯ�ϴ� �Լ�
{
    if (a < 0 || b < 0 || a >= N || b >= M) return true;
    return false;
}

void Move(int x, int y, int xx, int yy, int Cnt, int dir)    // ���������� ������ �����̴� �Լ�(����1x, ����1y, ����2x, ����2y, ��ư����Ƚ��, �����)��
{
    if (Answer < Cnt) return;            // ������ Ƚ������ �� ���� ��ư�� ���ȴٸ� �� �̻� �غ� �ʿ䰡 ����. (�ּҰ��� �ƴϹǷ�)
    if (Cnt > 10)                        // 10�� �̻��� ���, ���̻� ������ �ʿ䰡 ����.
    {
        Answer = Min(Answer, Cnt);        // ������ Ƚ���� ���ؼ� ���� ���Ÿ� �����ְ� �״�� ����.
        return;
    }

    int nx = x + dx[dir];
    int ny = y + dy[dir];
    int nxx = xx + dx[dir];
    int nyy = yy + dy[dir];

    if (Range_Over(nx, ny) == true && Range_Over(nxx, nyy) == true) return;    // �� ���� ��� �������ٸ� �״�� ����.
    else if (Range_Over(nx, ny) == true && Range_Over(nxx, nyy) == false)    // �� ������ �������� ���
    {
        Answer = Min(Answer, Cnt);
        return;
    }
    else if (Range_Over(nx, ny) == false && Range_Over(nxx, nyy) == true)     // �� ������ �������� ��� 
    {
        Answer = Min(Answer, Cnt);
        return;
    }

    if (MAP[nx][ny] == '#')        // ������ ���� ���� ��� ������ ������ �� ����.
    {
        nx = x;
        ny = y;
    }
    if (MAP[nxx][nyy] == '#')
    {
        nxx = xx;
        nyy = yy;
    }

    for (int i = 0; i < 4; i++)        // �� ���� ����������� 
    {
        Move(nx, ny, nxx, nyy, Cnt + 1, i);
    }
}

void Solution()
{
    for (int i = 0; i < 4; i++)
    {
        int x = Coin[0].first;
        int y = Coin[0].second;
        int xx = Coin[1].first;
        int yy = Coin[1].second;

        Move(x, y, xx, yy, 1, i);
    }
}

void Solve()
{
    Input();
    Solution();

    if (Answer > 10) Answer = -1;
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
