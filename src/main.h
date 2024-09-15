#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h> 

typedef struct {
	char *ptr;        // pointer to heap
	size_t word_size, // operating size 
				 word_count;  // allocated
} stream_t ; 

typedef struct {
	stream_t memory;
	size_t n; // Written   
} vector_t ; 

#endif 

