#include "Riostream.h"  // instead of #include <fstream>, #include <iostream>, and #include <iomanip>
#include "TFile.h"
#include "TSystemDirectory.h"
#include "TSystem.h"
#include "TMath.h"

#include "TTask1.h"
//-------------------------------------------------------------------------------

using namespace std;
//-------------------------------------------------------------------------------

TTask1::TTask1()
{
  InitHists();
}
//-------------------------------------------------------------------------------

TTask1::~TTask1()
{
  SaveAndDeleteHists();

  ClearDataStructures();
}
//-------------------------------------------------------------------------------

void TTask1::Run()
{
  FindDataFiles();

  CheckDataStructures();

  FillHists();
}
//-------------------------------------------------------------------------------

void TTask1::InitHists()
{
  TH1D* h1;

  h1 = mH1_CharmedParticleFlightLengths = new TH1D("H1_CharmedParticleFlightLengths",
                                                   "Flight lengths of charmed hadrons",
                                                   9, 0, 5300);

  h1->SetFillColor(kBlue);
  h1->SetXTitle("Flight length (#mum)");
  h1->SetYTitle("Nb of events");

  //---

  h1 = mH1_DaughterTrackIPs = new TH1D("H1_DaughterTrackIPs",
                                       "Impact parameters of tracks of the daughter particles",
                                       10, 0, 500);

  h1->SetFillColor(kRed);
  h1->SetXTitle("IP (#mum)");
  h1->SetYTitle("Nb of tracks");

  //---
}
//-------------------------------------------------------------------------------

void TTask1::FillHists()
{
  FillHist_CharmedParticleFlightLengths();

  FillHist_DaughterTrackIPs();
}
//-------------------------------------------------------------------------------

void TTask1::SaveAndDeleteHists()
{
  TFile* HistFile = new TFile("HistFile.root", "recreate");

  mH1_CharmedParticleFlightLengths->Write();
  SafeDelete(mH1_CharmedParticleFlightLengths);

  mH1_DaughterTrackIPs->Write();
  SafeDelete(mH1_DaughterTrackIPs);

  SafeDelete(HistFile);
}
//-------------------------------------------------------------------------------

void TTask1::ClearDataStructures()
{
  for (auto& PrimaryVertices : mPrimaryVertices) PrimaryVertices.second.clear();
  mPrimaryVertices.clear();

  for (auto& SecondaryVertices : mSecondaryVertices) SecondaryVertices.second.clear();
  mSecondaryVertices.clear();

  for (auto& DaughterTrackLineSets : mDaughterTrackLineSets)
  {
    for (auto& trackLines : DaughterTrackLineSets.second) trackLines.clear();
    DaughterTrackLineSets.second.clear();
  }
  mDaughterTrackLineSets.clear();
}
//-------------------------------------------------------------------------------

void TTask1::CheckDataStructures() // Just checks if the sizes of the three std::maps are equal, so each 2-ry vertex as well as each track can be associated with the 1-ry vertex of the same event
{
  mNbOfEvents = mPrimaryVertices.size();

  if ( mSecondaryVertices.size() != mNbOfEvents )
  {
    cerr << "Error in TTask1::" << __func__ << "():" << endl
         << "Nb of 1-ry vertices = " << mNbOfEvents << endl
         << "Nb of 2-ry vertices = " << mSecondaryVertices.size() << endl
         << "Exit..." << endl;
    exit(0);
  }

  if ( mDaughterTrackLineSets.size() != mNbOfEvents )
  {
    cerr << "Error in TTask1::" << __func__ << "():" << endl
         << "Nb of 1-ry vertices = " << mNbOfEvents << endl
         << "Nb of sets of daughter track lines = " << mDaughterTrackLineSets.size() << endl
         << "Exit..." << endl;
    exit(0);
  }
}
//-------------------------------------------------------------------------------

void TTask1::FindDataFiles()
{
  const string DataDirName = "data/CharmSample_EmulsionDataset";

  TSystemDirectory DataDir( DataDirName.data(), DataDirName.data() );

  TList* DataDirFileList = DataDir.GetListOfFiles();

  if ( !DataDirFileList || (DataDirFileList->GetSize() < 3) )
  {
    cerr << "Error in TTask1::" << __func__ << "():" << endl
         << "Current dir: " << gSystem->pwd() << endl
         << "The folder " << DataDirName << " has no files!" << endl
         << "Exit..." << endl;
    exit(0);
  }

  TIter nextFile(DataDirFileList);

  for (TSystemFile* DataFile; ( DataFile = (TSystemFile*)nextFile() ); )
  {
    if ( DataFile->IsDirectory() ) continue; //!!!

    string DataFileName = DataFile->GetName();

    size_t StrPos = DataFileName.find("_Vertices.csv");

    if (StrPos != string::npos)
    {
      mEventId = stoull( DataFileName.substr(0, StrPos) );

      string DataFilePath = DataDirName + "/" + DataFileName;

      ReadVertexFile(DataFilePath);

      continue; //!!!
    }

    StrPos = DataFileName.find("_TrackLines.csv");

    if (StrPos == string::npos) continue; //!!!

    mEventId = stoull( DataFileName.substr(0, StrPos) );

    string DataFilePath = DataDirName + "/" + DataFileName;

    ReadTrackLinesFile(DataFilePath);
  }
}
//-------------------------------------------------------------------------------

