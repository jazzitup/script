#include <TH1.h>
#include <TTree.h>
#include <iostream>
#include <TLegend.h>
#include <TCut.h>
class compareHist
{
   public:
   compareHist(TTree *myTree,char *var,char *cut1,char *cut2, float low=0,float high=0,int nbin=100,int normType=2);
   compareHist(TTree *myTree1,TTree *myTree2,char *var,char *cut1     ,double low=0,double high=0,int nbin=100,int normType=2);
   compareHist(TTree *myTree1,TTree *myTree2,char *var,char *cut1     ,char *cut2,double low=0,double high=0,int nbin=100,int normType=2);
   compareHist(TTree *myTree1,TTree *myTree2,char *var,char *histTitle,TCut  cut1,TCut cut2,double low=0,double high=0,int nbin=100,int normType=1);
   compareHist(TTree *myTree1,TTree *myTree2, TTree *myTree3,char *var,char *cut1,char *histTitle,double low=0,double high=0,int nbin=100,int normType=1);
   compareHist(TTree *myTree1,TTree *myTree2, TTree *myTree3,char *var,char *histTitle, TCut cut1,TCut cut2,TCut cut3,double low=0,double high=0,int nbin=100,int normType=1);
   
   compareHist(TH1 *myth1, TH1* myth2, TH1* myth3,char *histTitle,double low=0, double high=0, int rebin=1, int normType=0);
   
   TLegend * leg1;

       TH1F *h1;
       TH1F *h2;
       TH1F *h3;
       TH1F *h4;

       string name1;
       string name2;
       string name3;
       int nTree;

       void init();
       void SetXTitle(char *t) { h1->SetXTitle(t); h2->SetXTitle(t); if (nTree==3) h3->SetXTitle(t);}
       void SetYTitle(char *t) { h1->SetYTitle(t); h2->SetYTitle(t); if (nTree==3) h3->SetYTitle(t);}
       void SetHistName1(char *t) { name1 = t; };
       void SetHistName2(char *t) { name2 = t; };
       void SetHistName3(char *t) { name3 = t; };
       void SetHistName1(string t) { name1 = t; };
       void SetHistName2(string t) { name2 = t; };
       void SetHistName3(string t) { name3 = t; };
       void SetMarkerSize(double t) { h1->SetMarkerSize(t); h2->SetMarkerSize(t); if (nTree==3) h3->SetMarkerSize(t);}
       void Draw() { h1->Draw(); h2->Draw("same"); if (nTree==3) h3->Draw("same"); if(leg1) leg1->Draw();}
       void Draw2() { h2->Draw(); h1->Draw("same"); if (nTree==3) h3->Draw("same"); if(leg1) leg1->Draw();}
       void Draw3() { h3->Draw(); h2->Draw("same"); h1->Draw("same"); if(leg1) leg1->Draw();}
       void SetLegend(double x1,double y1, double x2, double y2);
};

compareHist::compareHist(TTree *myTree,char *var,char *cut1,char *cut2, float low,float high,int nbin,int normType)
{
   if (low==high) {
       low = myTree->GetMinimum(var);
       high = myTree->GetMaximum(var);
       
   }
   
   h1 = new TH1F(Form("h%s",var),"",nbin,low,high);
   h2 = new TH1F(Form("h2%s",var),"",nbin,low,high);
   myTree->Draw(Form("%s>>h%s",var,var),cut1);
   myTree->Draw(Form("%s>>h2%s",var,var),cut2);

   h1->SetLineColor(1);
   h2->SetLineColor(2);
   h1->SetMarkerColor(1);
   h2->SetMarkerColor(2);
   h1->SetMarkerStyle(20);
   h2->SetMarkerStyle(25);
   h1->SetTitleOffset(1.5,"Y");
   h2->SetTitleOffset(1.5,"Y");
   
   h1->Sumw2();
   h2->Sumw2();
   cout <<h1->GetMean()<<" "<<h2->GetMean()<<" "<<h1->GetMean()/h2->GetMean()<<endl;
   
   if (normType==1) {
      h1->Scale(1./h1->GetEntries());
      h2->Scale(1./h2->GetEntries());
   } else if (normType==2) {
      h1->Scale(1./myTree->GetEntries());
      h2->Scale(1./myTree->GetEntries());
   }
}

