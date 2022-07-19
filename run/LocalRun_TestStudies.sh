loglevel=info
extra=""
#extra="--inputList"

# this  has to be somewhere you can write
#parentsubmitdir="/afs/cern.ch/user/j/jodavies/darkjetresonances/DAODtoNTUPLE/run/"
parentsubmitdir="/afs/cern.ch/work/e/ebusch/public/SVJ/ana-exot-2021-19/run/"
#infile="/afs/cern.ch/work/e/ebusch/public/SVJ/signal_generation/run/DAOD_TRUTH3.output.root"
infile="/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/cutflow/mc16_13TeV.508548.MGPy8EG_SVJSChan_1500_3.deriv.DAOD_PHYS.e8357_s3126_r10201_p4838/DAOD_PHYS.27236297._000003.pool.root.1"
#infile="/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/mc16_13TeV.312808.MadGraphPythia8EvtGen_A14N30NLO_Mphi1500_Rinv4.deriv.DAOD_EXOT27.e7844_s3509_r10201_p4078/DAOD_EXOT27.23076874._000001.pool.root.1"
configFile=../configs/cutflow_signal_DAODtoNTUPLE_mc_OLD.py
#configFile=../configs/config_MultiBTaggedAlgo_signal.py

nevents=1000
submitdir=DAODtoTTREE_${nevents}


echo "xAH_run.py --files ${infile} --nevents $nevents --config $configFile --submitDir ${parentsubmitdir}/$submitdir --log-level $loglevel $extra --force direct"
xAH_run.py --files ${infile} --nevents $nevents --config $configFile --submitDir ${parentsubmitdir}/$submitdir --log-level $loglevel $extra --force direct 

# test command for using rucio with file list
#filelisttxt="/afs/cern.ch/user/m/mamerl/TLAWork/inputlisttest.txt"
#echo "xAH_run.py --files ${filelisttxt} --inputList --inputRucio --nevents $nevents --config $configFile --submitDir ${parentsubmitdir}/$submitdir --log-level $loglevel $extra --force direct"
#xAH_run.py --files ${filelisttxt} --inputList --inputRucio --nevents $nevents --config $configFile --submitDir ${parentsubmitdir}/$submitdir --log-level $loglevel $extra --force direct
