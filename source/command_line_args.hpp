#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include "RLogSU/logger.hpp"
#include "cxxopts.hpp"

struct AppSettings
{
public:
    friend bool ParseCommandLineArgs(AppSettings& settings, const int argc, const char *argv[]);

    std::istream* istream = nullptr;

private:
    std::unique_ptr<std::ifstream> file_input_storage_;

    static constexpr std::string_view DEFAULT_IFILE_NAME_ = "models/tensor_compiler_test.onnx";
    static constexpr std::string_view DEFAULT_LOGSPACE_   = "logs";
};

inline bool ParseCommandLineArgs(AppSettings& settings, const int argc, const char *argv[])
{
    cxxopts::Options options("tenpiler");

    options.add_options()
        ("i,input_onnx" , "Path to input onnx" , cxxopts::value<std::string>())
        ("l,logspace"   , "Path to logspace"   , cxxopts::value<std::string>())
        ("h,help"       , "SOS")
        ;

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return false;
    }

    //-------------------------input_onnx-----------------------------------------------------------
    std::string input_filename;

    if (result.count("input_onnx"))
    {
        input_filename = result["input_onnx"].as<std::string>();
    }

    else
    {
        input_filename = settings.DEFAULT_IFILE_NAME_;
    }

    settings.file_input_storage_ = std::make_unique<std::ifstream>(input_filename, std::ios::binary);

    if (!settings.file_input_storage_->is_open())
    {
        throw std::runtime_error("Could not open file: " + input_filename);
    }
    
    settings.istream = settings.file_input_storage_.get();


    //-------------------------logspace-------------------------------------------------------------
    if (result.count("logspace"))
    {
        RLSU_SET_LOGSPACE(result["logspace"].as<std::string>());
    }

    else
    {
        RLSU_SET_LOGSPACE(std::string(settings.DEFAULT_LOGSPACE_));
    }

    return true;
}
