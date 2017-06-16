# gearman-client

![picture alt](http://rs277.pbsrc.com/albums/kk66/manbat_bucket/GearMan.gif~c200 "Gearman")

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
servers  | job servers list for example jobserver2.domain.com:7003,10.0.0.3
function | worker function name
file     | file with input data - function argument (one for all client threads - shared)
threads  | number of client threads (started at once)
delay    | maximum delay at the beginning of each thread (random 0....delay milliseconds)
