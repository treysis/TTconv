/* Conversion tool to convert faulty NMEA0183 $GPRMC sentences on TomTom devices with  */
// AR1520 and GL1 GPS chipsets, which are affected by the GPS WNRO Event               */

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFERSIZE    1

/* C program to find date after adding given number of days.                                     */
// Modified after original source from Anuj Chauhan (and additions by Mithun Kumar, ayush2904):  */
// https://www.geeksforgeeks.org/date-after-adding-given-number-of-days-to-the-given-date/       */

/* Return if year is leap year or not. */
int isLeap(int y)
{
    if ((y%100 != 0 && y%4 == 0) || y %400 == 0)
        return 1;

    return 0;
}


/* Given a date, returns number of days elapsed from the  beginning of the current year (1st  jan). */
int offsetDays(int d, int m, int y)
{
    int offset = d;

    switch (m - 1)
    {
    case 11:
        offset += 30;
    case 10:
        offset += 31;
    case 9:
        offset += 30;
    case 8:
        offset += 31;
    case 7:
        offset += 31;
    case 6:
        offset += 30;
    case 5:
        offset += 31;
    case 4:
        offset += 30;
    case 3:
        offset += 31;
    case 2:
        offset += 28;
    case 1:
        offset += 31;
    }

    if (isLeap(y) && m > 2)
        offset += 1;

    return offset;
}


/* Given a year and days elapsed in it, finds date by storing results in d and m. */
void revoffsetDays(int offset, int y, int *d, int *m)
{
    int month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (isLeap(y))
        month[2] = 29;

    int i;
    for (i = 1; i <= 12; i++)
    {
        if (offset <= month[i])
            break;
        offset = offset - month[i];
    }

    *d = offset;
    *m = i;
}

/* Add x days to the given date. */
char * addDays(int d1, int m1, int y1, int x) 
{
    int offset1 = offsetDays(d1, m1, y1); 
    int remDays = isLeap(y1)?(366-offset1):(365-offset1); 
  
    /* y2 is going to store result year and offset2 is going to store */
    /* offset days in result year. */
    int y2, offset2;
    if (x <= remDays)
    {
        y2 = y1; 
        offset2 = offset1 + x;
    }

    else
    {
        /* x may store thousands of days. */
        /* We find correct year and offset in the year. */
        x -= remDays;
        y2 = y1 + 1;
        int y2days = isLeap(y2)?366:365;
        while (x >= y2days)
        {
            x -= y2days;
            y2++;
            y2days = isLeap(y2)?366:365;
        }
        offset2 = x;
    }

    /* Find values of day and month from offset of result year. */
    int m2, d2;
    revoffsetDays(offset2, y2, &d2, &m2);

    //printf("d2 = %i, m2 = %i, y2 = %i\n", d2, m2, y2);

    /* Convert yyyy to yy */
	y2 = y2%100;

    char str[7] = {};
	sprintf(str, "%02d%02d%02d", d2, m2, y2);
	//str[6] = '\0';

    return strdup(str);
}

/* Modified from Devendra Aaru/MADMAX/https://gist.github.com/DevNaga's source: */
/* https://gist.github.com/DevNaga/fce8e166f4335fa777650493cb9246db             */
int nmea0183_checksum(char *nmea_data)
{
    int crc = 0;
    int i;

    /* omit the first $ sign, last two bytes of original CRC + the * sign already removed */
    for (i = 1; i < strlen(nmea_data); i++) {
        crc ^= nmea_data[i];
    }

    return crc;
}

