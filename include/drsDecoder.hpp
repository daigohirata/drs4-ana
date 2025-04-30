//
// Created by Daigo Hirata on 2025/04/30
//

#ifndef DRS_DECODER_HPP
#define DRS_DECODER_HPP

#include <TString.h>

#define N_CHANNEL 4
#define N_SAMPLES 1024
#define N_SCALER 6

int drsDecoder(const TString& inputDir, const TString& outputFile);

#endif // DRS_DECODER_HPP