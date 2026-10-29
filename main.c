#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("[ENGINE] Initialized.\n");
    if (argc < 3) { return 1; }
    FILE *fin = fopen(argv[1], "rb");
    FILE *flog = fopen(argv[2], "r");
    if (!fin || !flog) return 1;
    char line[256];
    long start, end;
    int index = 0;
    while (fgets(line, sizeof(line), flog)) {
        if (line[0] == '#' || line[0] == '\n') continue;
        if (sscanf(line, "%ld,%ld", &start, &end) == 2) {
            printf("[SEEK] Segment %d -> Start: %ld, End: %ld\n", index++, start, end);
            fseek(fin, start, SEEK_SET);
        }
    }
    fclose(flog);
    fclose(fin);
    printf("[SUCCESS] Done.\n");
    return 0;
}
