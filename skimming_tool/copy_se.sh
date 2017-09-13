input="DYJetsToLL_amc_full_v24.root  
DYJetstoLL_HT100_200_full_v24.root  DYJetstoLL_HT200_400_full_v24.root  DYJetstoLL_HT400_600_full_v24.root  DYJetstoLL_HT600_Inf_full_v24.root 
DYJetsToLL_Pt-100To250_amc_v24.root  DYJetsToLL_Pt-250To400_amc_v24.root  DYJetsToLL_Pt-400To650_amc_v24.root  DYJetsToLL_Pt-650ToInf_amc_v24.root
DYJetstoLL_v24.root

 QCD_HT1000to1500_full_v24.root  QCD_HT100to200_full_v24.root  QCD_HT1500to2000_full_v24.root  QCD_HT2000toInf_full_v24.root  QCD_HT200to300_full_v24.root  QCD_HT300to500_full_v24.root  QCD_HT500to700_full_v24.root  QCD_HT700to1000_full_v24.root 
 WJetsToLNu_HT-100To200_madgraph_full_v24.root  WJetsToLNu_HT-200To400_madgraph_full_v24.root  WJetsToLNu_HT-400To600_madgraph_full_v24.root  WJetsToLNu_HT-600To800_madgraph_full_v24.root  WJetsToLNu_HT-800To1200_madgraph_full_v24.root

WJetsToLNu_Pt-100To250_amcatnlo_v24.root  WJetsToLNu_Pt-250To400_amcatnlo_v24.root  WJetsToLNu_Pt-400To600_amcatnlo_v24.root  WJetsToLNu_Pt-600ToInf_amcatnlo_v24.root


SingleMuon_v24.root SingleElectron_v24.root 
TT_v24.root 
 ST_s-channel_4f_leptonDecays_amc_v24.root                ST_t-channel_antitop_4f_leptonDecays_powheg_v24.root  ST_t-channel_top_4f_leptonDecays_powheg_v24.root  ST_tW_antitop_5f_inclusiveDecays_powheg_v24.root
ST_t-channel_antitop_4f_inclusiveDecays_powheg_v24.root  ST_t-channel_top_4f_inclusiveDecay_powheg_v24.root    ST_tW_5f_inclusiveDecays_powheg_v24.root          ST_tW_top_5f_inclusiveDecays_powheg_v24.root
 
WW_v24.root
WZ_v24.root
ZZ_v24.root"

for arg in $input
do
	printf 'xrdcp   /scratch/nchernya/'$arg 
	printf '    root://t3se01.psi.ch/store/user/nchernya/VBFZll/skimmed_loose/'
	echo
done
