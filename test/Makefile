default: main

param.py: param.cxx param.hxx param.i
	python setup.py build_ext --inplace

test: param.py
	LD_LIBRARY_PATH=../numini/build python test_numini.py

%.o: %.cxx
	$(CXX) -g -c -I../numini/ -I$(CONDA_ENV_PATH)/include $<

main: main.o param.o
	$(CXX) -g -o $@ $^ -L../numini/build -Wl,-rpath,../numini/build -lnumini -L$(CONDA_ENV_PATH)/lib -Wl,-rpath,$(CONDA_ENV_PATH)/lib -lyaml-cpp

clean:
	rm -rf build/ *.so param.py param_wrap.cpp main *.o
