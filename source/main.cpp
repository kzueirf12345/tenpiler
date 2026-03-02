#include <cstdlib>
#include <fstream>
#include <iostream>

#include <stdexcept>

#include "RLogSU/logger.hpp"

#include "graph/Graph.hpp"
#include "graph/Dumber.hpp"
#include "utils/concole.hpp"
#include "command_line_args.hpp"

#include <onnx/onnx-ml.pb.h>

//TODO CI
//TODO update README

int main(const int argc, const char *argv[]) try {

    AppSettings settings = {};
    if (ParseCommandLineArgs(settings, argc, argv) == false)
        return 0;

    std::vector<std::string> files;
    
    for (const auto& entry : std::filesystem::directory_iterator("./models/simple")) {
        if (!entry.is_regular_file() && entry.path().extension() != ".onnx") {
            continue;
        }
        const std::string filename = entry.path().string();

        std::cerr << filename << std::endl;

        std::ifstream input(filename, std::ios::binary);
        tenpiler::graph::Graph graph;
        graph.LoadFromOnnx(input);

        RLSU_DUMP(tenpiler::graph::dump::GraphDumb(graph));
    }

    return EXIT_SUCCESS;
}
catch(const std::logic_error& e) {
    std::cerr <<  RED_TEXT("!!!LOGIC_EXCEPTION!!\n") << e.what() << std::endl;
}
catch(const std::runtime_error& e) {
    std::cerr <<  RED_TEXT("!!!RUNTIME_EXCEPTION!!\n") << e.what() << std::endl;
}
catch(const std::exception& e) {
    std::cerr <<  RED_TEXT("!!!EXCEPTION!!\n") << e.what() << std::endl;
}
catch(...) {
    std::cerr << RED_TEXT("Something went wrong!!!") << std::endl;
}