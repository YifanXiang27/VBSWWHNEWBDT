#include "Graph1D.h"
#include "Plot1D.h"
#include "Plot2D.h"

void draw_test(){
    Plot1D P_MVAResult("BDT score","Number of Events",2);
    P_MVAResult.SetInputName("TMVA_read.root","P_MVA_BDT_cutS","Signal",0);
    P_MVAResult.SetInputName("TMVA_read.root","P_MVA_BDT_cutB","Backgr",1);
    P_MVAResult.AddLsig();
    P_MVAResult.AddpadRange(0,25);
    P_MVAResult.SetSave("PlotResult/BDTResult");
    P_MVAResult.DrawFigure();
}
