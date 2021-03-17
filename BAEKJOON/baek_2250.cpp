#define MAX(A,B) A > B ? A : B;
#define MIN(A,B) A < B ? A : B;

#include<iostream>
#include<string.h>
#include<queue>
#include<vector>
using namespace std;

struct Node {
	int parent = -1;
	int level;
	int col;
	int left;
	int right;
};

vector<Node> tree[10002];
vector<Node> level_list[20];
int max_level;
int col;

void in_order(int n, int level) {
	//왼쪽
	if (tree[n][0].left != -1) {
		in_order(tree[n][0].left,level + 1);
	}

	//level 및 col 정보 입력
	tree[n][0].level = level;
	tree[n][0].col = col;
	level_list[level].push_back(tree[n][0]);
	col++;
	max_level = MAX(max_level, level);

	//오른쪽
	if (tree[n][0].right != -1) {
		in_order(tree[n][0].right, level + 1);
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N;
	cin >> N;
	//tree 생성

	for (int i = 0; i <= N; i++) {
		Node temp;
		tree[i].push_back(temp);
	}
	max_level = 0;
	col = 1;

	for (int i = 0; i < N; i++) {
		int n, l, r;
		cin >> n >> l >> r;

		Node temp;
		tree[n][0].parent = -1;
		tree[n][0].col = 0;
		tree[n][0].level = 0;
		tree[n][0].left = l;
		tree[n][0].right = r;
	}

	for (int i = 1; i <= N; i++) {
		if (tree[i][0].left != -1) {
			tree[tree[i][0].left][0].parent = i;
		}
		if (tree[i][0].right != -1){
			tree[tree[i][0].right][0].parent = i;
		}
	}
	
	//root 찾기
	int root;
	for (int i = 1; i <= N; i++) {
		if (tree[i][0].parent == -1) {
			root = i;
			break;
		}
	}
	
	//level and col update
	in_order(root,1);

	//calc
	int answer_level = 100;
	int answer_width = 1;
	for (int i = 2; i <= max_level; i++) {
		int diff = level_list[i][level_list[i].size() - 1].col - level_list[i][0].col + 1;
		if (answer_width < diff) {
			answer_width = diff;
			answer_level = i;
		}
	}

	if(answer_width == 1) cout << 1 << " " << 1 << endl;
	else cout << answer_level << " " << answer_width << endl;
	
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}