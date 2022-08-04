#include "Graph1D.h"
#include "Plot1D.h"
#include "Plot2D.h"

void draw(){
    Plot1D P_MVAResult("BDT score","Number of Events",2);
    P_MVAResult.SetInputName("TMVA_read.root","P_MVA_BDT_cutS","Signal",0);
    P_MVAResult.SetInputName("TMVA_read.root","P_MVA_BDT_cutB","Backgr",1);
    P_MVAResult.AddLsig();
    P_MVAResult.AddpadRange(0,25);
    P_MVAResult.SetSave("PlotResult/BDTResult");
    P_MVAResult.DrawFigure();

    Plot1D P_MVADis("BDT score","Number of Events",2);
    P_MVADis.SetInputName("TMVA_read.root","P_MVA_BDT_S_scale","Signal",0);
    P_MVADis.SetInputName("TMVA_read.root","P_MVA_BDT_B_scale","Backgr",1);
    P_MVADis.SetSave("PlotResult/BDTResult_Dis");
    P_MVADis.SetRebin(2);
    P_MVADis.SetXRange(0.2,0.8);
    P_MVADis.DrawFigure();

    Plot2D P_sig_train_trans_E_BDT("ST","BDT");
    P_sig_train_trans_E_BDT.SetInputName("sigBDTresults.root","P_sig_train_trans_E_BDT");
    P_sig_train_trans_E_BDT.SetZRange(0,0.1);
    P_sig_train_trans_E_BDT.SetSave("PlotResult/2DBDTVSST_train");
    P_sig_train_trans_E_BDT.DrawFigure();

    Plot2D P_sig_test_trans_E_BDT("ST","BDT");
    P_sig_test_trans_E_BDT.SetInputName("sigBDTresults.root","P_sig_test_trans_E_BDT");
    P_sig_test_trans_E_BDT.SetZRange(0,0.1);
    P_sig_test_trans_E_BDT.SetSave("PlotResult/2DBDTVSST_test");
    P_sig_test_trans_E_BDT.DrawFigure();

    Plot1D P_BDT_test("BDT","Number of Events",2);
    P_BDT_test.SetInputName("sigBDTresults.root","P_sig_test_BDT","Signal",0);
    P_BDT_test.SetInputName("bkgBDTresults.root","P_bkg_test_BDT","Backgr",1);
    P_BDT_test.SetXRange(0.3,0.9);
    P_BDT_test.SetRebin(10);
    P_BDT_test.SetSave("PlotResult/BDTCompare");
    P_BDT_test.DrawFigure();

    Graph1D G_BDT_overtraining("passing signal efficiency","passing bkg efficiency",2);
    G_BDT_overtraining.SetInputNamex("sigBDTresults.root","E_sig_train_BDT","train",0);
    G_BDT_overtraining.SetInputNamey("bkgBDTresults.root","E_bkg_train_BDT","train",0);
    G_BDT_overtraining.SetInputNamex("sigBDTresults.root","E_sig_test_BDT","test",1);
    G_BDT_overtraining.SetInputNamey("bkgBDTresults.root","E_bkg_test_BDT","test",1);
    G_BDT_overtraining.SetXRange(0.8,1);
    G_BDT_overtraining.SetYRange(0,1);
    G_BDT_overtraining.SetSave("PlotResult/G_BDTresult");
    G_BDT_overtraining.DrawFigure();

}
