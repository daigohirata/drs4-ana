//
// Created by Daigo Hirata on 2025/04/30
//

#include <iostream>

#include <boost/program_options.hpp>

#include "drsDecoder.hpp"

namespace po = boost::program_options;

int main(int argc, char **argv) {
    // コマンドライン引数の解析
    po::options_description desc("Allowed options");
    desc.add_options()(
        "help,h", "Display help message")(
        "input-dir,i", po::value<std::string>(), "Input directory containing .dat files")(
        "output-file,o", po::value<std::string>(), "Output ROOT file");

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
    } catch (const po::error_with_option_name &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    } else if (!vm.count("input-dir")) {
        std::cerr << "[Error] Input directory is required." << std::endl;
        return 1;
    } else if (!vm.count("output-file")) {
        std::cerr << "[Error] Output file is required." << std::endl;
        return 1;
    };

    TString inputDir = vm["input-dir"].as<std::string>();
    TString outputFile = vm["output-file"].as<std::string>();

    if(drsDecoder(inputDir, outputFile)){
        std::cerr << "[Error] Failed to process files." << std::endl;
        return 1;
    } else {
        std::cout << "***** drsDecoder exits successfully. ******" << std::endl;
        return 0;
    }
}