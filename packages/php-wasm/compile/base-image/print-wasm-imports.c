#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define WASM_MAGIC 0x6D736100
#define WASM_VERSION 0x1

// Section IDs
#define IMPORT_SECTION 2

typedef struct {
    uint32_t magic;
    uint32_t version;
} wasm_header_t;

typedef struct {
    uint8_t id;
    uint32_t size;
} section_header_t;

// Read LEB128 encoded unsigned integer
uint32_t read_leb128(FILE *fp) {
    uint32_t result = 0;
    uint32_t shift = 0;
    uint8_t byte;
    
    do {
        byte = fgetc(fp);
        result |= ((byte & 0x7f) << shift);
        shift += 7;
    } while (byte & 0x80);
    
    return result;
}

// Read string from wasm binary
char* read_string(FILE *fp) {
    uint32_t len = read_leb128(fp);
    char *str = malloc(len + 1);
    fread(str, 1, len, fp);
    str[len] = '\0';
    return str;
}

void parse_imports(FILE *fp) {
    uint32_t count = read_leb128(fp);
    printf("Number of imports: %d\n", count);
    
    for (uint32_t i = 0; i < count; i++) {
        char *module = read_string(fp);
        char *name = read_string(fp);
        uint8_t kind = fgetc(fp);
        
        printf("Import %d:\n", i);
        printf("  Module: %s\n", module);
        printf("  Name: %s\n", name);
        printf("  Kind: 0x%02x\n", kind);
        
        free(module);
        free(name);
        
        // Parse import type based on kind
        switch(kind) {
            case 0x00: // Function
                printf("  Type: Function index %d\n", read_leb128(fp));
                break;
            case 0x01: // Table
                printf("  Type: Table\n");
                // Skip table type
                fgetc(fp); // element type
                uint8_t flags = fgetc(fp);
                read_leb128(fp); // initial size
                if (flags & 0x01) read_leb128(fp); // max size
                break;
            case 0x02: // Memory
                printf("  Type: Memory\n");
                // Skip memory type
                uint8_t mem_flags = fgetc(fp);
                read_leb128(fp); // initial size
                if (mem_flags & 0x01) read_leb128(fp); // max size
                break;
            case 0x03: // Global
                printf("  Type: Global\n");
                fgetc(fp); // value type
                fgetc(fp); // mutability
                break;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <wasm file>\n", argv[0]);
        return 1;
    }
    
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }
    
    // Read and verify header
    wasm_header_t header;
    fread(&header, sizeof(header), 1, fp);
    
    if (header.magic != WASM_MAGIC || header.version != WASM_VERSION) {
        fprintf(stderr, "Invalid WASM file\n");
        fclose(fp);
        return 1;
    }
    
    // Find imports section
    while (!feof(fp)) {
        section_header_t section;
        section.id = fgetc(fp);
        if (feof(fp)) break;
        
        section.size = read_leb128(fp);
        
        if (section.id == IMPORT_SECTION) {
            parse_imports(fp);
            break;
        } else {
            // Skip other sections
            fseek(fp, section.size, SEEK_CUR);
        }
    }
    
    fclose(fp);
    return 0;
}
