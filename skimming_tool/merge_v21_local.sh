export WORKDIR=`pwd`
echo "Working on a machine:" `uname -a`
cd $WORKDIR

output_dir=(
#SingleElectronF0
#SingleMuonC0
#SingleMuonC1 
#SingleMuonG0 
#SingleMuonG1 
#SingleMuonG2 
#SingleMuonF0 
#SignleMuonD0 
#SingleMuonD1 
#SingleMuonB0 
#SingleMuonB1 SingleMuonB2 SingleMuonB3 SingleMuonE0 SingleMuonE1
#SingleElectronC0 SingleElectronC1 SingleElectronB0 SingleElectronB1 SingleElectronB2 SingleElectronB3  SingleElectronD0 SingleElectronD1 SingleElectronG0 SingleElectronG1 SingleElectronG2 SingleElectronE0 SingleElectronE1 DYJetstoLL TT1 TT2 TT3 
#EWK_LLJJ
#DYJetsToLL_amc_full 
# WW WZ ZZ
# DYJetstoLL_HT100_200_ext DYJetstoLL_HT100_200 DYJetstoLL_HT200_400_ext DYJetstoLL_HT200_400 DYJetstoLL_HT400_600_ext DYJetstoLL_HT400_600 DYJetstoLL_HT600_Inf_ext DYJetstoLL_HT600_Inf
#DYJetsToLL_Pt-100To250_amc  DYJetsToLL_Pt-250To400_amc DYJetsToLL_Pt-400To650_amc DYJetsToLL_Pt-650ToInf_amc QCD_HT1000to1500_ext QCD_HT1000to1500  QCD_HT100to200 QCD_HT1500to2000_ext QCD_HT1500to2000 QCD_HT2000toInf_ext QCD_HT2000toInf QCD_HT200to300 QCD_HT200to300_ext QCD_HT300to500 QCD_HT300to500_ext QCD_HT500to700_ext QCD_HT500to700 QCD_HT700to1000_ext QCD_HT700to1000 WJetsToLNu_HT-100To200_madgraph   WJetsToLNu_HT-100To200_madgraph_ext   WJetsToLNu_HT-1200To2500_madgraph   WJetsToLNu_HT-1200To2500_madgraph_ext   WJetsToLNu_HT-200To400_madgraph_ext   WJetsToLNu_HT-200To400_madgraph   WJetsToLNu_HT-2500ToInf_madgraph_ext   WJetsToLNu_HT-2500ToInf_madgraph   WJetsToLNu_HT-400To600_madgraph_ext   WJetsToLNu_HT-400To600_madgraph   WJetsToLNu_HT-600To800_madgraph_ext   WJetsToLNu_HT-600To800_madgraph   WJetsToLNu_HT-800To1200_madgraph_ext   WJetsToLNu_HT-800To1200_madgraph   WJetsToLNu_Pt-100To250_amcatnlo   WJetsToLNu_Pt-250To400_amcatnlo   WJetsToLNu_Pt-400To600_amcatnlo   WJetsToLNu_Pt-600ToInf_amcatnlo   WJetsToLNu_amcatnlo   WJetsToLNu_madgraph  ST_s-channel_4f_leptonDecays_amc ST_t-channel_antitop_4f_inclusiveDecays_powheg ST_t-channel_antitop_4f_leptonDecays_powheg ST_t-channel_top_4f_inclusiveDecay_powheg ST_t-channel_top_4f_leptonDecays_powheg ST_tW_antitop_5f_inclusiveDecays_powheg ST_tW_top_5f_inclusiveDecays_powheg 

#DYJetstoLL_HT600to800
#DYJetstoLL_HT400to600
#ST_tW_antitop
#EWK_LL_JJ_herwig
#DYJetstoLL_HT1200to2500
#WW
#WJetsToLnu_madgraph
#WZ
#DYJetstoLL_madgraph
#DYJetstoLL_HT2500toInf
#TT
#DYJetstoLL_HT100to200
#DYJetstoLL_amc_1J
#ST_tW_top
#DYJetstoLL_HT200to400
#ST_t_antitop
#SingleMuon
#ZZ
#EWK_LL_JJ
#DYJetstoLL_HT800to1200
#SingleElectron
#ST_t_top
#DYJetstoLL_amc_0J
#DYJetstoLL_amc_2J_ext
#TTZToLLNuNu
#tZq_ll
#DYJetstoLL_amc_2J
#ST_s
#GluGlu_HToMuMu_passall
#GluGlu_HToMuMu
#VBF_HToMuMu
#VBF_HToMuMu_passall

##################################################################
#BTagCSV0
#BTagCSV1
#BTagCSV2
#BTagCSV3
#VBFHbb
#BTagCSV            DYJetstoLL_amc_2J  QCD_HT500to700    QCD_HT2000toInf  ST_t_antitop         WJetsToQQ         ggHbb
#DYJetsToQQ         QCD_HT100to200     QCD_HT700to1000   ST_s             ST_t_top             WminusHbb_powheg
#DYJetstoLL_amc_0J  QCD_HT200to300     QCD_HT1000to1500  ST_tW_antitop    TT                   WplusHbb_powheg
#DYJetstoLL_amc_1J  QCD_HT300to500     QCD_HT1500to2000  ST_tW_top        WJetsToLnu_madgraph  ZHbb_powheg


#JetHT
# QCD_HT100to200     QCD_HT700to1000  
# QCD_HT200to300     QCD_HT1000to1500   QCD_HT300to500     QCD_HT1500to2000 
#QCD_HT2000toInf
#QCD_HT500to700


#LLJJ_EWK_5f_LO_13TeV


#BTagCSV            QCD_HT1000to1500  QCD_HT500to700   ST_tW_top                WJetsToLnu_HT2500toInf  WJetsToQQ
#DYJetstoLL_amc_0J  QCD_HT100to200    QCD_HT700to1000  TT                       WJetsToLnu_HT400to600
#DYJetstoLL_amc_1J  QCD_HT1500to2000  ST_s             VBFHbb                   WJetsToLnu_HT600to800
#DYJetstoLL_amc_2J  QCD_HT2000toInf   ST_t_antitop     WJetsToLnu_HT100to200    WJetsToLnu_HT70to100
#DYJetsToQQ         QCD_HT200to300    ST_t_top         WJetsToLnu_HT1200to2500  WJetsToLnu_HT800to1200
#ggHbb              QCD_HT300to500    ST_tW_antitop    WJetsToLnu_HT200to400    WJetsToLnu_madgraph

#VBFHbb_herwig
#VBFHbb_CUEDown
#VBFHbb_CUEUp
#VBFHbb_amc
#WminusHbb_powheg
#WplusHbb_powheg
#ZHbb_powheg
#ggHbb_herwig
#ggHbb_amc
#bbH_yb2
#bbH_ybyt
#WW
#ZZ
#WZ
#ST_s_inclusive
#ttHbb
#ttHnonbb
EWK_LLJJ_aTGC_full







)

