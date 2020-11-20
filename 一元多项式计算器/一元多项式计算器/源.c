#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int comp_str(const void* a, const void* b)
{
	const char** sa = (const char**)a;
	const char** sb = (const char**)b;
	return strcmp(*sa, *sb);
}
void main()
{
	char* str[] = { "xyz","lmn", "kfc", "ufe", "abc", "opq" };
	int n = sizeof(str) / sizeof(str[0]);
	qsort(str, n, sizeof(char*), comp_str);
	for(int i=0;i<n;i++)
	puts(str[i]);
}
