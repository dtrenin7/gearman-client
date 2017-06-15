# gearman-client

[WTF]
Multitreaded Gearman client with some user emulation.

[REQUIRED]
linux
CMAKE 3.X
GCC 4.5+
libgearman 1.12+

[HOW TO BUILD]
./build.sh

[HOW TO RUN]
./run.sh

[RUN OPTIONS]
gearman-client <host> <port> <function> <file> <threads> <delay>
host = target german server host
port = target german server port
function = gearman worker function name
file = file with input dada (one for all client threads - shared)
threads = number of client threads (started at once)
delay = maximum delay at the beginning of each thread (random 0....<delay> milliseconds)