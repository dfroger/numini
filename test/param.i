%module param

%{
#include "param.hxx"
%}

%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"

namespace std {
    %template(vector_int) vector<int>;
    %template(map_string_double) map<string, double>;
    %template(vector_Vec3) vector<Vec3>;
    %template(map_string_Vec3) map<string,Vec3>;
}

%exception {
   try {
      $action
   }
   catch (numini::Error &e) {
      PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(e.what()));
      return NULL;
   }
   catch (YAML::Exception &e) {
      PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(e.what()));
      return NULL;
   }
}

%include "param.hxx"
