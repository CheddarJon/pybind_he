#define PY_SSIZE_T_CLEAN
#include <Python.h>

static int numargs=0;

struct FftTables {
	size_t n;
	size_t *bit_reversed;
	double *cos_table;
	double *sin_table;
};

static double ct[] = {1.0, 3.2, 4.5};
static double st[] = {3.2, 4.4, 6.7};
static size_t br[] = {3, 3, 4};

struct FftTables tmp = {
	3,
	br,
	ct,
	st
};

static PyObject*
getFftTable(PyObject *self, PyObject *args)
{
	PyObject *p_br = PyList_New(tmp.n);
	PyObject *p_ct = PyList_New(tmp.n);
	PyObject *p_st = PyList_New(tmp.n);

	for (size_t i = 0; i < tmp.n; i++) {
		PyObject *bre = PyLong_FromSize_t(tmp.bit_reversed[i]);
		PyObject *cse = Py_BuildValue("d", tmp.cos_table[i]);
		PyObject *sse = Py_BuildValue("d", tmp.sin_table[i]);

		PyList_SetItem(p_br, i, bre);
		PyList_SetItem(p_ct, i, cse);
		PyList_SetItem(p_st, i, sse);
	}
	return Py_BuildValue("(iOOO)", tmp.n, p_br, p_ct, p_st);
}

static PyMethodDef EmbMethods[] = {
	{"getFftTable", getFftTable, METH_VARARGS,
	 "Utility to pass c data to python."},
	{NULL, NULL, 0, NULL}
};

static PyModuleDef EmbModule = {
	PyModuleDef_HEAD_INIT, "emb", NULL, -1, EmbMethods,
	NULL, NULL, NULL, NULL
};

static PyObject*
PyInit_emb(void)
{
	return PyModule_Create(&EmbModule);
}

int
main(int argc, char *argv[])
{
	/* TODO Either run fft with python or c. */
	PyObject *pName, *pModule, *pFunc;
	PyObject *pArgs, *pValue;
	int i;

	if (argc < 3) {
		fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
		return 1;
	}

	numargs = argc;
	PyImport_AppendInittab("emb", &PyInit_emb);
    
	Py_Initialize();
	pName = PyUnicode_DecodeFSDefault(argv[1]);
	/* Error checking of pName left out */

	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (pModule == NULL) {
		PyErr_Print();
		fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
		return 1;
	}

	pFunc = PyObject_GetAttrString(pModule, argv[2]);
	/* pFunc is a new reference */

	if (pFunc && PyCallable_Check(pFunc)) {
		pArgs = PyTuple_New(argc - 3);
		for (i = 0; i < argc - 3; ++i) {
			pValue = PyLong_FromLong(atoi(argv[i + 3]));
			if (!pValue) {
				Py_DECREF(pArgs);
				Py_DECREF(pModule);
				fprintf(stderr, "Cannot convert argument\n");
				return 1;
			}
			/* pValue reference stolen here: */
			PyTuple_SetItem(pArgs, i, pValue);
		}
		pValue = PyObject_CallObject(pFunc, pArgs);
		Py_DECREF(pArgs);
		if (pValue != NULL) {
			printf("Result of call: %ld\n", PyLong_AsLong(pValue));
			Py_DECREF(pValue);
		}
		else {
			Py_DECREF(pFunc);
			Py_DECREF(pModule);
			PyErr_Print();
			fprintf(stderr,"Call failed\n");
			return 1;
		}
	}
	else {
		if (PyErr_Occurred())
			PyErr_Print();
		fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
	}
	Py_XDECREF(pFunc);
	Py_DECREF(pModule);

	if (Py_FinalizeEx() < 0) {
		return 120;
	}
	return 0;
}
