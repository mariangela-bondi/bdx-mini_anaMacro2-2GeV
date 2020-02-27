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

	hHALLA_cur_beam = new TH2D("hHALLA_cur_beam", "hHALLA_cur_beam;T(s);Current(uA)", N, 0, N * dT, 200, 0, 200);
	hHALLA_cur_cosmic = new TH2D("hHALLA_cur_cosmic", "hHALLA_cur_cosmic;T(s);Current(uA)", N, 0, N * dT, 200, 0, 200);
	hHALLA_cur_garbage = new TH2D("hHALLA_cur_garbage", "hHALLA_cur_garbage;T(s);Current(uA)", N, 0, N * dT, 200, 0, 200);
//	hTlive = new TH2D("hTlive", "hTlive;T(s);Live Time(%)", N, 0, N * dT, 100, 0, 100.);


	// HISTO VETO
	int Nbin_Atot = 201;
	int min_Atot =-0.5;
	int max_Atot = 2000.5;

	if(isMC ==0){
    hOV_Atot_beam = new TH1D("hOV_Atot_beam", "hOV_Atot_beam; phe;Counts", Nbin_Atot, min_Atot, max_Atot);
    hOV_multiplicity_beam = new TH1D("hOV_multiplicity_beam", "hOV_multiplicity_beam; multiplicity;Counts", 11,-0.5,10.5);
	hIV_Atot_beam = new TH1D("hIV_Atot_beam", "hIV_Atot_beam; phe;Counts", Nbin_Atot, min_Atot, max_Atot);
	hIV_multiplicity_beam = new TH1D("hIV_multiplicity_beam", "hIV_multiplicity_beam; multiplicity;Counts", 11,-0.5,10.5);
	hOV_Atot_vs_multiplicity_beam = new TH2D("hOV_Atot_vs_multiplicity_beam", "hOV_Atot_vs_multiplicity_beam; phe;multiplicity", Nbin_Atot, min_Atot, max_Atot, 11,-0.5,10.5);
	hIV_Atot_vs_multiplicity_beam = new TH2D("hIV_Atot_vs_multiplicity_beam", "hIV_Atot_vs_multiplicity_beam; phe;multiplicity", Nbin_Atot, min_Atot, max_Atot, 11,-0.5,10.5);

    hOV_Atot_cosmic = new TH1D("hOV_Atot_cosmic", "hOV_Atot_cosmic; phe;Counts", Nbin_Atot, min_Atot, max_Atot);
    hOV_multiplicity_cosmic = new TH1D("hOV_multiplicity_cosmic", "hOV_multiplicity_cosmic; multiplicity;Counts", 11,-0.5,10.5);
	hIV_Atot_cosmic= new TH1D("hIV_Atot_cosmic", "hIV_Atot_cosmic; phe;Counts",Nbin_Atot, min_Atot, max_Atot);
	hIV_multiplicity_cosmic = new TH1D("hIV_multiplicity_cosmic", "hIV_multiplicity_cosmic; multiplicity;Counts", 11,-0.5,10.5);
	hOV_Atot_vs_multiplicity_cosmic = new TH2D("hOV_Atot_vs_multiplicity_cosmic", "hOV_Atot_vs_multiplicity_cosmic; phe;multiplicity", Nbin_Atot, min_Atot, max_Atot, 11,-0.5,10.5);
	hIV_Atot_vs_multiplicity_cosmic = new TH2D("hIV_Atot_vs_multiplicity_cosmic", "hIV_Atot_vs_multiplicity_cosmic; phe;multiplicity", Nbin_Atot, min_Atot, max_Atot, 11,-0.5,10.5);
	}else{
    hOV_Atot_MC = new TH1D("hOV_Atot_MC", "hOV_Atot_MC; phe;Counts", Nbin_Atot, min_Atot, max_Atot);
    hOV_multiplicity_MC = new TH1D("hOV_multiplicity_MC", "hOV_multiplicity_MC; multiplicity;Counts", 11,-0.5,10.5);
	hIV_Atot_MC= new TH1D("hIV_Atot_MC", "hIV_Atot_MC; phe;Counts", Nbin_Atot, min_Atot, max_Atot);
	hIV_multiplicity_MC = new TH1D("hIV_multiplicity_MC", "hIV_multiplicity_MC; multiplicity;Counts", 11,-0.5,10.5);
	hOV_Atot_vs_multiplicity_MC = new TH2D("hOV_Atot_vs_multiplicity_MC", "hOV_Atot_vs_multiplicity_MC; phe;multiplicity", Nbin_Atot, min_Atot, max_Atot, 11,-0.5,10.5);
	hIV_Atot_vs_multiplicity_MC = new TH2D("hIV_Atot_vs_multiplicity_MC", "hIV_Atot_vs_multiplicity_MC; phe;multiplicity", Nbin_Atot, min_Atot, max_Atot, 11,-0.5,10.5);
	}

	// HISTO CALORIMETER

	int Nbin_Etot = 3000;
	int min_Etot =-0.5;
	int max_Etot = 2999.5;

	if(isMC ==0){
	hCrs_Etot_beam = new TH1D("hCrs_Etot_beam", "hCrs_Etot_beam; Etot [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_multiplicity_beam = new TH1D("hCrs_multiplicity_beam", "hCrs_multiplicity_beam; multiplicity; counts", 45, -0.5, 44.5);
	hCrs_Eseed_beam = new TH1D("hCrs_Eseed_beam", "hCrs_Eseed_beam; Eseed [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_Etop_beam = new TH1D("hCrs_Etop_beam", "hCrs_Etop_beam; Etop [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_Ebottom_beam = new TH1D("hCrs_Ebottom_beam", "hCrs_Ebottom_beam; Ebottom [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_R_EtopEtot_beam = new TH1D("hCrs_R_EtopEtot_beam", "hCrs_R_EtopEtot_beam; Etop/Etot; counts", 110, -0.5, 1.5);
	hCrs_R_EbottomEtot_beam = new TH1D("hCrs_R_EbottomEtot_beam", "hCrs_R_EbottomEtot_beam; Ebottom/Etot; counts", 110, -0.5, 1.5);
	hCrs_EtotVsEtop_beam = new TH2D("hCrs_EtotVsEtop_beam","hCrs_EtotVsEtop_beam; Etot [MeV]; Etop [MeV]",Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_XYseed_beam = new TH2D("hCrs_XYseed_beam","hCrs_XYseed_beam; X; Y",11,-5.5,5.5,11,-5.5,5.5);
	hCrs_XY_XYseed_beam = new TH2D("hCrs_XY_XYseed_beam","hCrs_XY_XYseed_beam; X-Xseed; Y-Yseed",11,-5.5,5.5,11,-5.5,5.5);
	hCrs_EseedVSEtot_beam = new TH2D("hCrs_EseedVSEtot_beam","hCrs_EseedVSEtot_beam; Eseed [MeV]; Etot [MeV]",Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EseedVSMulti_beam = new TH2D("hCrs_EseedVSMulti_beam","hCrs_EseedVSMulti_beam; Eseed [MeV]; Multiplicity",Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtotVSMulti_beam = new TH2D("hCrs_EtotVSMulti_beam","hCrs_EtotVSMulti_beam; Etot [MeV]; Multiplicity",Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);

	hCrs_Etot_cosmic = new TH1D("hCrs_Etot_cosmic", "hCrs_Etot_cosmic; Etot [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_multiplicity_cosmic = new TH1D("hCrs_multiplicity_cosmic", "hCrs_multiplicity_cosmic; multiplicity; counts", 45, -0.5, 44.5);
	hCrs_Eseed_cosmic = new TH1D("hCrs_Eseed_cosmic", "hCrs_Eseed_cosmic; Eseed [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_Etop_cosmic = new TH1D("hCrs_Etop_cosmic", "hCrs_Etop_cosmic; Etop [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_Ebottom_cosmic = new TH1D("hCrs_Ebottom_cosmic", "hCrs_Ebottom_cosmic; Ebottom [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_R_EtopEtot_cosmic = new TH1D("hCrs_R_EtopEtot_cosmic", "hCrs_R_EtopEtot_cosmic; Etop/Etot; counts", 110, -0.5, 1.5);
	hCrs_R_EbottomEtot_cosmic = new TH1D("hCrs_R_EbottomEtot_cosmic", "hCrs_R_EbottomEtot_cosmic; Ebottom/Etot; counts", 110, -0.5, 1.5);
	hCrs_EtotVsEtop_cosmic = new TH2D("hCrs_EtotVsEtop_cosmic","hCrs_EtotVsEtop_cosmic; Etot [MeV]; Etop [MeV]",Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
    hCrs_XYseed_cosmic = new TH2D("hCrs_XYseed_cosmic","hCrs_XYseed_cosmic; X; Y",11,-5.5,5.5,11,-5.5,5.5);
    hCrs_XY_XYseed_cosmic = new TH2D("hCrs_XY_XYseed_cosmic","hCrs_XY_XYseed_cosmic; X-Xseed; Y-Yseed",11,-5.5,5.5,11,-5.5,5.5);
    hCrs_EseedVSEtot_cosmic = new TH2D("hCrs_EseedVSEtot_cosmic","hCrs_EseedVSEtot_cosmic; Eseed [MeV]; Etot [MeV]",Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EseedVSMulti_cosmic = new TH2D("hCrs_EseedVSMulti_cosmic","hCrs_EseedVSMulti_cosmic; Eseed [MeV]; Multiplicity",Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtotVSMulti_cosmic = new TH2D("hCrs_EtotVSMulti_cosmic","hCrs_EtotVSMulti_cosmic; Etot [MeV]; Multiplicity",Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);

	}else{

	hCrs_Etot_MC = new TH1D("hCrs_Etot_MC", "hCrs_Etot_MC; Etot [MeV]; events/(EOT*MeV)", Nbin_Etot, min_Etot, max_Etot);
	hCrs_multiplicity_MC = new TH1D("hCrs_multiplicity_MC", "hCrs_multiplicity_MC; multiplicity; ", 45, -0.5, 44.5);
	hCrs_Eseed_MC = new TH1D("hCrs_Eseed_MC", "hCrs_Eseed_MC; Eseed [MeV]; events/(EOT*MeV)", Nbin_Etot, min_Etot, max_Etot);
	hCrs_Etop_MC = new TH1D("hCrs_Etop_MC", "hCrs_Etop_MC; Etop [MeV]; events/(EOT*MeV)", Nbin_Etot, min_Etot, max_Etot);
	hCrs_Ebottom_MC = new TH1D("hCrs_Ebottom_MC", "hCrs_Ebottom_MC; Ebottom [MeV]; events/(EOT*MeV)", Nbin_Etot, min_Etot, max_Etot);
	hCrs_R_EtopEtot_MC = new TH1D("hCrs_R_EtopEtot_MC", "hCrs_R_EtopEtot_MC; Etop/Etot; ", 110, -0.5, 1.5);
	hCrs_R_EbottomEtot_MC = new TH1D("hCrs_R_EbottomEtot_MC", "hCrs_R_EbottomEtot_MC; Ebottom/Etot; ", 110, -0.5, 1.5);
	hCrs_EtotVsEtop_MC = new TH2D("hCrs_EtotVsEtop_MC","hCrs_EtotVsEtop_MC; Etot [MeV]; Etop [MeV]",Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_XYseed_MC = new TH2D("hCrs_XYseed_MC","hCrs_XYseed_MC; X; Y",11,-5.5,5.5,11,-5.5,5.5);
	hCrs_XY_XYseed_MC = new TH2D("hCrs_XY_XYseed_MC","hCrs_XY_XYseed_MC; X-Xseed; Y-Yseed",11,-5.5,5.5,11,-5.5,5.5);
	hCrs_EseedVSEtot_MC = new TH2D("hCrs_EseedVSEtot_MC","hCrs_EseedVSEtot_MC; Eseed [MeV]; Etot [MeV]",Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EseedVSMulti_MC = new TH2D("hCrs_EseedVSMulti_MC","hCrs_EseedVSMulti_MC; Eseed [MeV]; Multiplicity",Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtotVSMulti_MC = new TH2D("hCrs_EtotVSMulti_MC","hCrs_EtotVSMulti_MC; Etot [MeV]; Multiplicity",Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	}

	// HISTO CALORIMETER NO VETO

	if(isMC ==0){
	hCrs_Etot_NoVETO_beam = new TH1D("hCrs_Etot_NoVETO_beam", "hCrs_Etot_NoVETO_beam; Etot [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_multiplicity_NoVETO_beam = new TH1D("hCrs_multiplicity_NoVETO_beam", "hCrs_multiplicity_NoVETO_beam; multiplicity; counts", 45, -0.5, 44.5);
	hCrs_Eseed_NoVETO_beam = new TH1D("hCrs_Eseed_NoVETO_beam", "hCrs_Eseed_NoVETO_beam; Eseed [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_Etop_NoVETO_beam = new TH1D("hCrs_Etop_NoVETO_beam", "hCrs_Etop_NoVETO_beam; Etop [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_Ebottom_NoVETO_beam = new TH1D("hCrs_Ebottom_NoVETO_beam", "hCrs_Ebottom_NoVETO_beam; Ebottom [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_R_EtopEtot_NoVETO_beam = new TH1D("hCrs_R_EtopEtot_NoVETO_beam", "hCrs_R_EtopEtot_NoVETO_beam; Etop/Etot; counts", 110, -0.5, 1.5);
	hCrs_R_EbottomEtot_NoVETO_beam = new TH1D("hCrs_R_EbottomEtot_NoVETO_beam", "hCrs_R_EbottomEtot_NoVETO_beam; Ebottom/Etot; counts", 110, -0.5, 1.5);
	hCrs_EtotVsEtop_NoVETO_beam = new TH2D("hCrs_EtotVsEtop_NoVETO_beam","hCrs_EtotVsEtop_NoVETO_beam; Etot [MeV]; Etop [MeV]",Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_XYseed_NoVETO_beam = new TH2D("hCrs_XYseed_NoVETO_beam","hCrs_XYseed_NoVETO_beam; X; Y",11,-5.5,5.5,11,-5.5,5.5);
	hCrs_XY_XYseed_NoVETO_beam = new TH2D("hCrs_XY_XYseed_NoVETO_beam","hCrs_XY_XYseed_NoVETO_beam; X-Xseed; Y-Yseed",11,-5.5,5.5,11,-5.5,5.5);
	hCrs_EseedVSEtot_NoVETO_beam = new TH2D("hCrs_EseedVSEtot_NoVETO_beam","hCrs_EseedVSEtot_NoVETO_beam; Eseed [MeV]; Etot [MeV]",Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EseedVSMulti_NoVETO_beam = new TH2D("hCrs_EseedVSMulti_NoVETO_beam","hCrs_EseedVSMulti_NoVETO_beam; Eseed [MeV]; Multiplicity",Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtotVSMulti_NoVETO_beam = new TH2D("hCrs_EtotVSMulti_NoVETO_beam","hCrs_EtotVSMulti_NoVETO_beam; Etot [MeV]; Multiplicity",Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);

	hCrs_Etot_NoVETO_cosmic = new TH1D("hCrs_Etot_NoVETO_cosmic", "hCrs_Etot_NoVETO_cosmic; Etot [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_multiplicity_NoVETO_cosmic = new TH1D("hCrs_multiplicity_NoVETO_cosmic", "hCrs_multiplicity_NoVETO_cosmic; multiplicity; counts", 45, -0.5, 44.5);
	hCrs_Eseed_NoVETO_cosmic = new TH1D("hCrs_Eseed_NoVETO_cosmic", "hCrs_Eseed_NoVETO_cosmic; Eseed [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_Etop_NoVETO_cosmic = new TH1D("hCrs_Etop_NoVETO_cosmic", "hCrs_Etop_NoVETO_cosmic; Etop [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_Ebottom_NoVETO_cosmic = new TH1D("hCrs_Ebottom_NoVETO_cosmic", "hCrs_Ebottom_NoVETO_cosmic; Ebottom [MeV]; Hz/MeV", Nbin_Etot, min_Etot, max_Etot);
	hCrs_R_EtopEtot_NoVETO_cosmic = new TH1D("hCrs_R_EtopEtot_NoVETO_cosmic", "hCrs_R_EtopEtot_NoVETO_cosmic; Etop/Etot; counts", 110, -0.5, 1.5);
	hCrs_R_EbottomEtot_NoVETO_cosmic = new TH1D("hCrs_R_EbottomEtot_NoVETO_cosmic", "hCrs_R_EbottomEtot_NoVETO_cosmic; Ebottom/Etot; counts", 110, -0.5, 1.5);
	hCrs_EtotVsEtop_NoVETO_cosmic = new TH2D("hCrs_EtotVsEtop_NoVETO_cosmic","hCrs_EtotVsEtop_NoVETO_cosmic; Etot [MeV]; Etop [MeV]",Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
    hCrs_XYseed_NoVETO_cosmic = new TH2D("hCrs_XYseed_NoVETO_cosmic","hCrs_XYseed_NoVETO_cosmic; X; Y",11,-5.5,5.5,11,-5.5,5.5);
	hCrs_XY_XYseed_NoVETO_cosmic = new TH2D("hCrs_XY_XYseed_NoVETO_cosmic","hCrs_XY_XYseed_NoVETO_cosmic; X-Xseed; Y-Yseed",11,-5.5,5.5,11,-5.5,5.5);
    hCrs_EseedVSEtot_NoVETO_cosmic = new TH2D("hCrs_EseedVSEtot_NoVETO_cosmic","hCrs_EseedVSEtot_NoVETO_cosmic; Eseed [MeV]; Etot [MeV]",Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EseedVSMulti_NoVETO_cosmic = new TH2D("hCrs_EseedVSMulti_NoVETO_cosmic","hCrs_EseedVSMulti_NoVETO_cosmic; Eseed [MeV]; Multiplicity",Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtotVSMulti_NoVETO_cosmic = new TH2D("hCrs_EtotVSMulti_NoVETO_cosmic","hCrs_EtotVSMulti_NoVETO_cosmic; Etot [MeV]; Multiplicity",Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);

	}else{

	hCrs_Etot_NoVETO_MC = new TH1D("hCrs_Etot_NoVETO_MC", "hCrs_Etot_NoVETO_MC; Etot [MeV]; events/(EOT*MeV)", Nbin_Etot, min_Etot, max_Etot);
	hCrs_multiplicity_NoVETO_MC = new TH1D("hCrs_multiplicity_NoVETO_MC", "hCrs_multiplicity_NoVETO_MC; multiplicity; counts", 45, -0.5, 44.5);
	hCrs_Eseed_NoVETO_MC = new TH1D("hCrs_Eseed_NoVETO_MC", "hCrs_Eseed_NoVETO_MC; Eseed [MeV]; events/(EOT*MeV)", Nbin_Etot, min_Etot, max_Etot);
	hCrs_Etop_NoVETO_MC = new TH1D("hCrs_Etop_NoVETO_MC", "hCrs_Etop_NoVETO_MC; Etop [MeV]; events/(EOT*MeV)", Nbin_Etot, min_Etot, max_Etot);
	hCrs_Ebottom_NoVETO_MC = new TH1D("hCrs_Ebottom_NoVETO_MC", "hCrs_Ebottom_NoVETO_MC; Ebottom [MeV]; events/(EOT*MeV)", Nbin_Etot, min_Etot, max_Etot);
	hCrs_R_EtopEtot_NoVETO_MC = new TH1D("hCrs_R_EtopEtot_NoVETO_MC", "hCrs_R_EtopEtot_NoVETO_MC; Etop/Etot; ", 110, -0.5, 1.5);
	hCrs_R_EbottomEtot_NoVETO_MC = new TH1D("hCrs_R_EbottomEtot_NoVETO_MC", "hCrs_R_EbottomEtot_NoVETO_MC; Ebottom/Etot; ", 110, -0.5, 1.5);
	hCrs_EtotVsEtop_NoVETO_MC = new TH2D("hCrs_EtotVsEtop_NoVETO_MC","hCrs_EtotVsEtop_NoVETO_MC; Etot [MeV]; Etop [MeV]",Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_XYseed_NoVETO_MC = new TH2D("hCrs_XYseed_NoVETO_MC","hCrs_XYseed_NoVETO_MC; X; Y",11,-5.5,5.5,11,-5.5,5.5);
	hCrs_XY_XYseed_NoVETO_MC = new TH2D("hCrs_XY_XYseed_NoVETO_MC","hCrs_XY_XYseed_NoVETO_MC; X-Xseed; Y-Yseed",11,-5.5,5.5,11,-5.5,5.5);
	hCrs_EseedVSEtot_NoVETO_MC = new TH2D("hCrs_EseedVSEtot_NoVETO_MC","hCrs_EseedVSEtot_NoVETO_MC; Eseed [MeV]; Etot [MeV]",Nbin_Etot, min_Etot, max_Etot, Nbin_Etot, min_Etot, max_Etot);
	hCrs_EseedVSMulti_NoVETO_MC = new TH2D("hCrs_EseedVSMulti_NoVETO_MC","hCrs_EseedVSMulti_NoVETO_MC; Eseed [MeV]; Multiplicity",Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	hCrs_EtotVSMulti_NoVETO_MC = new TH2D("hCrs_EtotVSMulti_NoVETO_MC","hCrs_EtotVSMulti_NoVETO_MC; Etot [MeV]; Multiplicity",Nbin_Etot, min_Etot, max_Etot,45, -0.5, 44.5);
	}



	outTree1 = new TTree("outTree1", "outTree1");
	
	outTree1->Branch("runNumber", &runNumber, "runNumber/I");
	outTree1->Branch("eventNumber", &eventNumber, "eventNumber/I");



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

	int multiplicity_OV =0;
	int multiplicity_IV =0;

	bool noOV =false;
	bool noIV =false;


	///CRS  Variables ///
	double E_singleCrs_thr = 10; //minima energia misurabile
	double Etot = 0;
	double Etop = 0;
	double Ebottom = 0;
	double Eseed = 0;
	double Ehit =0;
	int multip = 0;
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


if(isGarbage==true) hHALLA_cur_garbage->Fill(thisEventT, current);
	}


if((isGarbage==false)||(isMC==1)){

     if(isMC==0 && current==0) isCosmic=true;
     if(isMC==0 && current>0) isBeam =true;

	 if(isMC==0 && isCosmic==true) hHALLA_cur_cosmic->Fill(thisEventT, current);
	 if(isMC==0 && isBeam==true) hHALLA_cur_beam->Fill(thisEventT, current);




	/*Check if the event has a collection named IntVetoHits and the corresponding objects are IntVetoHit objects*/

	if (m_Event->hasCollection(IntVetoHit::Class(), "IntVetoHits")) {
	  TIter IntVetoHitsIter(m_Event->getCollection(IntVetoHit::Class(), "IntVetoHits"));
	  while (fIntVetoHit = (IntVetoHit*) IntVetoHitsIter.Next()) { //Need to cast to the proper object

		  if (fIntVetoHit->m_channel.layer == 0 && fIntVetoHit->m_channel.component!=3) {
			  OVAtot += fIntVetoHit->A;
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

	if(multiplicity_OV==0 && (OVAtot <= Veto_Atot_th )) noOV= true;
	if(multiplicity_IV==0 && (IVAtot <= Veto_Atot_th )) noIV= true;


	cout << weight<<endl;
	//HISTO VETO

	if(isMC==0){
	  if(isBeam==1){
        hOV_Atot_beam->Fill(OVAtot, weight);
        hOV_multiplicity_beam->Fill(multiplicity_OV, weight);
	    hIV_Atot_beam ->Fill(IVAtot, weight);
	    hIV_multiplicity_beam->Fill(multiplicity_IV, weight);
	    hOV_Atot_vs_multiplicity_beam->Fill(OVAtot, multiplicity_OV, weight);
	    hIV_Atot_vs_multiplicity_beam->Fill(IVAtot, multiplicity_IV, weight);
	  }
	  if(isCosmic==1){
        hOV_Atot_cosmic->Fill(OVAtot, weight);
        hOV_multiplicity_cosmic->Fill(multiplicity_OV, weight);
	    hIV_Atot_cosmic->Fill(IVAtot, weight);
	    hIV_multiplicity_cosmic->Fill(multiplicity_IV, weight);
	    hOV_Atot_vs_multiplicity_cosmic->Fill(OVAtot, multiplicity_OV, weight);
	    hIV_Atot_vs_multiplicity_cosmic->Fill(IVAtot, multiplicity_IV, weight);
	  }
	}else{
    hOV_Atot_MC ->Fill(OVAtot, weight);
    hOV_multiplicity_MC->Fill(multiplicity_OV, weight);
	hIV_Atot_MC->Fill(IVAtot, weight);
	hIV_multiplicity_MC->Fill(multiplicity_IV, weight);
	hOV_Atot_vs_multiplicity_MC->Fill(OVAtot, multiplicity_OV, weight);
	hIV_Atot_vs_multiplicity_MC->Fill(IVAtot, multiplicity_IV, weight);
	}


	/*Check if the event has a collection named CalorimeterHits, and the corresponding objects are CalorimeterHit objects*/
	if (m_Event->hasCollection(CalorimeterHit::Class(), "CalorimeterHits")) {
	  TIter CaloHitsIter(m_Event->getCollection(CalorimeterHit::Class(), "CalorimeterHits"));
	  //thisEventT = m_Event->getEventHeader()->getEventTime() - T0;

	  while (fCaloHit = (CalorimeterHit*) CaloHitsIter.Next()) { //Need to cast to the proper object

	    Ehit=0;
	    //MINIMUM ENERGY PER CRS //
	    if(fCaloHit->E > E_singleCrs_thr){

	      //Multiplicity//
	      multip ++;

	      //Hit Energy//
	      Ehit =  (fCaloHit->E);

	      // Total Energy
	      Etot = Etot + Ehit;

	      int sector =  fCaloHit->m_channel.sector;

	      // Top Energy
	      if(fCaloHit->m_channel.sector ==0) Etop = Etop + Ehit;

	      // Bottom Energy
	      if(fCaloHit->m_channel.sector ==1) Ebottom = Ebottom + Ehit;


	      // Eseed, Seed XY //
	      if(Ehit>Eseed){
		Eseed = Ehit;
		Xseed = fCaloHit->m_channel.x;
		Yseed = fCaloHit->m_channel.y;
		Zseed = fCaloHit->m_channel.sector;
	      }
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
	    		if(isMC==0){
	    	     if(isBeam==1) hCrs_XY_XYseed_beam->Fill(Xs,Ys,(weight));
	    	     if(isCosmic==1) hCrs_XY_XYseed_cosmic->Fill(Xs,Ys,(weight));

	    	     if(isBeam==1 && noOV==1 && noIV==1)hCrs_XY_XYseed_NoVETO_beam->Fill(Xs,Ys,(weight));
	    	     if(isCosmic==1 && noOV==1 && noIV==1)hCrs_XY_XYseed_NoVETO_cosmic->Fill(Xs,Ys,(weight));
	    		}else{
	    	     hCrs_XY_XYseed_MC->Fill(Xs,Ys,(weight));
	    	     if(noOV==1 && noIV==1) hCrs_XY_XYseed_NoVETO_MC->Fill(Xs,Ys,(weight));
	           }
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
	if(isMC==0){
     if(isBeam==1){
	   hCrs_Etot_beam->Fill(Etot, weight);
	   hCrs_multiplicity_beam->Fill(multip, weight);
       hCrs_Eseed_beam->Fill(Eseed, weight);
	   hCrs_Etop_beam->Fill(Etop, weight);
	   hCrs_Ebottom_beam->Fill(Ebottom, weight);
	   hCrs_R_EtopEtot_beam->Fill(Etop/Etot, weight);
	   hCrs_R_EbottomEtot_beam->Fill(Ebottom/Etot, weight);
	   hCrs_EtotVsEtop_beam->Fill(Etot, Etop, weight);
       hCrs_XYseed_beam->Fill(Xseed, Yseed, weight);
	   hCrs_EseedVSEtot_beam->Fill(Eseed, Etot, weight);
	   hCrs_EseedVSMulti_beam->Fill(Eseed, multip, weight);
	   hCrs_EtotVSMulti_beam->Fill(Etot, multip, weight);
     }
     if(isCosmic==1){
  	   hCrs_Etot_cosmic->Fill(Etot, weight);
  	   hCrs_multiplicity_cosmic->Fill(multip, weight);
       hCrs_Eseed_cosmic->Fill(Eseed, weight);
  	   hCrs_Etop_cosmic->Fill(Etop, weight);
  	   hCrs_Ebottom_cosmic->Fill(Ebottom, weight);
  	   hCrs_R_EtopEtot_cosmic->Fill(Etop/Etot, weight);
  	   hCrs_R_EbottomEtot_cosmic->Fill(Ebottom/Etot, weight);
  	   hCrs_EtotVsEtop_cosmic->Fill(Etot, Etop, weight);
       hCrs_XYseed_cosmic->Fill(Xseed, Yseed, weight);
  	   hCrs_EseedVSEtot_cosmic->Fill(Eseed, Etot, weight);
  	   hCrs_EseedVSMulti_cosmic->Fill(Eseed, multip, weight);
  	   hCrs_EtotVSMulti_cosmic->Fill(Etot, multip, weight);

     }

	}else{
	 hCrs_Etot_MC->Fill(Etot, weight);
	 hCrs_multiplicity_MC->Fill(multip, weight);
	 hCrs_Eseed_MC->Fill(Eseed, weight);
	 hCrs_Etop_MC->Fill(Etop, weight);
	 hCrs_Ebottom_MC->Fill(Ebottom, weight);
	 hCrs_R_EtopEtot_MC->Fill(Etop/Etot, weight);
	 hCrs_R_EbottomEtot_MC->Fill(Ebottom/Etot, weight);
	 hCrs_EtotVsEtop_MC->Fill(Ebottom/Etot, Etop/Etot, weight);
	 hCrs_XYseed_MC->Fill(Xseed, Yseed, weight);
	 hCrs_EseedVSEtot_MC->Fill(Eseed, Etot, weight);
	 hCrs_EseedVSMulti_MC->Fill(Eseed, multip, weight);
	 hCrs_EtotVSMulti_MC->Fill(Etot, multip, weight);

	}

	}


	if(Etot>E_singleCrs_thr && noOV==1 && noIV==1){
	if(isMC==0){
     if(isBeam==1){
	   hCrs_Etot_NoVETO_beam->Fill(Etot, weight);
	   hCrs_multiplicity_NoVETO_beam->Fill(multip, weight);
       hCrs_Eseed_NoVETO_beam->Fill(Eseed, weight);
	   hCrs_Etop_NoVETO_beam->Fill(Etop, weight);
	   hCrs_Ebottom_NoVETO_beam->Fill(Ebottom, weight);
	   hCrs_R_EtopEtot_NoVETO_beam->Fill(Etop/Etot, weight);
	   hCrs_R_EbottomEtot_NoVETO_beam->Fill(Ebottom/Etot, weight);
	   hCrs_EtotVsEtop_NoVETO_beam->Fill(Etot, Etop, weight);
       hCrs_XYseed_NoVETO_beam->Fill(Xseed, Yseed, weight);
	   hCrs_EseedVSEtot_NoVETO_beam->Fill(Eseed, Etot, weight);
	   hCrs_EseedVSMulti_NoVETO_beam->Fill(Eseed, multip, weight);
	   hCrs_EtotVSMulti_NoVETO_beam->Fill(Etot, multip, weight);
     }
     if(isCosmic==1){
  	   hCrs_Etot_NoVETO_cosmic->Fill(Etot, weight);
  	   hCrs_multiplicity_NoVETO_cosmic->Fill(multip, weight);
       hCrs_Eseed_NoVETO_cosmic->Fill(Eseed, weight);
  	   hCrs_Etop_NoVETO_cosmic->Fill(Etop, weight);
  	   hCrs_Ebottom_NoVETO_cosmic->Fill(Ebottom, weight);
  	   hCrs_R_EtopEtot_NoVETO_cosmic->Fill(Etop/Etot, weight);
  	   hCrs_R_EbottomEtot_NoVETO_cosmic->Fill(Ebottom/Etot, weight);
  	   hCrs_EtotVsEtop_NoVETO_cosmic->Fill(Etot, Etop, weight);
       hCrs_XYseed_NoVETO_cosmic->Fill(Xseed, Yseed, weight);
  	   hCrs_EseedVSEtot_NoVETO_cosmic->Fill(Eseed, Etot, weight);
  	   hCrs_EseedVSMulti_NoVETO_cosmic->Fill(Eseed, multip, weight);
  	   hCrs_EtotVSMulti_NoVETO_cosmic->Fill(Etot, multip, weight);

     }

	}else{
	 hCrs_Etot_NoVETO_MC->Fill(Etot, weight);
	 hCrs_multiplicity_NoVETO_MC->Fill(multip, weight);
	 hCrs_Eseed_NoVETO_MC->Fill(Eseed, weight);
	 hCrs_Etop_NoVETO_MC->Fill(Etop, weight);
	 hCrs_Ebottom_NoVETO_MC->Fill(Ebottom, weight);
	 hCrs_R_EtopEtot_NoVETO_MC->Fill(Etop/Etot, weight);
	 hCrs_R_EbottomEtot_NoVETO_MC->Fill(Ebottom/Etot, weight);
	 hCrs_EtotVsEtop_NoVETO_MC->Fill(Ebottom/Etot, Etop/Etot, weight);
	 hCrs_XYseed_NoVETO_MC->Fill(Xseed, Yseed, weight);
	 hCrs_EseedVSEtot_NoVETO_MC->Fill(Eseed, Etot, weight);
	 hCrs_EseedVSMulti_NoVETO_MC->Fill(Eseed, multip, weight);
	 hCrs_EtotVSMulti_NoVETO_MC->Fill(Etot, multip, weight);

	}

	}

}






	outTree1->Fill();
	

	//cout <<"end event"<<endl;
	
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


  hHALLA_cur_beam = (TH2D*)fOutput->FindObject("hHALLA_cur_beam");
  hHALLA_cur_cosmic = (TH2D*)fOutput->FindObject("hHALLA_cur_cosmic");
  hHALLA_cur_garbage = (TH2D*)fOutput->FindObject("hHALLA_cur_garbage");
  

  //HISTO VETO
  if(isMC==0){
  hOV_Atot_beam = (TH1D*)fOutput->FindObject("hOV_Atot_beam");
  hOV_multiplicity_beam = (TH1D*)fOutput->FindObject("hOV_multiplicity_beam");
  hIV_Atot_beam = (TH1D*)fOutput->FindObject("hIV_Atot_beam");
  hIV_multiplicity_beam = (TH1D*)fOutput->FindObject("hIV_multiplicity_beam");
  hOV_Atot_vs_multiplicity_beam = (TH2D*)fOutput->FindObject("hOV_Atot_vs_multiplicity_beam");
  hIV_Atot_vs_multiplicity_beam = (TH2D*)fOutput->FindObject("hIV_Atot_vs_multiplicity_beam");

  hOV_Atot_cosmic =(TH1D*)fOutput->FindObject("hOV_Atot_cosmic");
  hOV_multiplicity_cosmic = (TH1D*)fOutput->FindObject("hOV_multiplicity_cosmic");
  hIV_Atot_cosmic= (TH1D*)fOutput->FindObject("hIV_Atot_cosmic");
  hIV_multiplicity_cosmic = (TH1D*)fOutput->FindObject("hIV_multiplicity_cosmic");
  hOV_Atot_vs_multiplicity_cosmic = (TH2D*)fOutput->FindObject("hOV_Atot_vs_multiplicity_cosmic");
  hIV_Atot_vs_multiplicity_cosmic = (TH2D*)fOutput->FindObject("hIV_Atot_vs_multiplicity_cosmic");
  }else{
  hOV_Atot_MC = (TH1D*)fOutput->FindObject("hOV_Atot_MC");
  hOV_multiplicity_MC = (TH1D*)fOutput->FindObject("hOV_multiplicity_MC");
  hIV_Atot_MC= (TH1D*)fOutput->FindObject("hIV_Atot_MC");
  hIV_multiplicity_MC = (TH1D*)fOutput->FindObject("hIV_multiplicity_MC");
  hOV_Atot_vs_multiplicity_MC = (TH2D*)fOutput->FindObject("hOV_Atot_vs_multiplicity_MC");
  hIV_Atot_vs_multiplicity_MC = (TH2D*)fOutput->FindObject("hIV_Atot_vs_multiplicity_MC");
  }

  // HISTO CALORIMETER

 if(isMC==0){
  hCrs_Etot_beam = (TH1D*)fOutput->FindObject("hCrs_Etot_beam");
  hCrs_multiplicity_beam = (TH1D*)fOutput->FindObject("hCrs_multiplicity_beam");
  hCrs_Eseed_beam = (TH1D*)fOutput->FindObject("hCrs_Eseed_beam");
  hCrs_Etop_beam = (TH1D*)fOutput->FindObject("hCrs_Etop_beam");
  hCrs_Ebottom_beam = (TH1D*)fOutput->FindObject("hCrs_Ebottom_beam");
  hCrs_R_EtopEtot_beam = (TH1D*)fOutput->FindObject("hCrs_R_EtopEtot_beam");
  hCrs_R_EbottomEtot_beam = (TH1D*)fOutput->FindObject("hCrs_R_EbottomEtot_beam");
  hCrs_EtotVsEtop_beam = (TH2D*)fOutput->FindObject("hCrs_EtotVsEtop_beam");
  hCrs_XYseed_beam = (TH2D*)fOutput->FindObject("hCrs_XYseed_beam");
  hCrs_XY_XYseed_beam = (TH2D*)fOutput->FindObject("hCrs_XY_XYseed_beam");
  hCrs_EseedVSEtot_beam = (TH2D*)fOutput->FindObject("hCrs_EseedVSEtot_beam");
  hCrs_EseedVSMulti_beam = (TH2D*)fOutput->FindObject("hCrs_EseedVSMulti_beam");
  hCrs_EtotVSMulti_beam = (TH2D*)fOutput->FindObject("hCrs_EtotVSMulti_beam");


  hCrs_Etot_NoVETO_beam = (TH1D*)fOutput->FindObject("hCrs_Etot_NoVETO_beam");
  hCrs_multiplicity_NoVETO_beam = (TH1D*)fOutput->FindObject("hCrs_multiplicity_NoVETO_beam");
  hCrs_Eseed_NoVETO_beam = (TH1D*)fOutput->FindObject("hCrs_Eseed_NoVETO_beam");
  hCrs_Etop_NoVETO_beam = (TH1D*)fOutput->FindObject("hCrs_Etop_NoVETO_beam");
  hCrs_Ebottom_NoVETO_beam = (TH1D*)fOutput->FindObject("hCrs_Ebottom_NoVETO_beam");
  hCrs_R_EtopEtot_NoVETO_beam = (TH1D*)fOutput->FindObject("hCrs_R_EtopEtot_NoVETO_beam");
  hCrs_R_EbottomEtot_NoVETO_beam = (TH1D*)fOutput->FindObject("hCrs_R_EbottomEtot_NoVETO_beam");
  hCrs_EtotVsEtop_NoVETO_beam = (TH2D*)fOutput->FindObject("hCrs_EtotVsEtop_NoVETO_beam");
  hCrs_XYseed_NoVETO_beam = (TH2D*)fOutput->FindObject("hCrs_XYseed_NoVETO_beam");
  hCrs_XY_XYseed_NoVETO_beam = (TH2D*)fOutput->FindObject("hCrs_XY_XYseed_NoVETO_beam");
  hCrs_EseedVSEtot_NoVETO_beam = (TH2D*)fOutput->FindObject("hCrs_EseedVSEtot_NoVETO_beam");
  hCrs_EseedVSMulti_NoVETO_beam = (TH2D*)fOutput->FindObject("hCrs_EseedVSMulti_NoVETO_beam");
  hCrs_EtotVSMulti_NoVETO_beam = (TH2D*)fOutput->FindObject("hCrs_EtotVSMulti_NoVETO_beam");

 // COSMIC
  hCrs_Etot_cosmic = (TH1D*)fOutput->FindObject("hCrs_Etot_cosmic");
  hCrs_multiplicity_cosmic = (TH1D*)fOutput->FindObject("hCrs_multiplicity_cosmic");
  hCrs_Eseed_cosmic = (TH1D*)fOutput->FindObject("hCrs_Eseed_cosmic");
  hCrs_Etop_cosmic = (TH1D*)fOutput->FindObject("hCrs_Etop_cosmic");
  hCrs_Ebottom_cosmic = (TH1D*)fOutput->FindObject("hCrs_Ebottom_cosmic");
  hCrs_R_EtopEtot_cosmic = (TH1D*)fOutput->FindObject("hCrs_R_EtopEtot_cosmic");
  hCrs_R_EbottomEtot_cosmic = (TH1D*)fOutput->FindObject("hCrs_R_EbottomEtot_cosmic");
  hCrs_EtotVsEtop_cosmic = (TH2D*)fOutput->FindObject("hCrs_EtotVsEtop_cosmic");
  hCrs_XYseed_cosmic = (TH2D*)fOutput->FindObject("hCrs_XYseed_cosmic");
  hCrs_XY_XYseed_cosmic = (TH2D*)fOutput->FindObject("hCrs_XY_XYseed_cosmic");
  hCrs_EseedVSEtot_cosmic = (TH2D*)fOutput->FindObject("hCrs_EseedVSEtot_cosmic");
  hCrs_EseedVSMulti_cosmic = (TH2D*)fOutput->FindObject("hCrs_EseedVSMulti_cosmic");
  hCrs_EtotVSMulti_cosmic = (TH2D*)fOutput->FindObject("hCrs_EtotVSMulti_cosmic");

  hCrs_Etot_NoVETO_cosmic = (TH1D*)fOutput->FindObject("hCrs_Etot_NoVETO_cosmic");
  hCrs_multiplicity_NoVETO_cosmic = (TH1D*)fOutput->FindObject("hCrs_multiplicity_NoVETO_cosmic");
  hCrs_Eseed_NoVETO_cosmic = (TH1D*)fOutput->FindObject("hCrs_Eseed_NoVETO_cosmic");
  hCrs_Etop_NoVETO_cosmic = (TH1D*)fOutput->FindObject("hCrs_Etop_NoVETO_cosmic");
  hCrs_Ebottom_NoVETO_cosmic = (TH1D*)fOutput->FindObject("hCrs_Ebottom_NoVETO_cosmic");
  hCrs_R_EtopEtot_NoVETO_cosmic = (TH1D*)fOutput->FindObject("hCrs_R_EtopEtot_NoVETO_cosmic");
  hCrs_R_EbottomEtot_NoVETO_cosmic = (TH1D*)fOutput->FindObject("hCrs_R_EbottomEtot_NoVETO_cosmic");
  hCrs_EtotVsEtop_NoVETO_cosmic = (TH2D*)fOutput->FindObject("hCrs_EtotVsEtop_NoVETO_cosmic");
  hCrs_XYseed_NoVETO_cosmic = (TH2D*)fOutput->FindObject("hCrs_XYseed_NoVETO_cosmic");
  hCrs_XY_XYseed_NoVETO_cosmic = (TH2D*)fOutput->FindObject("hCrs_XY_XYseed_NoVETO_cosmic");
  hCrs_EseedVSEtot_NoVETO_cosmic = (TH2D*)fOutput->FindObject("hCrs_EseedVSEtot_NoVETO_cosmic");
  hCrs_EseedVSMulti_NoVETO_cosmic = (TH2D*)fOutput->FindObject("hCrs_EseedVSMulti_NoVETO_cosmic");
  hCrs_EtotVSMulti_NoVETO_cosmic = (TH2D*)fOutput->FindObject("hCrs_EtotVSMulti_NoVETO_cosmic");
 }else{
 // MC
  hCrs_Etot_MC = (TH1D*)fOutput->FindObject("hCrs_Etot_MC");
  hCrs_multiplicity_MC = (TH1D*)fOutput->FindObject("hCrs_multiplicity_MC");
  hCrs_Eseed_MC = (TH1D*)fOutput->FindObject("hCrs_Eseed_MC");
  hCrs_Etop_MC = (TH1D*)fOutput->FindObject("hCrs_Etop_MC");
  hCrs_Ebottom_MC = (TH1D*)fOutput->FindObject("hCrs_Ebottom_MC");
  hCrs_R_EtopEtot_MC = (TH1D*)fOutput->FindObject("hCrs_R_EtopEtot_MC");
  hCrs_R_EbottomEtot_MC = (TH1D*)fOutput->FindObject("hCrs_R_EbottomEtot_MC");
  hCrs_EtotVsEtop_MC = (TH2D*)fOutput->FindObject("hCrs_EtotVsEtop_MC");
  hCrs_XYseed_MC = (TH2D*)fOutput->FindObject("hCrs_XYseed_MC");
  hCrs_XY_XYseed_MC = (TH2D*)fOutput->FindObject("hCrs_XY_XYseed_MC");
  hCrs_EseedVSEtot_MC = (TH2D*)fOutput->FindObject("hCrs_EseedVSEtot_MC");
  hCrs_EseedVSMulti_MC = (TH2D*)fOutput->FindObject("hCrs_EseedVSMulti_MC");
  hCrs_EtotVSMulti_MC = (TH2D*)fOutput->FindObject("hCrs_EtotVSMulti_MC");

  hCrs_Etot_NoVETO_MC = (TH1D*)fOutput->FindObject("hCrs_Etot_NoVETO_MC");
  hCrs_multiplicity_NoVETO_MC = (TH1D*)fOutput->FindObject("hCrs_multiplicity_NoVETO_MC");
  hCrs_Eseed_NoVETO_MC = (TH1D*)fOutput->FindObject("hCrs_Eseed_NoVETO_MC");
  hCrs_Etop_NoVETO_MC = (TH1D*)fOutput->FindObject("hCrs_Etop_NoVETO_MC");
  hCrs_Ebottom_NoVETO_MC = (TH1D*)fOutput->FindObject("hCrs_Ebottom_NoVETO_MC");
  hCrs_R_EtopEtot_NoVETO_MC = (TH1D*)fOutput->FindObject("hCrs_R_EtopEtot_NoVETO_MC");
  hCrs_R_EbottomEtot_NoVETO_MC = (TH1D*)fOutput->FindObject("hCrs_R_EbottomEtot_NoVETO_MC");
  hCrs_EtotVsEtop_NoVETO_MC = (TH2D*)fOutput->FindObject("hCrs_EtotVsEtop_NoVETO_MC");
  hCrs_XYseed_NoVETO_MC = (TH2D*)fOutput->FindObject("hCrs_XYseed_NoVETO_MC");
  hCrs_XY_XYseed_NoVETO_MC = (TH2D*)fOutput->FindObject("hCrs_XY_XYseed_NoVETO_MC");
  hCrs_EseedVSEtot_NoVETO_MC = (TH2D*)fOutput->FindObject("hCrs_EseedVSEtot_NoVETO_MC");
  hCrs_EseedVSMulti_NoVETO_MC = (TH2D*)fOutput->FindObject("hCrs_EseedVSMulti_NoVETO_MC");
  hCrs_EtotVSMulti_NoVETO_MC = (TH2D*)fOutput->FindObject("hCrs_EtotVSMulti_NoVETO_MC");
 }

 if(isMC==0){

	 hCrs_Etot_beam->Sumw2();
	 hCrs_Etot_beam->Scale(1./BDX_time_beam.size(),"width");

	 hCrs_Eseed_beam->Sumw2();
	 hCrs_Eseed_beam->Scale(1./BDX_time_beam.size(),"width");

	 hCrs_Etot_cosmic->Sumw2();
	 hCrs_Etot_cosmic->Scale(1./BDX_time_cosmic.size(),"width");

	 hCrs_Eseed_cosmic->Sumw2();
	 hCrs_Eseed_cosmic->Scale(1./BDX_time_cosmic.size(),"width");

	 hCrs_Etot_NoVETO_beam->Sumw2();
	 hCrs_Etot_NoVETO_beam->Scale(1./BDX_time_beam.size(),"width");

	 hCrs_Eseed_NoVETO_beam->Sumw2();
	 hCrs_Eseed_NoVETO_beam->Scale(1./BDX_time_beam.size(),"width");

	 hCrs_Etot_NoVETO_cosmic->Sumw2();
	 hCrs_Etot_NoVETO_cosmic->Scale(1./BDX_time_cosmic.size(),"width");

	 hCrs_Eseed_NoVETO_cosmic->Sumw2();
	 hCrs_Eseed_NoVETO_cosmic->Scale(1./BDX_time_cosmic.size(),"width");

 }

if(isMC == 1){
	 hCrs_Etot_MC->Sumw2();
	 hCrs_Etot_MC->Scale(1.,"width");

	 hCrs_Eseed_MC->Sumw2();
	 hCrs_Eseed_MC->Scale(1.,"width");

	 hCrs_Etot_NoVETO_MC->Sumw2();
	 hCrs_Etot_NoVETO_MC->Scale(1.,"width");

	 hCrs_Eseed_NoVETO_MC->Sumw2();
	 hCrs_Eseed_NoVETO_MC->Scale(1.,"width");


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


