#include<iostream>
#include<string>
#include<cstdio>
double *z_dw;
double *z;
double *d_z;
double *w_z;
int    *ndw;
int nd, nz, nw;
int R;

#define Z_DW(z, d, w) (z_dw[d * nw * nz + w * nz + z])
#define Z(n) (z[n])
#define D_Z(d, z) (d_z[z * nd + d])
#define W_Z(w, z) (w_z[z * nw + w])
#define NDW(d, w) (ndw[d * nw + w])

void init_model () {
	z_dw = new double[nd * nw * nz];
	z = new double[nz];
	d_z = new double[nz * nd];
	w_z = new double[nz * nw];
	ndw = new int[nd * nw];
}

void step_e () {
	int i, j, k;
	double den;
	for (i = 0; i < nd; i++) {
		for (j = 0; j < nw; j++) {
			den = 0.0;
			for (k = 0; k < nz; k++) {
				den += Z(k) * D_Z(i, k) * W_Z(j, k);
			}
			for (k = 0; k < nz; k++) {
				Z_DW (k, i, j) = Z(k) * D_Z(i, k) * W_Z(j, k) / den;
			}
		}
	}
}

void step_m () {
	int i, j, k, l;
	double den, mol;
	/* update W_Z */
	for (i = 0; i < nz; i++) {
		den = 0.0;
		for (k = 0; k < nw; k++) {
			for (l = 0; l < nd; l++) {
				den += NDW(l, k) * Z_DW(i, l, k);
			}
		}
		for (j = 0; j < nw; j++) {
			mol = 0.0;
			for (l = 0; l < nd; l++) {
				mol += NDW(l, j) * Z_DW(i, l, j);
			}
			W_Z(j, i) = mol / den;
		}
	}	

	/* update D_Z */
	for (i = 0; i < nz; i++) {
		den = 0.0;
		for (j = 0; j < nd; j++) {
			for (k = 0; k < nw; k++) {
				den += NDW(j, k) * Z_DW(i, j, k);
			}
		}
		for (j = 0; j < nd; j++) {
			mol = 0.0;
			for (k = 0; k < nw; k++) {
				mol += NDW (j, k) * Z_DW (i, j, k);
			}
			D_Z (j, i) = mol / den;
		}
	}

	/* update Z */
	for (i = 0; i < nz; i++) {
		mol = 0.0;
		for (j = 0; j < nd; j++) {
			for (k = 0; k < nw; k++) {
				mol += NDW (j, k) * Z_DW (i, j, k);
			}
		}
		Z(i) = mol / R;
	}
}
#define MAXBUFFER
void read () {
	int i, w, n;
	int c;
	char buffer[MAXBUFFER];
	scanf ("%d%d\n", &nd, &nw);
	init_model ();
	while ((c = fgetc (stdin)) != '\n' && c != EOF)
		;
	for (i = 0; i < nd; i++) {
		fgets (buffer, MAXBUFFER, stdin);
		while (sscanf (buffer, "%d:%d", &w, &n) == 2) {
			NDW (i, w) += n;
			R += n;
		}
	}
}
void output () {
	int i, j;
	for (i = 0; i < nd; i++) {
		for (j = 0; j < nw; j++) {
			printf ("%d ", NDW (i, j));
		}
		printf ("\n");
	}
}
int main (int argc, char *argv[]) {
	nz = atoi (argv[1]);
	read ();
	output ();
}

