#include <cstdio>
#include <algorithm>
#include <vector>
#include <cfloat>
#include <cmath>
#pragma warning(disable:4996)
using namespace std;
double closest_pair_DC(int,int,int*,int*,vector<int>*,vector<int>*,vector<int>*,vector<int>*,int);
void sort_by_x_or_y(vector<int>*,int,int,vector<int>*);
void merge(vector<int>*, int,int,int,vector<int>*);
double center(int left, int right, int*pt1, int*pt2, vector<int>&x, vector<int>&y, vector<int>&xid, vector<int>&yid, int dis);
double dist(int x1, int y1, int x2, int y2);
//bool cmpx(point &p, point &q) { return p.x < q.x; };소팅 라이브러리를 쓸때에만 사용. 오름차순.
int main() {
	int n;
	int thr;//bruteforce 한계값.
	int pt1, pt2;
	freopen("A.txt", "r", stdin);
	scanf("%d%u", &n, &thr);
	vector<int> x(n), y(n);
	vector<int> xid(n), yid;


	for (int i = 0; i < n; i++) {
		scanf("%d%d", &x[i],&y[i]);
		xid[i] = i;
	}
	sort_by_x_or_y(x,0,xid.size()-1,xid);
	double distance = closest_pair_DC(0, n - 1, &pt1, &pt2, x, y, xid, yid, thr);
	printf("%d %d\n", x[pt1], y[pt1]);
	printf("%d %d\n", x[pt2], y[pt2]);
	printf("%lf", distance);

	system("pause");
	return 0;

}
void sort_by_x_or_y(vector<int> &vtr, int left, int right, vector<int> &id) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		sort_by_x_or_y(vtr, left, right, id);
		sort_by_x_or_y(vtr, mid + 1, right, id);
		merge(vtr, left, mid, right, id);
	}
}

void merge(vector<int> vtr, int left, int mid, int right,vector<int> id) {
	vector<int> temp;
	int i = left;
	int j = mid + 1;
	while (i <= mid && j <= right) {
		if (vtr[id[i]] <= vtr[id[j]]) temp.push_back(id[i++]);
		else temp.push_back(id[j++]);
	}
	for (; j <= mid; i++) temp.push_back(id[i]);
	for (; j <= right; j++)temp.push_back(id[j]);

	for (int t = left; t <= right; t++) id[t] = temp[t - left];
}
double closest_pair_DC(int left, int right, int*pt1, int*pt2, vector<int>&x, vector<int>&y,vector<int>&xid,vector<int>&yid,int thr){
	double inf = DBL_MAX;
	double distance;
	if (right - left + 1 <= thr) {
		for (int i = left; i <= right; i++) {
			for (int j = i + 1; j <= right; j++) {
				distance = dist(x[xid[i]], y[xid[i]], x[xid[j]], y[xid[j]]);
				if (distance < inf) {
					inf = distance;
					*pt1 = xid[i];
					*pt2 = xid[j];//최소거리의 x배열을 가리키는 두점.
				}
			}

		}
		return inf;
	}
	else {
		int mid = (left + right) / 2;
		int cpl1, cpl2, cpr1, cpr2, cpc1, cpc2;
		double cpl = closest_pair_DC(left, mid, &cpl1, &cpl2, x, y, xid, yid, thr);
		double cpr = closest_pair_DC(mid + 1, right, &cpl1, &cpl2, x, y, xid, yid, thr);
		double cpc = center(left, right, &cpc1, &cpc2, x, y, xid, yid, min(cpl, cpr));

		inf = min({cpr, cpl, cpc});
		if (inf == cpl) {
			*pt1 = cpl1;
			*pt2 = cpl2;
		}
		else if (inf == cpr) {
			*pt1 = cpr1;
			*pt2 = cpr2;

		}
		else {
			*pt1 = cpc1;
			*pt2 = cpc2;

		}
		return inf;
	}

}
double center(int left, int right, int*pt1, int*pt2, vector<int>&x, vector<int>&y, vector<int>&xid, vector<int>&yid, int dis) {
	int mid = (left + right) / 2;
	yid.clear();
	for (int i = left; i <= right; i++) {
		if (i <= mid && (x[xid[i]] >= x[xid[mid]] - dis)) yid.push_back(xid[i]);
		else if (i > mid && (x[xid[i]] <= x[xid[mid + 1]] + dis)) yid.push_back(xid[i]);
	}

	sort_by_x_or_y(y, 0, yid.size() - 1, yid);

	double inf = DBL_MAX;
	double distance;
	for (int i = 0; i <= yid.size()-1; i++) {
		for (int j = i + 1; j <= yid.size()&&j<=i+15; j++) {
			if (y[yid[i]] - y[yid[j]] >= dis) break;
			distance = dist(x[yid[i]], y[yid[i]], x[yid[j]], y[yid[j]]);
			if (distance < inf) {
				inf = distance;
				*pt1 = yid[i];
				*pt2 = yid[j];//최소거리의 x배열을 가리키는 두점.
			}
		}

	}
	return inf;

}



double dist(int x1, int y1, int x2, int y2) {
	return pow((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2), 1 / 2);
}
