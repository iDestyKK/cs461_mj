/*
 * Array Indexing Test 5
 */

int i[8];

main() {
	int x[2];
	int y;
	float z;
	x[0] = 8;
	x[1] = 13;
	y = 2;

	i[y] = x[0];
	i[y + 1] = x[1];

	i = z;
	i[-1] = z;
}
