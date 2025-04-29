//
// Created by Daigo Hirata on 2025/04/30
//

#ifndef DAT_FILE_CONVERTER_HPP
#define DAT_FILE_CONVERTER_HPP

#include <TString.h>

class TTree;

class DatFileConverter {
public:
    static bool ConvertToTree(TTree* tree, const TString& inputPath, ULong64_t fileIndexOffset);
};

#endif // DAT_FILE_CONVERTER_HPP
