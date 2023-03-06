#include "dynamic_array.h"

DynamicArray* dynamic_array_create(void* data, uint32_t data_size)
{
	DynamicArray* array = malloc(sizeof(DynamicArray));
	array->data = data;
	array->used = array->allocated_size = data_size;
	return array;
}

DynamicArray* dynamic_array_create_with_new_data(void* data, uint32_t data_size)
{
	DynamicArray* array = malloc(sizeof(DynamicArray));
	array->data = malloc(data_size);
	memcpy(array->data, data, data_size);
	array->used = array->allocated_size = data_size;
	return array;
}

void dynamic_array_add_data_logarithmic(DynamicArray* array, void* data, uint32_t data_size)
{
	while ((array->used + data_size) > array->allocated_size)
		array->allocated_size *= 2;
	array->data = realloc(array->data, array->allocated_size);
	memcpy(array->data + array->used, data, data_size);
	array->used += data_size;
}

void dynamic_array_add_data_linear(DynamicArray* array, void* data, uint32_t data_size)
{
	if ((array->used + data_size) > array->allocated_size)
		array->allocated_size += data_size;
	array->data = realloc(array->data, array->allocated_size);
	memcpy(array->data + array->used, data, data_size);
	array->used += data_size;
}

void dynamic_array_remove_byte(DynamicArray* array, uint32_t index)
{
	memcpy(array->data + index, array->data + index + 1, array->used - (index+1));
	array->used--;
}

void dynamic_array_remove_data_at_index(DynamicArray* array, uint32_t index, uint32_t index_size)
{
	memcpy(array->data + (index*index_size), array->data + (index*index_size) + index_size, array->used - ((index*index_size) + index_size));
	array->used -= index_size;
}

void dynamic_array_remove_data_at_address(DynamicArray* array, void* address, uint32_t index_size)
{
	memcpy(address, address + index_size, array->used - ((uint64_t)(address - array->used) + index_size));
	array->used -= index_size;
}

void dynamic_array_shrink_allocated_to_mininum(DynamicArray* array)
{
	array->allocated_size = array->used;
	array->data = realloc(array->data, array->used);
}