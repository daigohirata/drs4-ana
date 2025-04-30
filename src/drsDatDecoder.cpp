//
// Created by Daigo Hirata on 2025/04/30
//

// System include
#include <fstream>
#include <iostream>
#include <cerrno>
#include <cstring>

//  ROOT include
#include <TTree.h>

// Project include
#include "drsConst.hpp"
#include "drsDecoder.hpp"
#include "drsDatDecoder.hpp"

drsDatDecoder::drsDatDecoder(TTree *tree, const TString &inputPath)
    : decoded_tree_(tree), input_path_(inputPath) {
    if (!decoded_tree_) {
        std::cerr << "Error: Output tree is null." << std::endl;
        return;
    }
}

bool drsDatDecoder::ConvertToTree() {
    std::ifstream ifs(input_path_.Data());
    if (!ifs.is_open()) {
        std::cerr << "Error: Cannot open file: " << input_path_ << std::endl;
        return false;
    }

    // data structure
    ULong64_t eventid, timestamp;
    UInt_t timestamp_usec;
    Float_t t1, u1, t2, u2, t3, u3, t4, u4;
    UInt_t s0, s1, s2, s3, s4, s5;
    Float_t wf[N_CHANNEL][N_SAMPLES];
    Float_t tbin[N_CHANNEL][N_SAMPLES];
    UInt_t scaler[N_SCALER];

    UInt_t eventidOffset = 0;
    if (branch_set_) {
        decoded_tree_->SetBranchAddress("eventid", &eventid);
        decoded_tree_->SetBranchAddress("timestamp", &timestamp);
        decoded_tree_->SetBranchAddress("timestamp_usec", &timestamp_usec);
        decoded_tree_->SetBranchAddress("wf", wf);
        decoded_tree_->SetBranchAddress("tbin", tbin);
        decoded_tree_->SetBranchAddress("scaler", scaler);
        // Get the last entry to determine the eventid offset
        decoded_tree_->GetEntry(decoded_tree_->GetEntries() - 1);
        eventidOffset = eventid;
    } else {
        decoded_tree_->Branch("eventid", &eventid, "eventid/l");
        decoded_tree_->Branch("timestamp", &timestamp, "timestamp/l");
        decoded_tree_->Branch("timestamp_usec", &timestamp_usec, "timestamp_usec/i");
        decoded_tree_->Branch("wf", wf, "wf[4][1024]/F");
        decoded_tree_->Branch("tbin", tbin, "tbin[4][1024]/F");
        decoded_tree_->Branch("scaler", scaler, "scaler[6]/i");
        branch_set_ = true;
    }

    while (ifs >> eventid >> timestamp >> timestamp_usec) {
        eventid += eventidOffset + 1;
        ifs >> s0 >> s1 >> s2 >> s3 >> s4 >> s5;
        scaler[0] = s0; scaler[1] = s1; scaler[2] = s2;
        scaler[3] = s3; scaler[4] = s4; scaler[5] = s5;

        for (int ibin = 0; ibin < 1024; ++ibin) {
            ifs >> t1 >> u1 >> t2 >> u2 >> t3 >> u3 >> t4 >> u4;
            tbin[0][ibin] = t1; wf[0][ibin] = u1;
            tbin[1][ibin] = t2; wf[1][ibin] = u2;
            tbin[2][ibin] = t3; wf[2][ibin] = u3;
            tbin[3][ibin] = t4; wf[3][ibin] = u4;
        }

        decoded_tree_->Fill();
        nDecodedEvents_++;
    }

    ifs.close();

    return true;
}

int drsDatDecoder::GetDecodedEventCount() const {
    return nDecodedEvents_;
}

int drsDatDecoder::GetErrorCount() const {
    return nErrors_;
}

bool drsDatDecoder::branch_set_ = false;