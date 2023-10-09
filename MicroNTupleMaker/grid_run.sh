#prun --cmtConfig=x86_64-centos7-gcc8-opt --exec "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase; source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh; lsetup 'root 6.20.06-x86_64-centos7-gcc8-opt'; ./exe/MicroNTupleMaker %IN" --extFile exe/MicroNTupleMaker --inDS user.ebusch.364711.Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ11WithSW.v2a.mc16e_tree.root --outDS user.ebusch.364711.test10mc16e --outputs output.root

#prun --cmtConfig=x86_64-centos7-gcc8-opt --exec "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase; source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh; lsetup 'root 6.20.06-x86_64-centos7-gcc8-opt'; ./exe/MicroNTupleMaker %IN" --extFile exe/MicroNTupleMaker --outputs output.root --bulkSubmission --inOutDsJson filemap_resubmit.json --nGBPerJob 2 --allowTaskDuplication

#prun --cmtConfig=x86_64-centos7-gcc8-opt --exec "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase; source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh; lsetup 'root 6.20.06-x86_64-centos7-gcc8-opt'; ./exe/MicroNTupleMaker %IN" --extFile exe/MicroNTupleMaker --outputs output.root --bulkSubmission --inOutDsJson filemap_test.json --nGBPerJob 2

#prun --cmtConfig=x86_64-centos7-gcc8-opt --exec "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase; source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh; lsetup 'root 6.20.06-x86_64-centos7-gcc8-opt'; ./exe/MicroNTupleMaker %IN" --extFile exe/MicroNTupleMaker --outputs output.root --bulkSubmission --inOutDsJson filemap_data.json --nGBPerJob 2

prun --cmtConfig=x86_64-centos7-gcc8-opt --exec "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase; source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh; lsetup 'root 6.20.06-x86_64-centos7-gcc8-opt'; ./exe/MicroNTupleMaker %IN" --extFile exe/MicroNTupleMaker --outputs output.root --bulkSubmission --inOutDsJson filemap_multijet.json --nGBPerJob 2

prun --cmtConfig=x86_64-centos7-gcc8-opt --exec "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase; source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh; lsetup 'root 6.20.06-x86_64-centos7-gcc8-opt'; ./exe/MicroNTupleMaker %IN" --extFile exe/MicroNTupleMaker --outputs output.root --bulkSubmission --inOutDsJson filemap_signals.json --nGBPerJob 2

prun --cmtConfig=x86_64-centos7-gcc8-opt --exec "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase; source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh; lsetup 'root 6.20.06-x86_64-centos7-gcc8-opt'; ./exe/MicroNTupleMaker %IN" --extFile exe/MicroNTupleMaker --outputs output.root --bulkSubmission --inOutDsJson filemap_wjets.json

prun --cmtConfig=x86_64-centos7-gcc8-opt --exec "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase; source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh; lsetup 'root 6.20.06-x86_64-centos7-gcc8-opt'; ./exe/MicroNTupleMaker %IN" --extFile exe/MicroNTupleMaker --outputs output.root --bulkSubmission --inOutDsJson filemap_ttbar.json --nGBPerJob 2
