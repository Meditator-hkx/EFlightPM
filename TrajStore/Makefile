ttest: trajtest.o traj.o
	gcc -g -o ttest trajtest.o traj.o mmap/init.o -I./mmap/
trajtest.o: trajtest.c traj.c
	gcc -g -c trajtest.c traj.c mmap/init.c -I./mmap/
clean:
	rm -f *.o ttest
