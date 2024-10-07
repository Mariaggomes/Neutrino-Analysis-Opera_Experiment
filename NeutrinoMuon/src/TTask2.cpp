#include <sstream>

#include "Riostream.h"
#include "TSystemDirectory.h"
#include "TMath.h"
#include "TFile.h"

#include "TTask2.h"
//-------------------------------------------------------------------------------

using namespace std;
//-------------------------------------------------------------------------------

TTask2::TTask2()
{
  InitHists();
}
//-------------------------------------------------------------------------------

TTask2::~TTask2()
{
  SaveAndDeleteHists();

  ClearDataStructures();
}
//-------------------------------------------------------------------------------

void TTask2::Run()
{
  FindDataFiles();

  CheckDataStructures();

  FillHists();
}
//-------------------------------------------------------------------------------

void TTask2::InitHists()
{
  TH1I* h1;

  h1 = mH1_TrackMultiplicities_FromVertexFiles = new TH1I("H1_TrackMultiplicities_FromVertexFiles",
                                                          "Track multiplicities (from *_Vertex.csv files)",
                                                          10, 1, 11);

  h1->SetFillColor(kBlue);
  h1->SetXTitle("Multiplicity");
  h1->SetYTitle("Nb of events");

  h1->GetYaxis()->SetTitleOffset(1.4);

  //---

  h1 = mH1_TrackMultiplicities_FromTrackFiles = new TH1I("H1_TrackMultiplicities_FromTrackFiles",
                                                          "Track multiplicities (from *_Track.csv files)",
                                                          10, 1, 11);

  h1->SetFillColor(kGreen);
  h1->SetXTitle("Multiplicity");
  h1->SetYTitle("Nb of events");

  h1->GetYaxis()->SetTitleOffset(1.4);

  //---

  TH2D* h2;

  h2 = mH2_MuTrackAngles_InDeg = new TH2D("H2_MuTrackAngles_InDeg",
                                          "Muon track angles (in degrees)",
                                          20, -30, 30,           // The range is for XZ angle in degrees!
                                          20, -30, 30);          // The range is for YZ angle in degrees!

  h2->GetXaxis()->SetTitleOffset(1.5);
  h2->GetYaxis()->SetTitleOffset(1.5);

  h2->SetXTitle("AngXZ (deg)");
  h2->SetYTitle("AngYZ (deg)");
  h2->SetZTitle("Nb of events");

  //---

  h2 = mH2_MuTrackAngles_InRad = new TH2D("H2_MuTrackAngles_InRad",
                                          "Muon track angles (in radians)",
                                          20, -0.5236, 0.5236,           // The range is for XZ angle in radians!
                                          20, -0.5236, 0.5236);          // The range is for YZ angle in radians!

  h2->GetXaxis()->SetTitleOffset(1.5);
  h2->GetYaxis()->SetTitleOffset(1.5);

  h2->SetXTitle("AngXZ (rad)");
  h2->SetYTitle("AngYZ (rad)");
  h2->SetZTitle("Nb of events");
}
//-------------------------------------------------------------------------------

void TTask2::FillHists()
{
  FillHist_TrackMultiplicities();

  FillHist_MuTrackAngles();
}
//-------------------------------------------------------------------------------

void TTask2::SaveAndDeleteHists()
{
  TFile* HistFile = new TFile("HistFile.root", "recreate");

  mH1_TrackMultiplicities_FromVertexFiles->Write();
  SafeDelete(mH1_TrackMultiplicities_FromVertexFiles);

  mH1_TrackMultiplicities_FromTrackFiles->Write();
  SafeDelete(mH1_TrackMultiplicities_FromTrackFiles);

  mH2_MuTrackAngles_InDeg->Write();
  SafeDelete(mH2_MuTrackAngles_InDeg);

  mH2_MuTrackAngles_InRad->Write();
  SafeDelete(mH2_MuTrackAngles_InRad);

  SafeDelete(HistFile);
}
//-------------------------------------------------------------------------------

void TTask2::ClearDataStructures()
{
  mTrackMultiplicities_FromVertexFiles.clear();
  mTrackMultiplicities_FromTrackFiles.clear();

  for (auto& MuTrackSlopeSets : mMuTrackSlopeSets)
  {
    for (auto& trackSlopes : MuTrackSlopeSets.second) trackSlopes.clear();
    MuTrackSlopeSets.second.clear();
  }

  mMuTrackSlopeSets.clear();
}
//-------------------------------------------------------------------------------

void TTask2::CheckDataStructures()
{
  mNbOfEvents = mTrackMultiplicities_FromVertexFiles.size();

  if ( mTrackMultiplicities_FromTrackFiles.size() != mNbOfEvents )
  {
    cerr << "Error in TTask2::" << __func__ << "():" << endl
         << "Nb of vertex files = " << mNbOfEvents << endl
         << "Nb of track files = " << mTrackMultiplicities_FromTrackFiles.size() << endl
         << "Exit..." << endl;
    exit(0);
  }

  if ( mMuTrackSlopeSets.size() != mNbOfEvents )
  {
    cerr << "Error in TTask2::" << __func__ << "():" << endl
         << "Nb of vertex files = " << mNbOfEvents << endl
         << "Nb of track files = " << mMuTrackSlopeSets.size() << endl
         << "Exit..." << endl;
    exit(0);
  }
}
//-------------------------------------------------------------------------------

