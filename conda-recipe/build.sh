export MACOSX_DEPLOYMENT_TARGET=10.7

cd numini

if [ "$(uname)" == "Darwin" ]
then export CC=clang
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
else
    waf configure \
        --prefix=$PREFIX \
        --conda
fi

waf build

waf install

# waf (from the waf conda package), extract itself in $PREFIX/bin
rm -rf $PREFIX/bin/.waf-*
