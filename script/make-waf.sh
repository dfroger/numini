wget http://ftp.waf.io/pub/release/waf-1.8.5.tar.bz2
tar xfjv waf-1.8.5.tar.bz2
cd waf-1.8.5
python waf-light  --make-waf --tool=swig
