# gearman-client

![picture alt](http://rs277.pbsrc.com/albums/kk66/manbat_bucket/GearMan.gif~c200 "Gearman")

## [WTF]
1. Multithreaded Gearman client (C++) with some user emulation
2. Python 3.X wrapper over C++ client library

## [REQUIRED]
linux
CMAKE 3.X
GCC 4.5+
libgearman 1.12+
python 3.X

## [BUILD]
./build.sh
WARNING! You can build C++ lib or C++ client only separately (see comments in CMakeLists.txt)

## [RUN]
### [C++]
./run.sh
### [Python]
./run_py.sh

## [OPTIONS]
gearman-client host port function file threads delay

Option   | Description
-------- | ---------------------------------------------------------------------------------
servers  | job servers list for example jobserver2.domain.com:7003,10.0.0.3
function | worker function name
file     | file with input data - function argument (one for all client threads - shared)
threads  | number of client threads (started at once)
delay    | maximum delay at the beginning of each thread (random 0....delay milliseconds)
