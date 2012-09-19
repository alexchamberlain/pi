/* Python binding */

#include <Python.h>
#include "pi.h"

static PyObject * pi_dd(PyObject * self, PyObject *args);

static PyMethodDef PiMethods[] = {
  {"dd", pi_dd, METH_VARARGS, "Copy files byte for byte."},
  {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef pimodule = {
  PyModuleDef_HEAD_INIT,
  "_pi",    /* name of module */
  NULL,    /* module documentation */
  -1,      /* size of per-interpreter state of the module,
              or -1 if the module keeps state in global variables. */
  PiMethods
};

PyMODINIT_FUNC PyInit__pi(void) {
  return PyModule_Create(&pimodule);
}

static PyObject * pi_dd(PyObject * self, PyObject *args) {
  PyObject *in  = NULL;
  PyObject *out = NULL;
  
  int       in_fd;
  int       out_fd;

  if(!PyArg_UnpackTuple(args, "dd", 2, 2, &in, &out))
    return NULL;
 
  if(PyUnicode_Check(in)) {
    printf("String supplied\n");
    PyObject *infn = PyUnicode_AsASCIIString(in);

    in_fd = open_input_file(PyBytes_AS_STRING(infn));
    if(in_fd < 0) {
      printf("Failed to open input file.\n");
      goto error;
    }
  } else if (PyObject_AsFileDescriptor(in) != -1) {
    printf("File supplied\n");
  }

  if(PyUnicode_Check(out)) {
    printf("String supplied\n");
    PyObject *fn = PyUnicode_AsASCIIString(out);

    out_fd = open_output_file(PyBytes_AS_STRING(fn));
    if(out_fd < 0) {
      printf("Failed to open output file.\n");
      goto error;
    }
  } else if (PyObject_AsFileDescriptor(in) != -1) {
    printf("File supplied\n");
  }

  if(dd(in_fd, out_fd, 1024*1024*4) != 0) {
    printf("dd failed.\n");
    goto error;
  }

  close(in_fd);
  close(out_fd);


  Py_INCREF(Py_None);
  return Py_None;

error:
  return NULL;
}
