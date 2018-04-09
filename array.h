#include <stdio.h>
#include <stdlib.h>

typedef struct extend_array {
	void **contents;
	void **extension;
	size_t length;
	size_t capacity;
	size_t next;
	int resizing;
} extend_array;

extern void *emalloc(size_t size);
extern void *ecalloc(size_t nmemb, size_t size);
extern extend_array *array_initialize(size_t capacity);
extern void array_append(extend_array *array, void *element);
extern void *array_get(extend_array *array, size_t index);
extern void array_update(extend_array *array, size_t index, void *element);
extern void array_destroy(extend_array *array);
extern void *array_pop(extend_array *array);
