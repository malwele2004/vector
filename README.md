C is predominantly complex when it comes to making your data types.  
Working with the heap and creating flexible arrays.  
Abstract from this complexity using this vector module.  
Allows you to use the same vector functions(interface) to work with a variety   
of data types.   

Using a stream of bytes.  
This module allows you to specify the word size.   
Which allows you to work through bytes at specified word size

`vector_t vec_int = vec_new(sizeof(int), 1/* strict */);   
for (int i = 0; i < 100 ; i++) {   
  vec_push(&vec_int, 1 /* strict */, &i);  
}  
// strict means break process if heap allocation failed  
// otherwise return fail(0) else success`  
