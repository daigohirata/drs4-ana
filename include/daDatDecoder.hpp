//
// Created by Daigo Hirata on 2025/04/30
//

#ifndef DA_DAT_DECODER_HPP
#define DA_DAT_DECODER_HPP

#include <TString.h>

class TTree;

class daDatDecoder { 
public:
    static bool ConvertToTree(TTree* tree, const TString& inputPath);
};

#endif // DA_DAT_DECODER_HPP
