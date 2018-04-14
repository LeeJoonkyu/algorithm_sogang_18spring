#include <cstdio>
#include <algorithm>
#pragma warning(disable:4996)
//using namespace std;
typedef struct point {
	int xid;
	double x;
	double y;
}point;
double dist(point &p, point&q) { return (p.x - q.x)*(p.x - q.x) + (p.y - q.y)*(p.y - q.y); }
typedef struct pair {
	point p1;
	point p2;
	double dist;
}pair;
pair Closest_Pair_DC(point*p, int n);
void sort_by_x_or_y(point*p,int left, int right, int xory);
void merge(point*p, int left, int right, int xory);
//bool cmpx(point &p, point &q) { return p.x < q.x; };소팅 라이브러리를 쓸때에만 사용. 오름차순.
int main() {
	int n=0;
	//left bound right bound
	//최소거리 두점의 x,y배열에서 인덱스값
	//입력된 점 x,y좌표배열
	//정렬하기위한 임시배열
	int thr;//bruteforce 한계값.
	//입력은 test케이스 갯수(line1), 점갯수 및 thr값.
	freopen("A.txt", "r", stdin);
	scanf("%d", &testcase);
	scanf("%d%u", &n, &thr);

	point* p;//구조체 포인터
	p = (point*)malloc(n * sizeof(point));
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf", &p[i].x, &p[i].y);
		p[i].xid = i;
	}
	/*for (int i = 0; i < n; i++) {
		printf("%lf %lf\n", p[i].x, p[i].y);//실수의 과학적표기법
	}*/
	int left = 0; int right = n - 1; int xory=0;//x정렬혹은y정렬
	sort_by_x_or_y(p, left, right, xory);
	pair cp = Closest_Pair_DC(p, n);
	printf("%lf%lf\n", cp.p1.x,cp.p1.y);
	printf("%lf%lf\n", cp.p2.x,cp.p2.y);
	printf("%lf", cp.dist);

	system("pause");
	return 0;

}
void sort_by_x_or_y(point*p, int left, int right, int xory) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		sort_by_x_or_y(p, left, right, xory);
		sort_by_x_or_y(p, mid+1, right, xory);
		merge(p, left, right, xory);
	}

}
void merge(point*p, int left, int right,int xory) {
	point*q = (point*)malloc((right + 1) * sizeof(point));
	int mid = (left + right) / 2;
	int i = left;
	int j = mid + 1;
	int k = left;
	if (xory == 0) {
		while (i <= mid && j <= right) {
			if (p[i].x <= p[j].x) {
				q[k] = p[i];
				i++;
			}
			else {
				q[k] = p[j];
				j++;
			}
			k++;
		}
		int t;
		if (i > mid) t = j;
		else t = i;
		for (k; k <= right; k++, t++) q[k] = p[t];
		for (k = 0; k <= right; k++) p[k] = q[k];
	}
	else {
		while (i <= mid && j <= right) {
			if (p[i].y <= p[j].y) {
				q[k] = p[i];
				i++;
			}
			else {
				q[k] = p[j];
				j++;
			}
			k++;
		}
		int t;
		if (i > mid) t = j;
		else t = i;
		for (k; k <= right; k++, t++) q[k] = p[t];
		for (k = 0; k <= right; k++) p[k] = q[k];

	}
	free(q);

}
pair Closest_Pair_DC(point* p, int n) {
	pair cp;
	pair pleft;
	pair pright;

	double temp, leftbound, rightbound;

	if (n == 2) {
		cp.p1 = p[0];
		cp.p2 = p[1];
		cp.dist = dist(p[0], p[1]);
		return cp;
	}
	if (n == 3) {
		cp.p1 = p[0];
		cp.p2 = p[1];
		cp.dist = dist(p[0], p[1]);
		if (dist(p[1], p[2]) < cp.dist){
			cp.p1 = p[1];
			cp.p2 = p[2];
			cp.dist = dist(p[1], p[2]);
		}
		if (dist(p[0], p[2]) < cp.dist) {
			cp.p1 = p[0];
			cp.p2 = p[2];
			cp.dist = dist(p[0], p[2]);
		}
		return cp;
	}
	point* tmp1;
	point* tmp2;
	if (n % 2 == 0) {
		tmp1 = (point*)malloc((n / 2) * sizeof(point));
		tmp2 = (point*)malloc((n / 2) * sizeof(point));
		for (int i = 0; i < (n / 2); i++) {
			tmp1[i] = p[i];
			tmp2[i] = p[i + (n / 2)];
		}
		pleft = Closest_Pair_DC(tmp1, n / 2);//왼쪽분할->왼쪽쌍
		pright = Closest_Pair_DC(tmp2, n / 2);//오른쪽분할
		free(tmp1);
		free(tmp2);
	}
	else {
		tmp1 = (point*)malloc((n / 2) * sizeof(point));
		tmp2 = (point*)malloc(((n / 2)+1) * sizeof(point));
		for (int i = 0; i < (n / 2); i++) {
			tmp1[i] = p[i];
		}
		for (int i = 0; i <= (n / 2); i++) {
			tmp2[i] = p[i + (n / 2)];
		}
		pleft = Closest_Pair_DC(tmp1, n / 2);
		pright = Closest_Pair_DC(tmp2, (n / 2) + 1);
		free(tmp1);
		free(tmp2);

	}
	if (pleft.dist >= pright.dist) cp = pright;
	else cp = pleft;
	point* ymid = (point*)malloc(n * sizeof(point));
	int ymid_num=0;
	leftbound = p[n / 2].x;
	rightbound = p[(n / 2) + 1].x;
	for (int i = 0, ymid_num = 0; i < n; i++) {
		if (p[i].x >= leftbound - cp.dist || p[i].x <= rightbound + cp.dist) {
			ymid[ymid_num] = p[i];
			ymid_num++;
		}
	}
	ymid_num--;
	int xory = 1;
	sort_by_x_or_y(ymid, 0, ymid_num, xory);

	for (int i = 0; i < ymid_num - 1; i++) {
		for (int j = i + 1; j < ymid_num && j <= i + 15; j++) {
			temp = dist(ymid[i], ymid[j]);
			if (temp <= cp.dist) {
				cp.dist = temp;
				cp.p1 = ymid[i];
				cp.p2 = ymid[i + 1];

			}
		}
	}
	free(ymid);

	return cp;


}
