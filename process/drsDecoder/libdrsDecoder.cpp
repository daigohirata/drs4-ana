//
// Created by Daigo Hirata on 2025/04/30
//

#ifndef DRS_DECODER_HPP
#define DRS_DECODER_HPP

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

#include "drsDecoder.hpp"
#include "drsDatDecoder.hpp"

#define N_CHANNEL 4
#define N_SAMPLES 1024
#define N_SCALER 6


int drsDecoder(const TString& inputDir, const TString& outputFile) {
    TSystemDirectory dir(inputDir, inputDir);
    TList* files = dir.GetListOfFiles();
    if (!files) {
        std::cerr << "Error: Cannot open input directory: " << inputDir << std::endl;
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

    auto outFile = std::unique_ptr<TFile>(TFile::Open(outputFile, "RECREATE"));
    auto tree = std::make_unique<TTree>("raw", "4 channel raw data");
    
    // datFileNamesの各ファイルを処理
    for (const auto& fileName : datFileNames) {
        TString filePath = inputDir + "/" + fileName;
        std::cout << "Processing file: " << fileName << std::endl;

        auto decoder = std::make_unique<drsDatDecoder>(tree.get(), filePath);

        if (decoder->ConvertToTree()) {
            std::cerr << "Warning: Failed to decode file: " << fileName << std::endl;
        }
    }

    tree->Write();
    std::cout << "Decoded data is written to: " << outputFile << std::endl;

    return 0;
}

#endif // DRS_DECODER_HPP