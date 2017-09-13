#include <vector>
#include <utility>

using namespace std;

int preselection_single(Int_t trigger, Int_t loopJet_max, vector<TLorentzVector> &jets_pv, vector<std::pair<int, float> > &btag_vec, vector<std::pair<int, float> > &pt_vec, Int_t &btag_num1, Int_t &btag_num2, Int_t &pt_num1, Int_t &pt_num2,Int_t &cut_count ) {
	
		TLorentzVector Qjet1;
		TLorentzVector Qjet2;
		TLorentzVector Bjet1;
		TLorentzVector Bjet2;
		TLorentzVector qq;
		TLorentzVector bb;

		cut_count=0;
		int not_pass=0;

		btag_num1=btag_vec[0].first;
		btag_num2=btag_vec[1].first;
		Bjet1.SetPtEtaPhiM(jets_pv[btag_num1].Pt(),jets_pv[btag_num1].Eta(),jets_pv[btag_num1].Phi(),jets_pv[btag_num1].M());	
		Bjet2.SetPtEtaPhiM(jets_pv[btag_num2].Pt(),jets_pv[btag_num2].Eta(),jets_pv[btag_num2].Phi(),jets_pv[btag_num2].M());	
		int qjet_count=0;
		for(int i = 0; i < loopJet_max; i++){
			if (qjet_count==2) break;
			if ((pt_vec[i].first==btag_num1) || (pt_vec[i].first==btag_num2)) continue;	
			if (qjet_count==0) pt_num1=pt_vec[i].first;
			if (qjet_count==1) pt_num2=pt_vec[i].first;
			qjet_count++;
		}
		Qjet1.SetPtEtaPhiM(jets_pv[pt_num1].Pt(),jets_pv[pt_num1].Eta(),jets_pv[pt_num1].Phi(),jets_pv[pt_num1].M());	
		Qjet2.SetPtEtaPhiM(jets_pv[pt_num2].Pt(),jets_pv[pt_num2].Eta(),jets_pv[pt_num2].Phi(),jets_pv[pt_num2].M());	


		if (trigger!=1) not_pass = -1;
		if (jets_pv[0].Pt()<92) { not_pass=-2; cut_count++;	 };
		if (jets_pv[1].Pt()<76) { not_pass=-3; cut_count++;	 };
		if (jets_pv[2].Pt()<64) { not_pass=-4; cut_count++;	 };
		if (jets_pv[3].Pt()<30) { not_pass=-5; cut_count++;	 };

		qq=Qjet1+Qjet2;

		Double_t Mqq = qq.M();
		Double_t bbDeltaPhi = TMath::Abs(Bjet1.DeltaPhi(Bjet2));
		Double_t qqDeltaEta = TMath::Abs(Qjet1.Eta()-Qjet2.Eta());
		if (Mqq<500) {not_pass=-6; cut_count++;	 };
		if (qqDeltaEta<4.2){ not_pass=-7; cut_count++;	 };
		if (bbDeltaPhi>1.6){ not_pass =  -8; cut_count++;	 };
		

	return not_pass;
}