compareHist::compareHist(TTree *myTree1,TTree *myTree2,char *var,char *cut1,double low,double high,int nbin,int normType)
{
   if (low==high) {
       low = myTree1->GetMinimum(var);
       if (low>myTree2->GetMinimum(var)) low = myTree2->GetMinimum(var);
       high = myTree2->GetMaximum(var);
       if (high<myTree2->GetMinimum(var)) high = myTree2->GetMinimum(var);
       cout <<low<<" "<<high<<endl;
       
   }

   h1 = new TH1F(Form("h%s",var),"",nbin,low,high);
   h2 = new TH1F(Form("h2%s",var),"",nbin,low,high);
   myTree1->Draw(Form("%s>>h%s",var,var),cut1);
   myTree2->Draw(Form("%s>>h2%s",var,var),cut1);

   h1->SetLineColor(1);
   h2->SetLineColor(2);
   h1->SetMarkerColor(1);
   h2->SetMarkerColor(2);
   h1->SetMarkerStyle(20);
   h2->SetMarkerStyle(25);
   h1->SetTitleOffset(1.5,"Y");
   h2->SetTitleOffset(1.5,"Y");
      
   h1->Sumw2();
   h2->Sumw2();
   cout <<h1->GetMean()<<" "<<h2->GetMean()<<" "<<h1->GetMean()/h2->GetMean()<<endl;
   
   if (normType==1) {
      h1->Scale(1./h1->GetEntries());
      h2->Scale(1./h2->GetEntries());
   } else if (normType==2) {
      h1->Scale(1./myTree1->GetEntries());
      h2->Scale(1./myTree2->GetEntries());
   }
}



compareHist::compareHist(TTree *myTree1,TTree *myTree2,TTree *myTree3,char *var,char *histName,char *cut1,double low,double high,int nbin,int normType)
{
   if (low==high) {
       low = myTree1->GetMinimum(var);
       if (low>myTree2->GetMinimum(var)) low = myTree2->GetMinimum(var);
       if (low>myTree3->GetMinimum(var)) low = myTree3->GetMinimum(var);
       high = myTree2->GetMaximum(var);
       if (high<myTree2->GetMinimum(var)) high = myTree2->GetMinimum(var);
       if (high<myTree3->GetMinimum(var)) high = myTree3->GetMinimum(var);
       cout <<low<<" "<<high<<endl;
       
   }

   nTree=3;
   name3="";
   h1 = new TH1F(Form("h%s",histName),"",nbin,low,high);
   h2 = new TH1F(Form("h2%s",histName),"",nbin,low,high);
   h3 = new TH1F(Form("h3%s",histName),"",nbin,low,high);
   myTree1->Draw(Form("%s>>h%s",var,histName),cut1);
   myTree2->Draw(Form("%s>>h2%s",var,histName),cut1);
   myTree3->Draw(Form("%s>>h3%s",var,histName),cut1);

   h1->SetLineColor(4);
   h2->SetLineColor(2);
   h3->SetLineColor(1);
   h1->SetMarkerColor(4);
   h2->SetMarkerColor(2);
   h3->SetMarkerColor(1);
   h1->SetMarkerStyle(24);
   h2->SetMarkerStyle(25);
   h3->SetMarkerStyle(20);
   h1->SetTitleOffset(1.5,"Y");
   h2->SetTitleOffset(1.5,"Y");
   h3->SetTitleOffset(1.5,"Y");

   
   h1->Sumw2();
   h2->Sumw2();
   h3->Sumw2();
  
   if (normType==1) {
      h1->Scale(1./h1->GetEntries());
      h2->Scale(1./h2->GetEntries());
      h3->Scale(1./h3->GetEntries());
   } else if (normType==2) {
      h1->Scale(1./myTree1->GetEntries());
      h2->Scale(1./myTree2->GetEntries());
      h3->Scale(1./myTree3->GetEntries());
   }
}


compareHist::compareHist(TTree *myTree1,TTree *myTree2,char *var,char *histName,TCut  cut1,TCut cut2,double low,double high,int nbin,int normType)
{
   nTree=2;
   h1 = new TH1F(Form("h%s",histName),"",nbin,low,high);
   h2 = new TH1F(Form("h2%s",histName),"",nbin,low,high);
   myTree1->Draw(Form("%s>>h%s",var,histName),cut1);
   myTree2->Draw(Form("%s>>h2%s",var,histName),cut2);
   
   h1->SetLineColor(4);
   h2->SetLineColor(2);
   h1->SetMarkerColor(4);
   h2->SetMarkerColor(2);
   h1->SetMarkerStyle(24);
   h2->SetMarkerStyle(25);
   h1->SetTitleOffset(1.5,"Y");
   h2->SetTitleOffset(1.5,"Y");
   h1->SetTitleOffset(1.5,"Y");
   h2->SetTitleOffset(1.5,"Y");
   

   h1->Sumw2();
   h2->Sumw2();
   
   if (normType==1) {
      h1->Scale(1./h1->GetEntries());
      h2->Scale(1./h2->GetEntries());
   } else if (normType==2) {
      h1->Scale(1./myTree1->GetEntries());
      h2->Scale(1./myTree2->GetEntries());
   }
}


