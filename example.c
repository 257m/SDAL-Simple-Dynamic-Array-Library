#include <stdio.h>
#include "SDA.h"

// This going to be the size of each string
#define ELEMENT_SIZE 6
// Note: we use six because although the size of the words are five
// we need an extra byte to hold the null character

int main(void)
{
	// Create a new dynamic array and initialize it's data with Hello
	DynamicArray* array = SDA_create_with_new_data("Hello", ELEMENT_SIZE);
	// Add the word 'World' to the array
	SDA_add_data(array, "World", ELEMENT_SIZE);
	// Add the word 'Fives' to the array
	SDA_add_data(array, "Fives", ELEMENT_SIZE);
	// We remove the word 'World'
	SDA_remove_data_at_index(array, 1, ELEMENT_SIZE);
	// We shrink the array so that it only has 12 bytes allocated rather than 8
	SDA_shrink_allocated_to_mininum(array);
	// We print out the first element which is 'Hello'
	printf("%s\n", array->data);
	// We print out the second element which is 'Fives'
	printf("%s\n", array->data + ELEMENT_SIZE);
	// We return our resources back to the computer
	SDA_free(array);
	// It's good pratice to not leave hanging pointers
	array = NULL;
 	return 0;
}