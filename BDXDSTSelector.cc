#define BDXDSTSelector_cxx
// The class definition in BDXDSTSelector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("BDXDSTSelector.C")
// root> T->Process("BDXDSTSelector.C","some options")
// root> T->Process("BDXDSTSelector.C+")
//

#include "BDXDSTSelector.h"
#include <TH2.h>
#include <TStyle.h>
#include <TRandom3.h>
#include <vector>

void BDXDSTSelector::Begin(TTree * /*tree*/) {
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
	isMC = 0;

	if (option.Contains("MC") == true) {
		isMC = 1;
	}

	if (option.Contains("Tree") == true) {
		doTree = 1;
	}

	thisEventFineTime = 0;
	prevEventFineTime = 0;
}

void BDXDSTSelector::SlaveBegin(TTree * /*tree*/) {
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).
	TString option = GetOption();
	Info("SlaveBegin", "start with options: %s", option.Data());

	double dT = 1;
	int N = (int) (this->Ttot / dT);

	double dT1 = 60;
	int N1 = (int) (this->Ttot / dT1);
	isMC = 0;

	doTree = 0;

	if (option.Contains("MC") == true) {
		isMC = 1;
	}
	if (option.Contains("Tree") == true) {
		doTree = 1;
	}

	/*Create here the histograms.*/
	
	hHALLA_cur = new TH2D("hHALLA_cur", "hHALLA_cur;T(s);Current(uA)", N, 0, N * dT, 100, -0.05, 200.05);
	hTlive = new TH2D("hTlive", "hTlive;T(s);Live Time(%)", N, 0, N * dT, 111, -0.5, 110.5);

	hTrigAllEvents_stability = new TH1D("hTrigAllEvents_stability", "hTrigAllEvents_stability;T(s);Rate(Hz)",N1,0,N1 * dT1);

	hTrigAllEvents = new TH1D("hTrigAllEvents", "hTrigAllEvents;T(s);counts",N,0,N * dT);
	hTrigAllEvents_current_temp = new TH1D("hTrigAllEvents_current_temp", "hTrigAllEvents_current_temp;T(s);sum_current",N,0,N * dT);

	hTlive_temp = new TH1D("hTlive_temp", "hTlive_temp",N,0,N * dT);

	for(int i=0; i<32; i++){
		hBDXMiniStability_trg[i] = new TH1D(Form("hBDXMiniStability_trg_%i",i), Form("hBDXMiniStability_trg_%i;T(s);Rate(Hz)",i),N1,0,N1 * dT1);
	}

	for(int i=0; i<11; i++){
		hBDXMini_OV_A[i] = new TH1D(Form("hBDXMini_OV_A_%i",i), Form("hBDXMini_OV_A_%i;A; Counts",i),100,0,200);
		hBDXMini_IV_A[i] = new TH1D(Form("hBDXMini_IV_A_%i",i), Form("hBDXMini_IV_A_%i;A; Counts",i),100,0,200);
		hBDXMini_OV_T[i] = new TH1D(Form("hBDXMini_OV_T_%i",i), Form("hBDXMini_OV_T_%i;T[ns]; Counts",i),100,0,600);
		hBDXMini_IV_T[i] = new TH1D(Form("hBDXMini_IV_T_%i",i), Form("hBDXMini_IV_T_%i;T[ns]; Counts",i),100,0,600);
		hBDXMini_OV_Q[i] = new TH1D(Form("hBDXMini_OV_Q_%i",i), Form("hBDXMini_OV_Q_%i;Q[p.e.]; Counts",i),200,0,400);
		hBDXMini_IV_Q[i] = new TH1D(Form("hBDXMini_IV_Q_%i",i), Form("hBDXMini_IV_Q_%i;Q[p.e.]; Counts",i),200,0,400);
		hBDXMini_IV_AvT[i] = new TH2D(Form("hBDXMini_IV_AvT_%i",i), Form("hBDXMini_IV_AvT_%i;T; A",i),100,0,600, 200, 0, 400);
		hBDXMini_OV_AvT[i] = new TH2D(Form("hBDXMini_OV_AvT_%i",i), Form("hBDXMini_OV_AvT_%i;T; A",i),100,0,600, 200, 0, 400);

		if(i==9 || i==10){
			hBDXMini_OV_A[i] = new TH1D(Form("hBDXMini_OV_A_%i",i), Form("hBDXMini_OV_A_%i;A[mV]; Counts",i),200,0,400);
			hBDXMini_IV_A[i] = new TH1D(Form("hBDXMini_IV_A_%i",i), Form("hBDXMini_IV_A_%i;A[mV]; Counts",i),200,0,400);

		}
	}
	for(int i=0; i<45; i++){

		hBDXMini_crs_T[i] = new TH1D(Form("hBDXMini_crs_T_%i",i), Form("hBDXMini_crs_T_%i;T; Counts",i),300,0,600);
		hBDXMini_crs_E[i] = new TH1D(Form("hBDXMini_crs_E_%i",i), Form("hBDXMini_crs_E_%i;E[MeV]; Hz/MeV",i),1000,0,2000);
		hBDXMini_crs_EvT[i] = new TH2D(Form("hBDXMini_crs_EvT_%i",i), Form("hBDXMini_crs_EvT_%i;T; E",i),300,0,600, 1000, 0, 2000);

	}



	hBDXMiniStability_hasChannel_Alltrg = new TH1D("hBDXMiniStability_hasChannel_Alltrg", "hBDXMiniStability_hasChannel_Alltrg;Channel; Counts",64, 0 ,64);
	hBDXMiniStability_hasChannel_trg0 = new TH1D("hBDXMiniStability_hasChannel_trg0", "hBDXMiniStability_hasChannel_trg0;Channel; Counts",23, 0 ,23);
	hBDXMiniStability_hasChannel_trg1 = new TH1D("hBDXMiniStability_hasChannel_trg1", "hBDXMiniStability_hasChannel_trg1;Channel; Counts",23, 22 ,45);

	outTree = new TTree("outTree", "outTree");
	
	outTree->Branch("runNumber", &runNumber, "runNumber/I");
	outTree->Branch("eventNumber", &eventNumber, "eventNumber/I");




	Info("SlaveBegin", "AllHistos to fOutput");
	TIter next(gDirectory->GetList());
	TObject *obj;

	while (obj = (TObject*) next()) {
		if (obj->InheritsFrom(TH1::Class())) {
			fOutput->Add(obj);
		}
		if (obj->InheritsFrom(TTree::Class())) {
			fOutput->Add(obj);
		}
	}


	Info("SlaveBegin", "end");
}