/* NMEA conversion */
char * convNMEA(char *nmea_msg)
{
    //int d = 01, m = 02, y = 2000;
    int d, m, y;
    int x = 7168;
    int crc;

    //strcpy(nmea_msg, "$GPRMC,081836.000,A,3251.65,S,14207.36,E,000.0,360.0,130999,,,E*7E");
    //strcpy(nmea_msg, "$GPRMC,191029.000,V,,,,,,,211099,,,N*4D");
    //strcpy(nmea_msg, "$GPRMC,182724.000,V,,,,,,,,,,N*47");
    //strcpy(nmea_msg, "$GPRMC,100900.000,V,4715.2229,N,01120.5234,E,,,221099,,,N*71");

    /* Dissecting NMEA sentence and extract date --> arr[9] */
    ////printf("Dissecting...\n");
    char arr[13][16];
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
        arr[j][k] = '\0';

        //printf("%s\n", arr[j]);
        j++;
        i++;
    }
    //printf("NMEA-date (old): %s\n", arr[9]);

    //char * newDate;
    char *newDate;
    if (!strcmp(arr[9], ""))
    {
        newDate = "";
    }
    else
    {
        /* convert wrong ddmmyy to d, m, y */
        char day[3];
        char mon[3];
        char yea[3];

        day[0] = arr[9][0];
        day[1] = arr[9][1];
        mon[0] = arr[9][2];
        mon[1] = arr[9][3];
        yea[0] = arr[9][4];
        yea[1] = arr[9][5];
        day[2] = '\0';
        mon[2] = '\0';
        yea[2] = '\0';

        d = strtol(day, NULL, 10);
        m = strtol(mon, NULL, 10);
        y = strtol(yea, NULL, 10);

        //printf("Month: ->");
        //printf("%i<-\n", m);

        if (y==99) {
            y = 1999;
        }
        else {
            y = y+2000;
        }

   	    //printf("Date is:\nDay: %i\nMonth: %i\nYear: %i\n\n", d, m, y);

        //printf("ADD-DAYS: started...\n");
        newDate = addDays(d, m, y, x);
        //printf("ADD-DAYS: (%s) ended.\n", newDate);
    }
    //printf("NMEA-date (new): %s\n", newDate);

    //printf("A detected: ->%i<-\n", strlen(nmea_msg));
    sprintf(nmea_msg, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,,,%c", arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], \
                                                            arr[6], arr[7], arr[8], newDate, arr[12][0]);

    //////free(newDate);        

    //printf("CRC: started...\n");
    crc = nmea0183_checksum(nmea_msg);
    //printf("CRC: ended. ->%s<-\n", nmea_msg);

    sprintf(nmea_msg, "%s*%X", nmea_msg, crc);

    //nmea_msg[strlen(nmea_msg)+1]=0;
    //nmea_msg[strlen(nmea_msg)]='\n';

    //printf("convNMEA: returning nmea_msg string: %s\n", nmea_msg);
    return strdup(nmea_msg);
}

int main(int argc, char **argv)
{
    unsigned char   buffer[BUFFERSIZE];
    FILE            *instream;
    FILE            *outstream;
    int             bytes_read=0;
    int             buffer_size=0;
    int             i = 0;
    char            str[100];

    fprintf(stdout, "* TTconv-v11 date converter by treysis (treysis@gmx.net)\n");

    buffer_size=sizeof(unsigned char)*BUFFERSIZE;
    /* open named pipes for reading and writing */
    instream=fopen("/var/run/gpspip2","r");
    outstream=fopen("/var/run/gpspipe","w");

    /* did it open? */
    if (instream!=NULL && outstream !=NULL){
        /* read from instream until it's end */
        while ((bytes_read=fread(&buffer, buffer_size, 1, instream))==buffer_size) {
            //fprintf(stdout, "%c", buffer[0]);
            if (buffer[0] == '\n') {
                if (!strncmp(str,"$GPRMC", 6)) // strcmp returns 0 if strings match!
                {
                    //fprintf(stdout, "convNMEA: starting...\n");
                    char *str2 = convNMEA(str);
                    //fprintf(stdout, "convNMEA: ended.\n");
                    ////fprintf(stdout, "NMEA:%s<---\n", str);
                    strcpy(str, str2);
                    free(str2);
                }
                str[strlen(str)+1]=0;
                str[strlen(str)]='\n';
                fputs(str, outstream);
                fflush(outstream);

                i=0;
            } else {
                str[i++] = buffer[0];
                str[i] = '\0';
            }
        }
    }
    /* if any error occured, exit with an error message */
    else {
        fprintf(stderr, "* TTconv: ERROR opening fifos. Aborting.\n");
        exit(1);
    }

    fprintf(stdout, "* TTconv closing unexpectedly.\n");
    fprintf(stderr, "* TTconv: ERROR closing unexpectedly.\n");
    fclose(instream);
    fclose(outstream);

    return 0;
}

