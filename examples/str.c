#include "../src/cmstlstring.h"

int main() {
	cmstlstring a = cmstlstring_new_from_input(stdin,0);
	cmstlstring b = cmstlstring_new_from_input(stdin,0);
	cmstlstring_append(&a,&b);
	printf("%s\n",a.vc.data);
	return 0;
}

