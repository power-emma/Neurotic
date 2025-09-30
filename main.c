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
    char file[] = "test/hello_world.asm";

    fptr = fopen(file, "r");
    if (fptr == NULL) {
        printf("File not found");
        return 1;
    }
    // Open a file in writing mode
    wptr = fopen(strcat(file, ".bin"), "w");



    char nextLine[128] = "";

    while (fgets(nextLine, 127, fptr)) {
        //printf("%s", nextLine);
        char currentWord[128] = "";
        char* operation = (char*) malloc(4*sizeof(char));       
        uint32_t o1 = 0;
        uint32_t o2 = 0;
        uint32_t o3 = 0;
        // Register vs immediate flags
        char r1 = 0;
        char r2 = 0;
        char r3 = 0;
        uint8_t currentPhase = 0;

        for (int i = 0; i < strlen(nextLine); i++) {

            if (nextLine[i] == ' ' || nextLine[i] == '\n' || nextLine[i] == '\t') {

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
                            currentWord[0] = ' ';
                            o1 = atoi(currentWord);
                            r1 = 1;
                        } else if (currentWord[0] == '#') {
                            currentWord[0] = ' ';
                            o1 = atoi(currentWord);
                        } else if (currentWord[0] == '[') {
                            currentWord[strlen(currentWord)-1] = ' ';
                            currentWord[0] = ' ';
                            o1 = atoi(currentWord);
                            r1 = 0;
                        }
                        
                        break;
                    case 2:
                        if (currentWord[0] == 'r') {
                            currentWord[0] = ' ';
                            o2 = atoi(currentWord);
                            r2 = 1;
                        } else if (currentWord[0] == '#') {
                            currentWord[0] = ' ';
                            o2 = atoi(currentWord);
                        } else if (currentWord[0] == '[') {
                            currentWord[strlen(currentWord)-1] = ' ';
                            currentWord[0] = ' ';
                            o2 = atoi(currentWord);
                            r2 = 0;
                        }
                        break;
                    case 3:
                        if (currentWord[0] == 'r') {
                            currentWord[0] = ' ';
                            o3 = atoi(currentWord);
                            r3 = 1;
                        } else if (currentWord[0] == '#') {
                            currentWord[0] = ' ';
                            o3 = atoi(currentWord);
                        } else if (currentWord[0] == '[') {
                            currentWord[strlen(currentWord)-1] = ' ';
                            currentWord[0] = ' ';
                            o3 = atoi(currentWord);
                            r3 = 0;
                        }
                        break;
                    
                    default:
                        break;
                }

                
                // Clear Word
                memset(currentWord,0,strlen(currentWord));

                currentPhase ++;

                 
            } else if (nextLine[i] == ',') {

            } else if (nextLine[i] == ';') {
                break;
            } else {
                currentWord[strlen(currentWord)] = nextLine[i];
                //printf("Word: %s\n", currentWord);
            }

        }
        //printf("\"%s\"\n", operation);
        printf("Instruction %s and operands %d %d %d :3\n", operation, o1, o2, o3);

        uint32_t opcode;

        if (operation[0] == '0' && operation[1] == 'x') {
            opcode = (uint32_t) strtoul(operation, NULL, 16);
            printf("Opcode: %X\n", opcode);
            
        } else if (!strcmp(operation, "CMP")) {
            opcode = 0x13400000;
            opcode += o1 * 0x10000;
            opcode += o2;
            printf("Opcode: %X\n", opcode);

        } 
        // DP 0000
        else if (!strcmp(operation, "AND")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x12000000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x10000000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        }
        // DP 0001
        else if (!strcmp(operation, "EOR")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x12200000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x10200000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        } 
        
        // DP 0010
        else if (!strcmp(operation, "SUB")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x12400000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x10400000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        }
        // DP 0011
        else if (!strcmp(operation, "RSB")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x12600000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x10600000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        } 
        
        // DP 0100
        else if (!strcmp(operation, "ADD")) {
            if (r3) {
                opcode = 0x12800000;
            } else {
                opcode = 0x10800000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        } 
        // DP 0101
        else if (!strcmp(operation, "ADC")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x12A00000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x10A00000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        }
        // DP 0110
        else if (!strcmp(operation, "SBC")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x12C00000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x10C00000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        }
        // DP 0111
        else if (!strcmp(operation, "RSC")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x12E00000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x10E00000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        }
        // DP 1000
        else if (!strcmp(operation, "TST")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x13000000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x11000000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        }
        // DP 1001
        else if (!strcmp(operation, "TEQ")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x13200000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x11200000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        }
        // DP 1010
        else if (!strcmp(operation, "CMP")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x13400000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x11400000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        }
        // DP 1011
        else if (!strcmp(operation, "CMN")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x13600000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x11600000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        } // DP 1100
        else if (!strcmp(operation, "ORR")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x13800000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x11800000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        } // DP 1101
        else if (!strcmp(operation, "MOV")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x13A00000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x11A00000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        }
        // DP 1110
        else if (!strcmp(operation, "BIC")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x13C00000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x11C00000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        } // DP 1111
        else if (!strcmp(operation, "MVN")) {
            if (r3) {
                // 0001 001P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x13E00000;
            } else {
                // 0001 000P PPPS NNNN DDDD 2222 2222 2222
                opcode = 0x11E00000;
            }
            opcode += o2 * 0x10000;
            opcode += o1 * 0x1000;
            opcode += o3;
            printf("Opcode: %X\n", opcode);

        } else if (!strcmp(operation, "LDR")) {
            if (r2) {
                opcode = 0x17D00000;
            } else {
                opcode = 0x15D00000;
            }
            opcode += o1 * 0x1000;
            opcode += o2 * 0x1;
            printf("Opcode: %X\n", opcode);
        }  else if (!strcmp(operation, "STR")) {
            if (r2) {
                opcode = 0x17E00000;
            } else {
                opcode = 0x15E00000;
            }
            opcode += o1 * 0x1000;
            opcode += o2 * 0x1;
            printf("Opcode: %X\n", opcode);
        } else if (!strcmp(operation, "HLT")) {
            opcode = 0xD4400000;
            printf("Opcode: %X\n", opcode);
        } else if (!strcmp(operation, "B")) {
            opcode = 0xEA000000;
            opcode += (o1 << 8) >> 8;
            printf("Opcode: %X\n", opcode);
        } else if (!strcmp(operation, "BEQ")) {
            opcode = 0x0A000000;
            opcode += (o1 << 8) >> 8;
            printf("Opcode: %X\n", opcode);
        }

        

        // Write some text to the file
        fwrite(&opcode, 4, 1, wptr);
    }




    return 0;
}