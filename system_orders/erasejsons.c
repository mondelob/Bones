// Test ifdef

#include <stdio.h>
#include <stdlib.h> // EXIT_* Variables
#include <getopt.h> // Argparse

#include <dirent.h> // dirent struct
#include <string.h> // strcmp

// The name of the program
#define PROGRAM_NAME "erasejsons"

#define AUTHORS \
  proper_name ("Bruno Mondelo")

// Argument long options
static struct option long_options [] = {
	{"directory", required_argument, NULL, 'd'},
	{"help", no_argument, NULL, 'h'},
	{"verbose", no_argument, NULL, 'v'},
	{NULL, 0, NULL, 0}
};

void usage(int status) {

	// Error, show only help usage
	if (status != EXIT_SUCCESS) {
		fprintf(stderr, "Try '%s --help' for more information\n", PROGRAM_NAME);
	}
	else {
		// Show usage
		printf("Usage: %s [OPTION]...\n", PROGRAM_NAME);
		// Info about program
		printf("Erases all json files from the directory\n");
		printf("Without directory specefied erases from the actual directory\n");
		// Show arguments
		printf("\n\
  -d, --directory=DIRECTORY         sets the directory to erase\n\
  -h, --help                        shows this message\n\
  -v, --verbose                     shows all the erased items\n");
	}

	exit(status);

}

int main(int argc, char * argv[]) {

	int ok_end = 0;
	int is_verbose = 0;
	char * directory = ".";
	struct dirent  * dir_info;
	int rmd;
	char * name, * filename, file_type;
	size_t name_len;

	int opt;

	// Parse arguments
	while ((opt = getopt_long(argc, argv, "d:hv", long_options, NULL)) != -1) {
		switch(opt) {
			case 'd':
				directory = optarg;
				if (directory[strlen(directory) - 1] == '/') {
					directory[strlen(directory) - 1] = '\0';
				}
				break;
			case 'h':
				usage(EXIT_SUCCESS);
				break;
			case 'v':
				is_verbose = 1;
				break;
			default:
				usage(EXIT_FAILURE);
		}
	}

	// Open and read directory
	// Exit if we cannot open directory
	DIR * dd;
	if ((dd = opendir(directory)) == NULL) {
		fprintf(stderr, "%s: cannot access directory: '%s'\n", PROGRAM_NAME, directory);
		return EXIT_FAILURE;
	}
	
	int index = 0;
	while ((dir_info = readdir(dd)) != NULL) {
		// We only want to erase regular files
		// that ends with .json
		file_type = dir_info -> d_type;
		name = (char *)dir_info -> d_name;
		name_len = strlen(name);
		if (file_type == DT_REG && name_len >= 5 && 
			(strcmp(name + name_len - 5, ".json") == 0) || 
			(strcmp(name + name_len - 5, ".JSON") == 0)) {
			filename = malloc(strlen(directory) + strlen(name) + 2);
			strcpy(filename, directory);
			strcat(filename, "/");
			strcat(filename, name);
			if ((rmd = remove(filename)) != 0) {
				fprintf(stderr, "%s: cannot erase file: '%s'\n", PROGRAM_NAME, filename);
				ok_end = 1;
			}
			else if (is_verbose) {
				printf("%s\n", filename);
			}
		}
	}

	closedir(dd);
	
	if (ok_end == 0) {
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}

}
