cvs co -d UserCode/HafHistogram UserCode/CmsHi/HafHistogram
cvs co -d CmsHi/PhotonAnalysis UserCode/CmsHi/PhotonAnalysis
cvs co -d CmsHi/Analysis2010 UserCode/CmsHi/Analysis2010
cvs co UserCode/MitHig/PixelTrackletAnalyzer
mv UserCode/MitHig .

cvs co HeavyIonsAnalysis/Configuration
cvs co DataFormats/HeavyIonEvent
cvs co -d RandomConeAna UserCode/EYKim/photonStudy/RandomConeAna

cvs co RecoHI/HiEgammaAlgos                  # for 3_9_8 reconstruction   including spike cleaner 
addpkg RecoHI/Configuration     # get the reconstruction chain without electron reco                                                            


# remove the electron sequence 
#rm RecoHI/HiEgammaAlgos/python/HiElectronSequence_cff.py
#rm HeavyIonsAnalysis/Configuration/python/Skims_HI_cff.py
#rm HeavyIonsAnalysis/Configuration/python/HI_PhotonSkim_cff.py

# keep 39X version for spike cleaner.
rm RecoHI/HiEgammaAlgos/plugins/HiSpikeCleaner.cc
cvs co -r HI_HLT_2010_11_20_fix2 RecoHI/HiEgammaAlgos/plugins/HiSpikeCleaner.cc

# electron reco sequence
rm RecoHI/HiEgammaAlgos/python -rf
cvs co -r CMSSW_3_9_9_patch1 RecoHI/HiEgammaAlgos/python
cvs co RecoHI/HiEgammaAlgos/python/HiCoreTools.py
cvs co RecoHI/HiEgammaAlgos/python/HiHelperTools.py

#### To produce hiGoodTracks 
cvs co -d edwenger/HiTrkEffAnalyzer UserCode/edwenger/HiTrkEffAnalyzer
cvs co -d edwenger/HiVertexAnalyzer UserCode/edwenger/HiVertexAnalyzer 
cvs co -d Appeltel/PixelTracksRun2010 UserCode/Appeltel/PixelTracksRun2010 


##### appendix

# things for gen particle study
# cvs co UserCode/EYKim/photonStudy/GenPhotonHistProducer 
# mv UserCode/EYKim/photonStudy photonStudy/

