cd numini
../waf configure \
    --prefix=$PREFIX \
    --yaml-cpp-dir=$PREFIX \
    --boost-dir=$PREFIX/boost_1_55_0
../waf build
../waf install
