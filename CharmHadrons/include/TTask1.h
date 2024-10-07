#pragma once
//-------------------------------------------------------------------------------

#include <vector>
#include <map>

#include "TH1D.h"
//-------------------------------------------------------------------------------

class TTask1
{
 public:

  TTask1();

  TTask1(const TTask1&) = delete;

  virtual ~TTask1();

  TTask1& operator= (const TTask1&) = delete;

  void Run();

 private:

  ULong64_t mEventId;

  size_t mNbOfEvents;

  std::map<ULong64_t, std::vector<Double_t>> mPrimaryVertices;   // A structure where the 1-ry vertex coordinates will be stored separately for each event id
  std::map<ULong64_t, std::vector<Double_t>> mSecondaryVertices; // A structure where the 2-ry vertex coordinates will be stored separately for each event id

  std::map<ULong64_t, std::vector<std::vector<Double_t>>> mDaughterTrackLineSets; // A structure where 6 track coordinates (3 coordinates of the beginning point and 3 coordinate of the end point) will be stored separately for a set of daughter tracks for each event id

  TH1D* mH1_CharmedParticleFlightLengths;
  TH1D* mH1_DaughterTrackIPs;

  void FindDataFiles();

  void ReadVertexFile(const std::string& DataFilePath);

  void ReadTrackLinesFile(const std::string& DataFilePath);

  void CheckDataStructures();

  void ClearDataStructures();

  void InitHists();

  void SaveAndDeleteHists();

  void FillHists();

  void FillHist_CharmedParticleFlightLengths();

  void FillHist_DaughterTrackIPs();
};
//-------------------------------------------------------------------------------
