#include <stdio.h>

//フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] をソートして昇順に書き換える関数
*/
void quick_sort(int A[], int n){
    if(n <= 1) return;
    int i, l, r, pivot;
    i = l = 1;
    r = n-1;
    pivot = A[0];
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
    
    A[0] = A[l-1];
    A[l-1] = pivot;
    quick_sort(A, l-1);
    quick_sort(A+r+1, n-r-1);
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }

// すべての要素が同じ場合でも計算が早く終わるか確認する

  quick_sort(A, N);
  for(i=0;i<N;i++){
    if(A[i] != i) printf("ERROR %dth element is %d\n", i, A[i]);
  }
}

/*int main(){
    int i;
    A[0] = 4;
    A[1] = 2;
    for(i = 2; i < N; i++){
        A[i] = 3;
    }
    
    quick_sort(A, N);
    for(i=0;i<N;i++){
        if(A[i] != 3) printf("%dth element is %d\n", i, A[i]);
    }
}*/
