#include "BDXDSTSelector.h"
#include "BDXDSTSelector1.h"
#include "TTree.h"
#include "TFile.h"
#include <TStyle.h>
#include <TLine.h>
#include <iostream>
#include <string>
#include <vector>
#include "TMath.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TProof.h"
#include "TF1.h"
#include <TGraphErrors.h>
/*
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooLandau.h"
#include "RooNumConvPdf.h"
#include "RooAddPdf.h"
#include "RooAbsPdf.h"
#include "RooFFTConvPdf.h"
#include "RooPolynomial.h"
#include "RooExponential.h"
#include "RooArgusBG.h"
#include "RooGenericPdf.h"
 */
using namespace std;
//using namespace RooFit;

int isMC;
int nproof;
int Ntot;
int N0;

bool showGUI;

string ofname, fname;
vector<string> fnames;


double langau(double *x, double *par) {

	//Fit parameters:
	   //par[0]=Width (scale) parameter of Landau density
	   //par[1]=Most Probable (MP, location) parameter of Landau density
	   //par[2]=Total area (integral -inf to inf, normalization constant)
	   //par[3]=Width (sigma) of convoluted Gaussian function
	   //
	   //In the Landau distribution (represented by the CERNLIB approximation),
	   //the maximum is located at x=-0.22278298 with the location parameter=0.
	   //This shift is corrected within this function, so that the actual
	   //maximum is identical to the MP parameter.

	      // Numeric constants
	      Double_t invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)
	      Double_t mpshift  = -0.22278298;       // Landau maximum location

	      // Control constants
	      Double_t np = 1000.0;      // number of convolution steps
	      Double_t sc =   5.0;      // convolution extends to +-sc Gaussian sigmas

	      // Variables
	      Double_t xx;
	      Double_t mpc;
	      Double_t fland;
	      Double_t sum = 0.0;
	      Double_t xlow,xupp;
	      Double_t step;
	      Double_t i;

	      // MP shift correction
	      mpc = par[1] - mpshift * par[0];

	      // Range of convolution integral
	      xlow = x[0] - sc * par[3];
	      xupp = x[0] + sc * par[3];

	      step = (xupp-xlow) / np;

	      // Convolution integral of Landau and Gaussian by sum
	      for(i=1.0; i<=np/2; i++) {
	         xx = xlow + (i-.5) * step;
	         fland = TMath::Landau(xx,mpc,par[0]) / par[0];
	         sum += fland * TMath::Gaus(x[0],xx,par[3]);

	         xx = xupp - (i-.5) * step;
	         fland = TMath::Landau(xx,mpc,par[0]) / par[0];
	         sum += fland * TMath::Gaus(x[0],xx,par[3]);
	      }

	      return (par[2]*step*sum*invsq2pi / par[3]);
}

void parseCommandLine(int argc, char **argv) {
	isMC = 0;
	nproof = 0;
	Ntot = 0;
	N0 = 0;
	ofname = "";

	showGUI = false;

	for (int ii = 0; ii < argc; ii++) {
		string command = string(argv[ii]);
		if (command == "-f") {
			int jj = ii + 1;
			for (int jj = ii + 1; jj < argc; jj++) {
				fname = string(argv[jj]);
				if (fname[0] == '-') break;
				cout << "fname is: " << fname << endl;
				fnames.push_back(fname);
			}
		}
		if (command == "-o") {
			ofname = string(argv[ii + 1]);
			cout << "out fname is: " << ofname << endl;
		} else if (command == "-MC") {
			isMC = 1;
		} else if (command == "-nproof") {
			nproof = atoi(argv[ii + 1]);
		} else if (command == "-Ntot") {
			Ntot = atoi(argv[ii + 1]);
		} else if (command == "-GUI") showGUI = true;
		
	}
}

