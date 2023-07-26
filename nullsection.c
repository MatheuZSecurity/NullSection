#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://youtube.com/c/MatheuZSecurity

void overwrite(const char *file_path) {
    char command[512];
    char buffer[128];
    FILE *readelf;
    unsigned int n, s, st;
    int index, addr;

    snprintf(command, sizeof(command), "readelf -h %s | awk '/Number of section headers/ {print $NF}'", file_path);

    readelf = popen(command, "r");
    if (readelf == NULL) {
        perror("Error executing readelf");
        return;
    }
    fgets(buffer, sizeof(buffer), readelf);
    pclose(readelf);
    n = atoi(buffer);

    snprintf(command, sizeof(command), "readelf -h %s | awk '/Size of section headers/ {print $NF}'", file_path);

    readelf = popen(command, "r");
    if (readelf == NULL) {
        perror("Error executing readelf");
        return;
    }
    fgets(buffer, sizeof(buffer), readelf);
    pclose(readelf);
    s = atoi(buffer);

    snprintf(command, sizeof(command), "readelf -h %s | awk '/Section header table/ {print $NF}'", file_path);

    readelf = popen(command, "r");
    if (readelf == NULL) {
        perror("Error executing readelf");
        return;
    }
    fgets(buffer, sizeof(buffer), readelf);
    pclose(readelf);
    st = strtol(buffer, NULL, 16);

    for (index = 0; index < n; index++) {
        addr = st + index * s + 4;

        FILE *elf_file = fopen(file_path, "r+");
        if (elf_file == NULL) {
            perror("Error opening ELF file");
            return;
        }

        fseek(elf_file, addr, SEEK_SET);
        fputc(0x00, elf_file);
        fputc(0x00, elf_file);
        fputc(0x00, elf_file);
        fputc(0x00, elf_file);

        fclose(elf_file);
    }
}

int main() {
    char elf[256];

    printf("Enter the path to your ELF: ");
    if (fgets(elf, sizeof(elf), stdin) != NULL) {
        elf[strcspn(elf, "\n")] = '\0';
        if (strlen(elf) >= sizeof(elf)) {
            printf("Error: File path too long.\n");
            return 1;
        }

        FILE *file = fopen(elf, "r");
        if (file == NULL) {
            perror("Error opening the file");
            return 1;
        }
        fclose(file);

        overwrite(elf);
    } else {
        printf("Error reading input.\n");
        return 1;
    }

    return 0;
}
