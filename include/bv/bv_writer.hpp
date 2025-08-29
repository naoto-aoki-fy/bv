#ifndef BV_WRITER_HPP
#define BV_WRITER_HPP

#include <cstdio>
#include <string>
#include <vector>
#include <stdexcept>
#include <type_traits>
#include <cstdint>

namespace bv {

template<typename T>
class writer {
public:
    writer(const char* filename, const std::vector<std::string>& fields)
        : fp_(nullptr), num_fields_(fields.size())
    {
        const char* dtype = expected_dtype();
        fp_ = fopen(filename, "wb");
        if (!fp_) {
            throw std::runtime_error("failed to open file");
        }
        fputs("# binary values\n", fp_);
        fputs("# fields = ", fp_);
        for (size_t i = 0; i < fields.size(); ++i) {
            fputs(fields[i].c_str(), fp_);
            if (i + 1 != fields.size()) {
                fputs(", ", fp_);
            }
        }
        fputs("\n", fp_);
        fputs("# dtype = ", fp_);
        fputs(dtype, fp_);
        fputs("\n", fp_);
        fputs("# padding", fp_);
        long const fpos = ftell(fp_);
        int const remainder = (fpos + 1) & 7;
        if (remainder) {
            for (int i = remainder; i < 8; ++i) {
                fputc(' ', fp_);
            }
        }
        fputc('\n', fp_);
    }

    void add_row(const std::vector<T>& values) {
        if (values.size() != num_fields_) {
            throw std::runtime_error("row has wrong number of fields");
        }
        size_t written = fwrite(values.data(), sizeof(T), num_fields_, fp_);
        if (written != num_fields_) {
            throw std::runtime_error("failed to write row");
        }
    }

    void close() {
        fclose(fp_);
    }

private:
    static const char* expected_dtype() {
        if constexpr (std::is_same<T, float>::value) {
            return "float32";
        } else if constexpr (std::is_same<T, double>::value) {
            return "float64";
        } else if constexpr (std::is_same<T, std::int64_t>::value) {
            return "int64";
        } else if constexpr (std::is_same<T, std::int32_t>::value) {
            return "int32";
        } else if constexpr (std::is_same<T, std::int16_t>::value) {
            return "int16";
        } else if constexpr (std::is_same<T, std::int8_t>::value) {
            return "int8";
        } else if constexpr (std::is_same<T, std::uint64_t>::value) {
            return "uint64";
        } else if constexpr (std::is_same<T, std::uint32_t>::value) {
            return "uint32";
        } else if constexpr (std::is_same<T, std::uint16_t>::value) {
            return "uint16";
        } else if constexpr (std::is_same<T, std::uint8_t>::value) {
            return "uint8";
        } else {
            static_assert(sizeof(T) == 0, "unsupported type");
            return "";
        }
    }

    FILE* fp_;
    size_t num_fields_;
};

} // namespace bv

#endif // BV_WRITER_HPP
