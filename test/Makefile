param.py: parameter.hxx param.i
	python setup.py build_ext --inplace

test: param.py
	python test_numini.py

clean:
	rm -rf build/ *.so param.py param_wrap.cpp
