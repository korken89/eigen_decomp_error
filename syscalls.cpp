#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstddef>
#include <new>

extern "C" {
__attribute__((used))
caddr_t _sbrk_r(struct _reent *, int)
{
  return (caddr_t)-1;
}

__attribute__((used))
void* malloc(size_t)
{
  return NULL;
}

__attribute__((used))
void free(void *)
{
}

__attribute__((used))
void abort()
{
  while(1);
}

__attribute__((used))
int _read_r(struct _reent *, int, char *, int)
{
  return -1;
}

__attribute__((used))
int _lseek_r(struct _reent *, int, int, int)
{
  return 0;
}

__attribute__((used))
int _write_r(struct _reent *, int , char * , int len)
{
  return len;
}

__attribute__((used))
int _close_r(struct _reent *, int)
{
  return 0;
}

__attribute__((used))
int _fstat_r(struct _reent *, int, struct stat *)
{
  return 0;
}

int _isatty_r(struct _reent *, int)
{
  return 1;
}

}

void* operator new(std::size_t)
{
  abort();
  return (void*)1;
}

void* operator new(std::size_t, const std::nothrow_t&)
{
  abort();
  return (void*)1;
}

void* operator new[](std::size_t)
{
  abort();
  return (void*)1;
}

void* operator new[](std::size_t, const std::nothrow_t&)
{
  return (void*)1;
}

void operator delete(void*)
{
}

void operator delete(void*, std::size_t)
{
}

void operator delete(void*, const std::nothrow_t&)
{
}
