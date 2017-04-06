#include <stdio.h>

int main(int argc, char * argv[]) {

	printf("The name of this program is %s\n", argv[0]);
	printf("This program was invoked with %d arguments\n", argc - 1);

	if (argc > 1) {

		printf("The arguments are...\n");
		for (int i = 1; i < argc; i++) {
			printf(" %s\n", argv[i]);
		}

	}

	return 0;

}