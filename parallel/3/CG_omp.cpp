#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cmath>
using namespace std;
int N;
inline double dot(double *a, double *b) {
    double r = 0.0;
    for (int i = 0; i < N; i++) {
        r += a[i] * b[i];
    }
    return r;
}
int main (int argc, char *argv[]) {
    double *x, *b, **A, *Ap, *r, *p;
    double rk2, rk2n, alpha, beta, pAp; 
    double epsilon = 0.0000001;
    N = atoi(argv[1]);
    x = (double *) malloc(sizeof(double) * N);
    b = (double *) malloc(sizeof(double) * N);
    A = (double **) malloc(sizeof(double *) * N);
    Ap = (double *) malloc(sizeof(double) * N);
    r = (double *) malloc(sizeof(double) * N);
    p = (double *) malloc(sizeof(double) * N);
    for (int i = 0; i < N; i++) {
        A[i] = (double *) malloc(sizeof(double) * N);
    }

    ifstream Afile("A.dat");
    ifstream bfile("b.dat");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Afile >> A[i][j];
        }
        bfile >> b[i];
    }
    Afile.close();
    bfile.close();

    // x0
    for (int i = 0; i < N; i++) {
        x[i] = 0.0;
    }
    // r0 and p0
    for (int i = 0; i < N; i++) {
        r[i] = b[i];
        p[i] = r[i];
    }

    while (1) {
        rk2 = dot(r, r);

        #pragma omp parallel for private(i)
        for (int i = 0; i < N; i++) {
            Ap[i] = dot(A[i], p);
        }

        pAp = dot(p, Ap);

        alpha = rk2 / pAp;

        for (int i = 0; i < N; i++) {
            x[i] = x[i] + alpha * p[i];
        }

        for (int i = 0; i < N; i++) {
            r[i] = r[i] - alpha * Ap[i];
        }

        rk2n = dot(r, r);
        if (sqrt(rk2n) < epsilon)
            break;

        beta = rk2n / rk2;
        for (int i = 0; i < N; i++) {
            p[i] = r[i] + beta * p[i];
        }
    }
    for (int i = 0; i < N; i++)
        cout << x[i] << ' ';
    cout << endl;
    return 0;
}
