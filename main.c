#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>

// Arm Compiler
// Emma Power - 2025

int main () {
    FILE *fptr;
    FILE *wptr;
    
    fptr = fopen("../test/add.asm", "r");
    if (fptr == NULL) {
        printf("File not found");
        return 1;
    }
    // Open a file in writing mode
    wptr = fopen("file.bin", "a");

    char nextLine[128] = "";

    while (fgets(nextLine, 127, fptr)) {
        //printf("%s", nextLine);
        char currentWord[128] = "";
        char* operation = (char*) malloc(4*sizeof(char));       
        char o1 = 0;
        char o2 = 0;
        char o3 = 0;

        uint8_t currentPhase = 0;
        for (int i = 0; i < strlen(nextLine); i++) {

            if (nextLine[i] == ' ' || nextLine[i] == '\n') {

                switch (currentPhase) {
                    case 0:
                        //printf("Current Word: \"%s\"\n", currentWord);
                        for (int j = 0; j < strlen(currentWord); j++) {

                            operation[j] = currentWord[j];
                            
                            //printf("Current Word: \"%d\"\n", currentWord[j]);
                        }
                        //printf("Current Word: \"%s\"\n", operation);
                        break;
                    case 1:
                        if (currentWord[0] == 'r') {
                            o1 = currentWord[1] - '0';
                        } else if (currentWord[0] == '#') {
                            o1 = currentWord[1] - '0';
                        }
                        
                        break;
                    case 2:
                        if (currentWord[0] == 'r') {
                            o2 = currentWord[1] - '0';
                        } else if (currentWord[0] == '#') {
                            o2 = currentWord[1] - '0';
                        }
                        break;
                    case 3:
                        if (currentWord[0] == 'r') {
                            o3 = currentWord[1] - '0';
                        } else if (currentWord[0] == '#') {
                            o3 = currentWord[1] - '0';
                        }
                        break;
                    default:
                        break;
                }

                
                // Clear Word
                memset(currentWord,0,strlen(currentWord));

                currentPhase ++;

                 
            } else if (nextLine[i] == ',') {

            } else {
                currentWord[strlen(currentWord)] = nextLine[i];
                //printf("Word: %s\n", currentWord);
            }

        }
        //printf("\"%s\"\n", operation);
        printf("Instruction %s and operands %d %d %d :3\n", operation, o1, o2, o3);

        uint32_t opcode;
        

        if (!strcmp(operation, "ADD")) {
            opcode = 0x02800000;
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        } else if (!strcmp(operation, "LDR")) {
            opcode = 0x17D00000;
            opcode += o1 * 0x1000;
            opcode += o2 * 0x1;
            printf("Opcode: %X\n", opcode);
        }

        

        // Write some text to the file
        fwrite(&opcode, 4, 1, wptr);
    }




    return 0;
}