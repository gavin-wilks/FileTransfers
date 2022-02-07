#include "../StRoot/StEventPlaneMaker/StEventPlaneCons.h"
#include <string>
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TDirectory.h"

using namespace std;

void plotV2Comp(int beamEnergy = 1, int cent9 = 5)
{
  // Load in data
  string inputfile = Form("../StRoot/StEventPlaneUtility/ChargedFlow/file_%s_ChargedFlow.root",recoEP::mBeamEnergy[beamEnergy].c_str());
  TFile *File_InPut = TFile::Open(inputfile.c_str());
  TProfile *p_mChargedV2Ep[10]; // v2Ep vs. pt
  
  string ProName;
  ProName = Form("p_mChargedV2Ep_Cent%d",cent9);
  p_mChargedV2Ep = (TProfile*)File_InPut->Get(ProName.c_str());

  // Load in paper results
  string paperfile = Form"../ComparisonFiles/HEPData-ins1119620-v1-root.root";
  TFile *File_Paper = TFile::Open(paperfile.c_str());
  TDirectory *dir = (TDirectory*) File_Paper->Get("Table 5;1");
  dir->cd();
  TGraphAsymmErrors *g_mChargedV2Off = dir->Get("Graph1D_y1");
  
  TH1F *h_play = new TH1F("h_play","h_play",100,-2.0,8.0);
  for(Int_t i_bin = 0; i_bin < 100; i_bin++)
  {
    h_play->SetBinContent(i_bin+1,-10.0);
    h_play->SetBinError(i_bin+1,1.0);
  }
  h_play->SetTitle("");
  h_play->SetStats(0);
  h_play->GetXaxis()->SetTitle("#eta");
  h_play->GetYaxis()->SetTitle("v_{1} (%)");
  h_play->GetXaxis()->CenterTitle();
  h_play->GetYaxis()->CenterTitle();
  h_play->GetXaxis()->SetTitleSize(0.06);
  h_play->GetYaxis()->SetTitleSize(0.06);
  h_play->GetXaxis()->SetRangeUser(-1.1,1.1);
  h_play->GetYaxis()->SetRangeUser(-0.4,0.4);
  h_play->GetXaxis()->SetLabelSize(0.04);
  h_play->GetYaxis()->SetLabelSize(0.04);
  h_play->SetNdivisions(505,"X");
  h_play->SetNdivisions(505,"Y");

  TCanvas *c_v2 = new TCanvas("c_v2","c_v2",10,10,800,800);
  c_v2->SetLeftMargin(0.15);
  c_v2->SetBottomMargin(0.15);
  c_v2->SetGrid(0,0);
  c_v2->SetTicks(1,1);
  c_v2->cd();

  h_play->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  h_play->GetYaxis()->SetTitle("v_{2}");
  h_play->GetXaxis()->SetRangeUser(0.0,5.0);
  h_play->GetYaxis()->SetRangeUser(-0.05,0.35);
  h_play->DrawCopy("pE");

  p_mChargedV2Ep->SetMarkerStyle(24);
  p_mChargedV2Ep->SetMarkerColor(kAzure+2);
  p_mChargedV2Ep->SetMarkerSize(1.5);
  p_mChargedV2Ep->SetLineColor(kAzure+2);
  p_mChargedV2Ep->Draw("pE1X0 same");
  
  g_mChargedV2Off->SetMarkerColor(kRed);
  g_mChargedV2Off->SetMarkerStyle(20);
  g_mChargedV2Off->SetLineColor(kRed);
  g_mChargedV2Off->SetMarkerSize(1.5);
  g_mChargedV2Off->Draw("pE1X0 same");
  
  TLegend *leg = new TLegend(0.20,0.70,0.45,0.85);
  leg->SetFillColor(10);
  leg->SetBorderSize(0);
  leg->AddEntry(p_mChargedV2Ep,"v_{2}^{EP,TPC}","p");
  leg->Draw("same");
  FigureName = Form("./figures/c_mChargedV2Ep_%s_Cent%d.pdf",recoEP::mBeamEnergy[beamEnergy].c_str(),cent9);
  c_v2->SaveAs(FigureName.c_str());
}
