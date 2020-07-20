#define BDXDSTSelector1_cxx
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

#include "BDXDSTSelector1.h"
#include <TH2.h>
#include <TStyle.h>
#include <TRandom3.h>
#include <vector>

void BDXDSTSelector1::Begin(TTree * /*tree*/) {
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
	isMC = 0;
	isPROD = 0;
	if (option.Contains("MC") == true) {
		isMC = 1;
	}
	if (option.Contains("PROD") == true) {
		isPROD = 1;
	}

	thisEventFineTime = 0;
	prevEventFineTime = 0;
}

void BDXDSTSelector1::SlaveBegin(TTree * /*tree*/) {
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).
	TString option = GetOption();
	Info("SlaveBegin", "start with options: %s", option.Data());

	double dT = 1;
	int N = (int) (this->Ttot / dT);
	isMC = 0;
	isPROD = 0;
	if (option.Contains("MC") == true) {
		isMC = 1;
	}
	if (option.Contains("PROD") == true) {
		isPROD = 1;
	}
	/*Create here the histograms.*/
	hNormalization = new TH1D("hNormalization", "hNormalization", 100, -0.5, 99.5);

	if (isMC == 0) {
		hTrigAllEvents_rate_garbage = new TH1D("hTrigAllEvents_rate_garbage", "hTrigAllEvents_rate_garbage;T(s);Rate(Hz)", N, 0, N * dT);
		//	hHALLA_cur_beam = new TH2D("hHALLA_cur_beam", "hHALLA_cur_beam;T(s);Current(uA)", N, 0, N * dT, 100, -0.05, 200.05);
		//	hHALLA_cur_cosmic = new TH2D("hHALLA_cur_cosmic", "hHALLA_cur_cosmic;T(s);Current(uA)", N, 0, N * dT, 100, -0.05, 200.05);
		//	hHALLA_cur_garbage = new TH2D("hHALLA_cur_garbage", "hHALLA_cur_garbage;T(s);Current(uA)", N, 0, N * dT, 100, -0.05, 200.05);
	}
	// HISTO VETO
	int Nbin_Atot = 201;
	int min_Atot = -0.5;
	int max_Atot = 2000.5;

	// HISTO CALORIMETER

	int Nbin_Etot = 3000;
	int min_Etot = -0.5;
	int max_Etot = 2999.5;

	for (int i = 0; i < 3; i++) {
		hOV_Atot[i] = new TH1D(Form("hOV_Atot_%i", i), Form("hOV_Atot_%i; phe;Counts", i), Nbin_Atot, min_Atot, max_Atot);
		hOV_multiplicity[i] = new TH1D(Form("hOV_multiplicity_%i", i), Form("hOV_multiplicity_%i; multiplicity;Counts", i), 11, -0.5, 10.5);
		hIV_Atot[i] = new TH1D(Form("hIV_Atot_%i", i), Form("hIV_Atot_%i; phe;Counts", i), Nbin_Atot, min_Atot, max_Atot);
		hIV_multiplicity[i] = new TH1D(Form("hIV_multiplicity_%i", i), Form("hIV_multiplicity_%i; multiplicity;Counts", i), 11, -0.5, 10.5);
		hOV_Atot_vs_multiplicity[i] = new TH2D(Form("hOV_Atot_vs_multiplicity_%i", i), Form("hOV_Atot_vs_multiplicity_%i; phe;multiplicity", i), Nbin_Atot, min_Atot, max_Atot, 11, -0.5, 10.5);
		hIV_Atot_vs_multiplicity[i] = new TH2D(Form("hIV_Atot_vs_multiplicity_%i", i), Form("hIV_Atot_vs_multiplicity_%i; phe;multiplicity", i), Nbin_Atot, min_Atot, max_Atot, 11, -0.5, 10.5);

		// HISTO CALORIMETER

		hCrs_Etot[i] = new TH1D(Form("hCrs_Etot_%i", i), Form("hCrs_Etot_%i; Etot [MeV]; Hz/MeV", i), Nbin_Etot, min_Etot, max_Etot);
		hCrs_multiplicity[i] = new TH1D(Form("hCrs_multiplicity_%i", i), Form("hCrs_multiplicity_%i; multiplicity; counts", i), 45, -0.5, 44.5);
		hCrs_Eseed[i] = new TH1D(Form("hCrs_Eseed_%i", i), Form("hCrs_Eseed_%i; Eseed [MeV]; Hz/MeV", i), Nbin_Etot, min_Etot, max_Etot);
		hCrs_Etop[i] = new TH1D(Form("hCrs_Etop_%i", i), Form("hCrs_Etop_%i; Etop [MeV]; Hz/MeV", i), Nbin_Etot, min_Etot, max_Etot);
		hCrs_Ebottom[i] = new TH1D(Form("hCrs_Ebottom_%i", i), Form("hCrs_Ebottom_%i; Ebottom [MeV]; Hz/MeV", i), Nbin_Etot, min_Etot, max_Etot);
		hCrs_R_EtopEtot[i] = new TH1D(Form("hCrs_R_EtopEtot_%i", i), Form("hCrs_R_EtopEtot_%i; Etop/Etot; counts", i), 110, -0.5, 1.5);
		hCrs_R_EbottomEtot[i] = new TH1D(Form("hCrs_R_EbottomEtot_%i", i), Form("hCrs_R_EbottomEtot_%i; Ebottom/Etot; counts", i), 110, -0.5, 1.5);
		hCrs_EtotVsEtop[i] = new TH2D(Form("hCrs_EtotVsEtop_%i", i), Form("hCrs_EtotVsEtop_%i; Etot [MeV]; Etop [MeV]", i), Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
		hCrs_XYseed[i] = new TH2D(Form("hCrs_XYseed_%i", i), Form("hCrs_XYseed_%i; X; Y", i), 11, -5.5, 5.5, 11, -5.5, 5.5);
		hCrs_XY_XYseed[i] = new TH2D(Form("hCrs_XY_XYseed_%i", i), Form("hCrs_XY_XYseed_%i; X-Xseed; Y-Yseed", i), 11, -5.5, 5.5, 11, -5.5, 5.5);
		hCrs_EseedVSEtot[i] = new TH2D(Form("hCrs_EseedVSEtot_%i", i), Form("hCrs_EseedVSEtot_%i; Eseed [MeV]; Etot [MeV]", i), Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
		hCrs_EseedVSMulti[i] = new TH2D(Form("hCrs_EseedVSMulti_%i", i), Form("hCrs_EseedVSMulti_%i; Eseed [MeV]; Multiplicity", i), Nbin_Etot, min_Etot, max_Etot, 45, -0.5, 44.5);
		hCrs_EtotVSMulti[i] = new TH2D(Form("hCrs_EtotVSMulti_%i", i), Form("hCrs_EtotVSMulti_%i; Etot [MeV]; Multiplicity", i), Nbin_Etot, min_Etot, max_Etot, 45, -0.5, 44.5);
		hCrs_EtopEbotVsEtot[i] = new TH2D(Form("hCrs_EtopEbotVsEtot_%i", i), Form("hCrs_EtopEbotVsEtot_%i; Etop-Ebot/Etot; Etot [MeV]", i), 300, -1.5, 1.5, Nbin_Etot, min_Etot, max_Etot);
		hCrs_EtopEbotVsEseed[i] = new TH2D(Form("hCrs_EtopEbotVsEseed_%i", i), Form("hCrs_EtopEbotVsEseed_%i; Etop-Ebot/Etot; Eseed [MeV]", i), 300, -1.5, 1.5, Nbin_Etot, min_Etot, max_Etot);
		hCrs_Eseed_CutEasym[i] = new TH1D(Form("hCrs_Eseed_CutEasym_%i", i), Form("hCrs_Eseed_CutEasym_%i; Eseed [MeV]; Hz/MeV", i), Nbin_Etot, min_Etot, max_Etot);

		for (int j = 0; j < 3; j++) {
			hCrs_Etot_NoVETO[i][j] = new TH1D(Form("hCrs_Etot_NoVETO_%i_%i", i, j), Form("hCrs_Etot_NoVETO_%i_%i; Etot [MeV]; Hz/MeV", i, j), Nbin_Etot, min_Etot, max_Etot);
			hCrs_multiplicity_NoVETO[i][j] = new TH1D(Form("hCrs_multiplicity_NoVETO_%i_%i", i, j), Form("hCrs_multiplicity_NoVETO_%i_%i; multiplicity; counts", i, j), 45, -0.5, 44.5);
			hCrs_Eseed_NoVETO[i][j] = new TH1D(Form("hCrs_Eseed_NoVETO_%i_%i", i, j), Form("hCrs_Eseed_NoVETO_%i_%i; Eseed [MeV]; Hz/MeV", i, j), Nbin_Etot, min_Etot, max_Etot);
			hCrs_Etop_NoVETO[i][j] = new TH1D(Form("hCrs_Etop_NoVETO_%i_%i", i, j), Form("hCrs_Etop_NoVETO_%i_%i; Etop [MeV]; Hz/MeV", i, j), Nbin_Etot, min_Etot, max_Etot);
			hCrs_Ebottom_NoVETO[i][j] = new TH1D(Form("hCrs_Ebottom_NoVETO_%i_%i", i, j), Form("hCrs_Ebottom_NoVETO_%i_%i; Ebottom [MeV]; Hz/MeV", i, j), Nbin_Etot, min_Etot, max_Etot);
			hCrs_R_EtopEtot_NoVETO[i][j] = new TH1D(Form("hCrs_R_EtopEtot_NoVETO_%i_%i", i, j), Form("hCrs_R_EtopEtot_NoVETO_%i_%i; Etop/Etot; counts", i, j), 110, -0.5, 1.5);
			hCrs_R_EbottomEtot_NoVETO[i][j] = new TH1D(Form("hCrs_R_EbottomEtot_NoVETO_%i_%i", i, j), Form("hCrs_R_EbottomEtot_NoVETO_%i_%i; Ebottom/Etot; counts", i, j), 110, -0.5, 1.5);
			hCrs_EtotVsEtop_NoVETO[i][j] = new TH2D(Form("hCrs_EtotVsEtop_NoVETO_%i_%i", i, j), Form("hCrs_EtotVsEtop_NoVETO_%i_%i; Etot [MeV]; Etop [MeV]", i, j), Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
			hCrs_XYseed_NoVETO[i][j] = new TH2D(Form("hCrs_XYseed_NoVETO_%i_%i", i, j), Form("hCrs_XYseed_NoVETO_%i_%i; X; Y", i, j), 11, -5.5, 5.5, 11, -5.5, 5.5);
			hCrs_XY_XYseed_NoVETO[i][j] = new TH2D(Form("hCrs_XY_XYseed_NoVETO_%i_%i", i, j), Form("hCrs_XY_XYseed_NoVETO_%i_%i; X-Xseed; Y-Yseed", i, j), 11, -5.5, 5.5, 11, -5.5, 5.5);
			hCrs_EseedVSEtot_NoVETO[i][j] = new TH2D(Form("hCrs_EseedVSEtot_NoVETO_%i_%i", i, j), Form("hCrs_EseedVSEtot_NoVETO_%i_%i; Eseed [MeV]; Etot [MeV]", i, j), Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
			hCrs_EseedVSMulti_NoVETO[i][j] = new TH2D(Form("hCrs_EseedVSMulti_NoVETO_%i_%i", i, j), Form("hCrs_EseedVSMulti_NoVETO_%i_%i; Eseed [MeV]; Multiplicity", i, j), Nbin_Etot, min_Etot, max_Etot, 45, -0.5, 44.5);
			hCrs_EtotVSMulti_NoVETO[i][j] = new TH2D(Form("hCrs_EtotVSMulti_NoVETO_%i_%i", i, j), Form("hCrs_EtotVSMulti_NoVETO_%i_%i; Etot [MeV]; Multiplicity", i, j), Nbin_Etot, min_Etot, max_Etot, 45, -0.5, 44.5);
			hCrs_EtopEbotVsEtot_NoVETO[i][j] = new TH2D(Form("hCrs_EtopEbotVsEtot_NoVETO_%i_%i", i, j), Form("hCrs_EtopEbotVsEtot_NoVETO_%i_%i; Etop-Ebot/Etot; Etot [MeV]", i, j), 300, -1.5, 1.5, Nbin_Etot, min_Etot, max_Etot);
			hCrs_EtopEbotVsEseed_NoVETO[i][j] = new TH2D(Form("hCrs_EtopEbotVsEseed_NoVETO_%i_%i", i, j), Form("hCrs_EtopEbotVsEseed_NoVETO_%i_%i; Etop-Ebot/Etot; Eseed [MeV]", i, j), 300, -1.5, 1.5, Nbin_Etot, min_Etot, max_Etot);
			hCrs_Eseed_CutEasym_NoVETO[i][j] = new TH1D(Form("hCrs_Eseed_CutEasym_NoVETO_%i_%i", i, j), Form("hCrs_Eseed_CutEasym_NoVETO_%i_%i; Eseed [MeV]; Hz/MeV", i, j), Nbin_Etot, min_Etot, max_Etot);
		}
	}

	/*A.C. this is the "flat" ttree that we are using for output*/
	tOut = new TTree("tOut", "tOut");
	tOut->Branch("EventType", &EventType_tout);
	tOut->Branch("Multiplicity", &Multiplicity_tout);
	tOut->Branch("Weight", &Weight_tout);
	tOut->Branch("Etot", &Etot_tout);
	tOut->Branch("Eseed", &Eseed_tout);

	fOutput->Add(tOut);

	if (!isPROD) {
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
	}

	Info("SlaveBegin", "end");
}

Bool_t BDXDSTSelector1::Process(Long64_t entry) {
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

	//Andrea: entry==0 is probably wrong. Skip it.
	if (entry == 0) return kFALSE;

	this->GetEntry(entry);
	isGarbage = false;
	isCosmic = false;
	isBeam = false;

	// veto variables

	OV_A_max = 0;
	OV_T_max = 0;
	OV_max = 0;

	IV_A_max = 0;
	IV_T_max = 0;
	IV_max = 0;

	double OV_th = 3.5;    //threshold on Amplitude for OV
	double IV_th = 2.5;   //threshold on Amplitude for IV
	int INDEX_VETO = 0;   // O = No OV, 1 = NO IV, 2 = NO OV && NO IV

	double IVAtot = 0;
	double OVAtot = 0;

	int multiplicity_OV = 0;
	int multiplicity_IV = 0;

	bool OV = false;
	bool IV = false;

	//VETO  Variables //
	for (int i = 0; i < 11; i++) {
		QOV[i] = -10;
		QIV[i] = -10;
		TOV[i] = -10;
		TIV[i] = -10;
	}

	//variables CRS
	for (int i = 0; i < 45; i++) {
		Ecrs[i] = -10;
		Tcrs[i] = -10;
		Acrs[i] = -10;
	}

	///CRS  Variables ///
//	double E_singleCrs_thr = 4; //minima energia misurabile
	double Etot = 0;
	double Etop = 0;
	double Ebottom = 0;
	Eseed = 0;
	double Ehit = 0;
	multip = 0;
	int Xseed = 0;
	int Yseed = 0;
	int Zseed = 0;
	double AsY = 0;

	/*Objects to read collections*/
	CalorimeterHit *fCaloHit;
	IntVetoHit *fIntVetoHit;
	GenParticle *fGenParticle;

	/*Get the event header and fill some variables*/
	m_EventHeader = m_Event->getEventHeader();
	eventNumber = m_EventHeader->getEventNumber();
	runNumber = m_EventHeader->getRunNumber();
	///WEIGHT///
	weight = m_EventHeader->getWeight();
	//	if(weight>0.01)	cout << "ERR WEIGHT!!: "<< weight << endl;

	N_event++;

	hNormalization->Fill(1.); //1->Total number of events
	hNormalization->Fill(2., weight); //2->Sum of weights

	thisEventT = m_Event->getEventHeader()->getEventTime() - T0;

	if (isMC == 0) {
		current = m_EventHeader->getEpicsData()->getDataValue("pcrexHallA_beam_current");

		if (hStatus_selector->GetBinContent(hStatus_selector->FindBin(thisEventT)) == -1) {
			isGarbage = true;
		}

		if (isGarbage == true) {
			hTrigAllEvents_rate_garbage->Fill(thisEventT);
			//	hHALLA_cur_garbage->Fill(thisEventT, current);
			m_Event->Clear("C");
			return kTRUE;
		}
	}

	if ((isGarbage == false) || (isMC == 1)) {

		if (isMC == 0 && current <= 0.03) {
			isCosmic = true;
			//	hHALLA_cur_cosmic->Fill(thisEventT, current);
			INDEX = 0;
		}

		if (isMC == 0 && current > 0.03) {
			isBeam = true;
			//	hHALLA_cur_beam->Fill(thisEventT, current);
			INDEX = 1;
		}

		if (isMC == 1) INDEX = 2;

		if (INDEX == 1) {
			m_Event->Clear("C");
			return kTRUE;  // it has to be commented if you want save the beam on data
		}

		/*Check if the event has a collection named IntVetoHits and the corresponding objects are IntVetoHit objects*/

		if (m_Event->hasCollection(IntVetoHit::Class(), "IntVetoHits")) {
			TIter IntVetoHitsIter(m_Event->getCollection(IntVetoHit::Class(), "IntVetoHits"));
			while (fIntVetoHit = (IntVetoHit*) IntVetoHitsIter.Next()) { //Need to cast to the proper object

				if (fIntVetoHit->m_channel.layer == 0 && fIntVetoHit->m_channel.component != 3) {
					QOV[fIntVetoHit->m_channel.component] = fIntVetoHit->A;
					TOV[fIntVetoHit->m_channel.component] = fIntVetoHit->T;
					OVAtot += fIntVetoHit->A;

					if (fIntVetoHit->A > OV_A_max) {
						OV_A_max = fIntVetoHit->A;
						OV_T_max = fIntVetoHit->T;
						OV_max = fIntVetoHit->m_channel.component;
					}

				}

				if (fIntVetoHit->m_channel.layer == 1) {
					QIV[fIntVetoHit->m_channel.component] = fIntVetoHit->A;
					TIV[fIntVetoHit->m_channel.component] = fIntVetoHit->T;
					IVAtot += fIntVetoHit->A;
					if (fIntVetoHit->A > IV_A_max) {
						IV_A_max = fIntVetoHit->A;
						IV_T_max = fIntVetoHit->T;
						IV_max = fIntVetoHit->m_channel.component;
					}

				}
			}
		}

		/*See if the other counters are in coincidence with OV_max*/

		if (OV_A_max > OV_th) {
			multiplicity_OV = 1;

			for (int i = 1; i <= 10; i++) {

				if (i != OV_max && QOV[i] > OV_th && abs(TOV[i] - OV_T_max) < 100) multiplicity_OV = multiplicity_OV + 1;
			}
		}

		/*See if the other counters are in coincidence with IV_max*/

		if (IV_A_max > IV_th) {
			multiplicity_IV = 1;

			for (int i = 1; i <= 10; i++) {

				if (i != IV_max && QIV[i] > IV_th && abs(TIV[i] - IV_T_max) < 100) multiplicity_IV = multiplicity_IV + 1;
			}
		}

		/* Inner Veto event */
		if ((multiplicity_IV == 1 && IV_A_max > 5.5) || multiplicity_IV > 1) IV = true;
		/* Outer Veto event */
		if ((multiplicity_OV == 1 && OV_A_max > 6.5) || multiplicity_OV > 1) OV = true;

		//cout << weight<<endl;
		//HISTO VETO

		hOV_Atot[INDEX]->Fill(OVAtot, weight);
		hOV_multiplicity[INDEX]->Fill(multiplicity_OV, weight);
		hIV_Atot[INDEX]->Fill(IVAtot, weight);
		hIV_multiplicity[INDEX]->Fill(multiplicity_IV, weight);
		hOV_Atot_vs_multiplicity[INDEX]->Fill(OVAtot, multiplicity_OV, weight);
		hIV_Atot_vs_multiplicity[INDEX]->Fill(IVAtot, multiplicity_IV, weight);

		int idx_crs_up = 0;
		int idx_crs_down = 0;

		if (m_Event->hasCollection(CalorimeterHit::Class(), "CalorimeterHits")) {
			TIter CaloHitsIter(m_Event->getCollection(CalorimeterHit::Class(), "CalorimeterHits"));
			//thisEventT = m_Event->getEventHeader()->getEventTime() - T0;

			while (fCaloHit = (CalorimeterHit*) CaloHitsIter.Next()) {
				if (fCaloHit->m_channel.sector == 0) {   // sono la parte up del calorimetro
					idx_crs_up = this->getCaloIDXFromXY(fCaloHit->m_channel.x, fCaloHit->m_channel.y);
					Ecrs[idx_crs_up] = fCaloHit->E;
					Tcrs[idx_crs_up] = fCaloHit->T;
					Acrs[idx_crs_up] = fCaloHit->A;
				}
				if (fCaloHit->m_channel.sector == 1) {   // sono la parte down del calorimetro
					idx_crs_down = (this->getCaloIDXFromXY(fCaloHit->m_channel.x, fCaloHit->m_channel.y)) + 22;
					Ecrs[idx_crs_down] = fCaloHit->E;
					Tcrs[idx_crs_down] = fCaloHit->T;
					Acrs[idx_crs_down] = fCaloHit->A;

				}

			}
		}
		int idx_crs = 0;

		/*Check if the event has a collection named CalorimeterHits, and the corresponding objects are CalorimeterHit objects*/
		if (m_Event->hasCollection(CalorimeterHit::Class(), "CalorimeterHits")) {
			TIter CaloHitsIter(m_Event->getCollection(CalorimeterHit::Class(), "CalorimeterHits"));
			//thisEventT = m_Event->getEventHeader()->getEventTime() - T0;

			while (fCaloHit = (CalorimeterHit*) CaloHitsIter.Next()) { //Need to cast to the proper object

				Ehit = 0;

				if (fCaloHit->m_channel.sector == 0) idx_crs = this->getCaloIDXFromXY(fCaloHit->m_channel.x, fCaloHit->m_channel.y);
				if (fCaloHit->m_channel.sector == 1) idx_crs = (this->getCaloIDXFromXY(fCaloHit->m_channel.x, fCaloHit->m_channel.y)) + 22;
				//MINIMUM ENERGY PER CRS //
				if (fCaloHit->E > this->getCrystalThreshold(idx_crs)) {

					//Multiplicity//
					multip++;

					//Hit Energy//
					Ehit = (fCaloHit->E);

					// Total Energy
					Etot = Etot + Ehit;

					int sector = fCaloHit->m_channel.sector;

					// Top Energy
					if (fCaloHit->m_channel.sector == 0) Etop = Etop + Ehit;

					// Bottom Energy
					if (fCaloHit->m_channel.sector == 1) Ebottom = Ebottom + Ehit;

					// Eseed, Seed XY //
					if (Ehit > Eseed) {
						Eseed = Ehit;
						Xseed = fCaloHit->m_channel.x;
						Yseed = fCaloHit->m_channel.y;
						Zseed = fCaloHit->m_channel.sector;
					}
				}
			}
		}

		double Xs = 0;
		double Ys = 0;
		double Zs = 0;
		int flag = 0;

		if (m_Event->hasCollection(CalorimeterHit::Class(), "CalorimeterHits")) {
			TIter CaloHitsIter2(m_Event->getCollection(CalorimeterHit::Class(), "CalorimeterHits"));
			while (fCaloHit = (CalorimeterHit*) CaloHitsIter2.Next()) {

				if (fCaloHit->m_channel.sector == 0) idx_crs = this->getCaloIDXFromXY(fCaloHit->m_channel.x, fCaloHit->m_channel.y);
				if (fCaloHit->m_channel.sector == 1) idx_crs = (this->getCaloIDXFromXY(fCaloHit->m_channel.x, fCaloHit->m_channel.y)) + 22;
				//MINIMUM ENERGY PER CRS //
				if (fCaloHit->E > this->getCrystalThreshold(idx_crs)) {
					Xs = fCaloHit->m_channel.x - Xseed;
					Ys = fCaloHit->m_channel.y - Yseed;
					Zs = fCaloHit->m_channel.sector;

					if (Xs != 0 || Ys != 0) {
						hCrs_XY_XYseed[INDEX]->Fill(Xs, Ys, (weight));

						for (int j = 0; j < 3; j++) {
							if (j == 0) {
								if (OV == false) INDEX_VETO = 0;
								if (OV == true) continue;
							}

							if (j == 1) {
								if (IV == false) INDEX_VETO = 1;
								if (IV == true) continue;
							}

							if (j == 2) {
								if (IV == false && OV == false) {
									INDEX_VETO = 2;
								} else {
									continue;
								}
							}
							hCrs_XY_XYseed_NoVETO[INDEX][INDEX_VETO]->Fill(Xs, Ys, (weight));
						}
					}

					if (Zseed == Zs) {
						flag = 0;
					} else {
						flag = 1;
					}
				}
			}
		}

		if (Eseed > 0) {
			hCrs_Etot[INDEX]->Fill(Etot, weight);
			hCrs_multiplicity[INDEX]->Fill(multip, weight);
			//   hCrs_Eseed[INDEX]->Fill(Eseed, weight);
			hCrs_Eseed[INDEX]->Fill(Eseed);
			hCrs_Etop[INDEX]->Fill(Etop, weight);
			hCrs_Ebottom[INDEX]->Fill(Ebottom, weight);
			hCrs_R_EtopEtot[INDEX]->Fill(Etop / Etot, weight);
			hCrs_R_EbottomEtot[INDEX]->Fill(Ebottom / Etot, weight);
			hCrs_EtotVsEtop[INDEX]->Fill(Etot, Etop, weight);
			hCrs_XYseed[INDEX]->Fill(Xseed, Yseed, weight);
			hCrs_EseedVSEtot[INDEX]->Fill(Eseed, Etot, weight);
			hCrs_EseedVSMulti[INDEX]->Fill(Eseed, multip, weight);
			hCrs_EtotVSMulti[INDEX]->Fill(Etot, multip, weight);
			hCrs_EtopEbotVsEtot[INDEX]->Fill((Etop - Ebottom) / Etot, Etot, weight);
			hCrs_EtopEbotVsEseed[INDEX]->Fill((Etop - Ebottom) / Etot, Eseed, weight);
			if (fabs((Etop - Ebottom) / Etot) < 0.8) hCrs_Eseed_CutEasym[INDEX]->Fill(Eseed, weight);
		}

		if (Eseed > 0) {
			INDEX_VETO=-1;
			for (int j = 0; j < 3; j++) {

				if (j == 0) {
					if (OV == false) INDEX_VETO = 0;
					if (OV == true) continue;
				}

				if (j == 1) {
					if (IV == false) INDEX_VETO = 1;
					if (IV == true) continue;
				}

				if (j == 2) {
					if (IV == false && OV == false) {
						INDEX_VETO = 2;
					} else {
						continue;
					}
				}
				hCrs_Etot_NoVETO[INDEX][INDEX_VETO]->Fill(Etot, weight);
				hCrs_multiplicity_NoVETO[INDEX][INDEX_VETO]->Fill(multip, weight);
				hCrs_Eseed_NoVETO[INDEX][INDEX_VETO]->Fill(Eseed, weight);
				hCrs_Etop_NoVETO[INDEX][INDEX_VETO]->Fill(Etop, weight);
				hCrs_Ebottom_NoVETO[INDEX][INDEX_VETO]->Fill(Ebottom, weight);
				hCrs_R_EtopEtot_NoVETO[INDEX][INDEX_VETO]->Fill(Etop / Etot, weight);
				hCrs_R_EbottomEtot_NoVETO[INDEX][INDEX_VETO]->Fill(Ebottom / Etot, weight);
				hCrs_EtotVsEtop_NoVETO[INDEX][INDEX_VETO]->Fill(Etot, Etop, weight);
				hCrs_XYseed_NoVETO[INDEX][INDEX_VETO]->Fill(Xseed, Yseed, weight);
				hCrs_EseedVSEtot_NoVETO[INDEX][INDEX_VETO]->Fill(Eseed, Etot, weight);
				hCrs_EseedVSMulti_NoVETO[INDEX][INDEX_VETO]->Fill(Eseed, multip, weight);
				hCrs_EtotVSMulti_NoVETO[INDEX][INDEX_VETO]->Fill(Etot, multip, weight);
				hCrs_EtopEbotVsEtot_NoVETO[INDEX][INDEX_VETO]->Fill((Etop - Ebottom) / Etot, Etot, weight);
				hCrs_EtopEbotVsEseed_NoVETO[INDEX][INDEX_VETO]->Fill((Etop - Ebottom) / Etot, Eseed, weight);
				if (fabs((Etop - Ebottom) / Etot) < 0.8) hCrs_Eseed_CutEasym_NoVETO[INDEX][INDEX_VETO]->Fill(Eseed, weight);
			}
		}

		/*A.C. This is where we fill the FLAT ttree for output in anticoincidence*/
		if (OV == false && IV == false && Etot > 10.) {
			EventType_tout = INDEX;
			Weight_tout = weight;
			Etot_tout = Etot;
			Eseed_tout = Eseed;
			Multiplicity_tout = multip;
			tOut->Fill();
		}

	} //end isGarbage==false || isMC==1

	//cout <<"end event"<<endl;
	m_Event->Clear("C");
	return kTRUE;
}

void BDXDSTSelector1::SlaveTerminate() {
// The SlaveTerminate() function is called after all entries or objects
// have been processed. When running with PROOF SlaveTerminate() is called
// on each slave server.

}

void BDXDSTSelector1::Terminate() {
	// The Terminate() function is the last function to be called during
	// a query. It always runs on the client, it can be used to present
	// the results graphically or save the results to file.

	Info("Terminate", "Terminate starts");
	Info("Terminate", "Total events are: %i", nEventsTotal);

	if (!isPROD) {
		TListIter iter(fOutput);
		TObject *obj;

		hTrigAllEvents_rate_garbage = (TH1D*) fOutput->FindObject("hTrigAllEvents_rate_garbage");

		//HISTO VETO
		for (int i = 0; i < 3; i++) {
			// if(i!=1){
			hOV_Atot[i] = (TH1D*) fOutput->FindObject(Form("hOV_Atot_%i", i));
			hOV_multiplicity[i] = (TH1D*) fOutput->FindObject(Form("hOV_multiplicity_%i", i));
			hIV_Atot[i] = (TH1D*) fOutput->FindObject(Form("hIV_Atot_%i", i));
			hIV_multiplicity[i] = (TH1D*) fOutput->FindObject(Form("hIV_multiplicity_%i", i));
			hOV_Atot_vs_multiplicity[i] = (TH2D*) fOutput->FindObject(Form("hOV_Atot_vs_multiplicity_%i", i));
			hIV_Atot_vs_multiplicity[i] = (TH2D*) fOutput->FindObject(Form("hIV_Atot_vs_multiplicity_%i", i));

			// HISTO CALORIMETER
			hCrs_Etot[i] = (TH1D*) fOutput->FindObject(Form("hCrs_Etot_%i", i));
			hCrs_multiplicity[i] = (TH1D*) fOutput->FindObject(Form("hCrs_multiplicity_%i", i));
			hCrs_Eseed[i] = (TH1D*) fOutput->FindObject(Form("hCrs_Eseed_%i", i));
			hCrs_Etop[i] = (TH1D*) fOutput->FindObject(Form("hCrs_Etop_%i", i));
			hCrs_Ebottom[i] = (TH1D*) fOutput->FindObject(Form("hCrs_Ebottom_%i", i));
			hCrs_R_EtopEtot[i] = (TH1D*) fOutput->FindObject(Form("hCrs_R_EtopEtot_%i", i));
			hCrs_R_EbottomEtot[i] = (TH1D*) fOutput->FindObject(Form("hCrs_R_EbottomEtot_%i", i));
			hCrs_EtotVsEtop[i] = (TH2D*) fOutput->FindObject(Form("hCrs_EtotVsEtop_%i", i));
			hCrs_XYseed[i] = (TH2D*) fOutput->FindObject(Form("hCrs_XYseed_%i", i));
			hCrs_XY_XYseed[i] = (TH2D*) fOutput->FindObject(Form("hCrs_XY_XYseed_%i", i));
			hCrs_EseedVSEtot[i] = (TH2D*) fOutput->FindObject(Form("hCrs_EseedVSEtot_%i", i));
			hCrs_EseedVSMulti[i] = (TH2D*) fOutput->FindObject(Form("hCrs_EseedVSMulti_%i", i));
			hCrs_EtotVSMulti[i] = (TH2D*) fOutput->FindObject(Form("hCrs_EtotVSMulti_%i", i));
			hCrs_EtopEbotVsEtot[i] = (TH2D*) fOutput->FindObject(Form("hCrs_EtopEbotVsEtot_%i", i));
			hCrs_EtopEbotVsEseed[i] = (TH2D*) fOutput->FindObject(Form("hCrs_EtopEbotVsEseed_%i", i));
			hCrs_Eseed_CutEasym[i] = (TH1D*) fOutput->FindObject(Form("hCrs_Eseed_CutEasym_%i", i));

			for (int j = 0; j < 3; j++) {
				hCrs_Etot_NoVETO[i][j] = (TH1D*) fOutput->FindObject(Form("hCrs_Etot_NoVETO_%i_%i", i, j));
				hCrs_multiplicity_NoVETO[i][j] = (TH1D*) fOutput->FindObject(Form("hCrs_multiplicity_NoVETO_%i_%i", i, j));
				hCrs_Eseed_NoVETO[i][j] = (TH1D*) fOutput->FindObject(Form("hCrs_Eseed_NoVETO_%i_%i", i, j));
				hCrs_Etop_NoVETO[i][j] = (TH1D*) fOutput->FindObject(Form("hCrs_Etop_NoVETO_%i_%i", i, j));
				hCrs_Ebottom_NoVETO[i][j] = (TH1D*) fOutput->FindObject(Form("hCrs_Ebottom_NoVETO_%i_%i", i, j));
				hCrs_R_EtopEtot_NoVETO[i][j] = (TH1D*) fOutput->FindObject(Form("hCrs_R_EtopEtot_NoVETO_%i_%i", i, j));
				hCrs_R_EbottomEtot_NoVETO[i][j] = (TH1D*) fOutput->FindObject(Form("hCrs_R_EbottomEtot_NoVETO_%i_%i", i, j));
				hCrs_EtotVsEtop_NoVETO[i][j] = (TH2D*) fOutput->FindObject(Form("hCrs_EtotVsEtop_NoVETO_%i_%i", i, j));
				hCrs_XYseed_NoVETO[i][j] = (TH2D*) fOutput->FindObject(Form("hCrs_XYseed_NoVETO_%i_%i", i, j));
				hCrs_XY_XYseed_NoVETO[i][j] = (TH2D*) fOutput->FindObject(Form("hCrs_XY_XYseed_NoVETO_%i_%i", i, j));
				hCrs_EseedVSEtot_NoVETO[i][j] = (TH2D*) fOutput->FindObject(Form("hCrs_EseedVSEtot_NoVETO_%i_%i", i, j));
				hCrs_EseedVSMulti_NoVETO[i][j] = (TH2D*) fOutput->FindObject(Form("hCrs_EseedVSMulti_NoVETO_%i_%i", i, j));
				hCrs_EtotVSMulti_NoVETO[i][j] = (TH2D*) fOutput->FindObject(Form("hCrs_EtotVSMulti_NoVETO_%i_%i", i, j));
				hCrs_EtopEbotVsEtot_NoVETO[i][j] = (TH2D*) fOutput->FindObject(Form("hCrs_EtopEbotVsEtot_NoVETO_%i_%i", i, j));
				hCrs_EtopEbotVsEseed_NoVETO[i][j] = (TH2D*) fOutput->FindObject(Form("hCrs_EtopEbotVsEseed_NoVETO_%i_%i", i, j));
				hCrs_Eseed_CutEasym_NoVETO[i][j] = (TH1D*) fOutput->FindObject(Form("hCrs_Eseed_CutEasym_NoVETO_%i_%i", i, j));
			}
		}

		while (obj = iter.Next()) {
			Info("Terminate", "obj: %s", obj->GetName());
		}
	}
	Info("Terminate", "No more objs");

	cout << "*********" << endl;
	cout << eventNumber << endl;

}

