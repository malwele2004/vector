#include <assert.h> 
#include <stdlib.h> 
#include <string.h> 
#include "main.h"

#define INIT_SIZE 64 

int stream_valid(stream_t *ptr_stream) {
	return ptr_stream && ptr_stream->ptr;
}

stream_t stream_new(size_t word_size, int strict) {
	assert(word_size);  // prevent bad programmers 

	stream_t stream; 
	stream.ptr = calloc(INIT_SIZE, word_size);  
	if (strict && !stream.ptr) assert(0); // Sorry for bad use of assert 
	stream.word_count = (stream.ptr) ? INIT_SIZE  : 0; 
	stream.word_size = (stream.ptr) ? word_size : 0; 
	return stream; 
}

int stream_delete(stream_t *ptr_stream) {
	if (stream_valid(ptr_stream)) {
		free(ptr_stream->ptr); 
		ptr_stream->ptr = NULL; 
		return 1; 
	}
	return 0; 
}

int stream_grow(stream_t *ptr_stream, int strict) {
	if (stream_valid(ptr_stream)) {
		size_t new_word_count = ptr_stream->word_count * 2.0/* growth factor */ ;  
		char *ptr = reallocarray(ptr_stream->ptr, new_word_count, ptr_stream->word_size); 
		if (ptr) {
			ptr_stream->ptr = ptr; 
			ptr_stream->word_count = new_word_count; 
			return 1; // perfect exit
		}
		if (strict) assert(0); 
	}
	return 0; 
}

int stream_read_write(void *ptr, size_t off, size_t n, stream_t stream, int is_read) {
	if (stream_valid(&stream) && (n)/*nonzero*/ && (off + n) <= stream.word_count) {
		void *stream_ptr = stream.ptr + (off * stream.word_size);
		void *dest = (is_read) ? ptr : stream_ptr;
		void *src = (!is_read) ? ptr : stream_ptr; 
		memcpy(dest, src, stream.word_size * n); // copy bytes
		return 1;
	}
	return 0; 
}

int stream_read(void *ptr, size_t off, size_t n, stream_t stream) {
	return stream_read_write(ptr, off, n, stream, 1); 
}

int stream_write(void *ptr, size_t off, size_t n, stream_t stream) {
	return stream_read_write(ptr, off, n, stream, 0); 
}

int vec_valid(vector_t *ptr_vec) {
	return ptr_vec && stream_valid(&ptr_vec->memory);
}

vector_t vec_new(size_t type_size, int strict) {
	vector_t vec; 
	vec.memory = stream_new(type_size, strict); 
	vec.n = 0; 
	return vec; 
}

int vec_delete(vector_t *ptr_vec) {
	if (vec_valid(ptr_vec)) return stream_delete(&ptr_vec->memory);
	return 0; 
}

// Unsafe: No checks on whether vec has heap allocated data
int is_vec_full(vector_t vec) {
	return vec.n == vec.memory.word_count; 
}

int vec_pop(vector_t *ptr_vec, int strict, void *dest) {
	if (vec_valid(ptr_vec) && ptr_vec->n) {
		stream_read(dest, ptr_vec->n - 1, 1, ptr_vec->memory);  
		ptr_vec->n--; // remove 
		return 1; // success
	}
	return 0; 
}

int vec_push(vector_t *ptr_vec, int strict, void *src) {	
	if (vec_valid(ptr_vec)) {
		if (is_vec_full(*ptr_vec)) {
			if (!stream_grow(&ptr_vec->memory, strict)) goto Failed; 
		}
		stream_write(src, ptr_vec->n, 1, ptr_vec->memory); // write 
		ptr_vec->n++;																														// added 
		return 1; // success
	}
Failed: 
	return 0; 
}
