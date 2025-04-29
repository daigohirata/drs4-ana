//
// Created by Daigo Hirata on 2025/04/30
//

#ifndef DA_DIR_PROCESSOR_HPP
#define DA_DIR_PROCESSOR_HPP

#include <TString.h>

class TFile;
class TTree;

class daDirProcessor {
  public:
    daDirProcessor(const TString &inputDir,
                   const TString &outputRootFile);
    void ProcessAll();

  private:
    TString input_dir_;
    TString output_file_;
};

#endif // DA_DIR_PROCESSOR_HPP
