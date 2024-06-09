#include <stdlib.h>
int main(int argc, char **argv) {
	int *array = (int *)malloc(sizeof(int)*100);
	free(array);
	array[0] = 0;
	return 0;
}