#VBFSpin0ToBBbar_W_1p0_M_750_TuneCUEP8M1_13TeV_pythia8
#VBFSpin0ToBBbar_W_1p0_M_300_TuneCUEP8M1_13TeV_pythia8
#VBFSpin0ToBBbar_W_1p0_M_450_TuneCUEP8M1_13TeV_pythia8
#VBFSpin0ToBBbar_W_1p0_M_600_TuneCUEP8M1_13TeV_pythia8
#VBFSpin0ToBBbar_W_1p0_M_900_TuneCUEP8M1_13TeV_pythia8
#VBFSpin0ToBBbar_W_1p0_M_1050_TuneCUEP8M1_13TeV_pythia8
#VBFSpin0ToBBbar_W_1p0_M_375_TuneCUEP8M1_13TeV_pythia8
#VBFSpin0ToBBbar_W_1p0_M_525_TuneCUEP8M1_13TeV_pythia8
#VBFSpin0ToBBbar_W_1p0_M_675_TuneCUEP8M1_13TeV_pythia8
#VBFSpin0ToBBbar_W_1p0_M_825_TuneCUEP8M1_13TeV_pythia8
#VBFSpin0ToBBbar_W_1p0_M_975_TuneCUEP8M1_13TeV_pythia8

#VBFHToBB_M-125_13TeV_powheg-ext
# VBFHToBB_M-125_13TeV_powheg 
#QCD_HT100to200
#QCD_HT200to300
#QCD_HT300to500
#QCD_HT500to700
#QCD_HT700to1000
#QCD_HT1000to1500
#QCD_HT1500to2000 
#QCD_HT2000toInf
#TTJets_TuneCUETP8M1_13TeV-madgraph
#TT_TuneCUETP8M1_13TeV-amcatnlo
#DYJetsToQQ
#WJetsToQQ_HT180_13TeV-madgraph
#DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnlo_ext_1
#DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnlo_ext_2
#DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnlo
#ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg 
#ST_tW_top_5f_inclusiveDecays_13TeV-powheg
#ST_s-channel_4f_leptonDecays_13TeV-amcatnlo
#WJetsToLNu_TuneCUETP8M1_13TeV-amcatnlo
#GluGluHToBB_M125_13TeV_powheg-ext
#GluGluHToBB_M125_13TeV_powheg 
#ttHTobb_M125_13TeV_powheg
# ttHToNonbb_M125_13TeV_powheg 
#ZZ
#WZ
#WW
#ZH_HToBB
#WplusH_HToBB
#WminusH_HToBB
#TT_powheg_1
#TT_powheg_2
#TT_powheg_3
#TT_powheg_4
#TT_powheg_5
#TT_powheg_6
#TT_powheg_7
#BTagCSV_C
#BTagCSV_D
#SUSYGluGluToBBHToBB_M-120
#bbHToBB_M-125_4FS_yb2
#bbHToBB_M-125_4FS_ybyt
#VBFHToBB_M-125_13TeV_amc
#GluGluHToBB_M125_13TeV_amc
#ST_t-channel_top_4f_inclusiveDecays
#ST_t-channel_antitop_4f_inclusiveDecays 
#VBFHToBB_M-125_13TeV_powheg_herwigpp_weightfix
#VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix_CUETP8M1Down
#VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix_CUETP8M1Up 


