/*
    This is an example usage of SDAL aka Simple Dynamic Array Library which is a dynamic array implemention designed to be small and simple
    Copyright (C) 2023, Maaz S. Ali https://github.com/257m/SDAL-Simple-Dynamic-Array-Library

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    You can email me at 1alimaze@gmail.com if you have any questions about the program

    Maaz S. Ali, hereby disclaims all copyright interest in the program
    `Simple Dynamic Array Library Example` written by Maaz S. Ali.

    5th of March, 2023
    Maaz S. Ali, author
*/

#include <stdio.h>
#include "sda.h"

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
