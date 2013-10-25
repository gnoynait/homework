#include <stdlib.h>
#include <stdio.h>
#define EMPTY 0
enum direction {
	LEFT, RIGHT
};
struct status {
	enum direction *d;
	int *num;
};
void swap (int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
struct status *get_status (int *array, int size) {
	struct status *sta = (struct status *) malloc (sizeof (*sta));
	enum direction *d = (enum direction *) malloc ((size + 1) * sizeof (enum direction));
	int *num = (int *) malloc ((size + 1) * sizeof (int));
	int i = 2;
	int j;
	num[0] = 0;
	num[1] = 0;
	for (i = 2; i <= size; i++) {
		int c = 0;
		int see = num[i - 1];
		if (i % 2 == 0)
			see += num[i - 2];
		d[i] = see % 2 ? RIGHT : LEFT;
		if (d[i] == LEFT) {
			for (j = size - 1; array[j] != i; j--) {
				if (array[j] < i)
					++c;
				}
		} else {
			for (j = 0; array[j] != i; j++) {
				if (array[j] < i) {
					++c;
				}
			}
		}
		num[i] = c;
	}
	sta->d = d;
	sta->num = num;
	return sta;
}
int *next_permutation (int *array, int size, struct status *s) {
	enum direction *d;
	int *index = (int *) malloc ((size + 1) * sizeof (int));
	int i;
	if (s == NULL) {
		s = get_status (array, size);
	}
	d = s->d;
	for (i = 0; i < size; i++) {
		index[array[i]] = i;
	}

	for (i = size; i > 1; i--) {
		if (d[i] == LEFT && index[i] != -1 && i > array[index[i] - 1]) {
			swap (array + index[i], array + index[i] - 1);
			index[i] = i - 1;
			index[i - 1] = i;
			break;
		}
		if (d[i] == RIGHT && index[i] != size && i > array[index[i] + 1]) {
			swap (array + index[i], array + index[i] + 1);
			index[i] = i + 1;
			index[i + 1] = i;
			break;
		}
	}
	if (i == 1) {
		return NULL;
	}
	while (++i <= size) {
		d[i] = d[i] == LEFT ? RIGHT : LEFT;
	}
	return  array;	
}

struct status *next_n_status (struct status *sta, int size, int n) {
	int i = size;
	int r = 0, q = n, c = 0;
	int s;
	for (i = size; i > 1; i--) {
		r = q % i;
		q = q / i;
		s = sta->num[i] + r + c;
		sta->num[i] = s % i;
		c = s / i;
	}
	if (c != 0 || q != 0)
		return NULL;
	sta->d[2] = LEFT;
	for (i = 3; i <= size; i++)
		if (i % 2) 
			sta->d[i] = sta->num[i - 1] % 2 ? RIGHT : LEFT;
		else
			sta->d[i] = (sta->num[i - 1] + sta->num[i - 2]) % 2 ? RIGHT : LEFT;
	
	return sta;
}
int *next_n_permutation (int *array, int size, int n, struct status *sta) {
	int i, j, c;
	if (sta == NULL)
		sta = get_status (array, size);
	if (!next_n_status (sta, size, n)) {
		return NULL;
	}
	for (i = 0; i < size; i++) {
		array[i] = EMPTY;
	}
	for (i = size; i > 0; i--) {
		if (sta->d[i] == LEFT) {
			c = sta->num[i] + 1;
			j = size - 1;
			while (c > 0) {
				if (array[j] == EMPTY)
					c--;
				j--;
			}
			array[j + 1] = i;
		} else {
			c = sta->num[i] + 1;
			j = 0;
			while (c > 0) {
				if (array[j] == EMPTY)
					c--;
				j++;
			}
			array[j - 1] = i;
		}
	}
	return array;
}

void output (int *array, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf ("%d ", array[i]);
	}
	printf ("\n");
}
void init (int *array, int size ) {
	int i;
	for (i = 0; i < size; i++) {
		array[i] = i + 1;
	}
}
int main () {
	int array[4];
	struct status *sta = NULL;
	init (array, 4);
	while (1) {
		output (array, 4);
		if (!next_permutation (array, 4, sta))
			break;
	}
	/*
	output (array, 1000);
	next_n_permutation (array, 1000, 10, sta);
	output (array, 1000);
	next_n_permutation (array, 1000, -10, sta);
	output (array, 1000);
	next_n_permutation (array, 1000, 11, sta);
	output (array, 1000);
	next_n_permutation (array, 1000, -11, sta);
	output (array, 1000);
	*/

	return 0;
}
