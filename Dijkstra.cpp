#include <cstdio>
#include <vector>
#pragma warning(disable:4996)
using namespace std;

typedef pair<int, int> ii;
vector<ii> a[1001];
int dist[1001];
int visited[1001];
int inf = 987654321;

int main() {
	int n, m;
	int u, v, cost;
	int start, end;
	for (int i = 0; i < 1001; ++i)
		dist[i] = inf;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d", &u, &v, &cost);
		a[u].push_back(ii(v, cost));
	}
	scanf("%d%d", &start, &end);
	dist[start] = 0;
	for (int i = 0; i < n - 1; ++i) {
		int c;
		int min = inf + 1;
		for (int j = 1; j <= n; ++j) {
			if (visited[j] == 0 && dist[j] < min) {
				min = dist[j];
				c = j;

			}
		}
		visited[c] = 1;
		for (int j = 0; j < (int)a[c].size(); ++j) {
			int n = a[c][j].first;
			if (dist[n] > dist[c] + a[c][j].second)
				dist[n] = dist[c] + a[c][j].second;

		}
	}
	printf("%d\n", dist[end]);
	return 0;


}
