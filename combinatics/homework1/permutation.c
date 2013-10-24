#define EMPTY 1
enum direction {
	LEFT, RIGHT
};
struct status {
	enum direction *d;
	int *num;
};
void swap (int *a, int * b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
struct status *get_status (int *array, int size) {
	struct status *sta = malloc (sizeof (*s));
	enum direction *d = (enum direction *) malloc ((size + 1) * sizeof (enum direction));
	int *num = malloc ((size + 1) * sizeof (int));
	int i = 2;
	d[2] = LEFT;
	while (i <= size) {
		int c = 0;
		if (d[i] == LEFT)
			for (int j = size - 1; array[j] != i; j--)
				if (array[j] < i)
					++c;
		else
			for (int j = 0; array[j] != i; j++)
				if (array[j] < i)
					++c;
		num[i] = c;
		++i;
		int see = b[i - 1];
		if (i % 2 == 0)
			see += b[i - 2];

		d[i] = see % 2 ? RIGHT : LEFT;
	}
	status->d = d;
	status->num = num;
	return status;
}
struct status *next_permutation (int *array, int size) {
	struct status *s = get_status (array, size);
	int *d = s->d;
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
struct status *net_n_status (struct status *sta, int size, int n) {
// TODO implement this method
	
	
	return sta;
}
void next_n_permutation (int *array, int size, int n) {
	struct status *sta = get_status (array, size);
	struct status *nsta = next_n_status (sta, int size, int n);
	int i = 0;
	for (i = 0; i < size; i++) {
		array[i] = EMPTY;
	}
	for (i = size; i > 1; i--) {
		if (nsta->d[i] == LEFT) {
			int c = nsta->num + 1;
			int j = size - 1;
			while (c > 0) {
				if (array[j] == EMPTY)
					c--;
				j--;
			}
		} else {
			int c = nsta->num + 1;
			int j = 0;
			while (c > 0) {
				if (array[j] == EMPTY)
					c--;
				j++;
			}
		}
		array[j] = i;
	}
}
