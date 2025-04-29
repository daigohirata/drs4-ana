//
// Created by Daigo Hirata on 2025/04/30
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>

#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <TList.h>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>

#include "daDirProcessor.hpp"
#include "daDatDecoder.hpp"

daDirProcessor::daDirProcessor(const TString& inputDir, const TString& outputFile)
    : input_dir_(inputDir), output_file_(outputFile) {}

int daDirProcessor::ProcessAll() const {
    TSystemDirectory dir(input_dir_, input_dir_);
    TList* files = dir.GetListOfFiles();
    if (!files) {
        std::cerr << "Error: Cannot open input directory: " << input_dir_ << std::endl;
        return -1;
    }

    std::vector<TString> datFileNames;

    // ディレクトリ内の .dat ファイルを取得、datFileNamesに格納
    TIter next(files);
    TSystemFile* file;
    while ((file = (TSystemFile*)next())) {
        TString fileName = file->GetName();
        if (!file->IsDirectory() && fileName.EndsWith(".dat")) {
            datFileNames.push_back(fileName);
        }
    }

    // ファイル名を辞書順でソート
    std::sort(datFileNames.begin(), datFileNames.end());

    auto outFile = std::unique_ptr<TFile>(TFile::Open(output_file_, "RECREATE"));
    auto tree = std::make_unique<TTree>("raw", "4 channel raw data");
    
    // datFileNamesの各ファイルを処理
    for (const auto& fileName : datFileNames) {
        TString filePath = input_dir_ + "/" + fileName;
        std::cout << "Processing file: " << fileName << std::endl;
        if (!daDatDecoder::ConvertToTree(tree.get(), filePath)) {
            std::cerr << "Warning: Failed to process file: " << fileName << std::endl;
        }
    }

    tree->Write();
    std::cout << "Output written to: " << output_file_ << std::endl;
    return 0;
}
