// Sort of utilities

#include <stdio.h>
#include <stdlib.h>

/*
 * Array
 * 
 * Basic struct and functions, to create a grown array.
 * 
 * To start array you use:
 * 		array my_array;
 * 		a_init(&my_array, initial_size);
 * 
 * Adding new elements to array:
 * 		a_append(&my_array, 5);
 *
 * Erasing one element
 * 		a_erase(&my_array, element, offsize);
 *  
 * To erase array:
 * 		a_free(&my_array);
*/

typedef struct {
	
	int *		a_array;	// Element
	size_t		a_used;		// Used elements
	size_t		a_size;		// Array total size
	
} array;

array * a_init(array * a, int size) {
	
	/*
	 * Start a new array
	 * Input: array, int
	 * Output: none
	*/
	
	a -> a_array = (int *)malloc(size * sizeof(int));
	a -> a_used = 0;
	a -> a_size = size;
	
	return (array *)&a;
	
}

void * a_append(array * a, int new_element) {
	
	/*
	 * Appends a new element to the array
	 * Input: array, int
	 * Output: None
	*/
	
	// If maximum array space is used, resize it
	if (a -> a_used == a -> a_size) {
		a -> a_size++;
		a -> a_array = realloc(a -> a_array, (a -> a_size) * sizeof(int));
	}
	
	a -> a_used++;
	a -> a_array[a -> a_used] = new_element;
	
}

void * a_print(array * a) {
	
	/*
	 * Shows the array in a pretty print
	 * Input: array
	 * Output: None
	*/
	
	// Print every item
	printf("[ ");
	for (int i = 0; i < a -> a_used; i++) {
		printf("%d,", a -> a_array[i]);
	}
	printf("\b ]\n");
	
}

void * a_free(array * a) {
	
	/*
	 * Frees the array ocuppancy from memory
	 * Input: array
	 * Output: None
	*/
	
	// Free and point to NULL
	free(a -> a_array);
	a -> a_array = NULL;
	
}
