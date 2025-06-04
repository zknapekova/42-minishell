#include <stdio.h>
#define _BSD_SOURCE
#include <dirent.h>

int main(void)
{
	printf("DT_DIR = %d\n", DT_DIR);
	return 0;
}