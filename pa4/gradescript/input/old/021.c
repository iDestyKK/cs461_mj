/*
 * If Statements Test 2
 */

int i[8];

main() {
	int index;
	index = 2;

	/* Set up array elements */
	i[0] = 2;
	i[1] = 3;
	i[2] = 4;

	/* Do cool check */
	if (i[0] == index) {
		i[1] = -1;
		i[2] = -2;
	}
}
