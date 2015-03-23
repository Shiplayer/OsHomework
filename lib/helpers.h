#ifndef __HELPERS_H__
#define __HELPERS_H__

ssize_t read_(int, void*, size_t);
ssize_t write_(int, void*, size_t);
ssize_t read_until(int, void*, size_t, char);
void report_error();

#endif //__HELPERS_H__
