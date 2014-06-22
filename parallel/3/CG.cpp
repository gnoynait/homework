#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cmath>
using namespace std;
int main (int argc, char *argv[]) {
    int N;
    double *x, *b, **A, *Ap, *r, *p;
    double rk2, rk2n, alpha, beta, pAp; 
    double epsilon = 0.001;
    N = atoi(argv[1]);
    x = (double *) malloc(sizeof(double) * N);
    b = (double *) malloc(sizeof(double) * N);
    A = (double **) malloc(sizeof(double *) * N);
    Ap = (double *) malloc(sizeof(double) * N);
    r = (double *) malloc(sizeof(double) * N);
    p = (double *) malloc(sizeof(double) * N);
    for (int i = 0; i < N; i++) {
        A[i] = (double *)malloc(sizeof(double) * N);
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
    rk2n = 0;
    for (int i = 0; i < N; i++) {
        rk2n += r[i] * r[i];
    }

    while (1) {
        rk2 = rk2n;

        for (int i = 0; i < N; i++) {
            Ap[i] = 0.0;
            for (int j = 0; j < N; j++) {
                Ap[i] += A[i][j] * p[j];
            }
        }

        pAp = 0;
        for (int i = 0; i < N; i++) {
            pAp += p[i] * Ap[i];
        }

        alpha = rk2 / pAp;

        for (int i = 0; i < N; i++) {
            x[i] += alpha * p[i];
        }

        for (int i = 0; i < N; i++) {
            r[i] -= alpha * Ap[i];
        }

        rk2n = 0;
        for (int i = 0; i < N; i++) {
            rk2n += r[i] * r[i];
        }

        if (sqrt(rk2n) < epsilon)
            break;
        cout << sqrt(rk2n) << endl;

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
