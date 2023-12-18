mkdir build
cd src
asetup AnalysisBase,24.2.25,here
cd ../build
cmake ../src
make
source x86*/setup.sh
cd ..
