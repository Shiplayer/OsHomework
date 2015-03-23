#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <helpers.h>

void reverse(char* buf, int len) {
    int i;
    char t;
    for(i = 0; i < len/2; i++) {
        t = buf[i];
        buf[i] = buf[len - i - 1];
        buf[len - i - 1] = t;
    }
}

int main(int argc, char* argv[]) {
    char buf[5000];
    ssize_t rres = 0;
    ssize_t wres = 0;
    int i = 0;
    while(1) {
        ssize_t offset = rres;
        rres = read_until(STDIN_FILENO, buf + offset * sizeof(char), sizeof(buf) - offset * sizeof(char), ' ');

        if (rres == 0 || rres == -1) {
            reverse(buf, offset);
            wres = write_(STDOUT_FILENO, buf, offset * sizeof(char));
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
        for (i = 0; i < rres; i++) {
            if(buf[i] == ' ') {
                reverse(buf + offset * sizeof(char), i - offset);
                wres = write_(STDOUT_FILENO, buf + offset * sizeof(char), (i - offset + 1) * sizeof(char));

                if(wres == -1){
                    char* err = strerror(errno);
                    write_(STDERR_FILENO, err, strlen(err) * sizeof(char));
            	}
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