int main(int argc, char **argv) {

	TApplication gui("GUI", 0, NULL);
	parseCommandLine(argc, argv);

	if (isMC) {
		Info("main", "MC-mode");
	}

	int doFit = 0;

	string opt = "";
	string opt2 ="";

	if (isMC){
		opt = "MC";
	    opt2 = fname;
	}

	cout << "******"<<endl;
	cout << "******"<<endl;
	cout << "******"<<endl;
	cout << "******"<<endl;
	cout << "******"<<endl;
	cout << "******"<<endl;

	cout<< opt<<endl;
	

	BDXDSTSelector *myBDXDSTSelector = new BDXDSTSelector();
	BDXDSTSelector1 *myBDXDSTSelector1 = new BDXDSTSelector1();

	TChain *runInfo = new TChain("RunInfo");
	TChain *DSTChain = new TChain("EventDST");

	for (int jj = 0; jj < fnames.size(); jj++) {
		DSTChain->Add(fnames[jj].c_str());
		runInfo->Add(fnames[jj].c_str());
	}

	int N = DSTChain->GetEntries();
	if (Ntot <= 0) Ntot = N;
	cout << "Before process: N is " << N << endl;
	myBDXDSTSelector->setN0(N);
	myBDXDSTSelector1->setN0(N);
	/*Determine total run time*/
	double Ttot, Ttot2;
	int Tfirst, Tlast;
	int runN, dT;
	runInfo->SetBranchAddress("runN", &runN);
	runInfo->SetBranchAddress("dT", &dT);

	Ttot = 0;
	for (int irun = 0; irun < runInfo->GetEntries(); irun++) {
		runInfo->GetEntry(irun);
		printf("Run %i: %i\n", runN, dT);
		Ttot += dT;
	}

	/*Determine first event time*/
	cout << "Determine first/last event time " << endl;
	TEvent *event_tmp = 0;
	DSTChain->SetBranchAddress("Event", &event_tmp);
	DSTChain->GetEntry(N0);
	Tfirst = event_tmp->getEventHeader()->getEventTime();

	/*Determine last event time*/
	DSTChain->GetEntry(Ntot - 1);
	Tlast = event_tmp->getEventHeader()->getEventTime();

	cout << "From data: first event time is: " << Tfirst << " last event time is: " << Tlast << endl;
	Ttot = Tlast - Tfirst;
	cout << "setting time interval from data: " << Tlast - Tfirst << endl;
	myBDXDSTSelector->setTimeInterval(Ttot);
	myBDXDSTSelector1->setTimeInterval(Ttot);
	cout << "setting first event time: " << Tfirst << endl;
	myBDXDSTSelector->setT0(1. * Tfirst);
	myBDXDSTSelector1->setT0(1. * Tfirst);

	myBDXDSTSelector->setNProof(nproof);
	myBDXDSTSelector1->setNProof(nproof);

	if (nproof != 0) {
		cout << "USING PROOF WITH " << nproof << " WORKERS! " << endl;
		TProof *proof = TProof::Open(Form("workers=%i", nproof));
		//proof->Exec("gSystem->Load(\"libRooFit.so\")");
		proof->Exec("gSystem->Load(\"${BDXRECO_ROOT}/lib/libJANA.dylib\")");
		proof->Exec("gSystem->Load(\"${BDXRECO_ROOT}/lib/libbdxRecoExt.dylib\")");
		proof->Exec("gSystem->Load(\"${BDXRECO_ROOT}/lib/libbdxReco.dylib\")");
		proof->Exec("gSystem->Load(\"/Users/Mariangela/work/BDX-MINI/bdx-mini_anaMacro2-2GeV/libBDXDSTSelector.so\")");
		//proof->Exec("gSystem->Load(\"/auto_data/fiber7/bondi/bdx-mini_anaMacro2-2GeV/libBDXDSTSelector.so\")");
		proof->SetParameter("PROOF_Packetizer", "TPacketizer");
		DSTChain->SetProof(1);
	}
  cout << "Before process"<<endl;

	myBDXDSTSelector->nEventsTotal = Ntot;
	myBDXDSTSelector1->nEventsTotal = Ntot;

	vector<double> time_garbage;
	vector<double> time_beamON;
	vector<double> time_cosmic;
	vector<double> current_beamON;
	double meanTLive =1.;



	if(isMC==0){
	DSTChain->Process(myBDXDSTSelector, opt.c_str(), Ntot, N0);

	cout << "After process myBDXDSTSelector  " << endl;

	// define array rate in order to estimate the rate mean value and rate STDev:
	// these information are used to exclude the time with a wrong rate
	int Nrate_bin = myBDXDSTSelector->hTrigAllEvents_rate->GetNbinsX();
    float rate[Nrate_bin+1];
    double sum = 0;
    double var =0;
    double rate_mainValue=0;
    double rate_StDev=0;

    for(int i=0; i<=Nrate_bin; i++){
    	if(i==0){
    		rate[i] = 0;
    	}else{
    	  rate[i] = myBDXDSTSelector->hTrigAllEvents_rate->GetBinContent(i);
    	  sum +=rate[i];
    	}
    }

    rate_mainValue = sum/Nrate_bin;

    for(int i=1; i<=myBDXDSTSelector->hTrigAllEvents_rate->GetNbinsX(); i++){
    	var += (rate[i] - rate_mainValue)*(rate[i] - rate_mainValue) / Nrate_bin;
    }

    rate_StDev = sqrt(var);

    cout << rate_mainValue<< " "<<rate_StDev<<endl;

	double dT_bin = 1;
	int Nbin = (Ttot / dT_bin);
	float ratio;
	TH1D* hTrigAllEvents_current = new TH1D("hTrigAllEvents_current", "hTrigAllEvents_current;T(s), current",Nbin,0,Nbin * dT_bin);

	for(int i=1; i<=Nbin; i++){
		ratio = myBDXDSTSelector->hTrigAllEvents_current_temp->GetBinContent(i)/myBDXDSTSelector->hTrigAllEvents->GetBinContent(i);
		hTrigAllEvents_current->SetBinContent(i,ratio);
		}

    double halla_current=0;
    double halla_current_temp=0;
    double halla_current_time_temp=0;
    int i=0;
    bool isGarbage= false;
    double rate_temp=0;


     //first of all check rate : if the abs(rate - mean_value) <= 5*sigma is ok else time is time garbage
    // skim data in beam on event, cosmic event, garbage event:
    // an event is garbage if in the 5 sec after or before it there is a change of current :
    //i.e in the i-simo bin the current is >0 and in the following i+5 (or i-5) current=0 or viceversa

    for (int iX = 1; iX<=Nbin; iX++){
        isGarbage = false;
        if(abs(myBDXDSTSelector->hTrigAllEvents_rate->GetBinContent(iX)-rate_mainValue)>3*rate_StDev){

        	isGarbage=true;
        }
        halla_current = hTrigAllEvents_current->GetBinContent(iX);
        if(isGarbage==false && iX<=hTrigAllEvents_current->GetNbinsX()-6 ){
        for(int j=iX+1; j<=iX+5; j++){
        	halla_current_temp = hTrigAllEvents_current->GetBinContent(j);
            if((halla_current>0.030 && halla_current_temp<=0.030)||(halla_current<=0.030 && halla_current_temp>0.030)){
           //  cout <<"sono after " <<iX << " " << halla_current << " "<< j << " "<< halla_current_temp<<endl;
            	isGarbage = true;
               break;
            }
        }
        }
        if(isGarbage==false && iX>=6){
        for(int j=iX-5; j<=iX-1; j++){
        	halla_current_temp = hTrigAllEvents_current->GetBinContent(j);
        	if((halla_current>0.030 && halla_current_temp<=0.030)||(halla_current<=0.030 && halla_current_temp>0.030)){
       	//	 cout <<"sono before " <<iX << " " << halla_current << " "<< j << " "<< halla_current_temp<<endl;
               isGarbage = true;
               break;
            }
        }
        }

     if(isGarbage ==true) {
    	// cout <<hTrigAllEvents_current->GetBinCenter(iX)-0.5<<endl;
    	 time_garbage.push_back(hTrigAllEvents_current->GetBinCenter(iX)-0.5);

     }else{
    	 if(halla_current>0.03) {
    		 time_beamON.push_back(hTrigAllEvents_current->GetBinCenter(iX)-0.5);
    	     current_beamON.push_back(halla_current);
    	 }
    	 if(halla_current<=0.03) {
    	//	 cout << halla_current<<endl;
    		 time_cosmic.push_back(hTrigAllEvents_current->GetBinCenter(iX)-0.5);
    	 }

     }

    }   //end skim of data


    // evaluation of mean Tlive

   TH1D *hTLive = (TH1D*) myBDXDSTSelector->hTlive_temp->Clone("hTLive");
    hTLive->Divide(myBDXDSTSelector->hTrigAllEvents) ;
    for(int i=1; i<=hTLive->GetNbinsX(); i++){
    	meanTLive += hTLive->GetBinContent(i);
    }

    meanTLive = (meanTLive/myBDXDSTSelector->hTlive->GetNbinsX())/100;

    TCanvas *S00_c1 = new TCanvas("S00_c1", "current vs time");
    S00_c1->Divide(1,3);
    S00_c1->cd(1);
	myBDXDSTSelector->hTrigAllEvents->SetLineColor(1);
	myBDXDSTSelector->hTrigAllEvents->SetMarkerStyle(20);
	myBDXDSTSelector->hTrigAllEvents->Draw();
	S00_c1->cd(2);
	myBDXDSTSelector->hTrigAllEvents_current_temp->SetLineColor(1);
	myBDXDSTSelector->hTrigAllEvents_current_temp->SetMarkerStyle(20);
	myBDXDSTSelector->hTrigAllEvents_current_temp->Draw();
	S00_c1->cd(3);
	hTrigAllEvents_current->SetLineColor(1);
	hTrigAllEvents_current->SetMarkerStyle(20);
	hTrigAllEvents_current->Draw();

	} //end if isMC==0

	cout << time_garbage.size()<<" "<<time_beamON.size()<< " "<<time_cosmic.size()<<endl;


	myBDXDSTSelector1->BDX_time_garbage = time_garbage;
//	myBDXDSTSelector1->BDX_time_beam = time_beamON;
//	myBDXDSTSelector1->BDX_time_cosmic = time_cosmic;



	//evaluation of EOT

	double EOT =0;
	double charge_e= 1.6E-19;
	for(int i=0; i<current_beamON.size(); i++){

		EOT += current_beamON.at(i)*1;      // this corresponds to charge : current*dt where dt is 1 sec

	}

	EOT = (EOT*(1E-6))/charge_e;

	//cout<<halla_current.size()<<endl;



/* in hControl you can find the following info;
   bin 1 : number of EOT
   bin 3 : beam DT
   bin 5 : cosmic DT
   bin 7 : garbage DT

*/
TH1D* hControl = new TH1D("hControl", "hControl",100,0.5,100.5);

    for (int i=1; i<=100; i++){

    	if(i==1) hControl->SetBinContent(i, EOT);
    	if(i==3) hControl->SetBinContent(i, time_beamON.size());
    	if(i==5) hControl->SetBinContent(i, time_cosmic.size());
    	if(i==7) hControl->SetBinContent(i, time_garbage.size());
    }
    cout << "before BDXDSTSelector1"<<endl;
    myBDXDSTSelector1->mean_tlive = meanTLive;

 DSTChain->Process(myBDXDSTSelector1, opt.c_str(), Ntot, N0);

cout <<"after BDXDSTSelector1"<<endl;


        if(isMC==0){



        TCanvas *S0_c1 = new TCanvas("S0_c1", "TLive");
        S0_c1->Divide(1,2);
        S0_c1->cd(1);
		myBDXDSTSelector->hTlive->SetLineColor(1);
		myBDXDSTSelector->hTlive->SetMarkerStyle(20);
		myBDXDSTSelector->hTlive->Draw();
		TLine *Line1 = new TLine(0, meanTLive*100, Ttot, meanTLive*100 );
		Line1->SetLineColor(2);
		Line1->Draw("same");
		S0_c1->cd(2);
		//myBDXDSTSelector->hTrigAllEvents_rate->GetYaxis()->SetRangeUser(0, 10.);
		myBDXDSTSelector->hTrigAllEvents_rate->SetLineColor(1);
		myBDXDSTSelector->hTrigAllEvents_rate->SetMarkerStyle(20);
		myBDXDSTSelector->hTrigAllEvents_rate->Draw();

		TCanvas *S0_c2 = new TCanvas("S0_c2", "trigger_stability");

		S0_c2->Divide(3,3);
		S0_c2->cd(1);
		myBDXDSTSelector->hBDXMiniStability_trg[0]->SetLineColor(7);
		myBDXDSTSelector->hBDXMiniStability_trg[0]->SetMarkerColor(7);
		myBDXDSTSelector->hBDXMiniStability_trg[0]->SetMarkerStyle(20);
		myBDXDSTSelector->hBDXMiniStability_trg[0]->Draw();

		S0_c2->cd(2);
		myBDXDSTSelector->hBDXMiniStability_trg[1]->SetLineColor(2);
		myBDXDSTSelector->hBDXMiniStability_trg[1]->SetMarkerColor(2);
		myBDXDSTSelector->hBDXMiniStability_trg[1]->SetMarkerStyle(20);
		myBDXDSTSelector->hBDXMiniStability_trg[1]->Draw();

		S0_c2->cd(3);
		myBDXDSTSelector->hBDXMiniStability_trg[2]->SetLineColor(3);
		myBDXDSTSelector->hBDXMiniStability_trg[2]->SetMarkerColor(3);
		myBDXDSTSelector->hBDXMiniStability_trg[2]->SetMarkerStyle(20);
		myBDXDSTSelector->hBDXMiniStability_trg[2]->Draw();

		S0_c2->cd(4);
		myBDXDSTSelector->hBDXMiniStability_trg[3]->SetLineColor(4);
		myBDXDSTSelector->hBDXMiniStability_trg[3]->SetMarkerColor(4);
		myBDXDSTSelector->hBDXMiniStability_trg[3]->SetMarkerStyle(20);
		myBDXDSTSelector->hBDXMiniStability_trg[3]->Draw();

		S0_c2->cd(5);
		myBDXDSTSelector->hBDXMiniStability_trg[4]->SetLineColor(5);
		myBDXDSTSelector->hBDXMiniStability_trg[4]->SetMarkerColor(5);
		myBDXDSTSelector->hBDXMiniStability_trg[4]->SetMarkerStyle(20);
		myBDXDSTSelector->hBDXMiniStability_trg[4]->Draw();

		S0_c2->cd(6);
		myBDXDSTSelector->hBDXMiniStability_trg[31]->SetLineColor(6);
		myBDXDSTSelector->hBDXMiniStability_trg[31]->SetMarkerColor(6);
		myBDXDSTSelector->hBDXMiniStability_trg[31]->SetMarkerStyle(20);
		myBDXDSTSelector->hBDXMiniStability_trg[31]->Draw();

		S0_c2->cd(7);
		myBDXDSTSelector->hTrigAllEvents->Draw();

		myBDXDSTSelector->hBDXMiniStability_trg[0]->Draw("same");
		myBDXDSTSelector->hBDXMiniStability_trg[1]->Draw("same");
		myBDXDSTSelector->hBDXMiniStability_trg[2]->Draw("same");
		myBDXDSTSelector->hBDXMiniStability_trg[3]->Draw("same");
		myBDXDSTSelector->hBDXMiniStability_trg[4]->Draw("same");
		myBDXDSTSelector->hBDXMiniStability_trg[31]->Draw("same");


		TCanvas *S0_c3 = new TCanvas("S0_c3", "trigger_stability_hasChannel");
		S0_c3->Divide(1,3);

		S0_c3->cd(1);
		myBDXDSTSelector->hBDXMiniStability_hasChannel_Alltrg->SetLineColor(1);
		myBDXDSTSelector->hBDXMiniStability_hasChannel_Alltrg->SetMarkerColor(1);
		myBDXDSTSelector->hBDXMiniStability_hasChannel_Alltrg->SetMarkerStyle(20);
		myBDXDSTSelector->hBDXMiniStability_hasChannel_Alltrg->Draw();

		S0_c3->cd(2);
		myBDXDSTSelector->hBDXMiniStability_hasChannel_trg0->SetLineColor(1);
		myBDXDSTSelector->hBDXMiniStability_hasChannel_trg0->SetMarkerColor(1);
		myBDXDSTSelector->hBDXMiniStability_hasChannel_trg0->SetMarkerStyle(20);
		myBDXDSTSelector->hBDXMiniStability_hasChannel_trg0->Draw();

		S0_c3->cd(3);
		myBDXDSTSelector->hBDXMiniStability_hasChannel_trg1->SetLineColor(1);
		myBDXDSTSelector->hBDXMiniStability_hasChannel_trg1->SetMarkerColor(1);
		myBDXDSTSelector->hBDXMiniStability_hasChannel_trg1->SetMarkerStyle(20);
		myBDXDSTSelector->hBDXMiniStability_hasChannel_trg1->Draw();



		TCanvas *c2 = new TCanvas("c2", "Current Hall A");

		myBDXDSTSelector->hHALLA_cur->SetLineColor(1);
		myBDXDSTSelector->hHALLA_cur->Draw();

		myBDXDSTSelector1->hHALLA_cur_beam->SetMarkerStyle(20);
		myBDXDSTSelector1->hHALLA_cur_beam->SetMarkerColor(2);
		myBDXDSTSelector1->hHALLA_cur_beam->Draw("same");

		myBDXDSTSelector1->hHALLA_cur_garbage->SetMarkerStyle(20);
		myBDXDSTSelector1->hHALLA_cur_garbage->SetMarkerColor(4);
		myBDXDSTSelector1->hHALLA_cur_garbage->Draw("same");

		myBDXDSTSelector1->hHALLA_cur_cosmic->SetMarkerStyle(20);
		myBDXDSTSelector1->hHALLA_cur_cosmic->SetMarkerColor(5);
		myBDXDSTSelector1->hHALLA_cur_cosmic->Draw("same");

        }


        cout << "garbage DT: "<< time_garbage.size()<<" beam DT: "<< time_beamON.size()<<" cosmic DT "<<time_cosmic.size()<<endl;
        cout << "EOT "<< EOT<<endl;
        cout << "Tlive "<< meanTLive*100<<endl;





	/*Write histograms on the output file*/

	if (ofname != "") {
		TFile *ofile = new TFile(ofname.c_str(), "recreate");

		if(isMC==0){
		hControl->Write();
		//hRate->Write();
/*
		TListIter iter(myBDXDSTSelector->GetOutputList());
		TObject *obj;

		while (obj = iter.Next()) {
			if (obj->InheritsFrom(TH1::Class())) obj->Write();
		}
*/

		}
		TListIter iter1(myBDXDSTSelector1->GetOutputList());
		TObject *obj1;

		while (obj1 = iter1.Next()) {
			if (obj1->InheritsFrom(TH1::Class())) obj1->Write();
		}


		ofile->Close();
	}
	if (showGUI) {
		gui.Run(1);
	}

}
