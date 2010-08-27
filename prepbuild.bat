rm -r win_build
mkdir win_build
cd win_build
cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - MinGW Makefiles" ..
cp ../simplecalc* .
cd ..
