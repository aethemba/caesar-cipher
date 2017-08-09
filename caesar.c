#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


char * crypting(char input[], int encrypt) {
    int length = strlen(input);
    char *crypted;
    
    crypted = malloc(length+1);

    int i;
    for(i=0; i < length; i++) {
        if (encrypt == 1) {
            crypted[i] = input[i] + 10;
        } else {
            crypted[i] = input[i] - 10;
        }
    }

    crypted[length] = '\0';
    return crypted;
}


int main(int argc, char **argv) {
    
    int eflag = 0;
    int dflag = 0;
    int t;
    char *tvalue = NULL;
    int fflag = 0;
    int c;
    opterr = 0;

    while ((c=getopt(argc, argv, "edft:")) != -1) {
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
            case 'f':
                fflag = 1;
                break;
            case '?':
                if (optopt == 't') {
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

    if (tvalue) {
        if (dflag) {
            char *result = crypting(tvalue, 0);
            printf("%s\n", result);
        }

        if (eflag) {
            char *result = crypting(tvalue, 1);
            printf("%s\n", result);
        }
        return 0;

    }

    return 0;
}