void DrawHists()
{
  gStyle->SetOptStat(111110);
  //gStyle->SetOptFit(1);

  // Load histograms from a file

  TFile* HistFile = TFile::Open("HistFile.root");

  TH1I* H1_TrackMultiplicities_FromVertexFiles = (TH1I*)HistFile->Get("H1_TrackMultiplicities_FromVertexFiles");
  TH1I* H1_TrackMultiplicities_FromTrackFiles  = (TH1I*)HistFile->Get("H1_TrackMultiplicities_FromTrackFiles");

  TH2D* H2_MuTrackAngles_InDeg = (TH2D*)HistFile->Get("H2_MuTrackAngles_InDeg");
  TH2D* H2_MuTrackAngles_InRad = (TH2D*)HistFile->Get("H2_MuTrackAngles_InRad");

  // Draw histograms

  TCanvas* C1_NuMu = new TCanvas("C1_NuMu", "C1_NuMu", 50, 50, 800, 1200);

  C1_NuMu->Divide(2, 3);

  C1_NuMu->cd(1);

  H1_TrackMultiplicities_FromVertexFiles->Draw("hist");

  C1_NuMu->cd(2);

  H1_TrackMultiplicities_FromTrackFiles->Draw("hist");

  C1_NuMu->cd(3);

  H2_MuTrackAngles_InDeg->Draw("lego2");

  C1_NuMu->cd(4);

  H2_MuTrackAngles_InDeg->Draw("colz");

  C1_NuMu->cd(5);

  H2_MuTrackAngles_InRad->Draw("lego2");

  C1_NuMu->cd(6);

  H2_MuTrackAngles_InRad->Draw("colz");

  C1_NuMu->SaveAs("NuMuSampleHists.png");
}