Bool_t BDXDSTSelector::Process(Long64_t entry) {
	// The Process() function is called for each entry in the tree (or possibly
	// keyed object in the case of PROOF) to be processed. The entry argument
	// specifies which entry in the currently loaded tree is to be processed.
	// When processing keyed objects with PROOF, the object is already loaded
	// and is available via the fObject pointer.
	//
	// This function should contain the \"body\" of the analysis. It can contain
	// simple or elaborate selection criteria, run algorithms on the data
	// of the event and typically fill histograms.
	//
	// The processing can be stopped by calling Abort().
	//
	// Use fStatus to set the return value of TTree::Process().
	//
	// The return value is currently not used.
	this->GetEntry(entry);

	/*Get the event header and fill some variables*/
	m_EventHeader = m_Event->getEventHeader();
	eventNumber = m_EventHeader->getEventNumber();
	runNumber = m_EventHeader->getRunNumber();
	///WEIGHT///
	weight =  m_EventHeader->getWeight();

	thisEventT = m_Event->getEventHeader()->getEventTime() - T0;
	current = m_Event->getEventHeader()->getEpicsData()->getDataValue("pcrexHallA_beam_current");
	time_current = m_Event->getEventHeader()->getEpicsData()->getDataTime("pcrexHallA_beam_current") -T0;



	/*Objects to read collections*/
	CalorimeterHit *fCaloHit;
	IntVetoHit *fIntVetoHit;
	GenParticle *fGenParticle;
	triggerDataBDXmini *m_trigger;

	int idx_crs_up=0;
	int idx_crs_down=0;




	//	if(weight>0.01)	cout << "ERR WEIGHT!!: "<< weight << endl;

	N_event++;

	// Stability trigger
	if(m_Event->hasObject("triggerDataBDXmini")) {
	TObject *triggerDataObj = m_Event->getObject("triggerDataBDXmini");
	m_trigger = (triggerDataBDXmini*)triggerDataObj;




	for(int itrg=0; itrg<32; itrg++ ) {
		if(m_trigger->getNtriggers_single(itrg)) hBDXMiniStability_trg[itrg]->Fill(thisEventT);
	}

		for(int ichannel_trg=0; ichannel_trg<64; ichannel_trg++ ) {

		if(m_trigger->hasChannelTRG(ichannel_trg))	hBDXMiniStability_hasChannel_Alltrg->Fill(ichannel_trg);
        if((ichannel_trg>19&&ichannel_trg<42)&&(m_trigger->hasChannelTRG(ichannel_trg))&&m_trigger->getNtriggers_single(0)) hBDXMiniStability_hasChannel_trg0->Fill(ichannel_trg-19);
        if((ichannel_trg>41&&ichannel_trg<64)&&(m_trigger->hasChannelTRG(ichannel_trg))&&m_trigger->getNtriggers_single(1)) hBDXMiniStability_hasChannel_trg1->Fill(ichannel_trg-19);

		}

	}

	hTrigAllEvents_stability->Fill(thisEventT);

	hTrigAllEvents->Fill(thisEventT);
	hTrigAllEvents_current_temp->Fill(thisEventT, current);


	hHALLA_cur->Fill(thisEventT, current);


	Tlive = m_EventHeader->getEpicsData()->getDataValue("B_DET_BDX_FPGA:livetime");
	time_Tlive = m_EventHeader->getEpicsData()->getDataTime("B_DET_BDX_FPGA:livetime")-T0;
	hTlive->Fill(thisEventT, Tlive);
	hTlive_temp->Fill(thisEventT, Tlive);


	if (m_Event->hasCollection(IntVetoHit::Class(), "IntVetoHits")) {
	  TIter IntVetoHitsIter(m_Event->getCollection(IntVetoHit::Class(), "IntVetoHits"));
	  while (fIntVetoHit = (IntVetoHit*) IntVetoHitsIter.Next()) { //Need to cast to the proper object

	    if (fIntVetoHit->m_channel.layer == 0 &&  fIntVetoHit->m_channel.component!=3) {
	    	hBDXMini_OV_A[fIntVetoHit->m_channel.component]->Fill(fIntVetoHit->A);
	    	hBDXMini_OV_T[fIntVetoHit->m_channel.component]->Fill(fIntVetoHit->T);
	    	hBDXMini_OV_Q[fIntVetoHit->m_channel.component]->Fill(fIntVetoHit->Q);
	    	hBDXMini_OV_AvT[fIntVetoHit->m_channel.component]->Fill(fIntVetoHit->T,fIntVetoHit->A);
	    }

	    if (fIntVetoHit->m_channel.layer == 1) {
	    	hBDXMini_IV_A[fIntVetoHit->m_channel.component]->Fill(fIntVetoHit->A);
	    	hBDXMini_IV_T[fIntVetoHit->m_channel.component]->Fill(fIntVetoHit->T);
	    	hBDXMini_IV_Q[fIntVetoHit->m_channel.component]->Fill(fIntVetoHit->Q);
	    	hBDXMini_IV_AvT[fIntVetoHit->m_channel.component]->Fill(fIntVetoHit->T,fIntVetoHit->A);
	    }
	  }
	}

	if (m_Event->hasCollection(CalorimeterHit::Class(), "CalorimeterHits")) {
	  TIter CaloHitsIter(m_Event->getCollection(CalorimeterHit::Class(), "CalorimeterHits"));
	  //thisEventT = m_Event->getEventHeader()->getEventTime() - T0;

	  while (fCaloHit = (CalorimeterHit*) CaloHitsIter.Next()) {

		  if(fCaloHit->m_channel.sector ==0){

			  idx_crs_up = this->getCaloIDXFromXY(fCaloHit->m_channel.x, fCaloHit->m_channel.y);
			  hBDXMini_crs_E[idx_crs_up]->Fill(fCaloHit->E);
			  hBDXMini_crs_T[idx_crs_up]->Fill(fCaloHit->T);
			  hBDXMini_crs_EvT[idx_crs_up]->Fill(fCaloHit->T,fCaloHit->E);
		  }

		  if(fCaloHit->m_channel.sector ==1){

			  idx_crs_down = (this->getCaloIDXFromXY(fCaloHit->m_channel.x, fCaloHit->m_channel.y))+22;
			  hBDXMini_crs_E[idx_crs_down]->Fill(fCaloHit->E);
			  hBDXMini_crs_T[idx_crs_down]->Fill(fCaloHit->T);
			  hBDXMini_crs_EvT[idx_crs_down]->Fill(fCaloHit->T,fCaloHit->E);
		  }

	  }
	}
	outTree->Fill();


	//cout <<"end event"<<endl;

	return kTRUE;
	
}

