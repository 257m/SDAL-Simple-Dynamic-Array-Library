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

#include "SDA.h"

SDA* SDA_create(void* data, uint32_t data_size)
{
	SDA* array = malloc(sizeof(SDA));
	array->data = data;
	array->used = array->allocated_size = data_size;
	return array;
}

SDA* SDA_create_with_new_data(void* data, uint32_t data_size)
{
	SDA* array = malloc(sizeof(SDA));
	array->data = malloc(data_size);
	memcpy(array->data, data, data_size);
	array->used = array->allocated_size = data_size;
	return array;
}

void SDA_add_data_logarithmic(SDA* array, void* data, uint32_t data_size)
{
	while ((array->used + data_size) > array->allocated_size)
		array->allocated_size *= 2;
	array->data = realloc(array->data, array->allocated_size);
	memcpy(array->data + array->used, data, data_size);
	array->used += data_size;
}

void SDA_add_data_linear(SDA* array, void* data, uint32_t data_size)
{
	if ((array->used + data_size) > array->allocated_size)
		array->allocated_size += (data_size - (array->allocated - array->used));
	array->data = realloc(array->data, array->allocated_size);
	memcpy(array->data + array->used, data, data_size);
	array->used += data_size;
}

void SDA_remove_byte(SDA* array, uint32_t index)
{
	memcpy(array->data + index, array->data + index + 1, array->used - (index+1));
	array->used--;
}

void SDA_remove_data_at_index(SDA* array, uint32_t index, uint32_t index_size)
{
	memcpy(array->data + (index*index_size), array->data + (index*index_size) + index_size, array->used - ((index*index_size) + index_size));
	array->used -= index_size;
}

void SDA_remove_data_at_address(SDA* array, void* address, uint32_t index_size)
{
	memcpy(address, address + index_size, array->used - ((uint64_t)(address - array->used) + index_size));
	array->used -= index_size;
}

void SDA_shrink_allocated_to_mininum(SDA* array)
{
	array->allocated_size = array->used;
	array->data = realloc(array->data, array->used);
}

void SDA_free(SDA* array)
{
	free(array->data);
	free(array);
}