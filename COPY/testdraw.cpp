#include "Graph1D.h"
#include "Plot1D.h"
#include "Plot2D.h"

void testdraw(){
    Plot1D P_ST("ST","Number of Events",5);
    P_ST.SetInputName("tt1lBDTresults.root","P_tt1l_train_trans_E","tt1l",0);
    P_ST.SetInputName("tt2lBDTresults.root","P_tt2l_train_trans_E","tt2l",1);
    P_ST.SetInputName("ttXBDTresults.root","P_ttX_train_trans_E","ttX",2);
    P_ST.SetInputName("WJetBDTresults.root","P_WJet_train_trans_E","WJet",3);
    P_ST.SetInputName("ttbbBDTresults.root","P_ttbb_train_trans_E","ttbb",4);
//    P_ST.SetRebin(10);
    P_ST.SetXRange(1500,2000);
    P_ST.DrawFigure();




}