void BDXDSTSelector::SlaveTerminate() {
// The SlaveTerminate() function is called after all entries or objects
// have been processed. When running with PROOF SlaveTerminate() is called
// on each slave server.


}

void BDXDSTSelector::Terminate() {
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  
  Info("Terminate", "Terminate starts");
  Info("Terminate", "Total events are: %i", nEventsTotal);
  
  TListIter iter(fOutput);
  TObject *obj;



  hTrigAllEvents = (TH1D*)fOutput->FindObject("hTrigAllEvents");
  hTrigAllEvents_stability=(TH1D*)fOutput->FindObject("hTrigAllEvents_stability");
  hTrigAllEvents_current_temp=(TH1D*)fOutput->FindObject("hTrigAllEvents_current_temp");
  hHALLA_cur = (TH2D*)fOutput->FindObject("hHALLA_cur");
  hTlive = (TH2D*)fOutput->FindObject("hTlive");
  hTlive_temp=(TH1D*)fOutput->FindObject("hTlive_temp");
  hBDXMiniStability_hasChannel_Alltrg = (TH1D*)fOutput->FindObject("hBDXMiniStability_hasChannel_Alltrg");
  hBDXMiniStability_hasChannel_trg0 = (TH1D*)fOutput->FindObject("hBDXMiniStability_hasChannel_trg0");
  hBDXMiniStability_hasChannel_trg1 = (TH1D*)fOutput->FindObject("hBDXMiniStability_hasChannel_trg1");



  for(int i=0; i<32; i++){
  		hBDXMiniStability_trg[i] = (TH1D*)fOutput->FindObject(Form("hBDXMiniStability_trg_%i",i));
  }

  for(int i=0; i<11; i++){
	  hBDXMini_OV_A[i] = (TH1D*)fOutput->FindObject(Form("hBDXMini_OV_A_%i",i));
	  hBDXMini_IV_A[i] = (TH1D*)fOutput->FindObject(Form("hBDXMini_IV_A_%i",i));
	  hBDXMini_OV_T[i] = (TH1D*)fOutput->FindObject(Form("hBDXMini_OV_T_%i",i));
	  hBDXMini_IV_T[i] = (TH1D*)fOutput->FindObject(Form("hBDXMini_IV_T_%i",i));
	  hBDXMini_OV_Q[i] = (TH1D*)fOutput->FindObject(Form("hBDXMini_OV_Q_%i",i));
	  hBDXMini_IV_Q[i] = (TH1D*)fOutput->FindObject(Form("hBDXMini_IV_Q_%i",i));
	  hBDXMini_IV_AvT[i] = (TH2D*)fOutput->FindObject(Form("hBDXMini_IV_AvT_%i",i));
	  hBDXMini_OV_AvT[i] = (TH2D*)fOutput->FindObject(Form("hBDXMini_OV_AvT_%i",i));
  }

  for(int i=0; i<45; i++){

	  hBDXMini_crs_T[i] = (TH1D*)fOutput->FindObject(Form("hBDXMini_crs_T_%i",i));
	  hBDXMini_crs_E[i] = (TH1D*)fOutput->FindObject(Form("hBDXMini_crs_E_%i",i));
	  hBDXMini_crs_EvT[i] = (TH2D*)fOutput->FindObject(Form("hBDXMini_crs_EvT_%i",i));

  }



    hTrigAllEvents_stability->Sumw2();
    hTrigAllEvents_stability->Scale(1.,"width");

    hBDXMiniStability_trg[0]->Sumw2();
	hBDXMiniStability_trg[0]->Scale(1.,"width");
	hBDXMiniStability_trg[1]->Sumw2();
	hBDXMiniStability_trg[1]->Scale(1.,"width");
	hBDXMiniStability_trg[2]->Sumw2();
	hBDXMiniStability_trg[2]->Scale(1.,"width");
	hBDXMiniStability_trg[3]->Sumw2();
	hBDXMiniStability_trg[3]->Scale(1.,"width");
	hBDXMiniStability_trg[4]->Sumw2();
	hBDXMiniStability_trg[4]->Scale(1.,"width");
	hBDXMiniStability_trg[31]->Sumw2();
	hBDXMiniStability_trg[31]->Scale(1.,"width");

	for(int i=0; i<45; i++){
		hBDXMini_crs_E[i]->Sumw2();
		hBDXMini_crs_E[i]->Scale(1./this->Ttot,"width");
	}




    while (obj = iter.Next()) {
      Info("Terminate", "obj: %s", obj->GetName());
    }
    Info("Terminate", "No more objs");


  cout << "*********"<<endl;
  cout << eventNumber<<endl;
  

  
 



}


