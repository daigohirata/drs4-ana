//
// Created by Daigo Hirata on 2025/04/30
//

#ifndef DAT_DIR_PROCESSOR_HPP
#define DAT_DIR_PROCESSOR_HPP

#include <TString.h>

class TFile;
class TTree;

class DatDirProcessor {
  public:
    DatDirProcessor(const TString &inputDir,
                    const TString &outputRootFile);
    void ProcessAll();

  private:
    TString input_dir_;
    TString output_file_;
};

#endif // DAT_DIR_PROCESSOR_HPP
