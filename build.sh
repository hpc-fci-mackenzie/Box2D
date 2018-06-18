#!/bin/bash
mkdir -p bin
cd bin
curl -L "https://github.com/premake/premake-core/releases/download/v5.0.0-alpha12/premake-5.0.0-alpha12-macosx.tar.gz" -o premake-5.0.0-alpha12-macosx.tar.gz
tar xzf premake-5.0.0-alpha12-macosx.tar.gz
cd ../Box2D
../bin/premake5 xcode4
cd Build
for i in $( grep -R "C++11" * | cut -d : -f1 ); do
	sed -i '' -e "s/C\+\+11/c\+\+11/g" $i
done
#xcodebuild -project Box2D.xcodeproj -configuration Release -verbose OTHER_CFLAGS="-Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize"
#xcodebuild -workspace Box2D.xcworkspace -scheme Testbed -configuration Release -verbose OTHER_CFLAGS="-Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize -std=c++11"
xcodebuild -project Testbed.xcodeproj -configuration Release -verbose OTHER_CFLAGS="-Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize"
