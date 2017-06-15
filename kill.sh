ps aux | grep -ie gearman-client | awk '{print gearman-client}' | xargs kill -9 
kill -9 $(ps -A -ostat,ppid | grep -e '[zZ]'| awk '{ print gearman-client }')

