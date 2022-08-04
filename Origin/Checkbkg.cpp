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
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
using namespace std;

void Checkbkg(){

    TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent");

    Float_t  Hbbscore;
    Float_t  Hbbmass;
    Float_t  Hbbmsoftdrop;
    Float_t  Hbbtau21;
    Float_t  Hbbtau32;
    Float_t  Hbbtau1;
    Float_t  Hbbtau2;
    Float_t  Hbbtau3;
    Float_t  HbbPt;

    Float_t  Wjetscore;
    Float_t  Wjetmass;
    Float_t  Wjetmsoftdrop;
    Float_t  Wjettau21;
    Float_t  Wjettau32;
    Float_t  Wjettau1;
    Float_t  Wjettau2;
    Float_t  Wjettau3;
    Float_t  WjetPt;

    Float_t  leptonpt;
    Float_t  VBSMjj;
    Float_t  VBSdetajj;
    Float_t  VBSdphijj;
    Float_t  VBSPtjj;
    Float_t  trans_E;
    Float_t  MET;
    Float_t  weight;

    reader->AddVariable("Hbbscore",&Hbbscore);
    reader->AddVariable("Hbbmass",&Hbbmass);
//    reader->AddVariable("Hbbmsoftdrop",&Hbbmsoftdrop);
//    reader->AddVariable("Hbbtau21",&Hbbtau21);
//    reader->AddVariable("Hbbtau32",&Hbbtau32);
//    reader->AddVariable("Hbbtau1",&Hbbtau1);
//    reader->AddVariable("Hbbtau2",&Hbbtau2);
//    reader->AddVariable("Hbbtau3",&Hbbtau3);
//    reader->AddVariable("HbbPt",&HbbPt);

    reader->AddVariable("Wjetscore",&Wjetscore);
    reader->AddVariable("Wjetmass",&Wjetmass);
//    reader->AddVariable("Wjetmsoftdrop",&Wjetmsoftdrop);
//    reader->AddVariable("Wjettau21",&Wjettau21);
//    reader->AddVariable("Wjettau32",&Wjettau32);
//    reader->AddVariable("Wjettau1",&Wjettau1);
    reader->AddVariable("Wjettau2",&Wjettau2);
//    reader->AddVariable("Wjettau3",&Wjettau3);
//    reader->AddVariable("WjetPt",&WjetPt);

//    reader->AddVariable("leptonpt",&leptonpt);
//    reader->AddVariable("VBSMjj",&VBSMjj);
//    reader->AddVariable("VBSdetajj",&VBSdetajj);
//    reader->AddVariable("VBSdphijj",&VBSdphijj);
//    reader->AddVariable("VBSPtjj",&VBSPtjj);
    reader->AddVariable("trans_E",&trans_E);
//    reader->AddVariable("MET",&MET);

    reader->BookMVA("BDT","./dataset/weights/TMVAClassification_BDT.weights.xml");

    Double_t mvaValue = reader->EvaluateMVA("BDT");

    TFile *filebkg = TFile::Open("bkg.root");
    TTree *bkgtrainfChain = (TTree *)filebkg->Get("trainEvents");
    TTree *bkgtraintree;
    bkgtraintree = bkgtrainfChain;

    TTree *bkgtestfChain = (TTree *)filebkg->Get("testEvents");
    TTree *bkgtesttree;
    bkgtesttree = bkgtestfChain;

    TFile *writefile = new TFile("bkgBDTresults.root","RECREATE");
    TH1D *P_bkg_train_BDT = new TH1D("P_bkg_train_BDT","P_bkg_train_BDT",1000,0,1);
    TH1D *P_bkg_test_BDT = new TH1D("P_bkg_test_BDT","P_bkg_test_BDT",1000,0,1);
    TH1D *S_bkg_train_BDT = new TH1D("S_bkg_train_BDT","S_bkg_train_BDT",1000,0,1);
    TH1D *S_bkg_test_BDT = new TH1D("S_bkg_test_BDT","S_bkg_test_BDT",1000,0,1);

    TH1D *P_bkg_train_middle_trans_E = new TH1D("P_bkg_train_middle_trans_E","P_bkg_train_middle_trans_E",1000,0,10000);
    TH1D *P_bkg_train_side_trans_E = new TH1D("P_bkg_train_side_trans_E","P_bkg_train_side_trans_E",1000,0,10000);
    TH1D *P_bkg_test_middle_trans_E = new TH1D("P_bkg_test_middle_trans_E","P_bkg_test_middle_trans_E",1000,0,10000);
    TH1D *P_bkg_test_side_trans_E = new TH1D("P_bkg_test_side_trans_E","P_bkg_test_side_trans_E",1000,0,10000);
    TH2D *P_bkg_train_trans_E_BDT = new TH2D("P_bkg_train_trans_E_BDT","P_bkg_train_trans_E_BDT",40,1000,3000,60,0.4,1.0);
    TH2D *P_bkg_test_trans_E_BDT = new TH2D("P_bkg_test_trans_E_BDT","P_bkg_test_trans_E_BDT",40,1000,3000,60,0.4,1.0);

    P_bkg_train_BDT->Sumw2();
    P_bkg_test_BDT->Sumw2();
    S_bkg_train_BDT->Sumw2();
    S_bkg_test_BDT->Sumw2();

    P_bkg_train_middle_trans_E->Sumw2();
    P_bkg_train_side_trans_E->Sumw2();
    P_bkg_test_middle_trans_E->Sumw2();
    P_bkg_test_side_trans_E->Sumw2();
    P_bkg_train_trans_E_BDT->Sumw2();
    P_bkg_test_trans_E_BDT->Sumw2();


    bkgtraintree->SetBranchAddress("Hbbscore",&Hbbscore);
    bkgtraintree->SetBranchAddress("Hbbmass",&Hbbmass);
    bkgtraintree->SetBranchAddress("Hbbmsoftdrop",&Hbbmsoftdrop);
    bkgtraintree->SetBranchAddress("Hbbtau21",&Hbbtau21);
    bkgtraintree->SetBranchAddress("Hbbtau32",&Hbbtau32);
    bkgtraintree->SetBranchAddress("Hbbtau1",&Hbbtau1);
    bkgtraintree->SetBranchAddress("Hbbtau2",&Hbbtau2);
    bkgtraintree->SetBranchAddress("Hbbtau3",&Hbbtau3);
    bkgtraintree->SetBranchAddress("HbbPt",&HbbPt);
    bkgtraintree->SetBranchAddress("Wjetscore",&Wjetscore);
    bkgtraintree->SetBranchAddress("Wjetmass",&Wjetmass);
    bkgtraintree->SetBranchAddress("Wjetmsoftdrop",&Wjetmsoftdrop);
    bkgtraintree->SetBranchAddress("Wjettau21",&Wjettau21);
    bkgtraintree->SetBranchAddress("Wjettau32",&Wjettau32);
    bkgtraintree->SetBranchAddress("Wjettau1",&Wjettau1);
    bkgtraintree->SetBranchAddress("Wjettau2",&Wjettau2);
    bkgtraintree->SetBranchAddress("Wjettau3",&Wjettau3);
    bkgtraintree->SetBranchAddress("WjetPt",&WjetPt);
    bkgtraintree->SetBranchAddress("leptonpt",&leptonpt);
    bkgtraintree->SetBranchAddress("VBSMjj",&VBSMjj);
    bkgtraintree->SetBranchAddress("trans_E",&trans_E);
    bkgtraintree->SetBranchAddress("MET",&MET);
    bkgtraintree->SetBranchAddress("weight",&weight);

    bkgtesttree->SetBranchAddress("Hbbscore",&Hbbscore);
    bkgtesttree->SetBranchAddress("Hbbmass",&Hbbmass);
    bkgtesttree->SetBranchAddress("Hbbmsoftdrop",&Hbbmsoftdrop);
    bkgtesttree->SetBranchAddress("Hbbtau21",&Hbbtau21);
    bkgtesttree->SetBranchAddress("Hbbtau32",&Hbbtau32);
    bkgtesttree->SetBranchAddress("Hbbtau1",&Hbbtau1);
    bkgtesttree->SetBranchAddress("Hbbtau2",&Hbbtau2);
    bkgtesttree->SetBranchAddress("Hbbtau3",&Hbbtau3);
    bkgtesttree->SetBranchAddress("HbbPt",&HbbPt);
    bkgtesttree->SetBranchAddress("Wjetscore",&Wjetscore);
    bkgtesttree->SetBranchAddress("Wjetmass",&Wjetmass);
    bkgtesttree->SetBranchAddress("Wjetmsoftdrop",&Wjetmsoftdrop);
    bkgtesttree->SetBranchAddress("Wjettau21",&Wjettau21);
    bkgtesttree->SetBranchAddress("Wjettau32",&Wjettau32);
    bkgtesttree->SetBranchAddress("Wjettau1",&Wjettau1);
    bkgtesttree->SetBranchAddress("Wjettau2",&Wjettau2);
    bkgtesttree->SetBranchAddress("Wjettau3",&Wjettau3);
    bkgtesttree->SetBranchAddress("WjetPt",&WjetPt);
    bkgtesttree->SetBranchAddress("leptonpt",&leptonpt);
    bkgtesttree->SetBranchAddress("VBSMjj",&VBSMjj);
    bkgtesttree->SetBranchAddress("trans_E",&trans_E);
    bkgtesttree->SetBranchAddress("MET",&MET);
    bkgtesttree->SetBranchAddress("weight",&weight);

    double WNA_initial = 0; //Weighted Number All
    double WNA_passBDT = 0;
    double WNA_passBF = 0;
    double WNA_passboth = 0;

    double WEA_initial = 0; //Weighted Error All
    double WEA_passBDT = 0;
    double WEA_passBF = 0;
    double WEA_passboth = 0;

    double WNR_initial = 0; //Weighted Number Training
    double WNR_passBDT = 0;
    double WNR_passBF = 0;
    double WNR_passboth = 0;

    double WER_initial = 0; //Weighted Error Training
    double WER_passBDT = 0;
    double WER_passBF = 0;
    double WER_passboth = 0;

    double WNE_initial = 0; //Weighted Number Testing
    double WNE_passBDT = 0;
    double WNE_passBF = 0;
    double WNE_passboth = 0;

    double WEE_initial = 0; //Weighted Error Testing
    double WEE_passBDT = 0;
    double WEE_passBF = 0;
    double WEE_passboth = 0;

    int bkgNentries ;
    bool passBF;
    bool passBDT;
    bkgNentries = bkgtraintree->GetEntries();
    for(int ii  = 0 ; ii < bkgNentries ; ii ++){
        bkgtraintree->GetEntry(ii,0);
        if(trans_E > 4000) continue;
        if(trans_E < 1000) continue;
//        if(Hbbscore < 0.98) continue;
        WNA_initial += weight;
        WEA_initial += weight*weight;
        WNR_initial += weight;
        WER_initial += weight*weight;
        Double_t mvaValue = reader->EvaluateMVA("BDT");
        if(mvaValue > 0.6){
            passBDT = true;
        }else passBDT = false;
        if(trans_E > 1900 && Hbbscore > 0.985) passBF = true;
        else if(trans_E > 1400 && Hbbscore > 0.98 && Wjettau2 < 0.12 && Wjetscore > 0.96) passBF = true;
        else passBF = false;
        if(passBDT){
            WNA_passBDT += weight;
            WEA_passBDT += weight * weight;
            WNR_passBDT += weight;
            WER_passBDT += weight * weight;
        }
        if(passBF){
            WNA_passBF += weight;
            WEA_passBF += weight * weight;
            WNR_passBF += weight;
            WER_passBF += weight * weight;
        }
        if(passBDT && passBF){
            WNA_passboth += weight;
            WEA_passboth += weight * weight;
            WNR_passboth += weight;
            WER_passboth += weight * weight;
        }
        if(mvaValue > 0.54 && mvaValue < 0.56){
            P_bkg_train_middle_trans_E->Fill(trans_E,weight);
        }else{
            P_bkg_train_side_trans_E->Fill(trans_E,weight);
        }
        P_bkg_train_trans_E_BDT->Fill(trans_E,mvaValue,weight);
        P_bkg_train_BDT->Fill(mvaValue,weight);
    }

    bkgNentries = bkgtesttree->GetEntries();
    double totaltest = 0;
    for(int ii  = 0 ; ii < bkgNentries ; ii ++){
        bkgtesttree->GetEntry(ii,0);
        if(trans_E > 4000) continue;
        if(trans_E < 1000) continue;
        WNA_initial += weight;
        WEA_initial += weight*weight;
        WNE_initial += weight;
        WEE_initial += weight*weight;
        Double_t mvaValue = reader->EvaluateMVA("BDT");
        if(mvaValue > 0.6){
            passBDT = true;
        }else passBDT = false;
        if(trans_E > 1900 && Hbbscore > 0.985) passBF = true;
        else if(trans_E > 1400 && Hbbscore > 0.98 && Wjettau2 < 0.12 && Wjetscore > 0.96) passBF = true;
        else passBF = false;
        if(passBDT){
            WNA_passBDT += weight;
            WEA_passBDT += weight * weight;
            WNE_passBDT += weight;
            WEE_passBDT += weight * weight;
        }
        if(passBF){
            WNA_passBF += weight;
            WEA_passBF += weight * weight;
            WNE_passBF += weight;
            WEE_passBF += weight * weight;
        }
        if(passBDT && passBF){
            WNA_passboth += weight;
            WEA_passboth += weight * weight;
            WNE_passboth += weight;
            WEE_passboth += weight * weight;
        }

        if(mvaValue>0.54 && mvaValue < 0.56){
            P_bkg_test_middle_trans_E->Fill(trans_E,weight);
        }else{
            P_bkg_test_side_trans_E->Fill(trans_E,weight);
        }
        P_bkg_test_trans_E_BDT->Fill(trans_E,mvaValue,weight);
        P_bkg_test_BDT->Fill(mvaValue,weight);
    }
    cout<<"initial  events : "<<WNA_initial<<" +- "<<sqrt(WEA_initial)<<endl;
    cout<<"passing BDT     : "<<WNA_passBDT<<" +- "<<sqrt(WEA_passBDT)<<endl;
    cout<<"passing BF      : "<<WNA_passBF<<" +- "<<sqrt(WEA_passBF)<<endl;
    cout<<"passing both    : "<<WNA_passboth<<" +- "<<sqrt(WEA_passboth)<<endl;
    cout<<"training events : "<<WNR_initial<<" +- "<<sqrt(WER_initial)<<endl;
    cout<<"passing BDT     : "<<WNR_passBDT<<" +- "<<sqrt(WER_passBDT)<<endl;
    cout<<"passing BF      : "<<WNR_passBF<<" +- "<<sqrt(WER_passBF)<<endl;
    cout<<"passing both    : "<<WNR_passboth<<" +- "<<sqrt(WER_passboth)<<endl;
    cout<<"testing  events : "<<WNE_initial<<" +- "<<sqrt(WEE_initial)<<endl;
    cout<<"passing BDT     : "<<WNE_passBDT<<" +- "<<sqrt(WEE_passBDT)<<endl;
    cout<<"passing BF      : "<<WNE_passBF<<" +- "<<sqrt(WEE_passBF)<<endl;
    cout<<"passing both    : "<<WNE_passboth<<" +- "<<sqrt(WEE_passboth)<<endl;

    for(int ii = 0 ; ii < 1000 ; ii++){
        double totalweight = 0 ; 
        double totalerror = 0;
        for (int jj = ii ; jj < 1000 ; jj ++){
            totalweight += P_bkg_test_BDT->GetBinContent(jj+1);
            totalerror += P_bkg_test_BDT->GetBinError(jj+1) * P_bkg_test_BDT->GetBinError(jj+1);
        }
        totalerror = sqrt(totalerror);
        S_bkg_test_BDT->SetBinContent(ii+1,totalweight);
        S_bkg_test_BDT->SetBinError(ii+1,totalerror);
    }
    for(int ii = 0 ; ii < 1000 ; ii++){
        double totalweight = 0 ;
        double totalerror = 0;
        for (int jj = ii ; jj < 1000 ; jj ++){
            totalweight += P_bkg_train_BDT->GetBinContent(jj+1);
            totalerror += P_bkg_train_BDT->GetBinError(jj+1) * P_bkg_train_BDT->GetBinError(jj+1);
        }
        totalerror = sqrt(totalerror);
        S_bkg_train_BDT->SetBinContent(ii+1,totalweight);
        S_bkg_train_BDT->SetBinError(ii+1,totalerror);
    }
    TH1D *E_bkg_train_BDT = (TH1D *)S_bkg_train_BDT->Clone("E_bkg_train_BDT");
    TH1D *E_bkg_test_BDT = (TH1D *)S_bkg_test_BDT->Clone("E_bkg_test_BDT");

    E_bkg_train_BDT->Scale(1/S_bkg_train_BDT->GetBinContent(1));
    E_bkg_test_BDT->Scale(1/S_bkg_test_BDT->GetBinContent(1));


    writefile->cd();
    writefile->Write();
    writefile->Close();
}
