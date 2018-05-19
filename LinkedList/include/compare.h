#ifndef COMPARE_H
#define COMPARE_H
#include "string.h"
int compare_int (const void *const a, const void *const b);
int compare_string (const void *const a, const void *const b);
int compare_double (const void *const a, const void *const b);

int compare_int (const void *const a, const void *const b)
{
  const int *da = (const int *) a;
  const int *db = (const int *) b;

  return (*da > *db) - (*da < *db);
}

int compare_string (const void *a, const void *b)
{
    return strcmp( (const char *)a, (const char*)b );
}

int compare_double (const void *const a, const void *const b)
{
  const double *da = (const double *) a;
  const double *db = (const double *) b;

  return (*da > *db) - (*da < *db);
}
#endif // ifndef COMPARE_H
