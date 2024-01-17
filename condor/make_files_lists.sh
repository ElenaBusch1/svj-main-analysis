eosPath=/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v12/v12.2/user.ebusch*
echo "Large files to run locally: "
# f 10 takes last string after last "/"; could change if eos path changes
find $eosPath -name "user.ebusch*" -type f -size +900M | cut -d "/" -f 10
find $eosPath -name "user.ebusch*" -type f -size +900M | cut -d "/" -f 10 > v12p2_sig1_large_files.txt
echo""

echo "Small files to run on condor: "
find $eosPath -name "user.ebusch*" -type f -size -900M | cut -d "/" -f 10
find $eosPath -name "user.ebusch*" -type f -size -900M | cut -d "/" -f 10 > v12p2_sig1_condor_files.txt

