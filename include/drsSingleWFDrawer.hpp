//
// Created by Daigo Hirata on 2025/04/30
//

#ifndef DRS_SINGLE_WF_HPP
#define DRS_SINGLE_WF_HPP

#include <iostream>
#include <vector>

#include <TString.h>
#include <TCanvas.h>
#include <TGraph.h>

class drsSingleWFDrawer {
  public:
    drsSingleWFDrawer(const TCanvas *canvas,
                      const Float_t *xArray,
                      const Float_t *yArray, 
                      const int eventId, 
                      const TString &branchName, 
                      const TString &verticalScale,
                      const TString &horizontalScale,
                      const TString &outputFormat);
    ~drsSingleWFDrawer();

    TGraph *drawWaveform();

  private:
    Float_t *x_array_, *y_array_;
    int event_id_;
    std::vector<bool> draw_channel_;
    TString branch_name_;
    Float_t vertical_min_, vertical_max_;
    Float_t horizontal_min_, horizontal_max_;
    TString output_format_;

    static bool first_time_;
};

#endif // DRS_SINGLE_WF_HPP