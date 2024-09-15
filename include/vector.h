#ifndef INF_TYPES_H 
#define INF_TYPES_H 

#include "../src/main.h" 

extern int stream_valid(stream_t*); 
extern stream_t stream_new(size_t/*word size*/, int /*strict*/); 
extern int stream_delete(stream_t*); 
extern int stream_grow(stream_t*, int/*strict*/); 
extern int stream_read(void* /*dest*/, size_t/*offset*/, size_t/*n*/, stream_t); 
extern int stream_write(void* /*src*/, size_t/*offset*/, size_t /*n*/, stream_t); 
extern vector_t vec_new(size_t /*type_size*/, int /*strict */);
extern int vec_delete(vector_t*);  
extern int vec_pop(vector_t*, int/*strict*/, void* /*dest*/); 
extern int vec_push(vector_t*, int /*strict*/, void* /*src*/); 

#endif 
