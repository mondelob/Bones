// Array test
#include "wonderland.h"

int main() {
	
	array a;
	a_init(&a, 5);
	
	a_print(&a);
	
	a_append(&a, 1);
	a_append(&a, 2);
	a_append(&a, 3);
	a_append(&a, 4);
	a_append(&a, 5);
	a_append(&a, 6);
	
	a_print(&a);
	
	a_free(&a);
	
	return 0;
	
}