max_samples=1  #25 #28  #91
current_sample=0 
while [ $current_sample -lt $max_samples ]
#while [ $current_sample -gt 4 ] && [  $current_sample -lt 8  ]
do
#	echo ${output_dir[current_sample]}
#	rm list${output_dir[current_sample]}_single.txt
#	rm list${output_dir[current_sample]}_single2.txt
#	path=root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat/
#	path2=/store/user/nchernya/Hbb/v21/workflow/${output_dir[current_sample]}_single/
#	path3=/store/user/nchernya/Hbb/v21/workflow/
#	xrdfs t3se01.psi.ch ls $path2 > list${output_dir[current_sample]}_single.txt
#	awk -v path="$path" '{print path $0}' list${output_dir[current_sample]}.txt > list${output_dir[current_sample]}2.txt
#	rm list${output_dir[current_sample]}_single.txt


#	rm list${output_dir[current_sample]}.txt
#	rm list${output_dir[current_sample]}2.txt	
#	path=root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat/
##	path2=/store/user/nchernya/VBFHbb2016/workflow/v25/${output_dir[current_sample]}/
#	path2=/store/user/nchernya/VBFZll/workflow/v25_reskim/${output_dir[current_sample]}/
##	path2=/store/user/nchernya/VBFZll/workflow/v25_reskim/${output_dir[current_sample]}/
##	path2=/store/user/nchernya/VBFHbb2016/triggers/v25/QuadVBF/${output_dir[current_sample]}/
##	xrdfs t3se01.psi.ch ls $path2 > list${output_dir[current_sample]}.txt
#	awk -v path="$path" '{print path $0}' list${output_dir[current_sample]}.txt > list${output_dir[current_sample]}2.txt
#	rm list${output_dir[current_sample]}.txt		


#lit=\`
#	echo hadd -f -k -v 99  /scratch/$USER/${output_dir[current_sample]}_v21.root    cat list${output_dir[current_sample]}2.txt | xargs 


	echo hadd  /scratch/$USER/${output_dir[current_sample]}_v25_reskim.root    "\`"cat list${output_dir[current_sample]}2.txt"\`"   # used

	current_sample=$((current_sample + 1))
	##############xrdfs t3se01.psi.ch rm $path2${output_dir[current_sample]}_single_v21.root
done
