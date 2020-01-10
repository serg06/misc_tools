#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>


// extern int regexec (const regex_t *__restrict __preg,
//         const char *__restrict __string, size_t __nmatch,
//         regmatch_t __pmatch[__restrict_arr],
//         int __eflags);

int re_replace(char *str, char *regex_str, char *replace_with) {
	regex_t regex;
	int reti;
	// char msgbuf[100];

	/* Compile regular expression */
	reti = regcomp(&regex, regex_str, REG_EXTENDED);
	if (reti) {
	    fprintf(stderr, "Could not compile regex\n");
	    exit(1);
	}

	/* Execute regular expression */
	reti = regexec(&regex, "abc", 0, NULL, 0);
	if (!reti) {
	    puts("Match");
	}
	else if (reti == REG_NOMATCH) {
	    puts("No match");
	}
	else {
	    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
	    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
	    exit(1);
	}

}