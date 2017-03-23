void clear_screen(char * displayptr) {
	
	for (int i = 0; i < 80 * 25 * 2; i = i + 2) {
		
		// Blank character
		displayptr[i] = ' ';
		// Light grey
		displayptr[i + 1] = 0x09;
	}
	
	
}


void kmain(void) {
	
	
	const char * str = "Hello Kernel!";
	
	// Video Memory acces
	char * vidptr = (char *)0xb8000;
	
	int j = 0;
	int i = 0;
	
	// Clear screen
	clear_screen(vidptr);
	
	while (str[j] != '\0') {
		
		// Add the character
		vidptr[i] = str[j];
		
		// Color
		vidptr[i + 1] = 0x09;
		
		j++;
		i = i + 2;
		
	}
	
	return;
	
}
