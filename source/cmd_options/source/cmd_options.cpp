#include "cmd_options/cmd_options.hpp"
#include "cxxopts.hpp"
#include "RLogSU/logger.hpp"

bool AppSettings::parce(const int argc, const char *argv[])
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
        input_filename = DEFAULT_IFILE_NAME_;
    }

    file_input_storage_ = std::make_unique<std::ifstream>(input_filename, std::ios::binary);

    if (!file_input_storage_->is_open())
    {
        throw std::runtime_error("Could not open file: " + input_filename);
    }
    
    istream = file_input_storage_.get();


    //-------------------------logspace-------------------------------------------------------------
    if (result.count("logspace"))
    {
        RLSU_SET_LOGSPACE(result["logspace"].as<std::string>());
    }

    else
    {
        RLSU_SET_LOGSPACE(std::string(DEFAULT_LOGSPACE_));
    }

    return true;
}
