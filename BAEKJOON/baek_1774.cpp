#include<iostream>
#include<vector>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;

struct point {
	double x;
	double y;
};

vector<int> parent;
vector<point> locations;
vector<vector<double>> edges;

double get_distance(point a, point b) {
	double p1 = a.x - b.x;
	double p2 = a.y - b.y;
	return sqrt((p1 * p1) + (p2 * p2));
}

int get_parent(int n) {
	if (parent[n] == n) {
		return n;
	}
	return get_parent(parent[n]);
}

void Union(int a, int b) {
	a = get_parent(a);
	b = get_parent(b);
	if (a < b) {
		parent[b] = a;
	}
	else {
		parent[a] = b;
	}
}

bool find_parent(int a, int b) {
	a = get_parent(a);
	b = get_parent(b);
	if (a == b) {
		return true;
	}
	else {
		return false;
	}
}

bool compare(vector<double> a, vector<double> b) {
	if (a[2] < b[2]) return true;
	else return false;
}

int main() {
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		double x, y;
		cin >> x >> y;

		locations.push_back({x,y});
	}

	int length = locations.size();


	for (int i = 0; i < length - 1; i++) {
		for (int j = i + 1; j < length; j++) {
			edges.push_back({(double)i+1,(double)j+1,get_distance(locations[i],locations[j]) });
		}
	}

	for (int i = 0; i <= n; i++) {
		parent.push_back(i);
	}

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		Union(a, b);
	}

	sort(edges.begin(), edges.end(), compare);

	double answer = 0;
	for (int i = 0; i < edges.size(); i++) {
		if (!find_parent((int)edges[i][0], (int)edges[i][1])) {
			Union((int)edges[i][0], (int)edges[i][1]);
			answer += edges[i][2];
		}
	}

	printf("%0.2lf", answer);
}