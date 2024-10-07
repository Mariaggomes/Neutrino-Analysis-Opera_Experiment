void DrawHists()
{
  gStyle->SetOptStat(111111);

  // Load histograms from a file

  TFile* HistFile = TFile::Open("HistFile.root");

  TH1D* H1_CharmedParticleFlightLengths = (TH1D*)HistFile->Get("H1_CharmedParticleFlightLengths");

  TH1D* H1_DaughterTrackIPs = (TH1D*)HistFile->Get("H1_DaughterTrackIPs");

  // Draw the histograms

  TCanvas* C1_CharmSampleHists = new TCanvas("C1_CharmSampleHists",
                                             "C1_CharmSampleHists",
                                             50, 50,     // Position of the upper-left corner (in pixels)
                                             1400, 700); // Width and height (in pixels)

  C1_CharmSampleHists->Divide(2, 1); // Divides the canvas into cells organized in one row and too columns 

  C1_CharmSampleHists->cd(1); // Makes the first cell of the canvas active (to draw a histogram here)

  H1_CharmedParticleFlightLengths->Draw("hist");


  //gPad->SetGrid();   // Sets vertical and horizontal grid lines

  //gPad->SetTickx(1); // draws ticks along X axis not only in the bottom, but also in the top part of the frame

  //H1_CharmedParticleFlightLengths->GetYaxis()->SetNdivisions(-306); // Sets number of primary ticks (=5) and secondary ticks (=2). Minus before 306 forces to set exact numbers.


  C1_CharmSampleHists->cd(2); // Makes the second cell of the canvas active (to draw a histogram here)

  H1_DaughterTrackIPs->Draw("hist");

  C1_CharmSampleHists->SaveAs("CharmSampleHists.png");

  //---
}
