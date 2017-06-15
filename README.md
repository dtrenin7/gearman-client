![picture alt](http://rs277.pbsrc.com/albums/kk66/manbat_bucket/GearMan.gif~c200 "Gearman")

# gearman-client

## [WTF]
Multithreaded Gearman client with some user emulation.

## [REQUIRED]
linux
CMAKE 3.X
GCC 4.5+
libgearman 1.12+

## [BUILD]
./build.sh

## [RUN]
./run.sh

## [OPTIONS]
gearman-client host port function file threads delay

Option   | Description
-------- | ---------------------------------------------------------------------------------
host     | target german server host
port     | target german server port
function | gearman worker function name
file     | file with input data - function argument (one for all client threads - shared)
threads  | number of client threads (started at once)
delay    | maximum delay at the beginning of each thread (random 0....delay milliseconds)
