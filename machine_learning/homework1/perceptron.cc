#include <iostream>
#include <cstdio>
#include <vector>

int nfeature = 2000; // feature number
int niter = 200;     // iter times
double alpha = 0.001;// step size
double *w;           // model parameter w
double b;            // model parameter b

// train example class
struct Example {
	int y;       // label
	double *x;   // feature
};

/* perceptron trainning step */
template <class InputIterator>
void train (InputIterator begin, InputIterator end) {
	b = 0;
	for (int i = 0; i < nfeature; i++) {
		w[i] = 0;
	}
	for (int n = 0; n < niter; ++n) {
		for (InputIterator it = begin; it != end; ++it) {
			double p = b;
			for (int i = 0; i < nfeature; ++i) {
				p += w[i] * it->x[i];
			}
			if (it->y * p <= 0) {
				b += alpha * it->y * alpha;
				for (int i = 0; i < nfeature; ++i) {
					w[i] += alpha * it->y * it->x[i];
				}
			}

		}
	}
}	

/* perceptron predict step, results is stored in each example's y */
template <class ForwardIterator>
void predict (ForwardIterator begin, ForwardIterator end) {
	for (ForwardIterator it = begin; it != end; ++it) {
		double p = b;
		for (int i = 0; i < nfeature; ++i) {
			p += w[i] * it->x[i];
		}
		if (p >= 0)
			it->y = 1;
		else
			it->y = -1;
	}
}

/* divide the data set to 5 parts, 4 to train and 1 to test. */
template <class Iterator>
void test (Iterator begin, Iterator end) {
	printf ("perceptron test\n");
	printf ("id\tprecision\trecall  \tf1\n");
	float sp = 0, sr = 0, sf1 = 0;
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
		train (train_set.begin (), train_set.end ());
		predict (test_set.begin (), test_set.end ());

		/* evaluate the results */
		int tp = 0, fp = 0, tn = 0, fn = 0;
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
	printf ("average\t%f\t%f\t%f\n", sp / 5, sr / 5, sf1 / 5);
}


int main () {
	std::vector<Example> data_set;
	int c;
	// init the model
	w = new double[nfeature]();
	b = 0.0;
	// read in data
	while (std::cin >> c) {
		Example e;
		e.y = c;
		e.x = new double[nfeature];
		for (int i = 0; i < nfeature; ++i) {
			std::cin >> e.x[i];
		}
		data_set.push_back (e);
	}
	// perform tests
	test (data_set.begin (), data_set.end ());

	return 0;
}

