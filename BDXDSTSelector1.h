//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Dec 27 16:37:57 2016 by ROOT version 6.08/00
// from TTree EventDST/EventDST
// found on file: outTest.root
//////////////////////////////////////////////////////////

#ifndef BDXDSTSelector1_h
#define BDXDSTSelector1_h

#include <TROOT.h>
#include "TProofOutputFile.h"
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TClonesArray.h>
#include <TCollection.h>

#include <TH1D.h>
#include <TH2D.h>
#include <TAxis.h>
#include <TCanvas.h>

// Headers needed by this particular selector
#include "EventBuilder/TEvent.h"
#include "EventBuilder/TEventHeader.h"
#include "EPICS/epicsData.h"

#include "IntVeto/IntVetoDigiHit.h"
#include "Calorimeter/CalorimeterDigiHit.h"

#include "Calorimeter/CalorimeterHit.h"
#include "IntVeto/IntVetoHit.h"
#include "ExtVeto/ExtVetoHit.h"

#include "Calorimeter/CalorimeterMCRealHit.h"

#include "EventBuilder/TEventHeader.h"
#include "MC/GenParticle.h"


class BDXDSTSelector1: public TSelector {
public:

	TTree *fChain = 0;   //!pointer to the analyzed TTree or TChain

	// Readers to access the data
	//TTreeReaderValue<TEvent> event = { fReader, "Event" };

	BDXDSTSelector1(TTree * /*tree*/= 0) {
		/*All the histogram pointers MUST be initialized to 0 here*/
		m_EventHeader = 0;
		m_Event = 0;
		isMC = 0;

		Ttot = 0;
		T0 = 0;
		time=0;
		N0=0;

        INDEX =0;
		nEventsTotal = 0;
		thisEventN = 0;
		thisEventT = 0;

	
		N_event=0;
		t_start=0;
		t_stop=0;
		dt=0;
		DT_noBEAM=0;
		ii_time=0;
		DT_true =0;
      

		EOT =0;
		mean_tlive =0;


	       
		/*OutputTree and related stuff*/
		outProofFile = 0;
		outFile = 0;
		outTree1 = 0;

		hTrigAllEvents_rate_garbage =0;
		hHALLA_cur_garbage=0;
		hHALLA_cur_cosmic=0;
		hHALLA_cur_beam=0;

		//variables VETO

		for(int i=0; i<11; i++){
			QOV[i]=0;
			QIV[i]=0;
			TOV[i]=0;
			TIV[i]=0;
		}

		//variables CRS
		for(int i=0; i<45; i++){
			Ecrs[i]=0;
			Tcrs[i]=0;
			Acrs[i]=0;
		}


		// HISTO VETO
		for(int i=0; i<3; i++){
	    hOV_Atot[i] = 0;
	    hOV_multiplicity[i] = 0;
		hIV_Atot[i] = 0;
		hIV_multiplicity[i] = 0;
		hOV_Atot_vs_multiplicity[i] = 0;
		hIV_Atot_vs_multiplicity[i] = 0;


		// HISTO CALORIMETER
		hCrs_Etot[i] = 0;
		hCrs_multiplicity[i] = 0;
		hCrs_Eseed[i] = 0;
		hCrs_Etop[i] = 0;
		hCrs_Ebottom[i] = 0;
		hCrs_R_EtopEtot[i] = 0;
		hCrs_R_EbottomEtot[i] = 0;
		hCrs_EtotVsEtop[i] = 0;
	    hCrs_XYseed[i] = 0;
	    hCrs_XY_XYseed[i] = 0;
		hCrs_EseedVSEtot[i] = 0;
		hCrs_EseedVSMulti[i] = 0;
		hCrs_EtotVSMulti[i] = 0;


		  // HISTO CALORIMETER NO VETO

		hCrs_Etot_NoVETO[i] = 0;
		hCrs_multiplicity_NoVETO[i] = 0;
		hCrs_Eseed_NoVETO[i] = 0;
		hCrs_Etop_NoVETO[i] = 0;
		hCrs_Ebottom_NoVETO[i] = 0;
		hCrs_R_EtopEtot_NoVETO[i] = 0;
		hCrs_R_EbottomEtot_NoVETO[i] = 0;
		hCrs_EtotVsEtop_NoVETO[i] = 0;
	    hCrs_XYseed_NoVETO[i] = 0;
	    hCrs_XY_XYseed_NoVETO[i] = 0;
		hCrs_EseedVSEtot_NoVETO[i] = 0;
		hCrs_EseedVSMulti_NoVETO[i] = 0;
		hCrs_EtotVSMulti_NoVETO[i] = 0;

		//HISTO rejection study

		hCrs_Eseed_IVc1[i] =0;
		hCrs_Eseed_IVc2[i] =0;
		hCrs_Eseed_IVc3[i] =0;
		hCrs_Eseed_IVc4[i] =0;
		hCrs_Eseed_IVc5[i] =0;


		hCrs_Eseed_NoIVc1[i] =0;
		hCrs_Eseed_NoIVc2[i] =0;
		hCrs_Eseed_NoIVc3[i] =0;
		hCrs_Eseed_NoIVc4[i] =0;
		hCrs_Eseed_NoIVc5[i] =0;

		 IVc1=0;
		 IVc2=0;
		 IVc3=0;
		 IVc4=0;
		 IVc5=0;

		 Eseed=0;
		 multip=0;
		}



		hTlive=0;


	}

