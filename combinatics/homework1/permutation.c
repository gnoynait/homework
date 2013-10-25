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
struct status *next_permutation (int *array, int size) {
	struct status *s = get_status (array, size);
	enum direction *d = s->d;
	int *index = (int *) malloc ((size + 1) * sizeof (int));
	int i;
	for (i = 0; i < size; i++) {
		index[array[i]] = i;
	}
	for (i = size; i > 1; i--) {
		if (d[i] == LEFT && index[i] != -1 && i > array[index[i] - 1]) {
			swap (array + index[i], array + index[i] - 1);
			index[i] = i - 1;
			index[i - 1] = i;

		}
		if (d[i] == RIGHT && index[i] != size && i > array[index[i] + 1]) {
			swap (array + index[i], array + index[i] + 1);
			index[i] = i + 1;
			index[i + 1] = i;
		}
	}
	while (i <= size) {
		d[i] = d[i] == LEFT ? RIGHT : LEFT;
		i++;
	}
	return  s;	
}
struct status *next_n_status (struct status *sta, int size, int n) {
	int i = size;
	int r = 0, q = n, c = 0;
	while (q > 0) {
		r = q % i;
		q = q / i;
		sta->num[i] = (sta->num[i] + r + c) % i;
		c = (sta->num[i] + r + c) / i;
		i--;
	}
	sta->d[2] = LEFT;
	for (i = 3; i <= size; i++)
		if (i % 2) 
			sta->d[i] = sta->num[i - 1] % 2 ? RIGHT : LEFT;
		else
			sta->d[i] = (sta->num[i - 1] + sta->num[i - 2]) % 2 ? RIGHT : LEFT;
	
	return sta;
}
void next_n_permutation (int *array, int size, int n, struct status *sta) {
	int i = 0, j, c;
	if (sta == NULL)
		sta = get_status (array, size);
	next_n_status (sta, size, n);
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
		} else {
			c = sta->num[i] + 1;
			j = 0;
			while (c > 0) {
				if (array[j] == EMPTY)
					c--;
				j++;
			}
		}
		array[j] = i;
	}
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
	int array[6];
	struct status *sta = NULL;
	int n = 20;
	init (array, 6);
	while (n) {
		output (array, 6);
		next_n_permutation (array, 6, 1, sta);
		n--;
	}
	return 0;
}