compareHist::compareHist(TTree *myTree1,TTree *myTree2,TTree *myTree3,char *var,char *histName,TCut cut1,TCut cut2,TCut cut3,double low,double high,int nbin,int normType)
{
   if (low==high) {
      low = myTree1->GetMinimum(var);
      if (low>myTree2->GetMinimum(var)) low = myTree2->GetMinimum(var);
      if (low>myTree3->GetMinimum(var)) low = myTree3->GetMinimum(var);
      high = myTree2->GetMaximum(var);
      if (high<myTree2->GetMinimum(var)) high = myTree2->GetMinimum(var);
      if (high<myTree3->GetMinimum(var)) high = myTree3->GetMinimum(var);
      cout <<low<<" "<<high<<endl;

   }

   nTree=3;
   h1 = new TH1F(Form("h%s",histName),"",nbin,low,high);
   h2 = new TH1F(Form("h2%s",histName),"",nbin,low,high);
   h3 = new TH1F(Form("h3%s",histName),"",nbin,low,high);
   myTree1->Draw(Form("%s>>h%s",var,histName),cut1);
   myTree2->Draw(Form("%s>>h2%s",var,histName),cut2);
   myTree3->Draw(Form("%s>>h3%s",var,histName),cut3);

   h1->SetLineColor(4);
   h2->SetLineColor(2);
   h3->SetLineColor(1);
   h1->SetMarkerColor(4);
   h2->SetMarkerColor(2);
   h3->SetMarkerColor(1);
   h1->SetMarkerStyle(24);
   h2->SetMarkerStyle(25);
   h3->SetMarkerStyle(20);
   h1->SetTitleOffset(1.5,"Y");
   h2->SetTitleOffset(1.5,"Y");
   h3->SetTitleOffset(1.5,"Y");
   h1->SetTitleOffset(1.5,"Y");
   h2->SetTitleOffset(1.5,"Y");
   h3->SetTitleOffset(1.5,"Y");


   h1->Sumw2();
   h2->Sumw2();
   h3->Sumw2();

   if (normType==1) {
      h1->Scale(1./h1->GetEntries());
      h2->Scale(1./h2->GetEntries());
      h3->Scale(1./h3->GetEntries());
   } else if (normType==2) {
      h1->Scale(1./myTree1->GetEntries());
      h2->Scale(1./myTree2->GetEntries());
      h3->Scale(1./myTree3->GetEntries());
   }
}



compareHist::compareHist(TH1 *myth1   ,TH1* myth2   ,TH1* myth3   ,char *histName,double low, double high, int rebin, int normType)
{
   if (low==high) {
      low =  myth1->GetBinContent(myth1->GetMinimumBin());
      if (low>myth1->GetBinContent(myth1->GetMinimumBin())) low = myth2->GetBinContent(myth2->GetMinimumBin());
      if (low>myth2->GetBinContent(myth2->GetMinimumBin())) low = myth3->GetBinContent(myth3->GetMinimumBin());
      low =  myth1->GetBinContent(myth1->GetMaximumBin());
      if (low>myth1->GetBinContent(myth1->GetMaximumBin())) low = myth2->GetBinContent(myth2->GetMaximumBin());
      if (low>myth2->GetBinContent(myth2->GetMaximumBin())) low = myth3->GetBinContent(myth3->GetMaximumBin());
   }
   
   nTree=3;
   h1 = (TH1F*)myth1->Clone(Form("h1%s",histName));
   h2 = (TH1F*)myth2->Clone(Form("h2%s",histName));
   h3 = (TH1F*)myth3->Clone(Form("h3%s",histName));
   h1->Rebin(rebin);
   h2->Rebin(rebin);
   h3->Rebin(rebin);

   h1->SetLineColor(4);
   h2->SetLineColor(2);
   h3->SetLineColor(1);
   h1->SetMarkerColor(4);
   h2->SetMarkerColor(2);
   h3->SetMarkerColor(1);
   h1->SetMarkerStyle(24);
   h2->SetMarkerStyle(25);
   h3->SetMarkerStyle(20);
   h1->SetTitleOffset(1.5,"Y");
   h2->SetTitleOffset(1.5,"Y");
   h3->SetTitleOffset(1.5,"Y");


   //  h1->Sumw2();
   //  h2->Sumw2();
   //  h3->Sumw2();
   
   if (normType==1) {
      h1->Scale(1./h1->GetEntries());
      h2->Scale(1./h2->GetEntries());
      h3->Scale(1./h3->GetEntries());
   } else if (normType==2) {
      //      h1->Scale(1./myTree1->GetEntries());
      //   h2->Scale(1./myTree2->GetEntries());
   }
   
}



void compareHist::init()
{
   leg1=0;
   name1="";
   name2="";
}


void compareHist::SetLegend(double x1,double y1, double x2, double y2)
{
   leg1 = new TLegend(x1,y1,x2,y2);
   leg1->SetLineStyle(1);
   leg1->SetLineWidth(1);
   leg1->SetFillStyle(0);  
   leg1->SetFillColor(0); 
   leg1->SetBorderSize(0);
   leg1->SetTextSize(0.04);
   if (name1!="")  leg1->AddEntry(h1,name1.data(),"pl");
   if (name2!="")  leg1->AddEntry(h2,name2.data(),"pl");
   if (name3!="")  leg1->AddEntry(h3,name3.data(),"pl");
}
