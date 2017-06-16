kill -9 `pgrep gearman-client`

#for i in `seq 1 1000`;
#do
		
./build/bin/gearman-client 172.17.10.23:4730 tomita-parser input.txt 25 10000
#./build/bin/gearman-client localhost 10000 tomita-parser input.txt
#	echo $i
#done    
