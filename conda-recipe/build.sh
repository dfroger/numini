cd numini

if [ "$(uname)" == "Darwin" ]
then export CC=clang
    export MACOSX_DEPLOYMENT_TARGET=10.7
    export CXX=clang++

    unset CXXFLAGS
    unset CFLAGS
    unset LDFLAGS

    waf configure \
        --prefix=$PREFIX \
        --conda \
        --cflags='-mmacosx-version-min=10.7 -arch x86_64' \
        --cxxflags='-stdlib=libc++ -mmacosx-version-min=10.7 -arch x86_64' \
        --ldflags="-stdlib=libc++ -mmacosx-version-min=10.7 -arch x86_64"
    waf build
    waf install
else
    waf configure \
        --prefix=$PREFIX \
        --conda
    waf build
    waf install
    mkdir -p $PREFIX/lib
    ln -s $PREFIX/lib64/libnumini.so $PREFIX/lib/libnumini.so
fi


# waf (from the waf conda package), extract itself in $PREFIX/bin
rm -rf $PREFIX/bin/.waf-*
