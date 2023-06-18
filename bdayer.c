/* ISC License
 * Copyright 2023 Ivan Kovmir */

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/* Constants and Macros */
#define BUF_SIZE 256

/* Environmental variable that points to the roster. */
#define ROSTER_LOCATION_ENV "BDAYER_ROSTER"
/* A roster character used to separate dates and names. */
#define ROSTER_SEPARATOR ","
/* Convert the number of seconds to the number days. */
#define SECONDS_TO_DAYS(seconds) ((seconds) / (60 * 60 * 24))

/* Function Prototypes */
/* Prints error and terminates the execution. */
static inline int print_err(const char *);
/* Returns a name pointer within a line from the roster. */
static inline char *name_pt(const char *);
/* Count the days left to a given date. */
static int days_to(unsigned int, unsigned int, int *);

inline int
print_err(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

inline char *
name_pt(const char* bday)
{
	/* Find the second occurence of ROSTER_SEPARATOR. */
	return strstr(
		strstr(bday, ROSTER_SEPARATOR)+1,
		ROSTER_SEPARATOR
	)+1;
}

int
days_to(unsigned int bmonth, unsigned int bday, int *diffdays)
{
	time_t current_time = time(NULL);
	struct tm *current_date = localtime(&current_time);
	struct tm  birth_date = {
		.tm_mon  = bmonth-1, /* Count from 0. */
		.tm_mday = bday,
		.tm_year = current_date->tm_year,
	};

	time_t birth_time = mktime(&birth_date);
	if (birth_time == -1)
		return birth_time;

	double difference = difftime(birth_time, current_time);
	*diffdays = ceil(SECONDS_TO_DAYS(difference));
	return 0;
}

int
main(void)
{
	FILE *roster_file;
	char *tmp;
	char buf[BUF_SIZE];
	unsigned int bmonth, bday;
	int diffdays;

	if (!getenv(ROSTER_LOCATION_ENV))
		print_err("$"ROSTER_LOCATION_ENV" is undefined.");

	roster_file = fopen(getenv(ROSTER_LOCATION_ENV), "r");
	if (!roster_file)
		print_err("Failed to open $"ROSTER_LOCATION_ENV" file.");

	while (fgets(buf, BUF_SIZE, roster_file)) {
		/* Skip comments and empty lines. */
		if (buf[0] == '#' || buf[0] == '\n')
			continue;
		/* Discard comments at the end and newline characters. */
		if ( (tmp = strchr(buf, '#')) != NULL ||
		     (tmp = strchr(buf, '\n')) != NULL )
			*tmp = 0;

		/* Parse date. */
		if (sscanf(buf, "%u"ROSTER_SEPARATOR"%u"ROSTER_SEPARATOR,
		           &bmonth, &bday) != 2) {
			fprintf(stderr, "Invalid syntax: %s\n", buf);
			continue;
		}
		/* Count due days. */
		if (days_to(bmonth, bday, &diffdays)) {
			fprintf(stderr, "Invalid syntax: %s\n", buf);
			continue;
		}
		/* Print the result. */
		printf("%d day(s)\t%s\n", diffdays, name_pt(buf));
	}

	fclose(roster_file);
	return 0;
}