	virtual ~BDXDSTSelector1() {
	}
	virtual Int_t Version() const {
		return 2;
	}
	virtual void Begin(TTree *tree);
	virtual void SlaveBegin(TTree *tree);
	virtual void Init(TTree *tree);
	virtual Bool_t Notify();
	virtual Bool_t Process(Long64_t entry);
	virtual Int_t GetEntry(Long64_t entry, Int_t getall = 0) {
		return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0;
	}
	virtual void SetOption(const char *option) {
		fOption = option;
	}
	virtual void SetObject(TObject *obj) {
		fObject = obj;
	}
	virtual void SetInputList(TList *input) {
		fInput = input;
	}
	virtual TList *GetOutputList() const {
		return fOutput;
	}
	virtual void SlaveTerminate();
	virtual void Terminate();


	int eventNumber, runNumber;
	double weight;
	bool doTree;


	/*Pointers. Note that EACH histogram pointer MUST be initialized to 0 in the TSelector constructor*/
	TEventHeader *m_EventHeader;
	TEvent *m_Event;


	/*Counter histogram for normalization*/
	//	TH1D *hCounter;

	/*trigger histograms*/
	//TH1D *hTrigBits, *hTrigBitsPulser;

	/*Rate-Stability histograms*/
	//TH1D *hTrigAllEvents;
	//TH1D *hTrig1, *hTrig2, *hTrig3, *hTrig4, *hTrigP, *hTrig0;


	TH1D *hTrigAllEvents_rate_garbage;
	TH2D *hHALLA_cur_garbage, *hHALLA_cur_cosmic, *hHALLA_cur_beam, *hTlive;
	vector<double> BDX_time_garbage;
	vector<double> BDX_time_beam;
	vector<double> BDX_time_cosmic;
    bool isGarbage;
    bool isCosmic;
    bool isBeam;
    int INDEX;

    //variables VETO
    double QOV[11], QIV[11], TOV[11], TIV[11];

    //variables CRS

    double Ecrs[45], Tcrs[45], Acrs[45];

       // HISTO VETO


    TH1D *hOV_Atot[3], *hOV_multiplicity[3] ;
	TH1D *hIV_Atot[3], *hIV_multiplicity[3] ;
	TH2D *hOV_Atot_vs_multiplicity[3];
	TH2D *hIV_Atot_vs_multiplicity[3];



	  // HISTO CALORIMETER
	 // 0=cosmic, 1=beam, 2=MC
	TH1D *hCrs_Etot[3];
	TH1D *hCrs_multiplicity[3];
	TH1D *hCrs_Eseed[3];
	TH1D *hCrs_Etop[3];
	TH1D *hCrs_Ebottom[3];
	TH1D *hCrs_R_EtopEtot[3];
	TH1D *hCrs_R_EbottomEtot[3];
	TH2D *hCrs_EtotVsEtop[3];
	TH2D *hCrs_XYseed[3];
	TH2D *hCrs_XY_XYseed[3];
	TH2D *hCrs_EseedVSEtot[3];
	TH2D *hCrs_EseedVSMulti[3];
	TH2D *hCrs_EtotVSMulti[3];


