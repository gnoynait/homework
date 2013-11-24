#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<cassert>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<sstream>
#define DEBUG
using namespace std;

double *pz; // P(z)
double *pd_z; // P(d|z)
double *pw_z;// P(w|z)
int nd; // number of docs
int nz; // number of topics
int nw; // number of words
vector<vector<pair<int, int> > > docs;
const double epsilon = 0.001;
const int max_iter = 1000;
double inline uniform_rand () {
	double r = (double) rand () / RAND_MAX;
	assert (r >= 0 && r <= 1);
	return r;
}
void init_model () {
	pz = new double[nz];
	pd_z = new double[nz * nd];
	pw_z = new double[nz * nw];
	for (int z = 0; z < nz; z++) {
		pz[z] = uniform_rand ();
	}
	for (int d = 0; d < nd; d++) {
		for (int z = 0; z < nz; z++) {
			pd_z[d * nz + z] = uniform_rand ();
		}
	}
	for (int w = 0; w < nw; w++) {
		for (int z = 0; z < nz; z++) {
			pw_z[w * nz + z] = uniform_rand ();
		}
	}
}

double compute_likelihood () {
	double likelihood = 0;
	for (int d = 0; d < nd; d++) {
		for (vector<pair<int, int> >::iterator it = docs[d].begin ();
			it != docs[d].end (); it++) {
			int w = it->first;
			int n = it->second;
			double p = 0;
			for (int z = 0; z < nz; z++) {
				p += pz[z] * pw_z[w * nz + z] * pd_z[d * nz + z];
			}
			likelihood += n * log(p);
		}
	}
	return likelihood;
}

double update () {
	double *up_pz = new double[nz];
	double down_pz = 0;
	memset (up_pz, 0, sizeof (double) * nz);

	double *up_pd_z = new double[nz * nd];
	double *down_pd_z = new double[nz];
	memset (up_pd_z, 0, sizeof (double) * nz * nd);
	memset (down_pd_z, 0, sizeof (double) * nz);

	double *up_pw_z = new double[nz * nw];
	double *down_pw_z = new double[nz];
	memset (up_pw_z, 0, sizeof (double) * nz * nw);
	memset (down_pw_z, 0, sizeof (double) * nz);

	for (int d = 0; d < nd; d++) {
		for (vector<pair<int, int> >::iterator it = docs[d].begin ();
			it != docs[d].end (); it++) {
			int w = it->first;
			int n = it->second;
			double down = 0;
			double *up = new double[nz];
			
			for (int z = 0; z < nz; z++) {
				up[z] = pz[z] * pw_z[w * nz + z] * pd_z[d * nz + z];
				assert (up[z] >= 0);
				down += up[z];
			}
			assert (down >= 0);
			for (int z = 0; z < nz; z++) {
				double pz_dw = up[z] / down;

				up_pd_z[d * nz + z] = n * pz_dw;
				down_pd_z[z] += n * pz_dw;

				up_pw_z[w * nz + z] = n * pz_dw;
				down_pw_z[z] += n * pz_dw;
				
				up_pz[z] = n * pz_dw;
			}
			down_pz += n;
			delete[] up;
		}
	}

	for (int d = 0; d < nd; d++) {
		for (int z = 0; z < nz; z++) {
			pd_z[d * nz + z] = up_pd_z[d * nz + z] / down_pd_z[z];
			if (isnan(pd_z[d * nz + z]))
				printf ("%f:::%f\n", up_pd_z[d * nz + z], down_pd_z[z]);
			assert (pd_z[d * nz + z] >= 0);
			assert (pd_z[d * nz + z] <= 1);
		}
	}
	for (int w = 0; w < nw; w++) {
		for (int z = 0; z < nz; z++) {
			pw_z[w * nz + z] = up_pw_z[w * nz + z] / down_pw_z[z];
			assert (pw_z[w * nz + z] >= 0);
			assert (pw_z[w * nz + z] <= 1);
		}
	}
	for (int z = 0; z < nz; z++) {
		pz[z] = up_pz[z] / down_pz;
		assert (pz[z] >= 0);
		assert (pz[z] <= 1);
	}
	delete[] up_pz;
	delete[] up_pw_z;
	delete[] down_pw_z;
	delete[] up_pd_z;
	delete[] down_pd_z;
	return compute_likelihood ();
}

void read () {
	char sep;
	int w, n;
	int max_w = 0; // current maximum word id
	vector<pair<int, int> > doc;
	while (scanf ("%d:%d%c", &w, &n, &sep) == 3) {
		doc.push_back (make_pair (w, n));
		max_w = w > max_w ? w : max_w;
		if (sep == '\n') {
			docs.push_back (doc);
			doc.clear ();
		}
	}
	nd = docs.size ();
	nw = max_w + 1;
#ifdef DEBUG
	printf ("nd:%d, nw:%d\n", nd, nw);
#endif
}
void output () {
	FILE *fw_z = fopen ("w_z.txt", "w");
	for (int z = 0; z < nz; z++) {
		for (int w = 0; w < nw; w++) {
			if (w > 0)
				fprintf (fw_z, " ");
			fprintf (fw_z, "%f", pw_z[w * nz + z]);
		}
		fprintf (fw_z, "\n");
	}
	fclose (fw_z);
}
void plsi () {
	double likelihood = 0, oldhood = 0;
	int iter = 0;
	while (/*fabs((likelihood = update ()) - oldhood) > epsilon && */iter++ < max_iter) {
		oldhood = likelihood;
		oldhood = update ();
#ifdef DEBUG
		printf ("%f\n", oldhood);
#endif
	}
}
int main (int argc, char *argv[]) {
	if (argc < 2) {
		printf ("need k.\n");
		exit (-1);
	}
	nz = atoi (argv[1]);
	read ();
	init_model ();
	plsi ();
	output ();
}

