#include <cstdio>
#include <stdexcept>

int main(int argc, char** argv) {

    if (argc < 2) {
        throw std::runtime_error("please specify outbin_fn");
    }
    char* const outbin_fn = argv[1];

    FILE* const fp = fopen(outbin_fn, "wb");
    fputs("# binary values\n", fp);
    fputs("# fields = a, b, c, d\n", fp);
    fputs("# dtype = float64\n", fp);
    fputs("# padding", fp);
    long const fpos = ftell(fp);
    int const remainder = (fpos + 1) & 7;
    if (remainder) {
        for(int i = remainder; i < 8; i++) {
            fputs(" ", fp);
        }
    }
    fputs("\n", fp);

    
    for(int row_num = 0; row_num < 100; row_num++) {
        for(int field_num = 0; field_num < 4; field_num++) {
            double const dummy_value = field_num;
            fwrite(&dummy_value, sizeof(dummy_value), 1, fp);
        }
    }


    fclose(fp);
}