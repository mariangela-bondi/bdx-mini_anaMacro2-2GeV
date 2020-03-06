//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Dec 27 16:37:57 2016 by ROOT version 6.08/00
// from TTree EventDST/EventDST
// found on file: outTest.root
//////////////////////////////////////////////////////////

#ifndef BDXDSTSelector_h
#define BDXDSTSelector_h

#include <TROOT.h>
#include "TProofOutputFile.h"
#include <TChain.h>
#include <TFile.h>
#include <vector>
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
#include <BDXmini/triggerDataBDXmini.h>

#include "IntVeto/IntVetoDigiHit.h"
#include "Calorimeter/CalorimeterDigiHit.h"

#include "Calorimeter/CalorimeterHit.h"
#include "IntVeto/IntVetoHit.h"
#include "ExtVeto/ExtVetoHit.h"

#include "Calorimeter/CalorimeterMCRealHit.h"

#include "EventBuilder/TEventHeader.h"
#include "MC/GenParticle.h"


class BDXDSTSelector: public TSelector {
public:

	TTree *fChain = 0;   //!pointer to the analyzed TTree or TChain

	// Readers to access the data
	//TTreeReaderValue<TEvent> event = { fReader, "Event" };

	BDXDSTSelector(TTree * /*tree*/= 0) {
		/*All the histogram pointers MUST be initialized to 0 here*/
		m_EventHeader = 0;
		m_Event = 0;

		T0 = 0;
		Ttot=0;
		Tlive=0;
		time_Tlive=0;
		time_current=0;
		time_current_temp=0;
		N_event=0;

		nEventsTotal = 0;
		thisEventN = 0;
		thisEventT = 0;

	       
		/*OutputTree and related stuff*/
		outProofFile = 0;
		outFile = 0;
		outTree = 0;


		hHALLA_cur=0;
		hTlive=0;
		hTlive_temp=0;
		hTrigAllEvents =0;
		hTrigAllEvents_stability=0;
		hTrigAllEvents_current_temp=0;
		hBDXMiniStability_hasChannel_Alltrg=0;
		hBDXMiniStability_hasChannel_trg0=0;
		hBDXMiniStability_hasChannel_trg1=0;

	//	hBDXMiniStability_trg=0;

		for(int i=0; i<32; i++){
		hBDXMiniStability_trg[i] = 0;
		}

		for(int i=0; i<11; i++){
			hBDXMini_OV_A[i] = 0;
			hBDXMini_IV_A[i] = 0;
			hBDXMini_OV_T[i] = 0;
			hBDXMini_IV_T[i] = 0;
			hBDXMini_OV_Q[i] = 0;
			hBDXMini_IV_Q[i] = 0;
			hBDXMini_IV_AvT[i] = 0;
			hBDXMini_OV_AvT[i] = 0;
		}

		for(int i=0; i<45; i++){

			hBDXMini_crs_T[i]=0;
			hBDXMini_crs_E[i]=0;
			hBDXMini_crs_EvT[i]=0;

		}


		}

	virtual ~BDXDSTSelector() {
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


  
	TH2D *hHALLA_cur, *hTlive;
	/*trigger histograms*/
	TH1D *hTlive_temp;
	TH1D *hTrigAllEvents, *hTrigAllEvents_stability, *hTrigAllEvents_current_temp;
	TH1D *hBDXMiniStability_trg[32];
	TH1D *hBDXMiniStability_hasChannel_Alltrg;
	TH1D *hBDXMiniStability_hasChannel_trg0;
	TH1D *hBDXMiniStability_hasChannel_trg1;

    // Veto histograms
	TH1D *hBDXMini_OV_A[11];
	TH1D *hBDXMini_IV_A[11];
	TH1D *hBDXMini_OV_T[11];
	TH1D *hBDXMini_IV_T[11];
	TH1D *hBDXMini_OV_Q[11];
	TH1D *hBDXMini_IV_Q[11];
	TH2D *hBDXMini_IV_AvT[11];
	TH2D *hBDXMini_OV_AvT[11];

	// Crystals histograms
	TH1D *hBDXMini_crs_T[45];
	TH1D *hBDXMini_crs_E[45];
	TH2D *hBDXMini_crs_EvT[45];


	TTree *outTree;
	TProofOutputFile *outProofFile;
	TFile *outFile;

	//	hBDXMiniStability_trg = new TH1D*[32];

	
	/*Variables*/
    bool isGarbage;
    bool isCosmic;
    bool isBeam;
	double T0, Ttot;
	int N0, N_event;
	int thisEventN;
	double thisEventT;
	int nEventsTotal;
	int NProof;
	double current, Tlive, time_Tlive, time_current, time_current_temp;
    vector<double> Vect_current;
    vector<double> Vect_time_current;

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
		return this->outTree;
	}

ClassDef(BDXDSTSelector,1);

};

#endif

#ifdef BDXDSTSelector_cxx
void BDXDSTSelector::Init(TTree *tree)
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

Bool_t BDXDSTSelector::Notify()
{
	// The Notify() function is called when a new file is opened. This
	// can be either for a new TTree in a TChain or when when a new TTree
	// is started when using PROOF. It is normally not necessary to make changes
	// to the generated code, but the routine can be extended by the
	// user if needed. The return value is currently not used.

	return kTRUE;
}

#endif // #ifdef BDXDSTSelector_cxx
