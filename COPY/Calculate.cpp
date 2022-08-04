#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TChain.h>
#include <TRandom3.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TFile.h>
#include <TMath.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <Math/LorentzVector.h>
#include <Math/Point3D.h>
#include <TBranch.h>
#include <TTree.h>
#include <TBits.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void Calculate(){
    TFile *file = TFile::Open("ttH.root");
    TTree *sigtree;
    TTree *sigfChain;
    sigtree = (TTree *)gDirectory->Get("sigEvents");
    sigfChain = sigtree;
    TTree *bkgtree;
    TTree *bkgfChain;
    bkgtree = (TTree *)gDirectory->Get("bkgEvents");
    bkgfChain = bkgtree;

    TFile *wfile = new TFile("ttHHbb_result.root","RECREATE");
    TH1D *P_sig_HBBscore = new TH1D("P_sig_HBBscore","P_sig_HBBscore",10000,0,1);
    TH1D *P_sig_HBBscoreMD = new TH1D("P_sig_HBBscoreMD","P_sig_HBBscoreMD",10000,0,1);
    TH1D *P_bkg_HBBscore = new TH1D("P_bkg_HBBscore","P_bkg_HBBscore",10000,0,1);
    TH1D *P_bkg_HBBscoreMD = new TH1D("P_bkg_HBBscoreMD","P_bkg_HBBscoreMD",10000,0,1);
    TH1D *S_sig_HBBscore = new TH1D("S_sig_HBBscore","S_sig_HBBscore",10000,0,1);
    TH1D *S_bkg_HBBscore = new TH1D("S_bkg_HBBscore","S_bkg_HBBscore",10000,0,1);
    TH1D *S_sig_HBBscoreMD = new TH1D("S_sig_HBBscoreMD","S_sig_HBBscoreMD",10000,0,1);
    TH1D *S_bkg_HBBscoreMD = new TH1D("S_bkg_HBBscoreMD","S_bkg_HBBscoreMD",10000,0,1);

    Float_t sigHbbscore;
    Float_t sigHbbscoreMD;
    Float_t sigHbbmass;
    Float_t sigHbbmsoftdrop;
    Float_t sigHbbtau21;
    Float_t sigHbbtau32;
    Float_t sigHbbtau1;
    Float_t sigHbbtau2;
    Float_t sigHbbtau3;
    Float_t sigweight;
    sigfChain->SetBranchAddress("Hbbscore",&sigHbbscore);
    sigfChain->SetBranchAddress("HbbscoreMD",&sigHbbscoreMD);
    sigfChain->SetBranchAddress("Hbbmass",&sigHbbmass);
    sigfChain->SetBranchAddress("Hbbmsoftdrop",&sigHbbmsoftdrop);
    sigfChain->SetBranchAddress("Hbbtau21",&sigHbbtau21);
    sigfChain->SetBranchAddress("Hbbtau32",&sigHbbtau32);
    sigfChain->SetBranchAddress("Hbbtau1",&sigHbbtau1);
    sigfChain->SetBranchAddress("Hbbtau2",&sigHbbtau2);
    sigfChain->SetBranchAddress("Hbbtau3",&sigHbbtau3);
    sigfChain->SetBranchAddress("weight",&sigweight);
    Int_t sigNentries = sigfChain->GetEntries();

    for(int ii = 0 ; ii < sigNentries ; ii ++){
        sigfChain->GetEntry(ii,0);
        P_sig_HBBscore->Fill(sigHbbscore,sigweight);
        P_sig_HBBscoreMD->Fill(sigHbbscoreMD,sigweight);
    }


    Float_t bkgHbbscore;
    Float_t bkgHbbscoreMD;
    Float_t bkgHbbmass;
    Float_t bkgHbbmsoftdrop;
    Float_t bkgHbbtau21;
    Float_t bkgHbbtau32;
    Float_t bkgHbbtau1;
    Float_t bkgHbbtau2;
    Float_t bkgHbbtau3;
    Float_t bkgweight;
    bkgfChain->SetBranchAddress("Hbbscore",&bkgHbbscore);
    bkgfChain->SetBranchAddress("HbbscoreMD",&bkgHbbscoreMD);
    bkgfChain->SetBranchAddress("Hbbmass",&bkgHbbmass);
    bkgfChain->SetBranchAddress("Hbbmsoftdrop",&bkgHbbmsoftdrop);
    bkgfChain->SetBranchAddress("Hbbtau21",&bkgHbbtau21);
    bkgfChain->SetBranchAddress("Hbbtau32",&bkgHbbtau32);
    bkgfChain->SetBranchAddress("Hbbtau1",&bkgHbbtau1);
    bkgfChain->SetBranchAddress("Hbbtau2",&bkgHbbtau2);
    bkgfChain->SetBranchAddress("Hbbtau3",&bkgHbbtau3);
    bkgfChain->SetBranchAddress("weight",&bkgweight);
    Int_t bkgNentries = bkgfChain->GetEntries();

    for(int ii = 0 ; ii < bkgNentries ; ii ++){
        bkgfChain->GetEntry(ii,0);
        P_bkg_HBBscore->Fill(bkgHbbscore,bkgweight);
        P_bkg_HBBscoreMD->Fill(bkgHbbscoreMD,bkgweight);
    }

    for(int ii = 0 ; ii < 10000 ; ii ++){
        S_sig_HBBscore->SetBinContent(ii+1,P_sig_HBBscore->Integral(ii+1,10000));
        S_bkg_HBBscore->SetBinContent(ii+1,P_bkg_HBBscore->Integral(ii+1,10000));
        S_sig_HBBscoreMD->SetBinContent(ii+1,P_sig_HBBscoreMD->Integral(ii+1,10000));
        S_bkg_HBBscoreMD->SetBinContent(ii+1,P_bkg_HBBscoreMD->Integral(ii+1,10000));
        S_sig_HBBscore->SetBinError(ii+1,0);
        S_bkg_HBBscore->SetBinError(ii+1,0);
        S_sig_HBBscoreMD->SetBinError(ii+1,0);
        S_bkg_HBBscoreMD->SetBinError(ii+1,0);
    }

    S_sig_HBBscore->Scale(1/S_sig_HBBscore->GetBinContent(1));
    S_bkg_HBBscore->Scale(1/S_bkg_HBBscore->GetBinContent(1));
    S_sig_HBBscoreMD->Scale(1/S_sig_HBBscoreMD->GetBinContent(1));
    S_bkg_HBBscoreMD->Scale(1/S_bkg_HBBscoreMD->GetBinContent(1));

    wfile->cd();
    wfile->Write();
    wfile->Close();



}
