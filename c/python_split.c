#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "python_split.h"

/**
 * Count the number of occurrences of substring in str.
 */
unsigned count_substrings(char *str, char *substring) {
	int count = 0;
	char *tmp = str;
	int len = strlen(substring);

	while ((tmp = strstr(tmp, substring))) {
		count++; // found substring
		tmp += len; // go to end of substring before continuing, so we don't find it again
	}

	return count;
}

/**
 * Split a string into substrings, just like in Python.
 * However, allocate all the memory at once.
 *
 * Pros:
 *   - One free call required to free everything.
 *
 * Cons:
 *   - Perhaps contrary to the norm, calling realloc/free on elements of the struct can cause unexpected problems.
 */
struct split_string *split(char *str, char *separator) {
	char *start_of_part;
	char *end_of_part;
	unsigned chars_copied = 0;
	unsigned part_size;
	int parts_copied = 0;
	int num_parts = count_substrings(str, separator) + 1;
	int sep_len = strlen(separator);

	// allocate enough space for entire result struct
	unsigned size_of_struct = sizeof(struct split_string);
	unsigned size_of_parts_ptrs = num_parts * sizeof(char*);
	unsigned size_of_parts = strlen(str) - ((num_parts - 1) * sep_len) + (num_parts * 1);
	struct split_string* split_str = calloc(1, size_of_struct + size_of_parts_ptrs + size_of_parts);

	// fill it in:

	// part_ptrs are the first part of data[]
	split_str->part_ptrs = (char**) &(split_str->__data);

	// part copies are next part of data[]
	split_str->__parts = ((char*) split_str->__data) + size_of_parts_ptrs;

	// set num parts
	split_str->num_parts = num_parts;

	// add in each part except last, setting part ptrs along the way
	start_of_part = str;
	while ((end_of_part = strstr(start_of_part, separator))) { // find end of current part
		part_size = end_of_part-start_of_part;

		// copy current part into parts, and set its pointer
		strncpy(split_str->__parts + chars_copied, start_of_part, part_size);
		split_str->part_ptrs[parts_copied] = split_str->__parts + chars_copied;

		// keep progress
		chars_copied += part_size + 1; // include null-terminator
		parts_copied++;

		// point to start of the next part
		start_of_part = end_of_part+sep_len;
	}

	// add in last part
	strcpy(split_str->__parts + chars_copied, start_of_part);
	split_str->part_ptrs[parts_copied] = split_str->__parts + chars_copied;

	// bam
	return split_str;
}

// Test
int main() {
	int i;
	struct split_string *s = split("hello there my dear sir!", " ");

	printf("parts: \n");

	for (i = 0; i < s->num_parts; i++) {
		printf("\t%d: %s\n", i, s->part_ptrs[i]);
	}

	free(s);
}