void TTask2::FindDataFiles()
{
  const string DataDirName = "data/NuMuSample_EmulsionDataset";

  TSystemDirectory DataDir( DataDirName.data(), DataDirName.data() );

  TList* DataDirFileList = DataDir.GetListOfFiles();

  if ( !DataDirFileList || (DataDirFileList->GetSize() < 3) )
  {
    cerr << "Error in TTask2::" << __func__ << "():" << endl
         << "The folder " << DataDirName << " has no files!" << endl
         << "Exit..." << endl;
    exit(0);
  }

  TIter nextFile(DataDirFileList);

  for (TSystemFile* DataFile; ( DataFile = (TSystemFile*)nextFile() ); ) // !!!
  {
    if ( DataFile->IsDirectory() ) continue; //!!!

    string DataFileName = DataFile->GetName();

    size_t StrPos = DataFileName.find("_Vertex.csv");

    if (StrPos != string::npos)
    {
      mEventId = stoull( DataFileName.substr(0, StrPos) );

      string DataFilePath = DataDirName + "/" + DataFileName;

      ReadVertexFile(DataFilePath);

      continue; //!!!
    }

    StrPos = DataFileName.find("_Tracks.csv");

    if (StrPos == string::npos) continue; //!!!

    mEventId = stoull( DataFileName.substr(0, StrPos) );

    string DataFilePath = DataDirName + "/" + DataFileName;

    ReadTracksFile(DataFilePath);
  }
}
//-------------------------------------------------------------------------------

void TTask2::ReadVertexFile(const string& DataFilePath)
{
  ifstream ifs(DataFilePath);

  if (!ifs)
  {
    cerr << "Error in TTask2::" << __func__ << "():" << endl
         << "Can't open file " << DataFilePath << "!" << endl
         << "Exit..." << endl;
    exit(0);
  }

  string fstring;

  getline(ifs, fstring);

  getline(ifs, fstring);

  istringstream istr1(fstring);

  ULong64_t EventId;
  ULong64_t TimeStamp;

  istr1 >> EventId;
  istr1.ignore();

  istr1 >> TimeStamp;
  istr1.ignore();

  Double_t VertexCoords[6];

  for (Int_t i = 0; i < 6; i++)
  {
    istr1 >> VertexCoords[i];
    istr1.ignore();
  }

  istr1 >> mTrackMultiplicities_FromVertexFiles[mEventId];

  ifs.close();
}
//-------------------------------------------------------------------------------

void TTask2::ReadTracksFile(const string& DataFilePath)
{
  ifstream ifs(DataFilePath);

  if (!ifs)
  {
    cerr << "Error in TTask2::" << __func__ << "():" << endl
         << "Can't open file " << DataFilePath << "!" << endl
         << "Exit..." << endl;
    exit(0);
  }

  string fstring;

  getline(ifs, fstring);

  size_t NbOfTracks = 0; // Track multiplicity

  vector<vector<Double_t>>& MTSS = mMuTrackSlopeSets[mEventId];

  while ( getline(ifs, fstring) )
  {
    istringstream istr1(fstring);

    size_t trType;

    istr1 >> trType;

    NbOfTracks++;

    if (trType != 1) continue; // Skip all tracks except the muon tracks!

    istr1.ignore();

    Double_t trCoord;

    for (Int_t i = 0; i < 3; i++)
    {
      istr1 >> trCoord;
      istr1.ignore();
    }

    vector<Double_t> TS(2);

    //vector<Double_t>& TS = mMuTrackSlopes[mEventId];
    //TS.resize(2);

    for (Int_t i = 0; i < 2; i++) // Reading of the muon track slopes
    {
      istr1 >> TS[i];
      istr1.ignore();
    }

    MTSS.emplace_back(TS);
  }

  ifs.close();

  mTrackMultiplicities_FromTrackFiles[mEventId] = NbOfTracks;
}
//-------------------------------------------------------------------------------

void TTask2::FillHist_TrackMultiplicities()
{
  for (const auto& TrackMultiplicities_FromVertexFiles : mTrackMultiplicities_FromVertexFiles)
  {
    //const ULong64_t& EventId = TrackMultiplicities_FromVertexFiles.first;

    mH1_TrackMultiplicities_FromVertexFiles->Fill(TrackMultiplicities_FromVertexFiles.second);
  }


  for (const auto& TrackMultiplicities_FromTrackFiles : mTrackMultiplicities_FromTrackFiles)
  {
    //const ULong64_t& EventId = TrackMultiplicities_FromTrackFiles.first;

    mH1_TrackMultiplicities_FromTrackFiles->Fill(TrackMultiplicities_FromTrackFiles.second);
  }
}
//-------------------------------------------------------------------------------

void TTask2::FillHist_MuTrackAngles()
{
  for (const auto& MuTrackSlopeSets : mMuTrackSlopeSets)
  {
    //const ULong64_t& EventId = MuTrackSlopeSets.first;

    const vector<vector<Double_t>>& MTSS = MuTrackSlopeSets.second;

    for (const vector<Double_t>& TS : MTSS)
    {
      Double_t AngXZ = TMath::ATan(TS[0]);

      Double_t AngYZ = TMath::ATan(TS[1]);

      mH2_MuTrackAngles_InRad->Fill(AngXZ, AngYZ);

      AngXZ *= TMath::RadToDeg();
      AngYZ *= TMath::RadToDeg();

      mH2_MuTrackAngles_InDeg->Fill(AngXZ, AngYZ);
    }
  }
}
//-------------------------------------------------------------------------------
