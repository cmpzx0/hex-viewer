#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file;
    unsigned char buffer[16];
    size_t bytesRead;
    long offset = 0;

    if (argc < 2) {
        fprintf(stderr, "Using : %s <file>\n", argv[0]);
        return 1;
    } 

    file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        printf("%08lx: ", offset);
        for (size_t i = 0; i < bytesRead; i++) {
            printf("%02x ", buffer[i]);
        }

        for (size_t i = bytesRead; i < 16; i++) {
            printf("   ");
        }

        printf(" |");
        for (size_t i = 0; i < bytesRead; i++) {
            if (buffer[i] >= 32 && buffer[i] <= 126)
                printf("%c", buffer[i]);
            else
                printf(".");
        }
        printf("|\n");

        offset += bytesRead;
    }

    fclose(file);
    return 0;
}
