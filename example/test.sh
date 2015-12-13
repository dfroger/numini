waf clean
waf build
./build/main > output.txt
diff output.txt expected_output.txt

