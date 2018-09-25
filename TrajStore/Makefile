ttest: trajtest.o traj.o
	gcc -g -o ttest trajtest.o traj.o
trajtest.o: trajtest.c traj.c
	gcc -g -c trajtest.c traj.c
clean:
	rm -f *.o ttest
