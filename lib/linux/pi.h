#ifndef PI_H
#define PI_H

int open_input_file(char * fn);
int open_output_file(char * fn);
int dd(int in_fd, int out_fd, size_t buffersize);

#endif /* PI_H */
