build/libvector.a: src/main.c 
	gcc -O2 -c $^ -o build/main.o 
	ar rcs $@ build/main.o 

clean: 
	-rm build/* || true 

release: clean build/libvector.a  




