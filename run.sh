kill -9 `pgrep gearman-client`

#for i in `seq 1 1000`;
#do
		
./build/bin/gearman-client 127.0.0.1:4730 execute_js input2.txt
#./build/bin/gearman-client localhost 10000 tomita-parser input.txt
#	echo $i
#done    
