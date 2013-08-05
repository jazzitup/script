#include <TStyle.h>
#include <TH1F.h>
#include <TH2D.h>
#include <TFile.h>
#include <TChain.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TNtuple.h>
#include <iostream>
#include <TLine.h>
#include <TMath.h>
#include <math.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TCut.h>
#include <TClonesArray.h>
#include "/home/kimy/script/commonUtility.h"
#define PI 3.141592653589


TH1F* templ(char* prx="")
{
   
   
   TCanvas* c0 = new TCanvas("c0","",800,400);
   c0->Divide(2,1);
   c0->Draw();
   c0->cd(1);
   TFile *f1=new TFile("../rootFiles/compPhoton_scan_0-105-120-150-200.root","r");
   char* _ntupleName_ = "_directory/photons_";
   TNtuple *nt1 = (TNtuple*)f1->Get(_ntupleName_);
   
   //TCut etaCut = "abs(eta)<1.45";
   //char* label  = "Barrel";
   
   int nBin = 100;
   float xMin = -1;
   float xMax = 20;
   TH1F* theHist = new TH1F("_theHist_",";Track Iso(GeV);Entries",nBin,xMin,xMax);
   
   
   nt1->Draw("_theVariable_>>_theHist_",etCut&&etaCut);
   
   theHist->Sumw2();
   handsomeTH1(theHist);
   theHist->Draw();
   
   TLegend* leg = new TLegend(0.56,0.85, 0.95, 0.90,NULL,"brNDC");
   easyLeg(leg,"the legend");
   //   leg->AddEntry(theHist,"compl. cone","l");
   leg->Draw();
   
   c0->SaveAs(Form("plots/thePlot_%s.gif",prx));
   
   
}

