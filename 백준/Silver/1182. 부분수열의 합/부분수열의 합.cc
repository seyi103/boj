#include <stdio.h>
using namespace std;

int N, S;
int arr[21];
int res;

int main() {
    scanf("%d %d", &N, &S);
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);
    
    for (int i = 1; i < (1 << N); i++) {
        int sum = 0;
        for (int j = 0; j < N; j++) {
            if(i & (1<<j))
                sum += arr[j];
        }
        if (sum == S)
            res++;
    }
    printf("%d", res);
    return 0;
}