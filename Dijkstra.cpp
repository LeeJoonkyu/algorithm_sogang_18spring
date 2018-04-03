#include <cstdio>
#include <algorithm>
#include <vector>
#pragma warning(disable:4996)
using namespace std;
int map[1001][1001];
int way[1001];
int dist[1001];
int visited[1001];
int INF = 987654321;
void print_way(int, int);
int main() {
	int n, m;
	int u, v, cost;
	int start, end;


	for (int i = 0; i < 1001; i++) {
		for (int j = 0; j < 1001; j++) {
			map[i][j] = INF;
		}
		dist[i] = INF;
	}//인접행렬 초기화

	freopen("in.txt", "r", stdin);
	scanf("%d", &n); //n은 vertex의 갯수
	scanf("%d", &m); //m은 edge의 갯수
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &u, &v, &cost);
		if (map[u][v] > cost) {
			map[u][v] = cost;
		}
	}//인접행렬에 비용값 반영
	scanf("%d%d", &start, &end);
	//출발 정점과 도착 정점 값 입력.

	dist[start] = 0; //첫정점은 방문햇으니 n-1개만 탐색 //방문 지점이므로 0이상의 최소거리로 설정.ㅗ
	for (int i = 0; i < n - 1; i++) { //방문한 정점에서 갈 거리 찾기.
		int c;
		int min = INF + 1; //절대나올수없는 가장큰값
		for (int j = 1; j <= n; j++) {
			if (visited[j] == 0 && dist[j] < min) {

				min = dist[j]; //dist배열을 모두 탐색하면서 가장 작은 값을 찾는 것
				c = j;
			}
		}
		visited[c] = 1; //최소비용 정점 방문.

		for (int j = 1; j <= n; j++) {
			if (dist[j] > dist[c] + map[c][j]) { //그런데  c를 거쳐 j로 가는 것이 j로 직행보다 작다면. j직행값인 dist[j]를 갱신해줌
				dist[j] = dist[c] + map[c][j];
				way[j] = c;
			}
		}


	}
	printf("%d\n", dist[end]);
	print_way(start, end);


	return 0;

}
void print_way(int start, int end) {
	if (way[end] != start) print_way(start, way[end]);
	printf("%d -> %d\n", way[end], end);

}
