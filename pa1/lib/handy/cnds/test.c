#include <stdio.h>
#include <stdlib.h>

#include "cn_string.h"

main() {
	//Create new CN_STRING
	CN_STRING str = cn_string_from_cstr("This is a test.");
	cn_string_concat_from_cstr(str, ".. extended");
	cn_string_update(str);

	printf("%s\n", CN_STR(str));

	//Free the CN_STRING
	cn_string_free(str);
}
