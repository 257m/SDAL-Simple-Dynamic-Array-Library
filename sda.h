/*
    SDAL aka Simple Dynamic Array Library is a dynamic array implemention designed to be small and simple
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
    `Simple Dynamic Array Library` written by Maaz S. Ali.

    5th of March, 2023
    Maaz S. Ali, author
*/

#ifndef SDA_H
#define SDA_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef memcpy
	#define INCLUDE_MEMCPY
	extern void* memcpy (void* dest, const void* src, size_t len);
#endif

// Simple resizable/dynamic array implementation
typedef struct {
	void*  		data;          	// stores a pointer to the data the array is storing. This will grow and shrink as needed.
	uint32_t	used;          	// stores the amount of used bytes in the array.
	uint32_t	allocated_size;	// stores the total amount of bytes that have been allocated. This will never be less than used.
} SDA;


extern SDA* SDA_create(void* data, uint32_t data_size);
	/* 
		Sets the array's data pointer to the pointer passed in and
		the amount of used data and allocated both become set to the
		data_size. It is dangerous to pass in the address of stack allocated
		memory to this function as it is going to be realloc'd later on.
	*/

extern SDA* SDA_create_with_new_data(void* data, uint32_t data_size);
	/*
		Same as SDA_create but will allocate new space for the data
		and will copy the data passed to that allocation. This will be used when
		you need to put data that is on the stack into a SDA intiliazation.
	*/

extern void SDA_add_data_logarithmic(SDA* array, void* data, uint32_t data_size);
	/*
		Copy the data passed onto the end of the SDA.
		If there is not enough allocated space it will allocate more
		space as needed, doubling in size each time a new allocation is needed.
		This way the amount of realloc calls is kept to a minimum.
		If you fear the amount of allocated space is wasteful you can shrink
		the array or linearly add data as needed with SDA_add_data_linearly.
	*/

extern void SDA_add_data_linear(SDA* array, void* data, uint32_t data_size);
	/*
		Same as SDA_add_data_logarithmic but will
		add to the allocated size by data_size if it the amount of
		used data is going to overflow the amount of space we allocated.
	*/

extern void SDA_insert_element_logarithmic(SDA* array, void* data, uint32_t data_size, uint32_t index);
	/*
		Inserts data at index*data_size and will shift over
		the rest of the array to put in there. In most cases
		it is better to manually insert into the array to avoid
		the time it takes to shift data. It will double the allocated
		size if the buffer threatens to overflow.
	*/

extern void SDA_insert_element_linear(SDA* array, void* data, uint32_t data_size, uint32_t index);
	/*
		Inserts data at index*data_size and will shift over
		the rest of the array to put in there. In most cases
		it is better to manually insert into the array to avoid
		the time it takes to shift data. It will allocated just
		enough space for the element to fit if it does not fit with
		the current size of the buffer.
	*/

#ifdef SDA_ADD_DATA_DEFAULT
	#define SDA_add_data SDA_add_data_##SDA_ADD_DATA_DEFAULT
#else
	#define SDA_add_data SDA_add_data_logarithmic
#endif
#ifdef SDA_INSERT_ELEMENT_DEFAULT
	#define SDA_insert_element SDA_insert_element_##SDA_INSERT_ELEMENT_DEFAULT
#else
	#define SDA_insert_element SDA_insert_element_logarithmic
#endif
	/*
		The user can specify the add data default before they include the header
	 	If it is not defined it defaults to logarithmic
	*/

extern void SDA_remove_byte(SDA* array, uint32_t index);
	/*
		Removes a byte from anywhere in the array.
		It will shift all other data and effectively write over the byte
		with the byte ahead of it. If it is the last byte it will still
		exist but the array used integer will be less than it's index.
	*/

extern void SDA_remove_data_at_index(SDA* array, uint32_t index, uint32_t index_size);
	/*
		Given an index and an element size. It will remove the element
		at that index by shifting over the data from the rest of the
		array to overwrite it. If it is the last element it will not be
		overwritten but it will be beyond the array's used data size.
	*/

extern void SDA_remove_data_at_address(SDA* array, void* address, uint32_t index_size);
	/*
		Same as SDA_remove_data_at_index but rather than be
		given a index it is given a address of the data needed to be
		removed. Same as before since the data is being shifted it
		not necessarily always overwritten if it is the last element.
	*/

extern void SDA_shrink_allocated_to_mininum(SDA* array);
	/*
		This reallocates the data to the size of array used
		and makes the allocated size equal to the amount used.
	*/

#define SDA_shrink_used_by_amount(array, amount)	\
{                                               	\
	array->used -= amount                       	\
}
	/*
		Simply decrements the amount of used data.
	*/

extern void SDA_free(SDA* array);
	/*
		Frees the srtucture of the as well as the data it contains
	*/

#endif /* SDA_H */
