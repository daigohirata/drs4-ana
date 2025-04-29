//
// Created by Daigo Hirata on 2025/04/30
//

#include "daDirProcessor.hpp"
#include "daDatDecoder.hpp"

#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <TList.h>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>

#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>

daDirProcessor::daDirProcessor(const TString& inputDir, const TString& outputFile)
    : input_dir_(inputDir), output_dir_(outputFile) {}

int daDirProcessor::ProcessAll() {
    TSystemDirectory dir(input_dir_, input_dir_);
    TList* files = dir.GetListOfFiles();
    if (!files) {
        std::cerr << "Error: Cannot open input directory: " << fInputDir << std::endl;
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

    auto outFile = std::unique_ptr<TFile>(TFile::Open(fOutputFile, "RECREATE"));
    auto tree = std::make_unique<TTree>("raw", "4 channel raw data");
    
    // datFileNamesの各ファイルを処理
    for (const auto& fileName : datFileNames) {
        TString filePath = fInputDir + "/" + fileName;
        std::cout << "Processing file: " << fileName << std::endl;
        daDatDecoder decoder(filePath);
        if (!decoder.ConvertToTree(tree.get(), filePath)) {
            std::cerr << "Warning: Failed to process file: " << fileName << std::endl;
        }
    }

    tree->Write();
    std::cout << "Output written to: " << fOutputFile << std::endl;
    return 0;
}
