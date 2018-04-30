# Dynamically Extensible Array

## Specifications
* Implemented as an array
* Incrementally resizes
* Shrinks intelligently
* Uses generic void pointers

## Commands
* array_initialize is used to create the array with a starting size
* array_append adds another element to the end of the array
* array_get returns the element at the specified index
* array_update changes the element at the specified index to the specified value
* array_destroy frees all the memory used by the array
* array_pop removes and returns the last element of the array

## Properties
### Read Only
	* length is the number of elements in the array
	* capacity is the maximum number of elements the array can hold without expanding
	* resizing is a boolean that is 1 when the array is undergoing a resize (0 otherwise)
### Private
	* contents is the main array
	* extension is used as an overflow when contents is full (becomes contents)
	* next is the next element to copy over to the new array when expanding

## Examples

```c
#include "array.h"

int main() {
	unsigned int i;
	extend_array *array;

	int data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	array = array_initialize(5);
	
	for (i=0; i < 8; i++)
		array_append(array, (void *) (data + i));

	for (i=0; i < array->length; i++)
		printf("%d\n", *((int *) array_get(array, i)));

	array_destroy(array);

	return 0;
}
```

## Algorithm
* When an array reaches its maximum size, a new array of twice the size of the original is allocated
* Every new element is appended to the new array only while resizing
* Each time a new element is added while resizing causes three elements from the old array to be copied over (from the last element to the beginning element of the old array)
* If array_get is used on an array that is resizing, it will return elements from the first array if the index is low enough, otherwise it will return the element from the new array
* array_update will update the value on both arrays while resizing unless the index is greater than the capacity of the old array
* destroy_array will both arrays if necessary
