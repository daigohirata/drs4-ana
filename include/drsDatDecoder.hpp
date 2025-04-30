//
// Created by Daigo Hirata on 2025/04/30
//

#ifndef DRS_DAT_DECODER_HPP
#define DRS_DAT_DECODER_HPP

class TString;
class TTree;

class drsDatDecoder {
  public:
    drsDatDecoder(TTree *tree, const TString &inputPath);

    bool ConvertToTree();

    int GetDecodedEventCount() const;
    int GetErrorCount() const;

  private:
    TString input_path_;
    TTree *decoded_tree_;

    int nDecodedEvents_ = 0;
    int nErrors_ = 0;
    static bool branch_set_;
};

#endif // DRS_DAT_DECODER_HPP
