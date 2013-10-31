#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>

#define NFEATURE 2000
#define NHIDDEN 2
int niter = 1000;     // iter times
double alpha = 0.01;// step size

double w[NHIDDEN][NFEATURE];
double b[NHIDDEN];
double wo[NHIDDEN];
double bo;

// train example class
struct Example {
	int y;       // label
	double *x;   // feature
};
double drandom () {
	return 0.1 * (double) rand () / RAND_MAX;
	return 0;
}
void random_init () {
	int i, j;
	for (i = 0; i < NHIDDEN; i++) {
		b[i] = drandom ();
		wo[i] = drandom ();
		for (j = 0; j < NFEATURE; j++) {
			w[i][j] = drandom ();
		}
	}
	bo = drandom ();
}
	
	
double sigmoid (double x) {
	return 1.0 / (1 + exp (-x));
}
/* perceptron trainning step */
template <class InputIterator>
void train (InputIterator begin, InputIterator end) {
	random_init ();
	double *a = (double *)malloc (sizeof (double) * NHIDDEN);
	for (int n = 0; n < niter; ++n) {
		for (InputIterator it = begin; it != end; ++it) {
			double y;
			for (int i = 0; i < NHIDDEN; i++) {
				double sum = b[i];
				for (int j = 0; j < NFEATURE; j++) {
					sum += it->x[j] * w[i][j];
				}
				a[i] = sigmoid (sum);
			}
			double sum =  bo;
			for (int i = 0; i < NHIDDEN; ++i) {
				sum += wo[i] * a[i];
			}
			y = sigmoid (sum);
			double sigmav = (y - it->y) * y * (1 - y);
			double *sigmau = (double *)malloc (sizeof (double) * NHIDDEN);
			for (int i = 0; i < NHIDDEN; i++) {
				sigmau[i] = a[i] * (1 - a[i]) * wo[i] * sigmav;
			}
			bo -= alpha * sigmav;
			for (int i = 0; i < NHIDDEN; i++) {
				wo[i] -= alpha * sigmav * a[i];
			}
			for (int i = 0; i < NHIDDEN; i++) {
				for (int j = 0; j < NFEATURE; j++) {
					w[i][j] -= alpha * sigmau[i] * it->x[j];
				}
				b[i] -= alpha * sigmau[i];
			}

		}
	}
	free (a);
}	

/* perceptron predict step, results is stored in each example's y */
template <class ForwardIterator>
void predict (ForwardIterator begin, ForwardIterator end) {
	double *a = (double *)malloc (sizeof (double) * NHIDDEN);
	for (ForwardIterator it = begin; it != end; ++it) {
		double y;
		for (int i = 0; i < NHIDDEN; i++) {
			double sum = b[i];
			for (int j = 0; j < NFEATURE; j++) {
				sum += it->x[j] * w[i][j];
			}
			a[i] = sigmoid (sum);
		}
		double sum =  bo;
		for (int i = 0; i < NHIDDEN; ++i) {
			sum += wo[i] * a[i];
		}
		y = sigmoid (sum);

		if (y >= 0.5)
			it->y = 1;
		else
			it->y = -1;
	}
	free (a);
}

/* divide the data set to 5 parts, 4 to train and 1 to test. */
template <class Iterator>
void test (Iterator begin, Iterator end) {
	float sp = 0, sr = 0, sf1 = 0;
	printf ("ann test\n");
	printf ("id\tprecision\trecall  \tf1\n");
	for (int i = 0; i < 5; ++i) { // test 5 times
		int c = 0;
		std::vector<Example> train_set, test_set;
		std::vector<int> answer;
		for (Iterator it = begin; it != end; ++it) {
			if (c % 5 == i) {
				test_set.push_back (*it); // test set
				answer.push_back (it->y); // the actual class
			} else {
				train_set.push_back (*it);// train set
			}
			
			++c;
		}
		//train (begin, end); // warm up
		train (train_set.begin (), train_set.end ());
		predict (test_set.begin (), test_set.end ());

		/* evaluate the results */
		int tp = 0, fp = 0, fn = 0;
		for (int j = 0; j < test_set.size (); ++j) {
			if (test_set[j].y > 0) {
				if (answer[j] > 0)
					++tp;
				else
					++fp;
			} else if (answer[j] > 0) {
				++fn;
			}
		}
		float precision = 1.0 * tp / (tp + fp);
		sp += precision;
		float recall = 1.0 * tp / (tp + fn);
		sr += recall;
		float f1 = 2 * precision * recall / (precision+ recall);
		sf1 += f1;
		printf ("%d\t%f\t%f\t%f\n", i + 1, precision, recall, f1);
	}
	printf ("average\t%f\t%f\t%f\n", sp / 5, sr /5, sf1 / 5);
}


int main () {
	std::vector<Example> data_set;
	int c;
	// read in data
	while (std::cin >> c) {
		Example e;
		e.y = c;
		e.x = new double[NFEATURE];
		for (int i = 0; i < NFEATURE; ++i) {
			std::cin >> e.x[i];
		}
		data_set.push_back (e);
	}
	// perform tests
	test (data_set.begin (), data_set.end ());

	return 0;
}

