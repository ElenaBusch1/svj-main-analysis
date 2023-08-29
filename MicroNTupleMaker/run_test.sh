#!/bin/bash

#In SVJ area
#filePath="/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v8/"
##infileTag="user.ebusch.364710.Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ10WithSW.v8a.mc20e_tree.root"

#In my area
#filePath="/eos/user/r/rgarg/Rocky/Analyses/SemiVisibleJets/Samples/v8/Ntuples/"
filePath="/eos/user/r/rgarg/Rocky/Analyses/SemiVisibleJets/ForHon-Leon/"
###QCD
#infileTag="user.ebusch.364710.Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ10WithSW.v8a.mc20e_tree.root"
#Znunu
#infileTag="user.ebusch.700337.Sh_2211_Znunu_pTV2_CVetoBVeto.v8a.mc20e_tree.root"
#Signals
#infileTag="user.ebusch.515499.MGPy8EG_SVJSChan2j_2000_2.v8a.mc20e_tree.root"
#infileTag="user.ebusch.515502.MGPy8EG_SVJSChan2j_2000_8.v8a.mc20e_tree.root"
infileTag="user.ebusch.515519.MGPy8EG_SVJSChan2j_5000_2.v8a.mc20e_tree.root"
#infileTag="user.ebusch.515522.MGPy8EG_SVJSChan2j_5000_8.v8a.mc20e_tree.root"

local="true"

#./exe/MicroNTupleMaker user.ebusch.data16_13TeV.periodAllYear.v7d_tree.root true /eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v7/

./exe/MicroNTupleMaker ${infileTag} ${local} ${filePath}
