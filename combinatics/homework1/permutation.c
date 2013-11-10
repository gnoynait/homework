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
struct status *init_status (int size) {
	struct status *sta = (struct status *) malloc (sizeof (*sta));
	enum direction *d = (enum direction *) malloc ((size + 1) * sizeof (enum direction));
	int *num = (int *) malloc ((size + 1) * sizeof (int));
	int i;
	for (i = 0; i <= size; i++) {
		num[i] = 0;
		d[i] = LEFT;
	}
	sta->num = num;
	sta->d = d;
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
		if (d[i] == LEFT && index[i] != 0 && i > array[index[i] - 1]) {
			swap (array + index[i], array + index[i] - 1);
			index[i] = i - 1;
			index[i - 1] = i;
			break;
		}
		if (d[i] == RIGHT && index[i] != size - 1 && i > array[index[i] + 1]) {
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
	free (index);
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
int main (int argc, char *argv[]) {
	int n, m;
	int i;
	int *array;
	struct status *sta = NULL;

	n = atoi(argv[1]);
	m = atoi(argv[2]);
	array = (int *) malloc (sizeof (int) * n);
	init (array, n);
	sta = init_status (n);
	//output (sta->num, n + 1);	
	for (i = 0; i < m; i++) {
		//output (array, n);
		int *next = next_n_permutation (array, n, 1, sta);
		if (!next) {
			init (array, n);
		}
	}
	return 0;
}
