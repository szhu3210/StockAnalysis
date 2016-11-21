#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

int day(int i, int j)
{
	switch (j) 
	{
	case 1:
		return 31;
		break; /* optional */
	case 2:
		if ((i % 4 == 0) & (i % 100 != 0)) return 29;
		else return 28;
		break; /* optional */
	case 3:
		return 31;
		break; /* optional */
	case 4:
		return 30;
		break; /* optional */
	case 5:
		return 31;
		break; /* optional */
	case 6:
		return 30;
		break; /* optional */
	case 7:
		return 31;
		break; /* optional */
	case 8:
		return 31;
		break; /* optional */
	case 9:
		return 30;
		break; /* optional */
	case 10:
		return 31;
		break; /* optional */
	case 11:
		return 30;
		break; /* optional */
	case 12:
		return 31;
		break; /* optional */
	
	default: /* Optional */
		return -1;
	}
}

void main()
{
	FILE *f = fopen("/home/troy/Stock Analysis/1Data/1date/date.txt", "w");
	int i,j,k;
	int d,dmax;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	dmax = 10000 * (tm.tm_year + 1900) + 100 * (tm.tm_mon + 1) + tm.tm_mday;

	printf("%d\n", dmax);

	for (i = 1990; i < 3000; i++)
		for (j = 1; j < 13; j++)
			for (k = 1; k <= day(i, j); k++)
				if ((d= 10000 * i + 100 * j + k)<=dmax) fprintf(f, "%d\n", d);
	fclose(f);
}
