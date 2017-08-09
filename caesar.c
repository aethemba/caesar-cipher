#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


char * encrypting(char input[]) {
    int length = strlen(input);
    char *encrypted;
    
    encrypted = malloc(length+1);

    int i;
    for(i=0; i < length; i++) {
        encrypted[i] = input[i] + 10;
    }

    encrypted[length] = '\0';
    return encrypted;
}


char * decrypting(char input[]) {
    int length = strlen(input);
    char *decrypted;
    
    decrypted = malloc(length+1);

    int i;
    for(i=0; i < length; i++) {
        decrypted[i] = input[i] - 10;
    }

    decrypted[length] = '\0';
    return decrypted;
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
            char *result = decrypting(tvalue);
            printf("%s\n", result);
        }

        if (eflag) {
            char *result = encrypting(tvalue);
            printf("%s\n", result);
        }
        return 0;

    }

    return 0;
}