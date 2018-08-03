#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
 A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
 ただし、Aの中身は書き換えてしまう。
 */

void quick_sort(int A[], int n){
    if(n <= 1) return;
    int i, j, pivot;
    pivot = A[0];
    for(i = j = 1;i < n; i++){
        if(A[i] <= pivot){
            int z = A[j];
            A[j] = A[i];
            A[i] = z;
            j++;
        }
    }

    A[0] = A[j-1];
    A[j-1] = pivot;
    quick_sort(A, j-1);
    quick_sort(A+j, n-j);
}

int quick_select(int A[], int n, int k){
    //中央値の中央値を求めてA[0]に持ってくる。
    if(n <= 5){
      quick_sort(A,n);
      return A[k];
    }

    int a,  D[N];
    for(a = 0; a < n/5; a++){
      D[a] = quick_select(A+5*a, 5, 2);
    }
    if(n%5 != 0) D[n/5] = quick_select(A+(n/5)*5, n%5, (n%5)/2);
    int pivot = quick_select(D, (n+4)/5, ((n+4)/5)/2);

    int z = A[0];
    for (int i = 0; i < n; i++) {
      if(A[i] == pivot){
        A[0] = A[i];
        A[i] = z;
      }
    }
    //ここまで

    int i, l, r;
    i = l = 1;
    r = n-1;
    while(i <= r){
        if(A[i] < pivot){
            int z = A[l];
            A[l] = A[i];
            A[i] = z;
            l++;
            i++;
        }
        else if(A[i] > pivot){
            int z = A[r];
            A[r] = A[i];
            A[i] = z;
            r--;
        }
        else i++;
    }
    if(r < k) return quick_select(A+r+1, n-r-1, k-r-1);
    else if(l <= k+1) return pivot;
    else return quick_select(A+1, l-1, k);
}

int main(){
    int i;
    A[0] = 0;
    A[1] = 3; //原始元
    for(i=2;i<N;i++){
        A[i] = (long long int) A[i-1] * A[1] % N;
    }

    // すべての要素が同じ場合でも計算が早く終わるか確認する

    for(i=0;i<N;i++){
        if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
            printf("%d th element is %d\n", i, quick_select(A, N, i));
    }
}
