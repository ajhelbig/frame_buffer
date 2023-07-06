#!/usr/bin/env bash

clear

echo "----------run.sh----------"

echo "----------CONFIG----------"

if [ -d "build" ]
then
	cd build
	cmake ..


else
	mkdir build && cd build
	cmake ..

fi

echo "----------CONFIG----------"


echo "----------BUILD----------"

cmake --build .

echo "----------BUILD----------"


echo "----------RUN----------"

cd src
./ProjectName

echo "----------RUN----------"