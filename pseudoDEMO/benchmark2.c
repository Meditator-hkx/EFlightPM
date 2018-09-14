# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define FILE_NAME_PREFIX "/home/viking/HuangKaixin/pseudoDEMO/bench-stage"

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("not enough args!\n");
		return 0;
	}
	int testtype = atoi(argv[1]);
	int testsize = atoi(argv[2]);

	int delay, result;
	switch (testtype) {
	case 1: // fast
		delay = 100000;
		result = 2 * testsize / 100000;
		break;
	case 2: // middle
		delay = 125000;
		result = 2.4 * testsize / 100000;
		break;
	case 3: // slow
		delay = 300000;
		result = 6.3 * testsize / 100000;
		break;
	default:
		printf("unknown testtype!\n");
		return 0;
	}

	char filename[100] = FILE_NAME_PREFIX;
	char tstr[10];
	tstr[0] = '0' + testtype;
	tstr[1] = '\0';
	strcat(filename, tstr);
	printf("%s\n", filename);

	for (int i=0; i<=testsize;) {
		usleep(delay);
		FILE * fp = fopen(filename, "w");
		fprintf(fp, "%d", i);
		fclose(fp);
		i += 10000;
	}
	usleep(300000);
	FILE * fp = fopen(filename, "w");
	fprintf(fp, "$ 1 1 1 %d\n", result);
	fclose(fp);

	return 0;
}
