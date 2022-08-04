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

void Readttbb(){

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
//    reader->AddVariable("Wjetmass",&Wjetmass);
//    reader->AddVariable("Wjetmsoftdrop",&Wjetmsoftdrop);
//    reader->AddVariable("Wjettau21",&Wjettau21);
//    reader->AddVariable("Wjettau32",&Wjettau32);
//    reader->AddVariable("Wjettau1",&Wjettau1);
    reader->AddVariable("Zjettau2",&Wjettau2);
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

    TFile *filettbb = TFile::Open("ttbb.root");
    TTree *ttbbtrainfChain = (TTree *)filettbb->Get("trainEvents");
    TTree *ttbbtraintree;
    ttbbtraintree = ttbbtrainfChain;

    TTree *ttbbtestfChain = (TTree *)filettbb->Get("testEvents");
    TTree *ttbbtesttree;
    ttbbtesttree = ttbbtestfChain;

    TFile *writefile = new TFile("ttbbBDTresults.root","RECREATE");
    TH1D *P_ttbb_train_BDT = new TH1D("P_ttbb_train_BDT","P_ttbb_train_BDT",1000,0,1);
    TH1D *P_ttbb_test_BDT = new TH1D("P_ttbb_test_BDT","P_ttbb_test_BDT",1000,0,1);
    TH1D *P_ttbb_train_trans_E = new TH1D("P_ttbb_train_trans_E","P_ttbb_train_trans_E",1000,0,10000);
    TH1D *P_ttbb_test_trans_E = new TH1D("P_ttbb_test_trans_E","P_ttbb_test_trans_E",1000,0,10000);

    TH1D *P_ttbb_train_middle_trans_E = new TH1D("P_ttbb_train_middle_trans_E","P_ttbb_train_middle_trans_E",1000,0,10000);
    TH1D *P_ttbb_train_side_trans_E = new TH1D("P_ttbb_train_side_trans_E","P_ttbb_train_side_trans_E",1000,0,10000);
    TH1D *P_ttbb_test_middle_trans_E = new TH1D("P_ttbb_test_middle_trans_E","P_ttbb_test_middle_trans_E",1000,0,10000);
    TH1D *P_ttbb_test_side_trans_E = new TH1D("P_ttbb_test_side_trans_E","P_ttbb_test_side_trans_E",1000,0,10000);
    TH2D *P_ttbb_train_trans_E_BDT = new TH2D("P_ttbb_train_trans_E_BDT","P_ttbb_train_trans_E_BDT",20,1000,5000,40,0.4,0.8);
    TH2D *P_ttbb_test_trans_E_BDT = new TH2D("P_ttbb_test_trans_E_BDT","P_ttbb_test_trans_E_BDT",20,1000,5000,40,0.4,0.8);

    P_ttbb_train_BDT->Sumw2();
    P_ttbb_test_BDT->Sumw2();

    P_ttbb_test_trans_E->Sumw2();
    P_ttbb_train_trans_E->Sumw2();
    P_ttbb_train_middle_trans_E->Sumw2();
    P_ttbb_train_side_trans_E->Sumw2();
    P_ttbb_test_middle_trans_E->Sumw2();
    P_ttbb_test_side_trans_E->Sumw2();
    P_ttbb_train_trans_E_BDT->Sumw2();
    P_ttbb_test_trans_E_BDT->Sumw2();


    ttbbtraintree->SetBranchAddress("Hbbscore",&Hbbscore);
    ttbbtraintree->SetBranchAddress("Hbbmass",&Hbbmass);
    ttbbtraintree->SetBranchAddress("Hbbmsoftdrop",&Hbbmsoftdrop);
    ttbbtraintree->SetBranchAddress("Hbbtau21",&Hbbtau21);
    ttbbtraintree->SetBranchAddress("Hbbtau32",&Hbbtau32);
    ttbbtraintree->SetBranchAddress("Hbbtau1",&Hbbtau1);
    ttbbtraintree->SetBranchAddress("Hbbtau2",&Hbbtau2);
    ttbbtraintree->SetBranchAddress("Hbbtau3",&Hbbtau3);
    ttbbtraintree->SetBranchAddress("HbbPt",&HbbPt);
    ttbbtraintree->SetBranchAddress("Wjetscore",&Wjetscore);
    ttbbtraintree->SetBranchAddress("Wjetmass",&Wjetmass);
    ttbbtraintree->SetBranchAddress("Wjetmsoftdrop",&Wjetmsoftdrop);
    ttbbtraintree->SetBranchAddress("Wjettau21",&Wjettau21);
    ttbbtraintree->SetBranchAddress("Wjettau32",&Wjettau32);
    ttbbtraintree->SetBranchAddress("Wjettau1",&Wjettau1);
    ttbbtraintree->SetBranchAddress("Wjettau2",&Wjettau2);
    ttbbtraintree->SetBranchAddress("Wjettau3",&Wjettau3);
    ttbbtraintree->SetBranchAddress("WjetPt",&WjetPt);
    ttbbtraintree->SetBranchAddress("leptonpt",&leptonpt);
    ttbbtraintree->SetBranchAddress("VBSMjj",&VBSMjj);
    ttbbtraintree->SetBranchAddress("trans_E",&trans_E);
    ttbbtraintree->SetBranchAddress("MET",&MET);
    ttbbtraintree->SetBranchAddress("weight",&weight);

    ttbbtesttree->SetBranchAddress("Hbbscore",&Hbbscore);
    ttbbtesttree->SetBranchAddress("Hbbmass",&Hbbmass);
    ttbbtesttree->SetBranchAddress("Hbbmsoftdrop",&Hbbmsoftdrop);
    ttbbtesttree->SetBranchAddress("Hbbtau21",&Hbbtau21);
    ttbbtesttree->SetBranchAddress("Hbbtau32",&Hbbtau32);
    ttbbtesttree->SetBranchAddress("Hbbtau1",&Hbbtau1);
    ttbbtesttree->SetBranchAddress("Hbbtau2",&Hbbtau2);
    ttbbtesttree->SetBranchAddress("Hbbtau3",&Hbbtau3);
    ttbbtesttree->SetBranchAddress("HbbPt",&HbbPt);
    ttbbtesttree->SetBranchAddress("Wjetscore",&Wjetscore);
    ttbbtesttree->SetBranchAddress("Wjetmass",&Wjetmass);
    ttbbtesttree->SetBranchAddress("Wjetmsoftdrop",&Wjetmsoftdrop);
    ttbbtesttree->SetBranchAddress("Wjettau21",&Wjettau21);
    ttbbtesttree->SetBranchAddress("Wjettau32",&Wjettau32);
    ttbbtesttree->SetBranchAddress("Wjettau1",&Wjettau1);
    ttbbtesttree->SetBranchAddress("Wjettau2",&Wjettau2);
    ttbbtesttree->SetBranchAddress("Wjettau3",&Wjettau3);
    ttbbtesttree->SetBranchAddress("WjetPt",&WjetPt);
    ttbbtesttree->SetBranchAddress("leptonpt",&leptonpt);
    ttbbtesttree->SetBranchAddress("VBSMjj",&VBSMjj);
    ttbbtesttree->SetBranchAddress("trans_E",&trans_E);
    ttbbtesttree->SetBranchAddress("MET",&MET);
    ttbbtesttree->SetBranchAddress("weight",&weight);

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

    int ttbbNentries ;
    bool passBF;
    bool passBDT;
    ttbbNentries = ttbbtraintree->GetEntries();
    for(int ii  = 0 ; ii < ttbbNentries ; ii ++){
        ttbbtraintree->GetEntry(ii,0);
        WNA_initial += weight;
        WEA_initial += weight*weight;
        WNR_initial += weight;
        WER_initial += weight*weight;
        Double_t mvaValue = reader->EvaluateMVA("BDT");
        if(mvaValue > 0.569733){
            passBDT = true;
        }else passBDT = false;
        if(trans_E > 1700 && Hbbscore > 0.98) passBF = true;
        else if(trans_E > 1200 && Hbbscore > 0.96 && Hbbmass < 150 && Wjetscore > 0.96 && Wjettau2 < 0.1) passBF = true;
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
        P_ttbb_train_trans_E->Fill(trans_E,weight);
        if(mvaValue > 0.54 && mvaValue < 0.56){
            P_ttbb_train_middle_trans_E->Fill(trans_E,weight);
        }else{
            P_ttbb_train_side_trans_E->Fill(trans_E,weight);
        }
        P_ttbb_train_trans_E_BDT->Fill(trans_E,mvaValue,weight);
        P_ttbb_train_BDT->Fill(mvaValue,weight);
    }

    ttbbNentries = ttbbtesttree->GetEntries();
    double totaltest = 0;
    for(int ii  = 0 ; ii < ttbbNentries ; ii ++){
        ttbbtesttree->GetEntry(ii,0);
        WNA_initial += weight;
        WEA_initial += weight*weight;
        WNE_initial += weight;
        WEE_initial += weight*weight;
//        if(trans_E > 2000) continue;
        Double_t mvaValue = reader->EvaluateMVA("BDT");
        if(mvaValue > 0.569733){
            passBDT = true;
        }else passBDT = false;
        if(trans_E > 1700 && Hbbscore > 0.98) passBF = true;
        else if(trans_E > 1200 && Hbbscore > 0.96 && Hbbmass < 150 && Wjetscore > 0.96 && Wjettau2 < 0.1) passBF = true;
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

        P_ttbb_test_trans_E->Fill(trans_E,weight);
        if(mvaValue>0.54 && mvaValue < 0.56){
            P_ttbb_test_middle_trans_E->Fill(trans_E,weight);
        }else{
            P_ttbb_test_side_trans_E->Fill(trans_E,weight);
        }
        P_ttbb_test_trans_E_BDT->Fill(trans_E,mvaValue,weight);
        P_ttbb_test_BDT->Fill(mvaValue,weight);
    }
    cout<<"initial  events : "<<WNA_initial<<" +- "<<WEA_initial<<endl;
    cout<<"passing BDT     : "<<WNA_passBDT<<" +- "<<WEA_passBDT<<endl;
    cout<<"passing BF      : "<<WNA_passBF<<" +- "<<WEA_passBF<<endl;
    cout<<"passing both    : "<<WNA_passboth<<" +- "<<WEA_passboth<<endl;
    cout<<"training events : "<<WNR_initial<<" +- "<<WER_initial<<endl;
    cout<<"passing BDT     : "<<WNR_passBDT<<" +- "<<WER_passBDT<<endl;
    cout<<"passing BF      : "<<WNR_passBF<<" +- "<<WER_passBF<<endl;
    cout<<"passing both    : "<<WNR_passboth<<" +- "<<WER_passboth<<endl;
    cout<<"testing  events : "<<WNE_initial<<" +- "<<WEE_initial<<endl;
    cout<<"passing BDT     : "<<WNE_passBDT<<" +- "<<WEE_passBDT<<endl;
    cout<<"passing BF      : "<<WNE_passBF<<" +- "<<WEE_passBF<<endl;
    cout<<"passing both    : "<<WNE_passboth<<" +- "<<WEE_passboth<<endl;

    writefile->cd();
    writefile->Write();
    writefile->Close();
}
