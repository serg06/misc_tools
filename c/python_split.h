struct split_string {
	unsigned num_parts; // number of parts
	char **part_ptrs; // point to each part in here
	char *__parts; // point to beginning of part copies
	char __data[]; // rest of data (i.e. each part ptr, each part copy.)
};

struct split_string *split(char *str, char *separator);
unsigned count_substrings(char *str, char *substring);
