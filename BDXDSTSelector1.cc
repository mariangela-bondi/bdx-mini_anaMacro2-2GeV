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

	if (option.Contains("MC") == true) {
		isMC = 1;
	}

	if (option.Contains("Tree") == true) {
		doTree = 1;
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

	doTree = 0;

	if (option.Contains("MC") == true) {
		isMC = 1;
	}
	if (option.Contains("Tree") == true) {
		doTree = 1;
	}

	/*Create here the histograms.*/
	hTrigAllEvents_rate_garbage = new TH1D("hTrigAllEvents_rate_garbage", "hTrigAllEvents_rate_garbage;T(s);Rate(Hz)",N,0,N * dT);

	hHALLA_cur_beam = new TH2D("hHALLA_cur_beam", "hHALLA_cur_beam;T(s);Current(uA)", N, 0, N * dT, 100, -0.05, 200.05);
	hHALLA_cur_cosmic = new TH2D("hHALLA_cur_cosmic", "hHALLA_cur_cosmic;T(s);Current(uA)", N, 0, N * dT, 100, -0.05, 200.05);
	hHALLA_cur_garbage = new TH2D("hHALLA_cur_garbage", "hHALLA_cur_garbage;T(s);Current(uA)",N, 0, N * dT, 100, -0.05, 200.05);
//	hTlive = new TH2D("hTlive", "hTlive;T(s);Live Time(%)", N, 0, N * dT, 100, 0, 100.);


	// HISTO VETO
	int Nbin_Atot = 2000;
	int min_Atot =-0.5;
	int max_Atot = 2000.5;

	// HISTO CALORIMETER

	int Nbin_Etot = 3000;
	int min_Etot =-0.5;
	int max_Etot = 2999.5;


   for(int i=0; i<3; i++){
    hOV_Atot[i] = new TH1D(Form("hOV_Atot_%i",i), Form("hOV_Atot_%i; phe;Counts",i), Nbin_Atot, min_Atot, max_Atot);
    hOV_multiplicity[i] = new TH1D(Form("hOV_multiplicity_%i",i), Form("hOV_multiplicity_%i; multiplicity;Counts",i), 11,-0.5,10.5);
	hIV_Atot[i] = new TH1D(Form("hIV_Atot_%i",i), Form("hIV_Atot_%i; phe;Counts",i), Nbin_Atot, min_Atot, max_Atot);
	hIV_multiplicity[i] = new TH1D(Form("hIV_multiplicity_%i",i), Form("hIV_multiplicity_%i; multiplicity;Counts",i), 11,-0.5,10.5);
	hOV_Atot_vs_multiplicity[i] = new TH2D(Form("hOV_Atot_vs_multiplicity_%i",i), Form("hOV_Atot_vs_multiplicity_%i; phe;multiplicity",i), Nbin_Atot, min_Atot, max_Atot, 11,-0.5,10.5);
	hIV_Atot_vs_multiplicity[i] = new TH2D(Form("hIV_Atot_vs_multiplicity_%i",i), Form("hIV_Atot_vs_multiplicity_%i; phe;multiplicity",i), Nbin_Atot, min_Atot, max_Atot, 11,-0.5,10.5);


	// HISTO CALORIMETER

	hCrs_Etot[i] = new TH1D(Form("hCrs_Etot_%i",i), Form("hCrs_Etot_%i; Etot [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_multiplicity[i] = new TH1D(Form("hCrs_multiplicity_%i",i), Form("hCrs_multiplicity_%i; multiplicity; counts",i), 45, -0.5, 44.5);
	hCrs_Eseed[i] = new TH1D(Form("hCrs_Eseed_%i",i), Form("hCrs_Eseed_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Etop[i] = new TH1D(Form("hCrs_Etop_%i",i), Form("hCrs_Etop_%i; Etop [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Ebottom[i] = new TH1D(Form("hCrs_Ebottom_%i",i), Form("hCrs_Ebottom_%i; Ebottom [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_R_EtopEtot[i] = new TH1D(Form("hCrs_R_EtopEtot_%i",i), Form("hCrs_R_EtopEtot_%i; Etop/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_R_EbottomEtot[i] = new TH1D(Form("hCrs_R_EbottomEtot_%i",i), Form("hCrs_R_EbottomEtot_%i; Ebottom/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_EtotVsEtop[i] = new TH2D(Form("hCrs_EtotVsEtop_%i",i),Form("hCrs_EtotVsEtop_%i; Etot [MeV]; Etop [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_XYseed[i] = new TH2D(Form("hCrs_XYseed_%i",i),Form("hCrs_XYseed_%i; X; Y",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_XY_XYseed[i] = new TH2D(Form("hCrs_XY_XYseed_%i",i),Form("hCrs_XY_XYseed_%i; X-Xseed; Y-Yseed",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_EseedVSEtot[i] = new TH2D(Form("hCrs_EseedVSEtot_%i",i),Form("hCrs_EseedVSEtot_%i; Eseed [MeV]; Etot [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EseedVSMulti[i] = new TH2D(Form("hCrs_EseedVSMulti_%i",i),Form("hCrs_EseedVSMulti_%i; Eseed [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtotVSMulti[i] = new TH2D(Form("hCrs_EtotVSMulti_%i",i),Form("hCrs_EtotVSMulti_%i; Etot [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtopEbotVsEtot[i] = new TH2D(Form("hCrs_EtopEbotVsEtot_%i",i),Form("hCrs_EtopEbotVsEtot_%i; Etop-Ebot/Etot; Etot [MeV]",i),300, -1.5, 1.5, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EtopEbotVsEseed[i] = new TH2D(Form("hCrs_EtopEbotVsEseed_%i",i),Form("hCrs_EtopEbotVsEseed_%i; Etop-Ebot/Etot; Eseed [MeV]",i),300, -1.5, 1.5, Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_CutEasym[i] = new TH1D(Form("hCrs_Eseed_CutEasym_%i",i), Form("hCrs_Eseed_CutEasym_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);



	hCrs_Etot_NoVETO[i] = new TH1D(Form("hCrs_Etot_NoVETO_%i",i), Form("hCrs_Etot_NoVETO_%i; Etot [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_multiplicity_NoVETO[i] = new TH1D(Form("hCrs_multiplicity_NoVETO_%i",i), Form("hCrs_multiplicity_NoVETO_%i; multiplicity; counts",i), 45, -0.5, 44.5);
	hCrs_Eseed_NoVETO[i] = new TH1D(Form("hCrs_Eseed_NoVETO_%i",i), Form("hCrs_Eseed_NoVETO_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Etop_NoVETO[i] = new TH1D(Form("hCrs_Etop_NoVETO_%i",i), Form("hCrs_Etop_NoVETO_%i; Etop [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Ebottom_NoVETO[i] = new TH1D(Form("hCrs_Ebottom_NoVETO_%i",i), Form("hCrs_Ebottom_NoVETO_%i; Ebottom [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_R_EtopEtot_NoVETO[i] = new TH1D(Form("hCrs_R_EtopEtot_NoVETO_%i",i), Form("hCrs_R_EtopEtot_NoVETO_%i; Etop/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_R_EbottomEtot_NoVETO[i] = new TH1D(Form("hCrs_R_EbottomEtot_NoVETO_%i",i), Form("hCrs_R_EbottomEtot_NoVETO_%i; Ebottom/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_EtotVsEtop_NoVETO[i] = new TH2D(Form("hCrs_EtotVsEtop_NoVETO_%i",i),Form("hCrs_EtotVsEtop_NoVETO_%i; Etot [MeV]; Etop [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_XYseed_NoVETO[i] = new TH2D(Form("hCrs_XYseed_NoVETO_%i",i),Form("hCrs_XYseed_NoVETO_%i; X; Y",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_XY_XYseed_NoVETO[i] = new TH2D(Form("hCrs_XY_XYseed_NoVETO_%i",i),Form("hCrs_XY_XYseed_NoVETO_%i; X-Xseed; Y-Yseed",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_EseedVSEtot_NoVETO[i] = new TH2D(Form("hCrs_EseedVSEtot_NoVETO_%i",i),Form("hCrs_EseedVSEtot_NoVETO_%i; Eseed [MeV]; Etot [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EseedVSMulti_NoVETO[i] = new TH2D(Form("hCrs_EseedVSMulti_NoVETO_%i",i),Form("hCrs_EseedVSMulti_NoVETO_%i; Eseed [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtotVSMulti_NoVETO[i] = new TH2D(Form("hCrs_EtotVSMulti_NoVETO_%i",i),Form("hCrs_EtotVSMulti_NoVETO_%i; Etot [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);



	hCrs_Etot_noIVc1[i] = new TH1D(Form("hCrs_Etot_noIVc1_%i",i), Form("hCrs_Etot_noIVc1_%i; Etot [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_multiplicity_noIVc1[i] = new TH1D(Form("hCrs_multiplicity_noIVc1_%i",i), Form("hCrs_multiplicity_noIVc1_%i; multiplicity; counts",i), 45, -0.5, 44.5);
	//hCrs_Eseed_noIVc1[i] = new TH1D(Form("hCrs_Eseed_noIVc1_%i",i), Form("hCrs_Eseed_noIVc1_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Etop_noIVc1[i] = new TH1D(Form("hCrs_Etop_noIVc1_%i",i), Form("hCrs_Etop_noIVc1_%i; Etop [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Ebottom_noIVc1[i] = new TH1D(Form("hCrs_Ebottom_noIVc1_%i",i), Form("hCrs_Ebottom_noIVc1_%i; Ebottom [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_R_EtopEtot_noIVc1[i] = new TH1D(Form("hCrs_R_EtopEtot_noIVc1_%i",i), Form("hCrs_R_EtopEtot_noIVc1_%i; Etop/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_R_EbottomEtot_noIVc1[i] = new TH1D(Form("hCrs_R_EbottomEtot_noIVc1_%i",i), Form("hCrs_R_EbottomEtot_noIVc1_%i; Ebottom/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_EtotVsEtop_noIVc1[i] = new TH2D(Form("hCrs_EtotVsEtop_noIVc1_%i",i),Form("hCrs_EtotVsEtop_noIVc1_%i; Etot [MeV]; Etop [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_XYseed_noIVc1[i] = new TH2D(Form("hCrs_XYseed_noIVc1_%i",i),Form("hCrs_XYseed_noIVc1_%i; X; Y",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_XY_XYseed_noIVc1[i] = new TH2D(Form("hCrs_XY_XYseed_noIVc1_%i",i),Form("hCrs_XY_XYseed_noIVc1_%i; X-Xseed; Y-Yseed",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_EseedVSEtot_noIVc1[i] = new TH2D(Form("hCrs_EseedVSEtot_noIVc1_%i",i),Form("hCrs_EseedVSEtot_noIVc1_%i; Eseed [MeV]; Etot [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EseedVSMulti_noIVc1[i] = new TH2D(Form("hCrs_EseedVSMulti_noIVc1_%i",i),Form("hCrs_EseedVSMulti_noIVc1_%i; Eseed [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtotVSMulti_noIVc1[i] = new TH2D(Form("hCrs_EtotVSMulti_noIVc1_%i",i),Form("hCrs_EtotVSMulti_noIVc1_%i; Etot [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);

	hCrs_Etot_noIVc2[i] = new TH1D(Form("hCrs_Etot_noIVc2_%i",i), Form("hCrs_Etot_noIVc2_%i; Etot [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_multiplicity_noIVc2[i] = new TH1D(Form("hCrs_multiplicity_noIVc2_%i",i), Form("hCrs_multiplicity_noIVc2_%i; multiplicity; counts",i), 45, -0.5, 44.5);
	//hCrs_Eseed_noIVc2[i] = new TH1D(Form("hCrs_Eseed_noIVc2_%i",i), Form("hCrs_Eseed_noIVc2_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Etop_noIVc2[i] = new TH1D(Form("hCrs_Etop_noIVc2_%i",i), Form("hCrs_Etop_noIVc2_%i; Etop [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Ebottom_noIVc2[i] = new TH1D(Form("hCrs_Ebottom_noIVc2_%i",i), Form("hCrs_Ebottom_noIVc2_%i; Ebottom [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_R_EtopEtot_noIVc2[i] = new TH1D(Form("hCrs_R_EtopEtot_noIVc2_%i",i), Form("hCrs_R_EtopEtot_noIVc2_%i; Etop/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_R_EbottomEtot_noIVc2[i] = new TH1D(Form("hCrs_R_EbottomEtot_noIVc2_%i",i), Form("hCrs_R_EbottomEtot_noIVc2_%i; Ebottom/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_EtotVsEtop_noIVc2[i] = new TH2D(Form("hCrs_EtotVsEtop_noIVc2_%i",i),Form("hCrs_EtotVsEtop_noIVc2_%i; Etot [MeV]; Etop [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_XYseed_noIVc2[i] = new TH2D(Form("hCrs_XYseed_noIVc2_%i",i),Form("hCrs_XYseed_noIVc2_%i; X; Y",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_XY_XYseed_noIVc2[i] = new TH2D(Form("hCrs_XY_XYseed_noIVc2_%i",i),Form("hCrs_XY_XYseed_noIVc2_%i; X-Xseed; Y-Yseed",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_EseedVSEtot_noIVc2[i] = new TH2D(Form("hCrs_EseedVSEtot_noIVc2_%i",i),Form("hCrs_EseedVSEtot_noIVc2_%i; Eseed [MeV]; Etot [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EseedVSMulti_noIVc2[i] = new TH2D(Form("hCrs_EseedVSMulti_noIVc2_%i",i),Form("hCrs_EseedVSMulti_noIVc2_%i; Eseed [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtotVSMulti_noIVc2[i] = new TH2D(Form("hCrs_EtotVSMulti_noIVc2_%i",i),Form("hCrs_EtotVSMulti_noIVc2_%i; Etot [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);

	hCrs_Etot_noIVc5[i] = new TH1D(Form("hCrs_Etot_noIVc5_%i",i), Form("hCrs_Etot_noIVc5_%i; Etot [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_multiplicity_noIVc5[i] = new TH1D(Form("hCrs_multiplicity_noIVc5_%i",i), Form("hCrs_multiplicity_noIVc5_%i; multiplicity; counts",i), 45, -0.5, 44.5);
	//hCrs_Eseed_noIVc5[i] = new TH1D(Form("hCrs_Eseed_noIVc5_%i",i), Form("hCrs_Eseed_noIVc5_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Etop_noIVc5[i] = new TH1D(Form("hCrs_Etop_noIVc5_%i",i), Form("hCrs_Etop_noIVc5_%i; Etop [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Ebottom_noIVc5[i] = new TH1D(Form("hCrs_Ebottom_noIVc5_%i",i), Form("hCrs_Ebottom_noIVc5_%i; Ebottom [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_R_EtopEtot_noIVc5[i] = new TH1D(Form("hCrs_R_EtopEtot_noIVc5_%i",i), Form("hCrs_R_EtopEtot_noIVc5_%i; Etop/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_R_EbottomEtot_noIVc5[i] = new TH1D(Form("hCrs_R_EbottomEtot_noIVc5_%i",i), Form("hCrs_R_EbottomEtot_noIVc5_%i; Ebottom/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_EtotVsEtop_noIVc5[i] = new TH2D(Form("hCrs_EtotVsEtop_noIVc5_%i",i),Form("hCrs_EtotVsEtop_noIVc5_%i; Etot [MeV]; Etop [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_XYseed_noIVc5[i] = new TH2D(Form("hCrs_XYseed_noIVc5_%i",i),Form("hCrs_XYseed_noIVc5_%i; X; Y",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_XY_XYseed_noIVc5[i] = new TH2D(Form("hCrs_XY_XYseed_noIVc5_%i",i),Form("hCrs_XY_XYseed_noIVc5_%i; X-Xseed; Y-Yseed",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_EseedVSEtot_noIVc5[i] = new TH2D(Form("hCrs_EseedVSEtot_noIVc5_%i",i),Form("hCrs_EseedVSEtot_noIVc5_%i; Eseed [MeV]; Etot [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EseedVSMulti_noIVc5[i] = new TH2D(Form("hCrs_EseedVSMulti_noIVc5_%i",i),Form("hCrs_EseedVSMulti_noIVc5_%i; Eseed [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtotVSMulti_noIVc5[i] = new TH2D(Form("hCrs_EtotVSMulti_noIVc5_%i",i),Form("hCrs_EtotVSMulti_noIVc5_%i; Etot [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtopEbotVsEtot_noIVc5[i] = new TH2D(Form("hCrs_EtopEbotVsEtot_noIVc5_%i",i),Form("hCrs_EtopEbotVsEtot_noIVc5_%i; Etop-Ebot/Etot; Etot [MeV]",i),300, -1.5, 1.5, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EtopEbotVsEseed_noIVc5[i] = new TH2D(Form("hCrs_EtopEbotVsEseed_noIVc5_%i",i),Form("hCrs_EtopEbotVsEseed_noIVc5_%i; Etop-Ebot/Etot; Eseed [MeV]",i),300, -1.5, 1.5, Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_CutEasym_noIVc5[i] = new TH1D(Form("hCrs_Eseed_CutEasym_noIVc5_%i",i), Form("hCrs_Eseed_CutEasym_noIVc5_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);


	hCrs_Etot_noOVc1[i] = new TH1D(Form("hCrs_Etot_noOVc1_%i",i), Form("hCrs_Etot_noOVc1_%i; Etot [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_multiplicity_noOVc1[i] = new TH1D(Form("hCrs_multiplicity_noOVc1_%i",i), Form("hCrs_multiplicity_noOVc1_%i; multiplicity; counts",i), 45, -0.5, 44.5);
	//hCrs_Eseed_noOVc1[i] = new TH1D(Form("hCrs_Eseed_noOVc1_%i",i), Form("hCrs_Eseed_noOVc1_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Etop_noOVc1[i] = new TH1D(Form("hCrs_Etop_noOVc1_%i",i), Form("hCrs_Etop_noOVc1_%i; Etop [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Ebottom_noOVc1[i] = new TH1D(Form("hCrs_Ebottom_noOVc1_%i",i), Form("hCrs_Ebottom_noOVc1_%i; Ebottom [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_R_EtopEtot_noOVc1[i] = new TH1D(Form("hCrs_R_EtopEtot_noOVc1_%i",i), Form("hCrs_R_EtopEtot_noOVc1_%i; Etop/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_R_EbottomEtot_noOVc1[i] = new TH1D(Form("hCrs_R_EbottomEtot_noOVc1_%i",i), Form("hCrs_R_EbottomEtot_noOVc1_%i; Ebottom/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_EtotVsEtop_noOVc1[i] = new TH2D(Form("hCrs_EtotVsEtop_noOVc1_%i",i),Form("hCrs_EtotVsEtop_noOVc1_%i; Etot [MeV]; Etop [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_XYseed_noOVc1[i] = new TH2D(Form("hCrs_XYseed_noOVc1_%i",i),Form("hCrs_XYseed_noOVc1_%i; X; Y",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_XY_XYseed_noOVc1[i] = new TH2D(Form("hCrs_XY_XYseed_noOVc1_%i",i),Form("hCrs_XY_XYseed_noOVc1_%i; X-Xseed; Y-Yseed",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_EseedVSEtot_noOVc1[i] = new TH2D(Form("hCrs_EseedVSEtot_noOVc1_%i",i),Form("hCrs_EseedVSEtot_noOVc1_%i; Eseed [MeV]; Etot [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EseedVSMulti_noOVc1[i] = new TH2D(Form("hCrs_EseedVSMulti_noOVc1_%i",i),Form("hCrs_EseedVSMulti_noOVc1_%i; Eseed [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtotVSMulti_noOVc1[i] = new TH2D(Form("hCrs_EtotVSMulti_noOVc1_%i",i),Form("hCrs_EtotVSMulti_noOVc1_%i; Etot [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);

	hCrs_Etot_noOVc2[i] = new TH1D(Form("hCrs_Etot_noOVc2_%i",i), Form("hCrs_Etot_noOVc2_%i; Etot [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_multiplicity_noOVc2[i] = new TH1D(Form("hCrs_multiplicity_noOVc2_%i",i), Form("hCrs_multiplicity_noOVc2_%i; multiplicity; counts",i), 45, -0.5, 44.5);
	//hCrs_Eseed_noOVc2[i] = new TH1D(Form("hCrs_Eseed_noOVc2_%i",i), Form("hCrs_Eseed_noOVc2_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Etop_noOVc2[i] = new TH1D(Form("hCrs_Etop_noOVc2_%i",i), Form("hCrs_Etop_noOVc2_%i; Etop [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Ebottom_noOVc2[i] = new TH1D(Form("hCrs_Ebottom_noOVc2_%i",i), Form("hCrs_Ebottom_noOVc2_%i; Ebottom [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_R_EtopEtot_noOVc2[i] = new TH1D(Form("hCrs_R_EtopEtot_noOVc2_%i",i), Form("hCrs_R_EtopEtot_noOVc2_%i; Etop/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_R_EbottomEtot_noOVc2[i] = new TH1D(Form("hCrs_R_EbottomEtot_noOVc2_%i",i), Form("hCrs_R_EbottomEtot_noOVc2_%i; Ebottom/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_EtotVsEtop_noOVc2[i] = new TH2D(Form("hCrs_EtotVsEtop_noOVc2_%i",i),Form("hCrs_EtotVsEtop_noOVc2_%i; Etot [MeV]; Etop [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_XYseed_noOVc2[i] = new TH2D(Form("hCrs_XYseed_noOVc2_%i",i),Form("hCrs_XYseed_noOVc2_%i; X; Y",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_XY_XYseed_noOVc2[i] = new TH2D(Form("hCrs_XY_XYseed_noOVc2_%i",i),Form("hCrs_XY_XYseed_noOVc2_%i; X-Xseed; Y-Yseed",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_EseedVSEtot_noOVc2[i] = new TH2D(Form("hCrs_EseedVSEtot_noOVc2_%i",i),Form("hCrs_EseedVSEtot_noOVc2_%i; Eseed [MeV]; Etot [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EseedVSMulti_noOVc2[i] = new TH2D(Form("hCrs_EseedVSMulti_noOVc2_%i",i),Form("hCrs_EseedVSMulti_noOVc2_%i; Eseed [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtotVSMulti_noOVc2[i] = new TH2D(Form("hCrs_EtotVSMulti_noOVc2_%i",i),Form("hCrs_EtotVSMulti_noOVc2_%i; Etot [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);

	hCrs_Etot_noOVc5[i] = new TH1D(Form("hCrs_Etot_noOVc5_%i",i), Form("hCrs_Etot_noOVc5_%i; Etot [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_multiplicity_noOVc5[i] = new TH1D(Form("hCrs_multiplicity_noOVc5_%i",i), Form("hCrs_multiplicity_noOVc5_%i; multiplicity; counts",i), 45, -0.5, 44.5);
	//hCrs_Eseed_noOVc5[i] = new TH1D(Form("hCrs_Eseed_noOVc5_%i",i), Form("hCrs_Eseed_noOVc5_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Etop_noOVc5[i] = new TH1D(Form("hCrs_Etop_noOVc5_%i",i), Form("hCrs_Etop_noOVc5_%i; Etop [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Ebottom_noOVc5[i] = new TH1D(Form("hCrs_Ebottom_noOVc5_%i",i), Form("hCrs_Ebottom_noOVc5_%i; Ebottom [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_R_EtopEtot_noOVc5[i] = new TH1D(Form("hCrs_R_EtopEtot_noOVc5_%i",i), Form("hCrs_R_EtopEtot_noOVc5_%i; Etop/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_R_EbottomEtot_noOVc5[i] = new TH1D(Form("hCrs_R_EbottomEtot_noOVc5_%i",i), Form("hCrs_R_EbottomEtot_noOVc5_%i; Ebottom/Etot; counts",i), 110, -0.5, 1.5);
	hCrs_EtotVsEtop_noOVc5[i] = new TH2D(Form("hCrs_EtotVsEtop_noOVc5_%i",i),Form("hCrs_EtotVsEtop_noOVc5_%i; Etot [MeV]; Etop [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_XYseed_noOVc5[i] = new TH2D(Form("hCrs_XYseed_noOVc5_%i",i),Form("hCrs_XYseed_noOVc5_%i; X; Y",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_XY_XYseed_noOVc5[i] = new TH2D(Form("hCrs_XY_XYseed_noOVc5_%i",i),Form("hCrs_XY_XYseed_noOVc5_%i; X-Xseed; Y-Yseed",i),11,-5.5,5.5,11,-5.5,5.5);
	hCrs_EseedVSEtot_noOVc5[i] = new TH2D(Form("hCrs_EseedVSEtot_noOVc5_%i",i),Form("hCrs_EseedVSEtot_noOVc5_%i; Eseed [MeV]; Etot [MeV]",i),Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EseedVSMulti_noOVc5[i] = new TH2D(Form("hCrs_EseedVSMulti_noOVc5_%i",i),Form("hCrs_EseedVSMulti_noOVc5_%i; Eseed [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtotVSMulti_noOVc5[i] = new TH2D(Form("hCrs_EtotVSMulti_noOVc5_%i",i),Form("hCrs_EtotVSMulti_noOVc5_%i; Etot [MeV]; Multiplicity",i),Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtopEbotVsEtot_noOVc5[i] = new TH2D(Form("hCrs_EtopEbotVsEtot_noOVc5_%i",i),Form("hCrs_EtopEbotVsEtot_noOVc5_%i; Etop-Ebot/Etot; Etot [MeV]",i),300, -1.5, 1.5, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EtopEbotVsEseed_noOVc5[i] = new TH2D(Form("hCrs_EtopEbotVsEseed_noOVc5_%i",i),Form("hCrs_EtopEbotVsEseed_noOVc5_%i; Etop-Ebot/Etot; Eseed [MeV]",i),300, -1.5, 1.5, Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_CutEasym_noOVc5[i] = new TH1D(Form("hCrs_Eseed_CutEasym_noOVc5_%i",i), Form("hCrs_Eseed_CutEasym_noOVc5_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);



	hQIVmaxVSQIVtot_noIVc5[i] = new TH2D(Form("hQIVmaxVSQIVtot_noIVc5_%i",i),Form("hQIVmaxVSQIVtot_noIVc5_%i; QIVmax; IVtot",i),Nbin_Atot, min_Atot, max_Atot, Nbin_Atot, min_Atot, max_Atot);
	hQIVmaxVSQIVtot_noIVc5_Eseed_gr_100[i]=new TH2D(Form("hQIVmaxVSQIVtot_noIVc5_Eseed_gr_100_%i",i),Form("hQIVmaxVSQIVtot_noIVc5_Eseed_gr_100_%i; QIVmax; IVtot",i),Nbin_Atot, min_Atot, max_Atot, Nbin_Atot, min_Atot, max_Atot);



	hCrs_Etot_noVc5[i] = new TH1D(Form("hCrs_Etot_noVc5_%i",i), Form("hCrs_Etot_noVc5_%i; Etot [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_noVc5[i] = new TH1D(Form("hCrs_Eseed_noVc5_%i",i), Form("hCrs_Eseed_noVc5_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_EtopEbotVsEtot_noVc5[i] = new TH2D(Form("hCrs_EtopEbotVsEtot_noVc5_%i",i),Form("hCrs_EtopEbotVsEtot_noVc5_%i; Etop-Ebot/Etot; Etot [MeV]",i),300, -1.5, 1.5, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EtopEbotVsEseed_noVc5[i] = new TH2D(Form("hCrs_EtopEbotVsEseed_noVc5_%i",i),Form("hCrs_EtopEbotVsEseed_noVc5_%i; Etop-Ebot/Etot; Eseed [MeV]",i),300, -1.5, 1.5, Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_CutEasym_noVc5[i] = new TH1D(Form("hCrs_Eseed_CutEasym_noVc5_%i",i), Form("hCrs_Eseed_CutEasym_noVc5_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);


	hCrs_Eseed_IVc1[i] = new TH1D(Form("hCrs_Eseed_IVc1_%i",i), Form("hCrs_Eseed_IVc1_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_IVc2[i] = new TH1D(Form("hCrs_Eseed_IVc2_%i",i), Form("hCrs_Eseed_IVc2_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_IVc3[i] = new TH1D(Form("hCrs_Eseed_IVc3_%i",i), Form("hCrs_Eseed_IVc3_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_IVc4[i] = new TH1D(Form("hCrs_Eseed_IVc4_%i",i), Form("hCrs_Eseed_IVc4_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_IVc5[i] = new TH1D(Form("hCrs_Eseed_IVc5_%i",i), Form("hCrs_Eseed_IVc5_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);

	hCrs_Eseed_NoIVc1[i] = new TH1D(Form("hCrs_Eseed_NoIVc1_%i",i), Form("hCrs_Eseed_NoIVc1_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_NoIVc2[i] = new TH1D(Form("hCrs_Eseed_NoIVc2_%i",i), Form("hCrs_Eseed_NoIVc2_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_NoIVc3[i] = new TH1D(Form("hCrs_Eseed_NoIVc3_%i",i), Form("hCrs_Eseed_NoIVc3_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_NoIVc4[i] = new TH1D(Form("hCrs_Eseed_NoIVc4_%i",i), Form("hCrs_Eseed_NoIVc4_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_NoIVc5[i] = new TH1D(Form("hCrs_Eseed_NoIVc5_%i",i), Form("hCrs_Eseed_NoIVc5_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);

	hCrs_Eseed_NoOVc1[i] = new TH1D(Form("hCrs_Eseed_NoOVc1_%i",i), Form("hCrs_Eseed_NoOVc1_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_NoOVc2[i] = new TH1D(Form("hCrs_Eseed_NoOVc2_%i",i), Form("hCrs_Eseed_NoOVc2_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_NoOVc3[i] = new TH1D(Form("hCrs_Eseed_NoOVc3_%i",i), Form("hCrs_Eseed_NoOVc3_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_NoOVc4[i] = new TH1D(Form("hCrs_Eseed_NoOVc4_%i",i), Form("hCrs_Eseed_NoOVc4_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);
	hCrs_Eseed_NoOVc5[i] = new TH1D(Form("hCrs_Eseed_NoOVc5_%i",i), Form("hCrs_Eseed_NoOVc5_%i; Eseed [MeV]; Hz/MeV",i), Nbin_Etot, min_Etot, max_Etot);



   }


	outTree1 = new TTree("outTree1", "outTree1");
	
	outTree1->Branch("runNumber", &runNumber, "runNumber/I");
	outTree1->Branch("eventNumber", &eventNumber, "eventNumber/I");

	// veto BRANCH
/*
	outTree1->Branch("QOV",&QOV, "QOV[11]/D");
	outTree1->Branch("QIV",&QIV, "QIV[11]/D");
	outTree1->Branch("TOV",&TOV, "TOV[11]/D");
	outTree1->Branch("TIV",&TIV, "TIV[11]/D");

	outTree1->Branch("QIV_tot",&QIV_tot, "QIV_tot/D");
	outTree1->Branch("QIV_tot_corr",&QIV_tot_corr, "QIV_tot_corr/D");
	outTree1->Branch("IV_A_max",&IV_A_max, "IV_A_max/D");
	outTree1->Branch("IV_T_max",&IV_T_max, "IV_T_max/D");
	outTree1->Branch("multi_IVtot",&multi_IVtot, "multi_IVtot/I");
	outTree1->Branch("m_IVtot",&m_IVtot, "m_IVtot/I");

	outTree1->Branch("QOV_tot",&QOV_tot, "QOV_tot/D");
	outTree1->Branch("OV_A_max",&OV_A_max, "OV_A_max/D");
	outTree1->Branch("OV_T_max",&OV_T_max, "OV_T_max/D");
	outTree1->Branch("multi_OVtot",&multi_OVtot, "multi_OVtot/I");
	outTree1->Branch("m_OVtot",&m_OVtot, "m_OVtot/I");
*/
	// CRS BRANCH
	outTree1->Branch("Eseed",&Eseed, "Eseed/D");
	outTree1->Branch("Tseed",&Tseed, "Tseed/D");

	outTree1->Branch("Ecrs",&Ecrs, "Ecrs[45]/D");
	outTree1->Branch("Tcrs",&Tcrs, "Tcrs[45]/D");
//	outTree1->Branch("Acrs",&Acrs, "Acrs[45]/D");

	outTree1->Branch("multip",&multip, "multip/I");
	outTree1->Branch("Iseed",&Iseed, "Iseed/I");
	outTree1->Branch("Etot",&Etot, "Etot/D");
	outTree1->Branch("Etop",&Etop, "Etop/D");
	outTree1->Branch("Ebottom",&Ebottom, "Ebottom/D");
/*
	outTree1->Branch("IVc1",&IVc1,"IVc1/I");
	outTree1->Branch("IVc2",&IVc2,"IVc2/I");
	outTree1->Branch("IVc3",&IVc3,"IVc3/I");
	outTree1->Branch("IVc4",&IVc4,"IVc4/I");
	*/
	outTree1->Branch("IVc5",&IVc5,"IVc5/I");
/*
	outTree1->Branch("OVc1",&OVc1,"OVc1/I");
	outTree1->Branch("OVc2",&OVc2,"OVc2/I");
	outTree1->Branch("OVc3",&OVc3,"OVc3/I");
	outTree1->Branch("OVc4",&OVc4,"OVc4/I");
	*/
	outTree1->Branch("OVc5",&OVc5,"OVc5/I");


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
	this->GetEntry(entry);
	isGarbage = false;
	isCosmic = false;
	isBeam = false;


	// veto variables
	double OV_th =4;           //threshold on Amplitude for OV
	double IV_th =4;   //threshold on Amplitude for IV

	double Veto_Atot_th = 8;

	double IVAtot =0;
	double OVAtot =0;

	double Tmin = 50;
	double Tmax = 500;


	 IV_A_max=0;
	 IV_T_max=0;
	 int IV_max=0;
	double IV_Atot_oct=0;
	double IV_Amax_oct=0;
	double IV_Tmax_oct=0;
	int IV_max_oct=0;
	int multi_IVOct=0;
    multi_IVtot=0;
	QIV_tot=0;
	m_IVtot=0;
	QIV_tot_corr=0;

	 OV_A_max=0;
	 OV_T_max=0;
	 int OV_max=0;
	double OV_Atot_oct=0;
	double OV_Amax_oct=0;
	double OV_Tmax_oct=0;
	int OV_max_oct=0;
	int multi_OVOct=0;
    multi_OVtot=0;
	QOV_tot=0;
	m_OVtot=0;
	Iseed=0;



	int multiplicity_OV =0;
	int multiplicity_IV =0;

	bool noOV =false;
	bool noIV =false;

	 IVc1=0;
	 IVc2=0;
	 IVc3=0;
	 IVc4=0;
	 IVc5=0;

	 OVc1=0;
	 OVc2=0;
	 OVc3=0;
	 OVc4=0;
	 OVc5=0;

	//VETO  Variables //
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

	///CRS  Variables ///
	double E_singleCrs_thr = 10; //minima energia misurabile
	 Etot = 0;
	 Etop = 0;
	 Ebottom = 0;
	 Eseed = 0;
	 Tseed =0;
	double Ehit =0;
	 multip = 0;
	int Xseed = 0;
	int Yseed = 0;
	int Zseed = 0;
	double AsY =0;


	/*Objects to read collections*/
	CalorimeterHit *fCaloHit;
	IntVetoHit *fIntVetoHit;
	GenParticle *fGenParticle;



	/*Get the event header and fill some variables*/
	m_EventHeader = m_Event->getEventHeader();
	eventNumber = m_EventHeader->getEventNumber();
	runNumber = m_EventHeader->getRunNumber();
	///WEIGHT///
	weight =  m_EventHeader->getWeight();
	 
	//	if(weight>0.01)	cout << "ERR WEIGHT!!: "<< weight << endl;
	N_event++;

	thisEventT = m_Event->getEventHeader()->getEventTime() - T0;


	 if(isMC==0){
	current = m_EventHeader->getEpicsData()->getDataValue("pcrexHallA_beam_current");
    for(int i=0; i<BDX_time_garbage.size();i++){
         if(thisEventT==BDX_time_garbage[i]) {
        	 isGarbage = true;
             break;
         }

    }


if(isGarbage==true) {
	hTrigAllEvents_rate_garbage->Fill(thisEventT);
	hHALLA_cur_garbage->Fill(thisEventT, current);
	 m_Event->Clear("C");
 	return kTRUE;
}
	}


if((isGarbage==false)||(isMC==1)){
//if(1){
     if(isMC==0 && current<=0.03){
    	 isCosmic=true;
    	 hHALLA_cur_cosmic->Fill(thisEventT, current);
         INDEX =0;
     }

	 if(isMC==0 && current>0.03){
		 isBeam =true;
	     hHALLA_cur_beam->Fill(thisEventT, current);
         INDEX =1;

	 }

	 if(isMC==1) INDEX =2;

	 if(INDEX ==1) {
		 m_Event->Clear("C");
		 return kTRUE;  // it has to be commented if you want save the beam on data
	 }

	/*Check if the event has a collection named IntVetoHits and the corresponding objects are IntVetoHit objects*/

	if (m_Event->hasCollection(IntVetoHit::Class(), "IntVetoHits")) {
	  TIter IntVetoHitsIter(m_Event->getCollection(IntVetoHit::Class(), "IntVetoHits"));
	  while (fIntVetoHit = (IntVetoHit*) IntVetoHitsIter.Next()) { //Need to cast to the proper object

		  if (fIntVetoHit->m_channel.layer == 0 && fIntVetoHit->m_channel.component!=3) {
			  QOV[fIntVetoHit->m_channel.component] = fIntVetoHit->A;
			  TOV[fIntVetoHit->m_channel.component] = fIntVetoHit->T;
			  OVAtot += fIntVetoHit->A;
              QOV_tot += fIntVetoHit->A;
              if(fIntVetoHit->A>0) m_OVtot++;
              if(fIntVetoHit->A>OV_A_max) {
            	  OV_A_max = fIntVetoHit->A;
            	  OV_T_max = fIntVetoHit->T;
            	  OV_max = fIntVetoHit->m_channel.component;
             //	IV_seed=fIntVetoHit->m_channel.component;
              }

              if(fIntVetoHit->m_channel.component<9){
                  if(fIntVetoHit->A>OV_Amax_oct) {
                	  OV_Amax_oct = fIntVetoHit->A;
                	  OV_Tmax_oct = fIntVetoHit->T;
                	  OV_max_oct = fIntVetoHit->m_channel.component;
                 //	IV_seed=fIntVetoHit->m_channel.component;
                  }
                  OV_Atot_oct += fIntVetoHit->A;

              }

		      if(isMC==1){
			     if(fIntVetoHit->A > OV_th ){

			        multiplicity_OV++;
			}
		      }else{
		      //DATA//
		      	if(fIntVetoHit->A > OV_th && fIntVetoHit->T < Tmax && fIntVetoHit->T > Tmin ){

			       multiplicity_OV++;
			}

		      }

		  }



		  if (fIntVetoHit->m_channel.layer == 1) {
			  QIV[fIntVetoHit->m_channel.component] = fIntVetoHit->A;
			  TIV[fIntVetoHit->m_channel.component] = fIntVetoHit->T;
              QIV_tot += fIntVetoHit->A;
             if(fIntVetoHit->A>0) m_IVtot++;
              if(fIntVetoHit->A>IV_A_max) {
            	  IV_A_max = fIntVetoHit->A;
            	  IV_T_max = fIntVetoHit->T;
            	  IV_max = fIntVetoHit->m_channel.component;
             //	IV_seed=fIntVetoHit->m_channel.component;
              }

              if(fIntVetoHit->m_channel.component<9){
                  if(fIntVetoHit->A>IV_Amax_oct) {
                	  IV_Amax_oct = fIntVetoHit->A;
                	  IV_Tmax_oct = fIntVetoHit->T;
                	  IV_max_oct = fIntVetoHit->m_channel.component;
                 //	IV_seed=fIntVetoHit->m_channel.component;
                  }
                  IV_Atot_oct += fIntVetoHit->A;

              }

		     IVAtot += fIntVetoHit->A;
		      if(isMC==1){
			     if(fIntVetoHit->A > IV_th ){

			        multiplicity_IV++;
			}
		      }else{
		      //DATA//
		      	if(fIntVetoHit->A > IV_th && fIntVetoHit->T < Tmax && fIntVetoHit->T > Tmin ){

			       multiplicity_IV++;
			}

		      }
	  }
	}


}

	if(IV_A_max>2.5) {
		multi_IVtot =1;
		QIV_tot_corr = IV_A_max;
	for(int i=1; i<=10; i++){
		if(i!=IV_max&&abs(TIV[i]-IV_T_max)<100) QIV_tot_corr += QIV[i];
	  if(i!=IV_max&&QIV[i]>2.5&&abs(TIV[i]-IV_T_max)<100) multi_IVtot = multi_IVtot+1;
	}
	}

	if(IV_Amax_oct>2.5) {
		multi_IVOct =1;
	for(int i=1; i<=8; i++){
	  if(i!=IV_max_oct&&QIV[i]>2.5&&abs(TIV[i]-IV_Tmax_oct)<100) multi_IVOct = multi_IVOct+1;
	}
	}

	if(OV_A_max>3.5) {
		multi_OVtot =1;
	for(int i=1; i<=10; i++){
	  if(i!=OV_max&&QOV[i]>3.5&&abs(TOV[i]-OV_T_max)<100) multi_OVtot = multi_OVtot+1;
	}
	}

	if(OV_Amax_oct>2.5) {
		multi_OVOct =1;
	for(int i=1; i<=8; i++){
	  if(i!=OV_max_oct&&QOV[i]>2.5&&abs(TOV[i]-OV_Tmax_oct)<100) multi_OVOct = multi_OVOct+1;
	}
	}


	if(multiplicity_OV==0 && (OVAtot <= Veto_Atot_th )) noOV= true;
	if(multiplicity_IV==0 && (IVAtot <= Veto_Atot_th )) noIV= true;


	//cout << weight<<endl;
	//HISTO VETO


        hOV_Atot[INDEX]->Fill(OVAtot, weight);
        hOV_multiplicity[INDEX]->Fill(multiplicity_OV, weight);
	    hIV_Atot[INDEX] ->Fill(IVAtot, weight);
	    hIV_multiplicity[INDEX]->Fill(multiplicity_IV, weight);
	    hOV_Atot_vs_multiplicity[INDEX]->Fill(OVAtot, multiplicity_OV, weight);
	    hIV_Atot_vs_multiplicity[INDEX]->Fill(IVAtot, multiplicity_IV, weight);


	    int idx_crs_up=0;
	    int idx_crs_down=0;



		if (m_Event->hasCollection(CalorimeterHit::Class(), "CalorimeterHits")) {
		  TIter CaloHitsIter(m_Event->getCollection(CalorimeterHit::Class(), "CalorimeterHits"));
		  //thisEventT = m_Event->getEventHeader()->getEventTime() - T0;

		  while (fCaloHit = (CalorimeterHit*) CaloHitsIter.Next()) {
			  if(fCaloHit->m_channel.sector ==0){   // sono la parte up del calorimetro
			  idx_crs_up = this->getCaloIDXFromXY(fCaloHit->m_channel.x, fCaloHit->m_channel.y);
			  Ecrs[idx_crs_up] = fCaloHit->E;
			  Tcrs[idx_crs_up] = fCaloHit->T;
			  Acrs[idx_crs_up] = fCaloHit->A;
			  }
			  if(fCaloHit->m_channel.sector ==1){   // sono la parte down del calorimetro
			  idx_crs_down = (this->getCaloIDXFromXY(fCaloHit->m_channel.x, fCaloHit->m_channel.y)) +22;
			  Ecrs[idx_crs_down] = fCaloHit->E;
			  Tcrs[idx_crs_down] = fCaloHit->T;
			  Acrs[idx_crs_down] = fCaloHit->A;

			  }

			  Ehit =  (fCaloHit->E);

		      if(Ehit>Eseed){
			Eseed = Ehit;
			Tseed = (fCaloHit->T);
			Xseed = fCaloHit->m_channel.x;
			Yseed = fCaloHit->m_channel.y;
			Zseed = fCaloHit->m_channel.sector;
			if(Zseed ==0 ) Iseed = this->getCaloIDXFromXY(Xseed, Yseed);
			if(Zseed ==1 ) Iseed = this->getCaloIDXFromXY(Xseed, Yseed) + 22;
		      }


		  }
		  }



	/*Check if the event has a collection named CalorimeterHits, and the corresponding objects are CalorimeterHit objects*/
	if (m_Event->hasCollection(CalorimeterHit::Class(), "CalorimeterHits")) {
	  TIter CaloHitsIter(m_Event->getCollection(CalorimeterHit::Class(), "CalorimeterHits"));
	  //thisEventT = m_Event->getEventHeader()->getEventTime() - T0;

	  while (fCaloHit = (CalorimeterHit*) CaloHitsIter.Next()) { //Need to cast to the proper object

	    Ehit=0;
	    //MINIMUM ENERGY PER CRS //
	  //  if(fCaloHit->E > E_singleCrs_thr){
	    if(fCaloHit->E>4&&abs(Tseed -fCaloHit->T)<100){
	      //Multiplicity//
	      multip ++;

	      //Hit Energy//
	    //  Ehit =  (fCaloHit->E);

	      // Total Energy
	      Etot = Etot + (fCaloHit->E);

	      int sector =  fCaloHit->m_channel.sector;

	      // Top Energy
	      if(fCaloHit->m_channel.sector ==0) Etop = Etop + (fCaloHit->E);

	      // Bottom Energy
	      if(fCaloHit->m_channel.sector ==1) Ebottom = Ebottom + (fCaloHit->E);


	      // Eseed, Seed XY //
	      /*
	      if(Ehit>Eseed){
		Eseed = Ehit;
		Tseed = (fCaloHit->T);
		Xseed = fCaloHit->m_channel.x;
		Yseed = fCaloHit->m_channel.y;
		Zseed = fCaloHit->m_channel.sector;
		if(Zseed ==0 ) Iseed = this->getCaloIDXFromXY(Xseed, Yseed);
		if(Zseed ==1 ) Iseed = this->getCaloIDXFromXY(Xseed, Yseed) + 22;
	      }
	      */
	    }
	  }
	}

	double Xs = 0;
	double Ys =0;
	double Zs=0;
	int flag =0;

	if (m_Event->hasCollection(CalorimeterHit::Class(), "CalorimeterHits")) {
	  TIter CaloHitsIter2(m_Event->getCollection(CalorimeterHit::Class(), "CalorimeterHits"));
	  while (fCaloHit = (CalorimeterHit*) CaloHitsIter2.Next()) {
	    if(fCaloHit->E > E_singleCrs_thr){

	      Xs = fCaloHit->m_channel.x  - Xseed;
	      Ys = fCaloHit->m_channel.y  - Yseed;
	      Zs = fCaloHit->m_channel.sector;

	      if(Xs!= 0 || Ys != 0) {
	    	  hCrs_XY_XYseed[INDEX]->Fill(Xs,Ys,(weight));
	    	  if(noOV==1 && noIV==1) hCrs_XY_XYseed_NoVETO[INDEX]->Fill(Xs,Ys,(weight));

	      }

	      if(Zseed==Zs){
		flag =0;
	      }else{
		flag =1;
	      }
	    }
	  }
	}





	if(Etot>E_singleCrs_thr){
	   hCrs_Etot[INDEX]->Fill(Etot, weight);
	   hCrs_multiplicity[INDEX]->Fill(multip, weight);
    //   hCrs_Eseed[INDEX]->Fill(Eseed, weight);
	   hCrs_Eseed[INDEX]->Fill(Eseed);
	   hCrs_Etop[INDEX]->Fill(Etop, weight);
	   hCrs_Ebottom[INDEX]->Fill(Ebottom, weight);
	   hCrs_R_EtopEtot[INDEX]->Fill(Etop/Etot, weight);
	   hCrs_R_EbottomEtot[INDEX]->Fill(Ebottom/Etot, weight);
	   hCrs_EtotVsEtop[INDEX]->Fill(Etot, Etop, weight);
       hCrs_XYseed[INDEX]->Fill(Xseed, Yseed, weight);
	   hCrs_EseedVSEtot[INDEX]->Fill(Eseed, Etot, weight);
	   hCrs_EseedVSMulti[INDEX]->Fill(Eseed, multip, weight);
	   hCrs_EtotVSMulti[INDEX]->Fill(Etot, multip, weight);
		hCrs_EtopEbotVsEtot[INDEX]->Fill((Etop-Ebottom)/Etot, Etot, weight);
		hCrs_EtopEbotVsEseed[INDEX]->Fill((Etop-Ebottom)/Etot, Eseed, weight);
		if(abs((Etop-Ebottom)/Etot)<0.8)hCrs_Eseed_CutEasym[INDEX]->Fill(Eseed, weight);

	}


	if(Etot>E_singleCrs_thr && noOV==1 && noIV==1){


	   hCrs_Etot_NoVETO[INDEX]->Fill(Etot, weight);
	   hCrs_multiplicity_NoVETO[INDEX]->Fill(multip, weight);
       hCrs_Eseed_NoVETO[INDEX]->Fill(Eseed, weight);
	   hCrs_Etop_NoVETO[INDEX]->Fill(Etop, weight);
	   hCrs_Ebottom_NoVETO[INDEX]->Fill(Ebottom, weight);
	   hCrs_R_EtopEtot_NoVETO[INDEX]->Fill(Etop/Etot, weight);
	   hCrs_R_EbottomEtot_NoVETO[INDEX]->Fill(Ebottom/Etot, weight);
	   hCrs_EtotVsEtop_NoVETO[INDEX]->Fill(Etot, Etop, weight);
       hCrs_XYseed_NoVETO[INDEX]->Fill(Xseed, Yseed, weight);
	   hCrs_EseedVSEtot_NoVETO[INDEX]->Fill(Eseed, Etot, weight);
	   hCrs_EseedVSMulti_NoVETO[INDEX]->Fill(Eseed, multip, weight);
	   hCrs_EtotVSMulti_NoVETO[INDEX]->Fill(Etot, multip, weight);



	}

// IV event conditions
	if(IV_A_max>5.5) IVc1=1;
	if((IV_Amax_oct>4&&IV_Atot_oct>11)||(QIV[9]>5.5)||(QIV[10]>5.5)) IVc2=1;
    if(multi_IVOct>1||(QIV[9]>5.5)||(QIV[10]>5.5)) IVc3=1;
    if((multi_IVOct==1&&IV_Amax_oct>5.5)||multi_IVOct>1||(QIV[9]>5.5)||(QIV[10]>5.5)) IVc4=1;
    if((multi_IVtot==1&&IV_A_max>5.5)||multi_IVtot>1) IVc5=1;

    // OV event conditions
	if(OV_A_max>5.5) OVc1=1;
	if((OV_Amax_oct>4&&OV_Atot_oct>11)||(QOV[9]>5.5)||(QOV[10]>5.5)) OVc2=1;
    if(multi_OVOct>1||(QOV[9]>5.5)||(QOV[10]>5.5)) OVc3=1;
    if((multi_OVOct==1&&OV_Amax_oct>5.5)||multi_OVOct>1||(QOV[9]>5.5)||(QOV[10]>5.5)) OVc4=1;
    if((multi_OVtot==1&&OV_A_max>6.5)||multi_OVtot>1) OVc5=1;



   if(Eseed>0){
	if(IV_A_max>5.5) hCrs_Eseed_IVc1[INDEX]->Fill(Eseed);
	if((IV_Amax_oct>4&&IV_Atot_oct>11)||(QIV[9]>5.5)||(QIV[10]>5.5)) hCrs_Eseed_IVc2[INDEX]->Fill(Eseed);
    if(multi_IVOct>1||(QIV[9]>5.5)||(QIV[10]>5.5)) hCrs_Eseed_IVc3[INDEX]->Fill(Eseed);
    if((multi_IVOct==1&&IV_Amax_oct>5.5)||multi_IVOct>1||(QIV[9]>5.5)||(QIV[10]>5.5)) hCrs_Eseed_IVc4[INDEX]->Fill(Eseed);
    if((multi_IVtot==1&&IV_A_max>5.5)||multi_IVtot>1) hCrs_Eseed_IVc5[INDEX]->Fill(Eseed);


    if(!(multi_IVOct>1||(QIV[9]>5.5)||(QIV[10]>5.5))) hCrs_Eseed_NoIVc3[INDEX]->Fill(Eseed);
    if(!((multi_IVOct==1&&IV_Amax_oct>5.5)||multi_IVOct>1||(QIV[9]>5.5)||(QIV[10]>5.5))) hCrs_Eseed_NoIVc4[INDEX]->Fill(Eseed);





    if(IVc1==0){
       hCrs_Eseed_NoIVc1[INDEX]->Fill(Eseed);
 	   hCrs_Etot_noIVc1[INDEX]->Fill(Etot, weight);
 	   hCrs_multiplicity_noIVc1[INDEX]->Fill(multip, weight);
     //  hCrs_Eseed_noIVc1[INDEX]->Fill(Eseed, weight);
 	   hCrs_Etop_noIVc1[INDEX]->Fill(Etop, weight);
 	   hCrs_Ebottom_noIVc1[INDEX]->Fill(Ebottom, weight);
 	   hCrs_R_EtopEtot_noIVc1[INDEX]->Fill(Etop/Etot, weight);
 	   hCrs_R_EbottomEtot_noIVc1[INDEX]->Fill(Ebottom/Etot, weight);
 	   hCrs_EtotVsEtop_noIVc1[INDEX]->Fill(Etot, Etop, weight);
       hCrs_XYseed_noIVc1[INDEX]->Fill(Xseed, Yseed, weight);
 	   hCrs_EseedVSEtot_noIVc1[INDEX]->Fill(Eseed, Etot, weight);
 	   hCrs_EseedVSMulti_noIVc1[INDEX]->Fill(Eseed, multip, weight);
 	   hCrs_EtotVSMulti_noIVc1[INDEX]->Fill(Etot, multip, weight);


    }

    if(IVc2==0){
    	hCrs_Eseed_NoIVc2[INDEX]->Fill(Eseed);
 	   hCrs_Etot_noIVc2[INDEX]->Fill(Etot, weight);
 	   hCrs_multiplicity_noIVc2[INDEX]->Fill(multip, weight);
      // hCrs_Eseed_noIVc2[INDEX]->Fill(Eseed, weight);
 	   hCrs_Etop_noIVc2[INDEX]->Fill(Etop, weight);
 	   hCrs_Ebottom_noIVc2[INDEX]->Fill(Ebottom, weight);
 	   hCrs_R_EtopEtot_noIVc2[INDEX]->Fill(Etop/Etot, weight);
 	   hCrs_R_EbottomEtot_noIVc2[INDEX]->Fill(Ebottom/Etot, weight);
 	   hCrs_EtotVsEtop_noIVc2[INDEX]->Fill(Etot, Etop, weight);
        hCrs_XYseed_noIVc2[INDEX]->Fill(Xseed, Yseed, weight);
 	   hCrs_EseedVSEtot_noIVc2[INDEX]->Fill(Eseed, Etot, weight);
 	   hCrs_EseedVSMulti_noIVc2[INDEX]->Fill(Eseed, multip, weight);
 	   hCrs_EtotVSMulti_noIVc2[INDEX]->Fill(Etot, multip, weight);


    }


    if(IVc5==0){
    	hCrs_Eseed_NoIVc5[INDEX]->Fill(Eseed);
 	   hCrs_Etot_noIVc5[INDEX]->Fill(Etot, weight);
 	   hCrs_multiplicity_noIVc5[INDEX]->Fill(multip, weight);
     //  hCrs_Eseed_noIVc5[INDEX]->Fill(Eseed, weight);
 	   hCrs_Etop_noIVc5[INDEX]->Fill(Etop, weight);
 	   hCrs_Ebottom_noIVc5[INDEX]->Fill(Ebottom, weight);
 	   hCrs_R_EtopEtot_noIVc5[INDEX]->Fill(Etop/Etot, weight);
 	   hCrs_R_EbottomEtot_noIVc5[INDEX]->Fill(Ebottom/Etot, weight);
 	   hCrs_EtotVsEtop_noIVc5[INDEX]->Fill(Etot, Etop, weight);
        hCrs_XYseed_noIVc5[INDEX]->Fill(Xseed, Yseed, weight);
 	   hCrs_EseedVSEtot_noIVc5[INDEX]->Fill(Eseed, Etot, weight);
 	   hCrs_EseedVSMulti_noIVc5[INDEX]->Fill(Eseed, multip, weight);
 	   hCrs_EtotVSMulti_noIVc5[INDEX]->Fill(Etot, multip, weight);
	  hCrs_EtopEbotVsEtot_noIVc5[INDEX]->Fill((Etop-Ebottom)/Etot, Etot, weight);
		hCrs_EtopEbotVsEseed_noIVc5[INDEX]->Fill((Etop-Ebottom)/Etot, Eseed, weight);

		hQIVmaxVSQIVtot_noIVc5[INDEX]->Fill(IV_A_max, QIV_tot, weight);
		if(Eseed>=100) hQIVmaxVSQIVtot_noIVc5_Eseed_gr_100[INDEX]->Fill(IV_A_max, QIV_tot, weight);
		if(abs((Etop-Ebottom)/Etot)<0.8)hCrs_Eseed_CutEasym_noIVc5[INDEX]->Fill(Eseed, weight);


    }


    if(OVc1==0){

 	   hCrs_Etot_noOVc1[INDEX]->Fill(Etot, weight);
 	   hCrs_multiplicity_noOVc1[INDEX]->Fill(multip, weight);
       hCrs_Eseed_NoOVc1[INDEX]->Fill(Eseed, weight);
 	   hCrs_Etop_noOVc1[INDEX]->Fill(Etop, weight);
 	   hCrs_Ebottom_noOVc1[INDEX]->Fill(Ebottom, weight);
 	   hCrs_R_EtopEtot_noOVc1[INDEX]->Fill(Etop/Etot, weight);
 	   hCrs_R_EbottomEtot_noOVc1[INDEX]->Fill(Ebottom/Etot, weight);
 	   hCrs_EtotVsEtop_noOVc1[INDEX]->Fill(Etot, Etop, weight);
       hCrs_XYseed_noOVc1[INDEX]->Fill(Xseed, Yseed, weight);
 	   hCrs_EseedVSEtot_noOVc1[INDEX]->Fill(Eseed, Etot, weight);
 	   hCrs_EseedVSMulti_noOVc1[INDEX]->Fill(Eseed, multip, weight);
 	   hCrs_EtotVSMulti_noOVc1[INDEX]->Fill(Etot, multip, weight);


    }

    if(OVc2==0){

 	   hCrs_Etot_noOVc2[INDEX]->Fill(Etot, weight);
 	   hCrs_multiplicity_noOVc2[INDEX]->Fill(multip, weight);
       hCrs_Eseed_NoOVc2[INDEX]->Fill(Eseed, weight);
 	   hCrs_Etop_noOVc2[INDEX]->Fill(Etop, weight);
 	   hCrs_Ebottom_noOVc2[INDEX]->Fill(Ebottom, weight);
 	   hCrs_R_EtopEtot_noOVc2[INDEX]->Fill(Etop/Etot, weight);
 	   hCrs_R_EbottomEtot_noOVc2[INDEX]->Fill(Ebottom/Etot, weight);
 	   hCrs_EtotVsEtop_noOVc2[INDEX]->Fill(Etot, Etop, weight);
        hCrs_XYseed_noOVc2[INDEX]->Fill(Xseed, Yseed, weight);
 	   hCrs_EseedVSEtot_noOVc2[INDEX]->Fill(Eseed, Etot, weight);
 	   hCrs_EseedVSMulti_noOVc2[INDEX]->Fill(Eseed, multip, weight);
 	   hCrs_EtotVSMulti_noOVc2[INDEX]->Fill(Etot, multip, weight);


    }


    if(OVc5==0){

 	   hCrs_Etot_noOVc5[INDEX]->Fill(Etot, weight);
 	   hCrs_multiplicity_noOVc5[INDEX]->Fill(multip, weight);
       hCrs_Eseed_NoOVc5[INDEX]->Fill(Eseed, weight);
 	   hCrs_Ebottom_noOVc5[INDEX]->Fill(Ebottom, weight);
 	   hCrs_R_EtopEtot_noOVc5[INDEX]->Fill(Etop/Etot, weight);
 	   hCrs_R_EbottomEtot_noOVc5[INDEX]->Fill(Ebottom/Etot, weight);
 	   hCrs_EtotVsEtop_noOVc5[INDEX]->Fill(Etot, Etop, weight);

       hCrs_XYseed_noOVc5[INDEX]->Fill(Xseed, Yseed, weight);
 	   hCrs_EseedVSEtot_noOVc5[INDEX]->Fill(Eseed, Etot, weight);
 	   hCrs_EseedVSMulti_noOVc5[INDEX]->Fill(Eseed, multip, weight);
 	   hCrs_EtotVSMulti_noOVc5[INDEX]->Fill(Etot, multip, weight);
	   hCrs_EtopEbotVsEtot_noOVc5[INDEX]->Fill((Etop-Ebottom)/Etot, Etot, weight);
		hCrs_EtopEbotVsEseed_noOVc5[INDEX]->Fill((Etop-Ebottom)/Etot, Eseed, weight);

		if(abs((Etop-Ebottom)/Etot)<0.8)hCrs_Eseed_CutEasym_noOVc5[INDEX]->Fill(Eseed, weight);


    }


    if(IVc5==0 && OVc5==0){
		hCrs_Etot_noVc5[INDEX]->Fill(Etot, weight);
		hCrs_Eseed_noVc5[INDEX]->Fill(Eseed, weight);
		hCrs_EtopEbotVsEtot_noVc5[INDEX]->Fill((Etop-Ebottom)/Etot, Etot, weight);
		hCrs_EtopEbotVsEseed_noVc5[INDEX]->Fill((Etop-Ebottom)/Etot, Eseed, weight);
		if(abs((Etop-Ebottom)/Etot)<0.8)hCrs_Eseed_CutEasym_noVc5[INDEX]->Fill(Eseed, weight);

    }


} //end if Eseed










}






	outTree1->Fill();
	

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
  
  TListIter iter(fOutput);
  TObject *obj;

  hTrigAllEvents_rate_garbage = (TH1D*)fOutput->FindObject("hTrigAllEvents_rate_garbage");
  hHALLA_cur_beam = (TH2D*)fOutput->FindObject("hHALLA_cur_beam");
  hHALLA_cur_cosmic = (TH2D*)fOutput->FindObject("hHALLA_cur_cosmic");
  hHALLA_cur_garbage = (TH2D*)fOutput->FindObject("hHALLA_cur_garbage");
  

  //HISTO VETO
  for(int i=0; i<3; i++){
	 // if(i!=1){
  hOV_Atot[i] = (TH1D*)fOutput->FindObject(Form("hOV_Atot_%i",i));
  hOV_multiplicity[i] = (TH1D*)fOutput->FindObject(Form("hOV_multiplicity_%i",i));
  hIV_Atot[i] = (TH1D*)fOutput->FindObject(Form("hIV_Atot_%i",i));
  hIV_multiplicity[i] = (TH1D*)fOutput->FindObject(Form("hIV_multiplicity_%i",i));
  hOV_Atot_vs_multiplicity[i] = (TH2D*)fOutput->FindObject(Form("hOV_Atot_vs_multiplicity_%i",i));
  hIV_Atot_vs_multiplicity[i] = (TH2D*)fOutput->FindObject(Form("hIV_Atot_vs_multiplicity_%i",i));

  // HISTO CALORIMETER
  hCrs_Etot[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etot_%i",i));
  hCrs_multiplicity[i] = (TH1D*)fOutput->FindObject(Form("hCrs_multiplicity_%i",i));
  hCrs_Eseed[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_%i",i));
  hCrs_Etop[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etop_%i",i));
  hCrs_Ebottom[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Ebottom_%i",i));
  hCrs_R_EtopEtot[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EtopEtot_%i",i));
  hCrs_R_EbottomEtot[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EbottomEtot_%i",i));
  hCrs_EtotVsEtop[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVsEtop_%i",i));
  hCrs_XYseed[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XYseed_%i",i));
  hCrs_XY_XYseed[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XY_XYseed_%i",i));
  hCrs_EseedVSEtot[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSEtot_%i",i));
  hCrs_EseedVSMulti[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSMulti_%i",i));
  hCrs_EtotVSMulti[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVSMulti_%i",i));
  hCrs_EtopEbotVsEtot[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtopEbotVsEtot_%i",i));
  hCrs_EtopEbotVsEseed[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtopEbotVsEseed_%i",i));
  hCrs_Eseed_CutEasym[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_CutEasym_%i",i));

  hCrs_Etot_NoVETO[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etot_NoVETO_%i",i));
  hCrs_multiplicity_NoVETO[i] = (TH1D*)fOutput->FindObject(Form("hCrs_multiplicity_NoVETO_%i",i));
  hCrs_Eseed_NoVETO[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_NoVETO_%i",i));
  hCrs_Etop_NoVETO[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etop_NoVETO_%i",i));
  hCrs_Ebottom_NoVETO[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Ebottom_NoVETO_%i",i));
  hCrs_R_EtopEtot_NoVETO[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EtopEtot_NoVETO_%i",i));
  hCrs_R_EbottomEtot_NoVETO[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EbottomEtot_NoVETO_%i",i));
  hCrs_EtotVsEtop_NoVETO[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVsEtop_NoVETO_%i",i));
  hCrs_XYseed_NoVETO[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XYseed_NoVETO_%i",i));
  hCrs_XY_XYseed_NoVETO[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XY_XYseed_NoVETO_%i",i));
  hCrs_EseedVSEtot_NoVETO[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSEtot_NoVETO_%i",i));
  hCrs_EseedVSMulti_NoVETO[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSMulti_NoVETO_%i",i));
  hCrs_EtotVSMulti_NoVETO[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVSMulti_NoVETO_%i",i));



  hCrs_Etot_noIVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etot_noIVc1_%i",i));
  hCrs_multiplicity_noIVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_multiplicity_noIVc1_%i",i));
  hCrs_Etop_noIVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etop_noIVc1_%i",i));
  hCrs_Ebottom_noIVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Ebottom_noIVc1_%i",i));
  hCrs_R_EtopEtot_noIVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EtopEtot_noIVc1_%i",i));
  hCrs_R_EbottomEtot_noIVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EbottomEtot_noIVc1_%i",i));
  hCrs_EtotVsEtop_noIVc1[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVsEtop_noIVc1_%i",i));
  hCrs_XYseed_noIVc1[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XYseed_noIVc1_%i",i));
  hCrs_XY_XYseed_noIVc1[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XY_XYseed_noIVc1_%i",i));
  hCrs_EseedVSEtot_noIVc1[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSEtot_noIVc1_%i",i));
  hCrs_EseedVSMulti_noIVc1[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSMulti_noIVc1_%i",i));
  hCrs_EtotVSMulti_noIVc1[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVSMulti_noIVc1_%i",i));


  hCrs_Etot_noIVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etot_noIVc2_%i",i));
  hCrs_multiplicity_noIVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_multiplicity_noIVc2_%i",i));
  hCrs_Etop_noIVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etop_noIVc2_%i",i));
  hCrs_Ebottom_noIVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Ebottom_noIVc2_%i",i));
  hCrs_R_EtopEtot_noIVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EtopEtot_noIVc2_%i",i));
  hCrs_R_EbottomEtot_noIVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EbottomEtot_noIVc2_%i",i));
  hCrs_EtotVsEtop_noIVc2[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVsEtop_noIVc2_%i",i));
  hCrs_XYseed_noIVc2[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XYseed_noIVc2_%i",i));
  hCrs_XY_XYseed_noIVc2[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XY_XYseed_noIVc2_%i",i));
  hCrs_EseedVSEtot_noIVc2[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSEtot_noIVc2_%i",i));
  hCrs_EseedVSMulti_noIVc2[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSMulti_noIVc2_%i",i));
  hCrs_EtotVSMulti_noIVc2[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVSMulti_noIVc2_%i",i));


  hCrs_Etot_noIVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etot_noIVc5_%i",i));
  hCrs_multiplicity_noIVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_multiplicity_noIVc5_%i",i));
  hCrs_Etop_noIVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etop_noIVc5_%i",i));
  hCrs_Ebottom_noIVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Ebottom_noIVc5_%i",i));
  hCrs_R_EtopEtot_noIVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EtopEtot_noIVc5_%i",i));
  hCrs_R_EbottomEtot_noIVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EbottomEtot_noIVc5_%i",i));
  hCrs_EtotVsEtop_noIVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVsEtop_noIVc5_%i",i));
  hCrs_XYseed_noIVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XYseed_noIVc5_%i",i));
  hCrs_XY_XYseed_noIVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XY_XYseed_noIVc5_%i",i));
  hCrs_EseedVSEtot_noIVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSEtot_noIVc5_%i",i));
  hCrs_EseedVSMulti_noIVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSMulti_noIVc5_%i",i));
  hCrs_EtotVSMulti_noIVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVSMulti_noIVc5_%i",i));
  hCrs_EtopEbotVsEtot_noIVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtopEbotVsEtot_noIVc5_%i",i));
  hCrs_EtopEbotVsEseed_noIVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtopEbotVsEseed_noIVc5_%i",i));
  hCrs_Eseed_CutEasym_noIVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_CutEasym_noIVc5_%i",i));

	hQIVmaxVSQIVtot_noIVc5[i] = (TH2D*)fOutput->FindObject(Form("hQIVmaxVSQIVtot_noIVc5_%i",i));
	hQIVmaxVSQIVtot_noIVc5_Eseed_gr_100[i] = (TH2D*)fOutput->FindObject(Form("hQIVmaxVSQIVtot_noIVc5_Eseed_gr_100_%i",i));

  hCrs_Eseed_IVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_IVc1_%i",i));
  hCrs_Eseed_IVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_IVc2_%i",i));
  hCrs_Eseed_IVc3[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_IVc3_%i",i));
  hCrs_Eseed_IVc4[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_IVc4_%i",i));
  hCrs_Eseed_IVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_IVc5_%i",i));

  hCrs_Eseed_NoIVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_NoIVc1_%i",i));
  hCrs_Eseed_NoIVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_NoIVc2_%i",i));
  hCrs_Eseed_NoIVc3[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_NoIVc3_%i",i));
  hCrs_Eseed_NoIVc4[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_NoIVc4_%i",i));
  hCrs_Eseed_NoIVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_NoIVc5_%i",i));

  hCrs_Eseed_NoOVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_NoOVc1_%i",i));
  hCrs_Eseed_NoOVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_NoOVc2_%i",i));
  hCrs_Eseed_NoOVc3[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_NoOVc3_%i",i));
  hCrs_Eseed_NoOVc4[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_NoOVc4_%i",i));
  hCrs_Eseed_NoOVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_NoOVc5_%i",i));



  hCrs_Etot_noOVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etot_noOVc1_%i",i));
  hCrs_multiplicity_noOVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_multiplicity_noOVc1_%i",i));
  hCrs_Etop_noOVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etop_noOVc1_%i",i));
  hCrs_Ebottom_noOVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Ebottom_noOVc1_%i",i));
  hCrs_R_EtopEtot_noOVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EtopEtot_noOVc1_%i",i));
  hCrs_R_EbottomEtot_noOVc1[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EbottomEtot_noOVc1_%i",i));
  hCrs_EtotVsEtop_noOVc1[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVsEtop_noOVc1_%i",i));
  hCrs_XYseed_noOVc1[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XYseed_noOVc1_%i",i));
  hCrs_XY_XYseed_noOVc1[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XY_XYseed_noOVc1_%i",i));
  hCrs_EseedVSEtot_noOVc1[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSEtot_noOVc1_%i",i));
  hCrs_EseedVSMulti_noOVc1[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSMulti_noOVc1_%i",i));
  hCrs_EtotVSMulti_noOVc1[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVSMulti_noOVc1_%i",i));


  hCrs_Etot_noOVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etot_noOVc2_%i",i));
  hCrs_multiplicity_noOVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_multiplicity_noOVc2_%i",i));
  hCrs_Etop_noOVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etop_noOVc2_%i",i));
  hCrs_Ebottom_noOVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Ebottom_noOVc2_%i",i));
  hCrs_R_EtopEtot_noOVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EtopEtot_noOVc2_%i",i));
  hCrs_R_EbottomEtot_noOVc2[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EbottomEtot_noOVc2_%i",i));
  hCrs_EtotVsEtop_noOVc2[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVsEtop_noOVc2_%i",i));
  hCrs_XYseed_noOVc2[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XYseed_noOVc2_%i",i));
  hCrs_XY_XYseed_noOVc2[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XY_XYseed_noOVc2_%i",i));
  hCrs_EseedVSEtot_noOVc2[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSEtot_noOVc2_%i",i));
  hCrs_EseedVSMulti_noOVc2[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSMulti_noOVc2_%i",i));
  hCrs_EtotVSMulti_noOVc2[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVSMulti_noOVc2_%i",i));


  hCrs_Etot_noOVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etot_noOVc5_%i",i));
  hCrs_multiplicity_noOVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_multiplicity_noOVc5_%i",i));
  hCrs_Etop_noOVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etop_noOVc5_%i",i));
  hCrs_Ebottom_noOVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Ebottom_noOVc5_%i",i));
  hCrs_R_EtopEtot_noOVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EtopEtot_noOVc5_%i",i));
  hCrs_R_EbottomEtot_noOVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_R_EbottomEtot_noOVc5_%i",i));
  hCrs_EtotVsEtop_noOVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVsEtop_noOVc5_%i",i));
  hCrs_XYseed_noOVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XYseed_noOVc5_%i",i));
  hCrs_XY_XYseed_noOVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_XY_XYseed_noOVc5_%i",i));
  hCrs_EseedVSEtot_noOVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSEtot_noOVc5_%i",i));
  hCrs_EseedVSMulti_noOVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EseedVSMulti_noOVc5_%i",i));
  hCrs_EtotVSMulti_noOVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtotVSMulti_noOVc5_%i",i));
  hCrs_EtopEbotVsEtot_noOVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtopEbotVsEtot_noOVc5_%i",i));
  hCrs_EtopEbotVsEseed_noOVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtopEbotVsEseed_noOVc5_%i",i));
  hCrs_Eseed_CutEasym_noOVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_CutEasym_noOVc5_%i",i));

  hCrs_Etot_noVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Etot_noVc5_%i",i));
  hCrs_Eseed_noVc5[i]= (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_noVc5_%i",i));
  hCrs_EtopEbotVsEtot_noVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtopEbotVsEtot_noVc5_%i",i));
  hCrs_EtopEbotVsEseed_noVc5[i] = (TH2D*)fOutput->FindObject(Form("hCrs_EtopEbotVsEseed_noVc5_%i",i));
  hCrs_Eseed_CutEasym_noVc5[i] = (TH1D*)fOutput->FindObject(Form("hCrs_Eseed_CutEasym_noVc5_%i",i));





  }


  hTrigAllEvents_rate_garbage->Sumw2();
  hTrigAllEvents_rate_garbage->Scale(1.,"width");

      for(int i=0; i<3; i++){

	 hCrs_Etot[i]->Sumw2();
	 hCrs_Etot[i]->Scale(1./mean_tlive,"width");

//	 hCrs_Eseed[i]->Sumw2();
//	 hCrs_Eseed[i]->Scale(1./mean_tlive,"width");

	 hCrs_Etot[i]->Sumw2();
	 hCrs_Etot[i]->Scale(1./mean_tlive,"width");

//	 hCrs_Eseed[i]->Sumw2();
//	 hCrs_Eseed[i]->Scale(1./mean_tlive,"width");

	 hCrs_Etot_NoVETO[i]->Sumw2();
	 hCrs_Etot_NoVETO[i]->Scale(1./mean_tlive,"width");

	 hCrs_Eseed_NoVETO[i]->Sumw2();
	 hCrs_Eseed_NoVETO[i]->Scale(1./mean_tlive,"width");

	 hCrs_Etot_NoVETO[i]->Sumw2();
	 hCrs_Etot_NoVETO[i]->Scale(1./mean_tlive,"width");

	 hCrs_Eseed_NoVETO[i]->Sumw2();
	 hCrs_Eseed_NoVETO[i]->Scale(1./mean_tlive,"width");

 }



  while (obj = iter.Next()) {
    Info("Terminate", "obj: %s", obj->GetName());
  }
  Info("Terminate", "No more objs");
  
 
 
  
  

  cout << "*********"<<endl;
  cout << eventNumber<<endl;
  

  
 

  
  
  /*if (doTree) {
    outProofFile = dynamic_cast<TProofOutputFile*>(fOutput->FindObject("BDXDSTSELECTOR.root"));
    TString outputFile(outProofFile->GetOutputFileName());
    //Info("Terminate", "outputFile is: %s", outputFile.c_str());
    
    outFile = TFile::Open(outputFile);
    if (outFile) {
      outTree = (TTree*) outFile->Get("outTree");
      
      }
    
  }*/
}


