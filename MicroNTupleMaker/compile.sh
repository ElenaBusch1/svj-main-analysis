echo "Compiling MicroNTupleMaker..."
g++ -lstdc++fs util/MicroNTupleMaker.C -o exe/MicroNTupleMaker `root-config --cflags --glibs` -lstdc++fs `/afs/cern.ch/work/r/rgarg/public/Analyses/SemiVisibleJets/fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` -lNsubjettiness -lEnergyCorrelator
echo "Done"
