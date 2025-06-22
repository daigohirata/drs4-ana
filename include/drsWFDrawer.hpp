//
// Created by Daigo Hirata on 2025/04/30
//

#ifndef DRS_WF_DRAWER_HPP
#define DRS_WF_DRAWER_HPP

#include <vector>

#include <TString.h>

bool drsWFDrawer(const TString& inputFile,
                 const TString& outputFile,
                 const int eventId,
                 const std::vector<bool>& drawChannel,
                 const TString& branchName,
                 const TString& verticalScale,
                 const TString& horizontalScale,
                 const TString& outputFormat);

#endif // DRS_WF_DRAER_HPP