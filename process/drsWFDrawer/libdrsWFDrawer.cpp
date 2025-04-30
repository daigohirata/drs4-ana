//
// Created by David on 2025/04/30.
//

#include <iostream>

#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraph.h>

#include "drsConst.hpp"
#include "drsWFDrawer.hpp"

bool drsWFDrawer(const TString& inputFile,
                 const TString& outputFile,
                 const int eventId,
                 const std::vector<bool>& drawChannel,
                 const TString& branchName,
                 const TString& verticalScale,
                 const TString& horizontalScale,
                 const TString& outputFormat) {
    TFile *file = TFile::Open(inputFile);
    if (!file || file->IsZombie()) {
        std::cerr << "[Error] Failed to open file: " << inputFile << std::endl;
        return false;
    }
    TTree *tree = (TTree *)file->Get("raw");

    ULong64_t eventid;
    Float_t   draw_array[4][1024];
    Float_t   tbin[4][1024];

    tree->SetBranchAddress("eventid", &eventid);
    tree->SetBranchAddress(branchName, draw_array);
    tree->SetBranchAddress("tbin", tbin);

    tree->GetEntry(eventId);

    TCanvas* c1 = new TCanvas("c1", "Waveform Display", 800, 600);

                
}