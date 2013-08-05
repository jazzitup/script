#ifndef csCompare_C
#define csCompare_C

#include <TCut.h>
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
#include <TClonesArray.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include "commonUtility.h"


float csCompareTwo(TCanvas* c101=0, int nv=1, int nv2=4, TString fname1="rootFiles/genParticles_diJet50.root", TString fname2="rootFiles/genParticles_emJet50.root", char* prx="x" ) ;
void csCompareMerge(TCanvas* c101=0, TString fname1d="",float f1d=0,  TString fname1e="", float f1e=0, TString fname2d="",float f2d=0,  TString fname2e="", float f2e=0, TString fname3d="", float f3d=0,TString fname3e="",float f3e=0, TString fname4d="",float f4d=0,  TString fname4e="", float f4e=0  );

void csCompare() {
   TCanvas* c101 = new TCanvas("c101","",1400,700);
   makeMultiPanelCanvas(c101,4,2,0.0,0.0,0.2,0.15,0.02);

   float r1 = csCompareTwo(c101,1,5,"rootFiles/genParticles_dijet15_simpler.root", "rootFiles/genParticles_emJet15_simpler.root","15GeV");
   drawText( Form("15GeV ratio = %.3f",(float)r1), 0.45,0.85);
   
   float r2 = csCompareTwo(c101,2,6,"rootFiles/genParticles_dijet30_simpler.root", "rootFiles/genParticles_emJet30_simpler.root", "30GeV" );
   drawText( Form("30GeV ratio = %.3f",(float)r2), 0.45,0.85);
   
   float r3 = csCompareTwo(c101,3,7,"rootFiles/genParticles_dijet50_simpler.root", "rootFiles/genParticles_emJet50_simpler.root", "50GeV" );
   drawText( Form("50GeV ratio = %.3f",(float)r3), 0.45,0.85);
   
   float r4 = csCompareTwo(c101,4,8,"rootFiles/genParticles_dijet80_simpler.root", "rootFiles/genParticles_emJet80_simpler.root", "80GeV" );
   drawText( Form("80GeV ratio = %.3f",(float)r4), 0.45,0.85);
   
   cout << "r =" << r1 << ", "  << r2 << ", "  << r3 << ", "  << r4 << endl; 
   
   const double csDij15 =   1.928e-01;
   const double csDij30 =   9.715e-03;
   const double csDij50 =   9.198e-04;
   const double csDij80 =   9.968e-05;
   double cs1 =csDij15;  //- csDij30;  those number above are already differential cross-section in pT 
   double cs2 = csDij30; // - csDij50;
   double cs3 = csDij50; // - csDij80;
   double cs4 = csDij80;
   float f1d=  cs1;     float f1e=cs1 * r1;
   float f2d=  cs2;     float f2e=cs2 * r2;
   float f3d=  cs3;     float f3e=cs3 * r3;
   float f4d=  cs4;     float f4e=cs4 * r4;

   TCanvas* c102 = new TCanvas("c102","",500,500);
   csCompareMerge(c102, 
		  "rootFiles/genParticles_dijet15_simpler.root", f1d,
		  "rootFiles/genParticles_emJet15_simpler.root", f1e,
		  "rootFiles/genParticles_dijet30_simpler.root", f2d,
                  "rootFiles/genParticles_emJet30_simpler.root", f2e,
                  "rootFiles/genParticles_dijet50_simpler.root", f3d,
                  "rootFiles/genParticles_emJet50_simpler.root", f3e,
                  "rootFiles/genParticles_dijet80_simpler.root", f4d,
                  "rootFiles/genParticles_emJet80_simpler.root", f4e
		  );
      
      
      
   
}

float csCompareTwo(TCanvas* c101, int nv, int nv2, TString fname1, TString fname2, char* prx) {
   TFile *file1 = new TFile(fname1);
   TTree *ana1 = (TTree*)file1->FindObjectAny("photon");
   
   TFile *file2 = new TFile(fname2);
   TTree *ana2 = (TTree*)file2->FindObjectAny("photon");


   c101->cd(nv);

   TH1D* pt1 = new TH1D(Form("pt1_%s",prx),";pt;Entries",10,0,100);
   TH1D* pt2 = new TH1D(Form("pt2_%s",prx),";pt;Entries",10,0,100);
ana1->Draw(Form("et>>pt1_%s",prx),"(id==221 || id==111) && abs(eta)<1.44");
   ana2->Draw(Form("et>>pt2_%s",prx),"(id==221 || id==111) && abs(eta)<1.44");
   pt1->Sumw2(); 
   pt2->Sumw2();
   pt1->Scale( 1. / ana1->GetEntries());
   pt2->Scale( 1. / ana2->GetEntries());
   
   float r12 = pt1->Integral( 3,10) / pt2->Integral(3,10);
   pt2->Scale(r12);
   pt1->DrawCopy();
   handsomeTH1(pt2,2);
   pt2->DrawCopy("same");
   gPad->SetLogy();
   
   c101->cd(nv2);
   TH1D* hratio = (TH1D*)pt2->Clone(Form("ratio_%s",prx));
   hratio->SetYTitle("ratio");
   hratio->Divide(pt1);
   hratio->SetAxisRange(0,3,"Y");
   hratio->Draw();
   return r12;







}





