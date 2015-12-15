export MACOSX_DEPLOYMENT_TARGET=10.7

export CC=clang
export CXX=clang++
export CFLAGS="-mmacosx-version-min=10.7"
export CXXFLAGS="-stdlib=libc++ -mmacosx-version-min=10.7"
export LDFLAGS="-stdlib=libc++ -mmacosx-version-min=10.7"

cd numini
../waf configure \
    --prefix=$PREFIX \
    --yaml-cpp-dir=$PREFIX \
    --boost-dir=$PREFIX/include
../waf build
../waf install
