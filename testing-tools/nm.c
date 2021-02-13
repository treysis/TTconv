#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE    1

int main(int argc, char **argv){
    unsigned char     buffer[BUFFERSIZE];
    FILE                         *instream;
    int                            bytes_read=0;
    int                            buffer_size=0;


    buffer_size=sizeof(unsigned char)*BUFFERSIZE;
    /* open stdin for reading */
    //instream=fopen("/dev/stdin","r");
    instream=fopen("/var/run/gpspipe2", "r");

    /* did it open? */
    if(instream!=NULL){
        /* read from stdin until it's end */
        while((bytes_read=fread(&buffer, buffer_size, 1, instream))==buffer_size){
            fprintf(stdout, "%c", buffer[0]);
        }
    }
    /* if any error occured, exit with an error message */
    else{
        fprintf(stderr, "ERROR opening stdin. aborting.\n");
        exit(1);
    }

    return(0);
}

