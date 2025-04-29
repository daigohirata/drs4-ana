//
// Created by Daigo Hirata on 2025/04/30
//

#include "DatDirectoryProcessor.hpp"
#include "DatFileConverter.hpp"

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

DatDirProcessor::DatDirProcessor(const TString& inputDir, const TString& outputFile)
    : input_dir_(inputDir), output_dir_(outputFile) {}

int DatDirectoryProcessor::ProcessAll() {
    TSystemDirectory dir(input_dir_, input_dir_);
    TList* files = dir.GetListOfFiles();
    if (!files) {
        std::cerr << "Error: Cannot open input directory: " << fInputDir << std::endl;
        return -1;
    }

    std::vector<TString> datFileNames;

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

    TFile outFile = std::unique_ptr<TFile>(TFile::Open(fOutputFile, "RECREATE"));
    TTree tree = std::make_unique<TTree>("raw", "4 channel waveforms");

    for (const auto& fileName : datFileNames) {
        TString filePath = fInputDir + "/" + fileName;
        std::cout << "Processing file: " << fileName << std::endl;
        DatFileConverter converter(filePath);
        if (!converter.ConvertToTree(tree.get())) {
            std::cerr << "Warning: Failed to process file: " << fileName << std::endl;
        }
    }

    tree->Write();
    std::cout << "Output written to: " << fOutputFile << std::endl;
    return 0;
}
