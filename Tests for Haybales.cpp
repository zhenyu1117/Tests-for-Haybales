#include <cstdio>

int N, j[100010], k;
int M, x[400040], y[400040], l[400040], prev[400040], last[100010];
int head, tail, inq[100010], q[1000100];
long long res[100010];

const int qs = 1000000;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", j + i);
    }

    k = N*1000000;

    M = 0;

    for (int i = 1; i < N; i++) {
        M++;
        x[M] = i + 1;
        y[M] = i;
        l[M] = 0;
    }

    for (int i = 1; i <= N; i++) {
        M++;
        x[M] = i;
        y[M] = j[i];
        l[M] = k;

        if (j[i] < N) {
            M++;
            x[M] = j[i] + 1;
            y[M] = j[i];
            l[M] = -1;

            M++;
            x[M] = j[i] + 1;
            y[M] = i;
            l[M] = -(k + 1);
        }
    }

    for (int i = 1; i <= M; i++) {
        prev[i] = last[x[i]];
        last[x[i]] = i;
    }

    for (int i = 1; i <= N; i++) {
        res[i] = 1;
    }
    res[N] = 0;
    head = tail = 1;
    q[tail % qs] = N;
    inq[q[tail % qs]] = 1;

    while (head <= tail) {
        int v = q[tail % qs];
        inq[v] = 0;
        tail--;

        int it = last[v];
        while (it > 0) {
            if (res[y[it]] > res[v] + l[it]) {
                res[y[it]] = res[v] + l[it];
                if (inq[y[it]] == 0) {
                    tail++;
                    q[tail % qs] = y[it];
                    inq[q[tail % qs]] = 1;
                }
            }

            it = prev[it];
        }
    }

    printf("%d\n", k);
    for (int i = 1; i <= N; i++) {
        printf("%lld\n", res[i] - res[1] + 1);
    }

    for (int i = 1; i < N; i++) {
        if (res[i+1] < res[i]) {
            return 1;
        }
    }

    for (int i = 1; i <= N; i++) {
        if (res[j[i]] > res[i] + N) {
            return 1;
        }

        if (j[i] < N) {
            if (res[j[i]+1] <= res[i] + N) {
                return 1;
            }
        }
    }

    return 0;
}
