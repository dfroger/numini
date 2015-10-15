cd numini
../waf configure \
    --prefix=$PREFIX \
    --yaml-cpp-dir=$PREFIX \
    --boost-dir=$PREFIX/include
../waf build
../waf install
