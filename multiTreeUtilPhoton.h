#ifndef MULTITREETUIL_H
#define MULTITREETUIL_H
// =========================================================================
// Multi Tree Utility
// Author: Yen-Jie Lee (MIT)
//       A tool for multiTree handling
// =========================================================================
#include <TTree.h>
#include <TCut.h>
#include <TFile.h>
//#include <vector.h>
#include <TH1.h>
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"

class multiTreeUtil
{
   public:
      multiTreeUtil() {
         nTrees=0;
	 for (int i=0;i<100;i++)
	 {
	    color[i]=i;
	 }
	 color[0]=2;
	 color[1]=4;
	 color[2]=kGreen+2;
	 color[3]=6;
	 color[4]=7;
	 color[5]=kGreen+4;
	 color[6]=kBlue-2;
         color[7]=kAzure+3;
         color[8]=kOrange+3;
	 color[9]=kSpring-7;
	 color[10]=kPink+4;

	 /*
	   handsomeTH1(tmp1[1],2);
	   handsomeTH1(tmp1[2],4);
	   handsomeTH1(tmp1[3],kGreen+2);
	   handsomeTH1(tmp1[4],6);
	   handsomeTH1(tmp1[5],7);
	   handsomeTH1(tmp1[6],kGreen+4);
	   handsomeTH1(tmp1[7],kBlue-2);
	   handsomeTH1(tmp1[8],kAzure+3);
	   handsomeTH1(tmp1[9],kOrange+3);
	   handsomeTH1(tmp1[10],kSpring-7);
	   handsomeTH1(tmp1[11],kPink+4);
	 */
	 
      }
      ~multiTreeUtil() {
	 
      }
      void addFile(TString filename, TString treeName, TCut cut, Float_t scaleFactor);
      void Draw(TH1D* h, TString expression,TCut cut = "" , TString  opt="");
      void Draw2(TH1D* h,TString expression,TCut cut = "", TString opt="",bool hist=true);
      void Print(Option_t* option = "");
      TTree *getTree(int i) { return trees_[i]; };
      
 private:
      int nTrees;
      vector<TFile*>  tfiles_;                // TFile 
      vector<TTree*>  trees_;                 // Trees
      vector<TString>   tfileNames_;            // File names
      vector<TCut>    tcuts_;
      vector<Float_t> scaleFactors_;
      int color[100];

      void cleanHist(TH1* h);

};

// =========================================================================
// Add file
// =========================================================================
void multiTreeUtil::addFile(TString filename, TString treeName, TCut cut, Float_t scaleFactor)
{
   TFile *f = new TFile(filename.Data());
   TTree *t = (TTree*) f->FindObjectAny(treeName.Data());
   
   if (t!=0) {
      nTrees++;
      tfileNames_.push_back(filename);
      tfiles_.push_back(f);
      trees_.push_back(t);
      tcuts_.push_back(cut);
      scaleFactors_.push_back(scaleFactor);
   }
}

// =========================================================================
// Draw
// =========================================================================
void multiTreeUtil::Draw(TH1D *h, TString expression, TCut cut, TString opt)
{

   h->Reset();
   
   for (int i=0;i<(int)trees_.size();i++)
   {
      TH1D *htmp = (TH1D*)h->Clone();
      htmp->SetName(Form("my_htmp_%d",i));
      trees_[i]->Draw(Form("%s>>my_htmp_%d",expression.Data(),i),cut&&tcuts_[i]);
      htmp->Sumw2();
      htmp->Scale(scaleFactors_[i]);
      h->Add(htmp);
      delete htmp;
   }
   
   h->Draw(opt.Data());
}

// =========================================================================
// Draw components
// =========================================================================
void multiTreeUtil::Draw2(TH1D *h, TString expression, TCut cut, TString opt,bool hist)
{
   // prepare ncoll table
   TFile* fglaub = new TFile("rootFiles/glaubertest_d1220_v1.root");
   CentralityBins* glaub = (CentralityBins*)fglaub->Get("Eff100_sim00_g0/run1");
   double ncoll[40];
   for (int icent = 0 ; icent< 40 ; icent++ ) {
      ncoll[icent] = (double)glaub->NcollMeanOfBin(icent);
   }
   
   TH1D *hComponent[100];
   h->Reset();
   
   TH1D * tempCent[40];
   
   for (int i=0;i<(int)trees_.size();i++)
      {
      TString hName = Form("%s_Draw_%d",h->GetName(),i);
      TH1D *htmp= (TH1D*)h->Clone();
      htmp->SetName(hName.Data());
      
      for ( int icent = 0 ; icent <40 ; icent++ ) {
	 tempCent[icent] = (TH1D*)htmp->Clone(Form("%s_%d",hName.Data(),icent));
	 tempCent[icent]->Reset();
	 TCut ithCent = Form("cBin==%d",icent);
	 trees_[i]->Draw(Form("%s>>%s_%d",expression.Data(),hName.Data(),icent),cut&&tcuts_[i]&&ithCent);
	 tempCent[icent]->Sumw2();
	 htmp->Add(tempCent[icent],  ncoll[icent]);
      }
      //      htmp->Sumw2();
      htmp->Scale(scaleFactors_[i]);
      h->Add(htmp);
      hComponent[i]=htmp;
      }
   h->Sumw2();
   h->DrawCopy(opt.Data());
   
   for (int i=0;i<(int)trees_.size();i++)
      {
	 hComponent[i]->SetLineColor(color[i]);
         hComponent[i]->SetMarkerColor(color[i]);
	 if ( hist) opt ="hist";
	 hComponent[i]->DrawCopy(Form("%s same",opt.Data()));
      }
}

// =========================================================================
// Print variables from the first tree
// =========================================================================
void multiTreeUtil::Print(Option_t* option)
{
   trees_[0]->Print(option);   
}

//--------------------------------PRIVATE-----------------------------------

// =========================================================================
// Clear
// =========================================================================
void multiTreeUtil::cleanHist(TH1* h)
{
   for (int i=0;i<=h->GetNbinsX()+1;i++) {
      h->SetBinContent(i,0);
      h->SetBinError(i,0);
   }
}


#endif
