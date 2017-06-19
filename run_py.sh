#kill -9 `pgrep gearman-client`

#for i in `seq 1 1000`;
#do

export LD_LIBRARY_PATH=build/bin
python3 src/gearman_client.py 172.17.10.23:4730 tomita-parser input.txt

#	echo $i
#done    
