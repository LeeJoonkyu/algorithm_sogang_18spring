#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
using namespace std;

// 두 점 사이의 거리를 계산한다.
double calc_dist(int x1, int y1, int x2, int y2){
    return pow(pow(x2-x1,2) + pow(y2-y1,2), 0.5);
}

// merge_sort에서 사용하는 merge 함수.
void merge(vector<int> &vec, vector<int> &target, int s, int mid, int e){
    vector<int> tmp;
    int i = s, j = mid + 1;
    while(i <= mid && j <= e){
        if(vec[target[i]] <= vec[target[j]]) tmp.push_back(target[i++]);
        else tmp.push_back(target[j++]);
    }

    for(;i<=mid;i++) tmp.push_back(target[i]);
    for(;j<=e; j++) tmp.push_back(target[j]);

    for(int k = s; k <= e; k++) target[k] = tmp[k - s];
}

// merge sort를 활용한 정렬함수.
void sort_by_X_or_Y(vector<int> &vec, vector<int> &target, int s, int e){
    if(s == e) return;

    int mid = (s+e)/2;
    sort_by_X_or_Y(vec,target,s,mid);
    sort_by_X_or_Y(vec,target,mid+1 ,e);
    merge(vec,target,s,mid,e);
}

// 중간 영역에서 closest pair를 찾는 함수.
double closest_pair_center(int L, int R, vector<int> &X, vector<int> &Y, vector<int> &p1, vector<int> &p2, int* pt1, int* pt2, int d){
    int mid = (L + R) / 2;
    p2.clear(); // 새로운 y 좌표 정렬을 위해 p2 배열을 비운다.
    for(int i=L; i<= R; i++){
        if(i <= mid && X[p1[i]] >= X[p1[mid]] - d) p2.push_back(p1[i]);
        else if(i > mid && X[p1[i]] <= X[p1[mid+1]] + d) p2.push_back(p1[i]);    
    } // 중간 영역의 범위에 속한 점들을 p2 배열에 push 한다.

    sort_by_X_or_Y(Y, p2, 0, p2.size() - 1); // p2 배열을 Y좌표를 기준으로 정렬한다.

    // p2 배열에 있는 점들을 비교하며 최솟값을 찾아낸다.
    double mn = 987654321;
    for(int i= 0 ; i<p2.size() -1 ; i++){
        for(int j=i + 1; j < p2.size() && j <= i + 15;  j++){
            if(Y[p2[i]] - Y[p2[j]] >= d) break;
            double dist = calc_dist(X[p2[i]], Y[p2[i]], X[p2[j]], Y[p2[j]]);
            if(dist < mn){
                mn = dist;
                *pt1 = p2[i];
                *pt2 = p2[j];
            }
        }
    }
    return mn;
}

double closest_pair_DC(int L, int R, int *pt1, int *pt2, vector<int> &X, vector<int> &Y, vector<int> &p1, vector<int> &p2, int THR){
    double mn;
    // 점의 갯수가 THR 보다 작다면 O(n^2) 방식으로 비교해 최솟값을 리턴한다.
    if(R - L + 1 <= THR){
        mn = 987654321;
        for(int i = L; i<=R - 1; i++){
            for(int j = i + 1; j<=R; j++){
                double dist = calc_dist(X[p1[i]], Y[p1[i]], X[p1[j]], Y[p1[j]]);
                if(dist < mn){
                    mn = dist;
                    *pt1 = p1[i];
                    *pt2 = p1[j];
                }
            }
        }
        return mn;
    }

    // mid 값을 기준으로 왼쪽, 가운데, 오른쪽 최솟값을 구한다.
    int mid = (L + R) / 2;
    int CPL1, CPL2, CPR1, CPR2, CPC1, CPC2; // 각 최솟값을 만족하는 좌표를 저장하는 변수.
    double CPL = closest_pair_DC(L, mid, &CPL1, &CPL2, X, Y, p1, p2, THR);
    double CPR = closest_pair_DC(mid + 1, R, &CPR1, &CPR2, X, Y, p1, p2, THR);
    double CPC = closest_pair_center(L, R, X, Y, p1, p2, &CPC1, &CPC2, min(CPL, CPR));

    // 가장 작은 최솟값을 구하고 해당하는 좌표를 저장한다.
    mn = min({CPR, CPL, CPC});
    if(mn == CPL){
        *pt1 = CPL1;
        *pt2 = CPL2;
    }
    else if (mn == CPR){
        *pt1 = CPR1;
        *pt2 = CPR2;
    }
    else{
        *pt1 = CPC1;
        *pt2 = CPC2;
    }

    return mn;
}

int main(){
    ifstream inFile("A.txt", ios::in);

    int N, THR;
    inFile >> N >> THR;
    vector<int> X(N), Y(N);
    vector<int> p1(N), p2;

    for(int i=0; i<N; i++){
        inFile >> X[i] >> Y[i];
        p1[i] = i;
    }

    sort_by_X_or_Y(X ,p1, 0, p1.size()-1);

    int pt1, pt2;
    double dist = closest_pair_DC(0, N-1, &pt1, &pt2, X,Y,p1,p2,THR);
    printf("%d %d\n", X[pt1], Y[pt1]);
    printf("%d %d\n", X[pt2], Y[pt2]);
    printf("%.2f\n", dist);
    return 0;
}
