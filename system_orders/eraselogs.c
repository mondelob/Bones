// Erase all log's files from a directory

#include <stdio.h>
#include <stdlib.h> // EXIT_* Variables
#include <getopt.h> // Argparse

#include <dirent.h> // dirent struct
#include <string.h> // strcmp

// Define the name of the program
#define PROGRAM_NAME "eraselogs"

#define AUTHORS \
	proper_name ("Bruno Mondelo")

// Arguments long options
static struct option long_options[] = {



}