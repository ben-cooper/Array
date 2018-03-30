#include "array.h"

void *emalloc(size_t size) {
	void *result;
	if ((result = malloc(size)) == NULL) {
		perror("malloc");
		exit(1);
	}
	return result;
}

void *ecalloc(size_t nmemb, size_t size) {
	void *result;
	if ((result = calloc(nmemb, size)) == NULL) {
		perror("calloc");
		exit(1);
	}
	return result;
}

extend_array *array_initialize(size_t capacity) {
	extend_array *result;
	void *contents;

	result = (extend_array *) ecalloc(1, sizeof(extend_array));
	contents = emalloc(capacity * sizeof(void *));

	result->contents = contents;
	result->capacity = capacity;

	return result;
}

void array_append(extend_array *array, void *element) {
	int i;
	
	/* array is full and needs to be extended */
	if (array->length == array->capacity) {
		array->resizing = 1;
		array->next = array->capacity - 1;
		array->capacity *= 2;
		array->extension = emalloc(array->capacity * sizeof(void *));
	}

	/* array is resizing new elements should go into the new array
	 * extension and old element are incrementally moved over */
	if (array->resizing) {
		array->extension[array->length] = element;
		
		for(i=0; i < 3; i++) {
			array->extension[array->next] = array->contents[array->next];
			/* array has finished resizing, so extension can become the
	 		* main contents */
			if (array->next == 0) {
				array->next = 0;
				free(array->contents);
				array->contents = array->extension;
				array->resizing = 0;
				break;
			}
			array->next--;
		}
	/* array is not a full capacity, inserting as normal */
	} else {
		array->contents[array->length] = element;
	}


	array->length++;
}

void *array_get(extend_array *array, size_t index) {
	/* checking for out of bounds */
	if (!(index < array->length))
		return NULL;

	/* if the array is resizing, search both arrays */
	if (array->resizing && index > (array->capacity / 2))
		return array->extension[index];

	return array->contents[index];
}

void array_destroy(extend_array *array) {
	free(array->contents);
	if (array->resizing)
		free(array->extension);
	free(array);
}

void array_update(extend_array *array, size_t index, void *element) {
	/* checking for out of bounds */
	if (!(index < array->length))
		return;

	if (array->resizing)
		array->extension[index] = element;

	array->contents[index] = element;
}