void TTask1::ReadVertexFile(const string& DataFilePath)
{
  ifstream ifs(DataFilePath);

  if (!ifs)
  {
    cerr << "Error in TTask1::" << __func__ << "():" << endl
         << "Can't open file " << DataFilePath << "!" << endl
         << "Exit..." << endl;
    exit(0);
  }

  string fstring;

  getline(ifs, fstring);

  getline(ifs, fstring);

  istringstream istr1(fstring);

  vector<Double_t>& V0 = mPrimaryVertices[mEventId];
  V0.resize(3);

  istr1 >> V0[0]; // reads the 1-ry vertex type (V0[0] is just temporarily used for that)
  istr1.ignore(); // skips the comma

  for (Int_t i = 0; i < 3; i++)
  {
    istr1 >> V0[i]; // reads the 1-ry vertex position
    istr1.ignore(); // skips the comma
  }

  getline(ifs, fstring);

  istringstream istr2(fstring);

  vector<Double_t>& V1 = mSecondaryVertices[mEventId];
  V1.resize(3);

  istr2 >> V1[0]; // reads the 2-ry vertex type (V1[0] is just temporarily used for that)
  istr2.ignore(); // skips the comma

  for (Int_t i = 0; i < 3; i++)
  {
    istr2 >> V1[i];
    istr2.ignore();
  }

  ifs.close();
}
//-------------------------------------------------------------------------------

void TTask1::ReadTrackLinesFile(const string& DataFilePath)
{
  ifstream ifs(DataFilePath);

  if (!ifs)
  {
    cerr << "Error in TTask1::" << __func__ << "():" << endl
         << "Can't open file " << DataFilePath << "!" << endl
         << "Exit..." << endl;
    exit(0);
  }

  string fstring;

  getline(ifs, fstring);

  vector<vector<Double_t>>& DTLS = mDaughterTrackLineSets[mEventId];

  while ( getline(ifs, fstring) )
  {
    istringstream istr1(fstring);

    size_t trType;

    istr1 >> trType;

    if (trType != 10) continue; // skips all tracks except for the daughter particle ones!

    istr1.ignore(); // skips the comma

    vector<Double_t> DTLC(6);

    for (Int_t i = 0; i < 6; i++)
    {
      istr1 >> DTLC[i];
      istr1.ignore();
    }

    DTLS.emplace_back(DTLC);
  }

  ifs.close();
}
//-------------------------------------------------------------------------------

void TTask1::FillHist_CharmedParticleFlightLengths()
{
  for (const auto& PrimaryVertices : mPrimaryVertices)
  {
    const ULong64_t& EventId = PrimaryVertices.first;

    const vector<Double_t>& V0 = PrimaryVertices.second;
    const vector<Double_t>& V1 = mSecondaryVertices[EventId];

    Double_t dx10 = V1[0] - V0[0]; // x1 - x0
    Double_t dy10 = V1[1] - V0[1]; // y1 - y0
    Double_t dz10 = V1[2] - V0[2]; // z1 - z0

    Double_t D = TMath::Sqrt(dx10*dx10 + dy10*dy10 + dz10*dz10);

    mH1_CharmedParticleFlightLengths->Fill(D);
  }
}
//-------------------------------------------------------------------------------

void TTask1::FillHist_DaughterTrackIPs()
{
  for (const auto& PrimaryVertices : mPrimaryVertices)
  {
    const ULong64_t& EventId = PrimaryVertices.first;

    const vector<Double_t>& V0 = PrimaryVertices.second;

    const vector<vector<Double_t>>& DTLS = mDaughterTrackLineSets[EventId];

    for (const vector<Double_t>& DTLC : DTLS)
    {
      Double_t dx21 = DTLC[3] - DTLC[0]; // x2 - x1
      Double_t dy21 = DTLC[4] - DTLC[1]; // y2 - y1
      Double_t dz21 = DTLC[5] - DTLC[2]; // z2 - z1

      Double_t dx10 = DTLC[0] - V0[0];   // x1 - x0
      Double_t dy10 = DTLC[1] - V0[1];   // y1 - y0
      Double_t dz10 = DTLC[2] - V0[2];   // z1 - z0

      Double_t s1 = (dy21*dz10 - dy10*dz21);
      Double_t s2 = (dx21*dz10 - dx10*dz21);
      Double_t s3 = (dx21*dy10 - dx10*dy21);

      Double_t IP = TMath::Sqrt( (s1*s1 + s2*s2 + s3*s3)/(dx21*dx21 + dy21*dy21 + dz21*dz21) );

      mH1_DaughterTrackIPs->Fill(IP);
    }

  }
}
//-------------------------------------------------------------------------------
