#include <iostream>
#include <string_view>
#include <memory>
#include <fstream>

struct AppSettings
{
public:
    bool parce(const int argc, const char *argv[]);

    std::istream* istream = nullptr;

private:
    std::unique_ptr<std::ifstream> file_input_storage_;

    static constexpr std::string_view DEFAULT_IFILE_NAME_ = "models/tensor_compiler_test.onnx";
    static constexpr std::string_view DEFAULT_LOGSPACE_   = "logs";
};