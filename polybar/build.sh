#/bin/sh
g++ -std=c++11 music-roll-client.cpp -o music-roll-client -lfmt -lzmq
g++ -std=c++11 music-roll-daemon.cpp -o music-roll-daemon -lfmt -lzmq
