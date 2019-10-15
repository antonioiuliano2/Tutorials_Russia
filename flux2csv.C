void flux2csv(){
    TString neutrinoname = TString("nu_tau");
    double potperspill = 4e+13; 
    double totalpot = 2e+20; //in five years;

    //opening the file and getting the neutrino flux
    TFile * inputfile = TFile::Open("neutrinos_detector.root");
    TH1D * hnuflux = (TH1D*)inputfile->Get((TString("h")+neutrinoname).Data());

    const int nbins = hnuflux->GetNbinsX();
    double x,y;
    //opening new file for writing
    ofstream outputfile;
    outputfile.open ((neutrinoname+TString(".csv")).Data());
    outputfile << "E,counts"<<endl;

    //bin indexes start from 1   
    cout<<"Start loop on bins: "<<nbins<<endl;
    for (int ibin = 1; ibin <= nbins; ibin++){
        x = hnuflux->GetBinLowEdge(ibin) + hnuflux->GetBinWidth(ibin)/2.; //x is the center of the bin
        y = hnuflux->GetBinContent(ibin);
        y = y /potperspill * totalpot; //renormalization
        outputfile<<x<<","<<y<<endl;
    }
}
