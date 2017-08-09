#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


char * crypting(char input[], int encrypt, int shift) {
    int length = strlen(input);
    char *crypted;
    
    crypted = malloc(length+1);
    int i;
    for(i=0; i < length; i++) {
        if (encrypt == 1) {
            crypted[i] = input[i] + shift;
        } else {
            crypted[i] = input[i] - shift;
        }
    }

    crypted[length] = '\0';
    return crypted;
}


int main(int argc, char **argv) {
    
    int eflag = 0;
    int dflag = 0;
    int t;
    int s;
    char *tvalue = NULL;
    char *svalue = NULL;

    int fflag = 0;
    int c;
    opterr = 0;

    while ((c=getopt(argc, argv, "edft:s:")) != -1) {
        switch(c) {
            case 'e':
                eflag = 1;
                break;
            case 'd': 
                dflag = 1;
                break;
            case 't':
                tvalue = optarg;
                break;
            case 's':
                svalue = optarg;
                break;
            case 'f':
                fflag = 1;
                break;
            case '?':
                if (optopt == 't' || optopt == 's') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else if (isprint(optopt)) {
                    fprintf(stderr, "Unknown option '-%c'.\n", optopt);
                }
                return 1;
            default: 
                abort();
        }
    }

    if (!dflag && !eflag) {
        fprintf(stderr, "You must select to encrypt (-e) or decrypt (-d). Please choose one and run again.\n");
        return 1;   }

    if (tvalue && fflag) {
        fprintf(stderr, "Cannot use -t and -f flag together. Please choose one and run again.\n");
        return 1;
    }

    if (argc <= 1) {
        printf("Please provide the correct arguments. Use 'man caeser' for options.\n");
        exit(1);
    }
    
    int shift = 10;
    if (svalue) {
        shift = atoi(svalue);
    }

    if (tvalue) {

        if (dflag) {
            char *result = crypting(tvalue, 0, shift);
            printf("%s\n", result);
        }

        if (eflag) {
            char *result = crypting(tvalue, 1, shift);
            printf("%s\n", result);
        }
        return 0;

    }

    return 0;
}