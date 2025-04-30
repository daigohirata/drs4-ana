//
// Created by Daigo Hirata on 2025/04/30
//

#include <iostream>
#include <vector>

#include <TString.h>
#include <boost/program_options.hpp>

#include "drsConst.hpp"
#include "drsWFDrawer.hpp"

namespace po = boost::program_options;

int main(int argc, char **argv) {
    // analyse command line arguments
    po::options_description desc("Allowed options");
    desc.add_options()(
        "help,h", "Display help message")(
        "input-file,i", po::value<std::string>(), "Input ROOT file (mandatory)")(
        "output-file,o", po::value<std::string>(), "Output image file (mandatory)")(
        "event-id,e", po::value<int>()->default_value(0), "Event ID to draw waveform")(
        "channel,c", po::value<int>()->default_value(1111), "Channel number to draw waveform (default : 1111)\n"
                                       "--Example \"-c 1011\" if you want to draw CH1,3,4")(
        "branch-name,b", po::value<std::string>()->default_value("wf"), "Branch name (default : wf)")(
        "vertical-scale,v", po::value<double>(), "Vertical scale [mV]\n"
                                                 "--Example \"--vertical-scale -350:-5\"")(
        "horizontal-scale,h", po::value<double>(), "Horizontal scale [ns]\n"
                                                   "--Example \"--horizontal-scale 34:54\"")(
        "output-format,f", po::value<std::string>()->default_value("png"), "Output format, png or pdf (default : png)"
    );
        

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
    } else if (!vm.count("input-file")) {
        std::cerr << "[Error] Input file is required." << std::endl;
        return 1;
    } else if (!vm.count("output-file")) {
        std::cerr << "[Error] Output file is required." << std::endl;
        return 1;
    };

    TString inputFile = vm["input-file"].as<std::string>();
    TString outputFile = vm["output-file"].as<std::string>();
    Int_t eventId = vm["event-id"].as<int>();
    TString branchName = vm["branch-name"].as<std::string>();
    TString verticalScale = vm["vertical-scale"].as<std::string>();
    TString horizontalScale = vm["horizontal-scale"].as<std::string>();
    TString outputFormat = vm["output-format"].as<std::string>();

    // analyse channel number
    std::string chstr = vm["channel"].as<std::string>();  // 例: "1101"
    std::vector<bool> drawChannel(N_CHANNEL, true);  // CH1〜CH4（index 0〜3）
    int len = chstr.size();
    for (int i = 0; i < 4 && i < len; ++i) {
        drawChannel[i] = (chstr[i] == '1');
    }

    if (drsWFDrawer(inputFile, outputFile, eventId, drawChannel, branchName,
                    verticalScale, horizontalScale, outputFormat)) {
        std::cout << "[Info] Waveform " << eventId << " drawing completed." << std::endl;
        return 0;
    } else {
        std::cerr << "[Error] Failed to draw waveform." << std::endl;
        return 1;
    }

    return 0;
}