	// HISTO CALORIMETER No VETO
	TH1D *hCrs_Etot_NoVETO[3];
	TH1D *hCrs_multiplicity_NoVETO[3];
	TH1D *hCrs_Eseed_NoVETO[3];
	TH1D *hCrs_Etop_NoVETO[3];
	TH1D *hCrs_Ebottom_NoVETO[3];
	TH1D *hCrs_R_EtopEtot_NoVETO[3];
	TH1D *hCrs_R_EbottomEtot_NoVETO[3];
	TH2D *hCrs_EtotVsEtop_NoVETO[3];
	TH2D *hCrs_XYseed_NoVETO[3];
	TH2D *hCrs_XY_XYseed_NoVETO[3];
	TH2D *hCrs_EseedVSEtot_NoVETO[3];
	TH2D *hCrs_EseedVSMulti_NoVETO[3];
	TH2D *hCrs_EtotVSMulti_NoVETO[3];

	//HISTO rejection study
	TH1D *hCrs_Eseed_IVc1[3];
	TH1D *hCrs_Eseed_IVc2[3];
	TH1D *hCrs_Eseed_IVc3[3];
	TH1D *hCrs_Eseed_IVc4[3];
	TH1D *hCrs_Eseed_IVc5[3];

	TH1D *hCrs_Eseed_NoIVc1[3];
	TH1D *hCrs_Eseed_NoIVc2[3];
	TH1D *hCrs_Eseed_NoIVc3[3];
	TH1D *hCrs_Eseed_NoIVc4[3];
	TH1D *hCrs_Eseed_NoIVc5[3];

	int IVc1;
	int IVc2;
	int IVc3;
	int IVc4;
	int IVc5;
	double Eseed;
	int multip;

	vector<TTree*> tQmatrix;

	TTree *outTree1;
	TProofOutputFile *outProofFile;
	TFile *outFile;


	
	/*Variables*/
	double EOT, mean_tlive;
	double Ttot, T0;
	int N0;
	int thisEventN;
	double thisEventT;
	int nEventsTotal;
	int NProof;
	double time, current;



		int N_event;
		int t_start, t_stop, dt, DT_noBEAM, ii_time, DT_true;

	

	uint64_t thisEventFineTime, prevEventFineTime; //works only if proof = 0

	int isMC;

	/*Methods*/
	double getTimeInterval() {
		return Ttot;
	}
	void setTimeInterval(double T) {
		Ttot = T;
		Info("setTimeInterval", Form("Ttot set to %f", Ttot));
	}
	double getT0() {
		return T0;
	}
	void setT0(double T) {
		T0 = T;
		Info("setT0", Form("time0 set to %f", T0));
	}


	double getN0() {
		return N0;
	}
	void setN0(double N) {
		N0 = N;
		Info("setN0", Form("events set to %f", N0));
	}



	void setNProof(int N) {
		NProof = N;
	}

	int getCaloIDXFromXY(const int &x, const int &y) {

		if(x==-2 && y==-2) return 1;
		if(x==-1 && y==-2) return 2;
		if(x==0 && y==-2) return 3;
		if(x==1 && y==-2) return 4;
		if(x==2 && y==-2) return 5;

		if(x==0 && y==-1) return 6;

		if(x==-2 && y==0) return 7;
		if(x==-1 && y==0) return 8;
		if(x==0 && y==0) return 9;
		if(x==1 && y==0) return 10;
		if(x==2 && y==0) return 11;

		if(x==-2 && y==1) return 12;
		if(x==-1 && y==1) return 13;
		if(x==0 && y==1) return 14;
		if(x==1 && y==1) return 15;
		if(x==2 && y==1) return 16;

		if(x==-2 && y==2) return 17;
		if(x==-1 && y==2) return 18;
		if(x==1 && y==2) return 19;
		if(x==2 && y==2) return 20;

		//if(x==1 && y==3) return 21;
		//if(x==2 && y==3) return 22;

		if(x==-1 && y==3) return 21;
		if(x==1 && y==3) return 22;
	}

	TTree *GetOutTree(){
		return this->outTree1;
	}

ClassDef(BDXDSTSelector1,1);

};

#endif

#ifdef BDXDSTSelector1_cxx
void BDXDSTSelector1::Init(TTree *tree)
{
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the reader is initialized.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).
	if (!tree) return;
	fChain = tree;

	fChain->SetBranchAddress("Event", &m_Event);

}

Bool_t BDXDSTSelector1::Notify()
{
	// The Notify() function is called when a new file is opened. This
	// can be either for a new TTree in a TChain or when when a new TTree
	// is started when using PROOF. It is normally not necessary to make changes
	// to the generated code, but the routine can be extended by the
	// user if needed. The return value is currently not used.

	return kTRUE;
}

#endif // #ifdef BDXDSTSelector1_cxx