void csCompareMerge(TCanvas* c101, TString fname1d, float f1d, TString fname1e, float f1e, TString fname2d, float f2d, TString fname2e, float f2e, TString fname3d,float f3d,  TString fname3e,float f3e, TString fname4d, float f4d, TString fname4e,float f4e )
{
   
   TFile *file1d = new TFile(fname1d);
   TTree *ana1d = (TTree*)file1d->FindObjectAny("photon");
   TFile *file1e = new TFile(fname1e);
   TTree *ana1e = (TTree*)file1e->FindObjectAny("photon");

   TFile *file2d = new TFile(fname2d);
   TTree *ana2d = (TTree*)file2d->FindObjectAny("photon");
   TFile *file2e = new TFile(fname2e);
   TTree *ana2e = (TTree*)file2e->FindObjectAny("photon");

   TFile *file3d = new TFile(fname3d);
   TTree *ana3d = (TTree*)file3d->FindObjectAny("photon");
   TFile *file3e = new TFile(fname3e);
   TTree *ana3e = (TTree*)file3e->FindObjectAny("photon");

   TFile *file4d = new TFile(fname4d);
   TTree *ana4d = (TTree*)file4d->FindObjectAny("photon");
   TFile *file4e = new TFile(fname4e);
   TTree *ana4e = (TTree*)file4e->FindObjectAny("photon");
   
   c101->Divide(1,2);
   c101->cd(1);


   const int nBins = 6;
   double pTs[nBins+1] = {0,20,25,30,40,50,80};

   TH1D* pt1d = new TH1D("pt1d",";pt;Entries", nBins, pTs);
   TH1D* pt1e = new TH1D("pt1e",";pt;Entries",nBins, pTs);
   TH1D* pt2d = new TH1D("pt2d",";pt;Entries",nBins, pTs);
   TH1D* pt2e = new TH1D("pt2e",";pt;Entries",nBins, pTs);
   TH1D* pt3d = new TH1D("pt3d",";pt;Entries",nBins, pTs);
   TH1D* pt3e = new TH1D("pt3e",";pt;Entries",nBins, pTs);
   TH1D* pt4d = new TH1D("pt4d",";pt;Entries",nBins, pTs);
   TH1D* pt4e = new TH1D("pt4e",";pt;Entries",nBins, pTs);

   ana1d->Draw("et>>pt1d","(id==221 || id==111) && abs(eta)<1.44");
   ana1e->Draw("et>>pt1e","(id==221 || id==111) && abs(eta)<1.44");
   ana2d->Draw("et>>pt2d","(id==221 || id==111) && abs(eta)<1.44");
   ana2e->Draw("et>>pt2e","(id==221 || id==111) && abs(eta)<1.44");
   ana3d->Draw("et>>pt3d","(id==221 || id==111) && abs(eta)<1.44");
   ana3e->Draw("et>>pt3e","(id==221 || id==111) && abs(eta)<1.44");
   ana4d->Draw("et>>pt4d","(id==221 || id==111) && abs(eta)<1.44");
   ana4e->Draw("et>>pt4e","(id==221 || id==111) && abs(eta)<1.44");

   pt1d->Sumw2();    pt1e->Sumw2();
   pt2d->Sumw2();    pt2e->Sumw2();
   pt3d->Sumw2();    pt3e->Sumw2();
   pt4d->Sumw2();    pt4e->Sumw2();

   pt1d->Scale( f1d / ana1d->GetEntries());    pt1e->Scale( f1e / ana1e->GetEntries());
   pt2d->Scale( f2d / ana2d->GetEntries());    pt2e->Scale( f2e / ana2e->GetEntries());
   pt3d->Scale( f3d / ana3d->GetEntries());    pt3e->Scale( f3e / ana3e->GetEntries());
   pt4d->Scale( f4d / ana4d->GetEntries());    pt4e->Scale( f4e / ana4e->GetEntries());

   TH1D* mD = (TH1D*)pt1d->Clone("mD");
   mD->Reset();
   mD->Add(pt1d); mD->Add(pt2d);  mD->Add(pt3d);  mD->Add(pt4d);
 
   TH1D* mE = (TH1D*)pt1d->Clone("mE");
   mE->Reset();
   mE->Add(pt1e); mE->Add(pt2e); mE->Add(pt3e); mE->Add(pt4e);

   handsomeTH1(mD,1);
   handsomeTH1(mE,2);
   //   mD->Rebin(2);
   //  mE->Rebin(2);
   mD->DrawCopy();
   mE->DrawCopy("same");
   gPad->SetLogy();

   c101->cd(2);
   TH1D* hratio = (TH1D*)mE->Clone("ratioED");
   hratio->SetYTitle("ratio");
   hratio->Divide(mD);
   hratio->SetAxisRange(0,2,"Y");
   hratio->Draw();
   jumSun(pTs[0],1, pTs[nBins],1);
}










#endif
