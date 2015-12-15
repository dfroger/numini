param.py: parameter.hxx param.i
	python setup.py build_ext --inplace

test: param.py
	LD_LIBRARY_PATH=../numini/build python test_numini.py NumIniTest.test_normal

clean:
	rm -rf build/ *.so param.py param_wrap.cpp
