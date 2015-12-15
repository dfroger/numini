cd numini
waf configure --prefix=$PREFIX --conda
waf build
waf install
