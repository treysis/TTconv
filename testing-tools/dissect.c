#include <stdio.h>
#include <string.h>

//non skip version strtok
char *my_strtok_r(char *str, const char *delims, char **store){
    char *p, *wk;
    if(str != NULL){
        *store = str;
    }
    if(*store == NULL) return NULL;
    //*store += strspn(*store, delims);//skip delimiter
    if(**store == '\0') return NULL;
    p=strpbrk(wk=*store, delims);
    if(p != NULL){
        *p='\0';
        *store = p + 1;
    } else {
        *store = NULL;
    }
    return wk;
}

char *my_strtok(char *str, const char *delims){
    static char *p;
    return my_strtok_r(str, delims, &p);
}



int main() {
    char *nmea_msg;
    char arr[13][16];

    nmea_msg = "$GPRMC,100900.000,V,4715.2229,N,01120.5234,E,,,221099,,,N*71";

    fprintf(stdout, "NMEA: %s\n", nmea_msg);


    int i = 0;
    int j = 0;
    while(i < strlen(nmea_msg))
    {
        int k = 0;
        while (nmea_msg[i] != ',' && i < strlen(nmea_msg))
        {
            arr[j][k] = nmea_msg[i];
            i++; k++;
        }
        /*
        if (nmea_msg[i] == nmea_msg[i-1])
        {
            arr[j][0] = '\0';
            arr[j][0] = '\n';
        }
        */

        arr[j][k] = '\0';
        fprintf(stdout, "%s", arr[j]);
        j++;
        printf("\n");
        i++;
    }

    fprintf(stdout, "* TTconv ended unexpectedly\n");
    fprintf(stderr, "ERROR: * TTconv ended unexpectedly\n");
    return 0;
}

