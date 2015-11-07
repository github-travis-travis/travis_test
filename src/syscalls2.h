#ifndef _SYSCALLS_2_
#define _SYSCALLS_2_

#include <sys/types.h>

#include "uthash.h"

// The methods below use user file descriptor tables

typedef enum {
	READ,
	WRITE
} exec_mode;

struct file_descriptor_entry {
	int fd;
	exec_mode mode;
	int inode_number;
	int byte_offset;
};

struct file_descriptor_table {
	int pid;
	int total_descriptors;
	struct file_descriptor_entry *entries;
	UT_hash_handle hh;
}; // We need to use dynamic allocation with that hash table otherwise it doesn't work correctly


ssize_t pread(int fildes, void *buf, size_t nbyte, off_t offset); 
ssize_t pwrite(int fildes, const void *buf, size_t nbyte, off_t offset);

int open(const char *path, int oflag, ... );
int close(int fildes);


// UTILITIES
struct file_descriptor_table * get_file_descriptor_table(int pid);
void set_file_descriptor_table(int pid, struct file_descriptor_table * table);
void delete_file_descriptor_table(int pid);
struct file_descriptor_entry * get_file_descriptor_entry(int fd);
void set_file_descriptor_entry(int pid, struct file_descriptor_entry * entry);

#endif
