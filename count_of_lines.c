// by Moskovchenko Nastya
// Count lines on all files like wc -l filename1 filename2


#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// count lines for all files
static uintmax_t total_lines;

// printing options
static bool print_lines;

// used to make neat columns
static unsigned int number_width;

// format string for printing counts
static const char *number_format;

// number of files successfully opened and read
static unsigned int files_read;

// count how many digits are in a number
static unsigned int ndigits(uintmax_t x) {
    if (x == 0) {
        return 1;
    } else {
        return (unsigned int) (floor(log10(x)) + 1);
    }
}

// compute the optimal number width for the given files
static int compute_number_width(int nfiles, char **files) {
    uintmax_t total_size = 0;

    for (int i = 0; i < nfiles; i++) {
        if (!streq(files[i], "-")) {
            struct stat st;

            if (stat(files[i], &st) == 0) {
                total_size += st.st_size;
            }
        }
    }

    return ndigits(total_size);
}

// print the number of lines in the file
void print_counts(uintmax_t lines, const char *file) {
    if (print_lines) printf(number_format, number_width, lines);

    if (file == NULL) {
        puts("-");
    } else {
        puts(file);
    }
}

// count the number of lines in the file
// if filename is NULL, count from stdin
int count(const char *filename) {
    FILE *fp;

    if (filename == NULL) {
        fp = stdin;
    } else if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "wc: %s: %s\n", filename, strerror(errno));
        return 1;
    }

    int lines;
    lines = 0;

    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        // count lines
        if (ch == '\n') {
            lines++;
        }

    }

    if (fp != stdin) fclose(fp);
    files_read++;

    print_counts((uintmax_t) lines, filename);

    total_lines += lines;

    return 0;
}

int main(int argc, char *argv[]) {
    // default option values
    print_lines = false;

    // parse options
    while ((argc > 1) && (argv[1][0] == '-') && (!streq(argv[1], "-"))) {
        if (streq(argv[1], "-l") || streq(argv[1], "--lines")) {
            print_lines = true;
        } 

        argv++;
        argc--;
    }

    // if no options were specified, print everything
    if (!(print_lines) {
        print_lines = true;
    }

    number_width = (unsigned int) compute_number_width(argc - 1, argv + 1);
    number_format = "%*" PRIuMAX " ";

    // if no args were given, count from stdin
    if (argc == 1) {
        count(NULL);
    } else {
        for (int i = 1; i < argc; i++) {
            if (streq(argv[i], "-")) {
                count(NULL);
            } else {
                count(argv[i]);
            }
        }
    }

    // print total counts if there was more than one file
    if (files_read > 1) {
        print_counts(total_lines, "total");
    }

    return EXIT_SUCCESS;
}
