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
#include "daDatDecoder.hpp"

bool daDatDecoder::ConvertToTree(TTree* tree, const TString& inputFile) {
    std::ifstream ifs(inputFile.Data());
    if (!ifs.is_open()) {
        std::cerr << "Error: Cannot open file: " << inputFile << std::endl;
        return false;
    }

    // data structure
    ULong64_t eventid, timestamp;
    UInt_t timestamp_usec;
    Float_t t1, u1, t2, u2, t3, u3, t4, u4;
    UInt_t s0, s1, s2, s3, s4, s5;
    Float_t wf[4][1024];
    Float_t tbin[4][1024];
    UInt_t scaler[6];

    UInt_t eventidOffset = 0;
    static bool branchesSet = false;
    if (branchSet) {
        tree->SetBranchAddress("eventid", &eventid);
        tree->SetBranchAddress("timestamp", &timestamp);
        tree->SetBranchAddress("timestamp_usec", &timestamp_usec);
        tree->SetBranchAddress("wf", wf);
        tree->SetBranchAddress("tbin", tbin);
        tree->SetBranchAddress("scaler", scaler);
        // Get the last entry to determine the eventid offset
        tree->GetEntry(tree->GetEntries() - 1);
        eventidOffset = eventid;
    } else {
        tree->Branch("eventid", &eventid, "eventid/l");
        tree->Branch("timestamp", &timestamp, "timestamp/l");
        tree->Branch("timestamp_usec", &timestamp_usec, "timestamp_usec/i");
        tree->Branch("wf", wf, "wf[4][1024]/F");
        tree->Branch("tbin", tbin, "tbin[4][1024]/F");
        tree->Branch("scaler", scaler, "scaler[6]/i");
        branchSet = true;
    }

    while (ifs >> eventid >> timestamp >> timestamp_usec) {
        eventid += eventidOffset;
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

        tree->Fill();
    }

    ifs.close();
    return true;
}
