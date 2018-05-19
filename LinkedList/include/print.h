#ifndef PRINT_H
#define PRINT_H value
#include <stdio.h>
#include <string.h>

void print_int (const void* data)
{
    printf("%d", *(int*)data);
}


void print_double (const void* data)
{
    printf("%lf", *(double*)data);
}

void print_string (const void* data)
{
    printf("%s", (const char*)data);
}


#endif // ifndef PRINT_H
