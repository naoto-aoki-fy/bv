#include <bv/bv_writer.hpp>
#include <stdexcept>
#include <vector>
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        throw std::runtime_error("please specify outbin_fn");
    }
    char* const outbin_fn = argv[1];

    std::vector<std::string> fields = {"a", "b", "c", "d"};
    bv::writer<double> writer(outbin_fn, fields);

    std::vector<double> row(fields.size());
    for (int row_num = 0; row_num < 100; ++row_num) {
        for (int field_num = 0; field_num < static_cast<int>(fields.size()); ++field_num) {
            row[field_num] = field_num;
        }
        writer.add_row(row);
    }
    writer.close();
    return 0;
}
