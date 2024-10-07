#pragma once
//-------------------------------------------------------------------------------

#include <vector>
#include <map>

#include "TH2.h"
//-------------------------------------------------------------------------------

class TTask2
{
 public:

  TTask2();

  TTask2(const TTask2&) = delete;

  virtual ~TTask2();

  TTask2& operator= (const TTask2&) = delete;

  void Run();

 private:

  ULong64_t mEventId;

  size_t mNbOfEvents;

  std::map<ULong64_t, Int_t> mTrackMultiplicities_FromVertexFiles;
  std::map<ULong64_t, Int_t> mTrackMultiplicities_FromTrackFiles;

  std::map<ULong64_t, std::vector<std::vector<Double_t>>> mMuTrackSlopeSets;

  TH1I* mH1_TrackMultiplicities_FromVertexFiles;
  TH1I* mH1_TrackMultiplicities_FromTrackFiles;

  TH2D* mH2_MuTrackAngles_InDeg;
  TH2D* mH2_MuTrackAngles_InRad;

  void FindDataFiles();

  void ReadVertexFile(const std::string& DataFilePath);

  void ReadTracksFile(const std::string& DataFilePath);

  void CheckDataStructures();

  void ClearDataStructures();

  void InitHists();

  void SaveAndDeleteHists();

  void FillHists();

  void FillHist_TrackMultiplicities();

  void FillHist_MuTrackAngles();
};
//-------------------------------------------------------------------------------
