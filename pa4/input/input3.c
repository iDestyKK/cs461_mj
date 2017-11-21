main() {
	int a;
	test_func();
}

test_func() {
	goto test;
	goto tester;
	goto test;
tester:
	goto test;
test:
	goto test;
}


