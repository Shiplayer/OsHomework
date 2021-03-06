#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "helpers.h"

ssize_t read_(int fd, void *buf, size_t count){
	int res = 0;
	int rres = 0;
	while(1){
		res = read(fd, buf, count);
		
		if(res == count){
			return rres + res;
		}

		if(res == -1){
			return -1;
		}

		if(res == 0){
			return rres;
		}

		count -= res;
		rres += res;
		buf += res;
	}
}

ssize_t write_(int fd, void* buf, size_t count){
	int res = 0;
	int rres = 0;
	while(1){
		res = write(fd, buf, count);

		if(res == -1) {
			return -1;
		}

		if(res == count) {
			return rres + res;
		}

		count -= res;
		rres += res;
		buf += res;
	}
}

ssize_t read_until(int fd, void* buf, size_t count, char delimeter) {
	int res = 0;
	int rres = 0;
	while(1) {
		res = read(fd, buf, count);
		int i;
		for(i = 0; i < res; i++) {
			if(((char*) buf)[i] == delimeter) {
				return rres + res;
			}
		}

		if(res == count) {
			return rres + res;
		}

		if(res == -1) {
			return -1;
		}

		if(res == 0) {
			return rres;
		}

		rres += res;
		buf += res;
		count -= res;
	}
}


int spawn(const char* file, char* const argv[]){
    pid_t id = fork();
    int err;
    if(id == -1){
        return -1;
    }
    if(id == 0){
        err = execvp(file, argv);
        if(err == -1){
            return -1;
        }
    } else{
        int status;
        err = wait(&status);
        if(err == -1 || !WIFEXITED(status)){
            return -1;
        }

        return WEXITSTATUS(status);
    }

    return -1;
}
