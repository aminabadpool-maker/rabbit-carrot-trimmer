#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_video> <segments_file>\n", argv[0]);
        return 1;
    }
    FILE *fin = fopen(argv[1], "rb");
    FILE *flog = fopen(argv[2], "r");
    if (!fin || !flog) {
        perror("[-] Initialization Error");
        if (fin) fclose(fin);
        if (flog) fclose(flog);
        return 1;
    }
    char line[256]; long s, e; int idx = 0;
    while (fgets(line, sizeof(line), flog)) {
        if (line[0] == '#' || line[0] == '\n') continue;
        if (sscanf(line, "%ld,%ld", &s, &e) == 2) {
            char name[64]; snprintf(name, sizeof(name), "segment_%d.mp4", idx++);
            FILE *fout = fopen(name, "wb"); if (!fout) continue;
            fseek(fin, s, SEEK_SET);
            long left = e - s; char buf[8192]; long w = 0;
            while (w < left) {
                long rem = left - w;
                long c = ((long)sizeof(buf) < rem) ? (long)sizeof(buf) : rem;
                size_t n = fread(buf, 1, c, fin); if (n <= 0) break;
                fwrite(buf, 1, n, fout); w += n;
            }
            fclose(fout);
        }
    }
    fclose(flog); fclose(fin);
    printf("[SUCCESS] All segments extracted successfully.\n");
    return 0;
}
