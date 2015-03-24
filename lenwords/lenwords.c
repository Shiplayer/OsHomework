#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <helpers.h>

int main(int argc, char* argv[]) {
    char buf[5000];
    ssize_t rres = 0;
    ssize_t wres = 0;
    int i = 0;
    while(1) {
        ssize_t offset = rres;
        rres = read_until(STDIN_FILENO, buf + offset * sizeof(char), sizeof(buf) - offset * sizeof(char), ' ');
	printf("%d", rres);
        if (rres == 0 ) {
	    return 0;
        }
        if(wres == -1){
			char* err = strerror(errno);
			write_(STDERR_FILENO, err, strlen(err) * sizeof(char));
			return 1;
		}
		
        if(rres == -1){
			char* err = strerror(errno);
			write_(STDERR_FILENO, err, strlen(err) * sizeof(char));
			return 1;
		}

        if (rres == 0) {
                return 0;
        }

        rres += offset;

        offset = 0;
        char has_space = 0;
	int begin = 0, end = 0;
/*        for (i = 0; i < rres; i++) {
            if(buf[i] == ' ') {
		end = i;
		char str[5000];
		printf("%d", end - begin);
		sprintf(str, "%d", end - begin);
                wres = write_(STDOUT_FILENO, str, strlen(str));
		

                if(wres == -1){
                    char* err = strerror(errno);
                    write_(STDERR_FILENO, err, strlen(err) * sizeof(char));
		    return 1;
            	}
                offset = i + 1;
		begin = end + 1;
                has_space = 1;
            }*/
        for (i = 0; i < rres; i++) {
            if(buf[i] == ' ') {
		end = i;
		printf("%d", end - begin);
                //reverse(buf + offset * sizeof(char), i - offset);
                //wres = write_(STDOUT_FILENO, buf + offset * sizeof(char), (i - offset + 1) * sizeof(char));

                if(wres == -1){
                    char* err = strerror(errno);
                    write_(STDERR_FILENO, err, strlen(err) * sizeof(char));
		    return 1;
            	}
		begin = end + 1;
                offset = i + 1;
                has_space = 1;
            }

        }

        if (has_space) {
            rres -= offset * sizeof(char);
            if(rres > 0) {
                memmove(buf, buf + offset * sizeof(char), rres);
            }
        }
    }
}


