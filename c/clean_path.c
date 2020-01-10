#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void remove_dup_slashes(char *str) {
	char *start_of_slashes;
	char *end_of_slashes;

	char *end_of_str = str + strlen(str);

	// while there are slashes remaining, find start of slashes
	while ((start_of_slashes = strchr(str, '/'))) {
		// find end of current slashes
		end_of_slashes = start_of_slashes+1;
		while(end_of_slashes[0] == '/') {
			end_of_slashes++;
		}

		// given n slashes, move the tail of the string to cover up the last n-1 slashes.
		memmove(start_of_slashes + 1, end_of_slashes, (end_of_str-end_of_slashes)+1);
		str = start_of_slashes+1;
		end_of_str -= (end_of_slashes - (start_of_slashes+1));
	}
}

int main(int argc, char **argv) {
	printf("argc: %d\n", argc);
	printf("input : %s\n", argv[1]);
	remove_dup_slashes(argv[1]);
	printf("output: %s\n", argv[1]);
}
