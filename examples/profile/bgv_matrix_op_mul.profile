--------------------------------------------------------------------------------------------------------------
-------------- bgv_matrix_op with parameters: p = 4999, m = 321090, r = 1, bits = 300, c = 2 -----------------
-------------- only timing the vector multiplication  --------------------------------------------------------
--------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------
-Function name: time in seconds / number of times called = average [path/to/file/where/function/resides:line]-
--------------------------------------------------------------------------------------------------------------

  AAA_embeddingLargest: 4.37631 / 315 = 0.013893   [/home/jon/projects/HElib/src/norms.cpp:258]
  AAA_embeddingLargest_x2: 2.60835 / 192 = 0.0135852   [/home/jon/projects/HElib/src/norms.cpp:428]
  AAA_modDownEnbeddings: 2.60841 / 192 = 0.0135855   [/home/jon/projects/HElib/src/Ctxt.cpp:384]
  BluesteinFFT: 214.943 / 6677 = 0.0321915   [/home/jon/projects/HElib/src/bluestein.cpp:136]
  CRT_reconstruct: 2.97957 / 97 = 0.0307172   [/home/jon/projects/HElib/src/PAlgebra.cpp:947]
  CompMod: 0.000298 / 97 = 3.07216e-06   [/home/jon/projects/HElib/src/PAlgebra.cpp:911]
  Decrypt: 167.084 / 97 = 1.72252   [/home/jon/projects/HElib/src/keys.cpp:910]
  DoubleCRT: 94.4797 / 481 = 0.196424   [/home/jon/projects/HElib/src/DoubleCRT.cpp:474]
  FFT: 100.728 / 3080 = 0.0327038   [/home/jon/projects/HElib/src/CModulus.cpp:427]
  FFT: 100.729 / 675 = 0.149229   [/home/jon/projects/HElib/src/DoubleCRT.cpp:54]
  FFT: 28.1331 / 131 = 0.214757   [/home/jon/projects/HElib/src/DoubleCRT.cpp:73]
  FFT: 28.1326 / 885 = 0.0317882   [/home/jon/projects/HElib/src/CModulus.cpp:441]
  FFT_aux: 125.866 / 3965 = 0.0317443   [/home/jon/projects/HElib/src/CModulus.cpp:358]
  FFT_remainder: 2.90367 / 3080 = 0.000942752   [/home/jon/projects/HElib/src/CModulus.cpp:432]
  FFT_remainder: 0.086351 / 885 = 9.75718e-05   [/home/jon/projects/HElib/src/CModulus.cpp:446]
  GenKeySWmatrix: 13.126 / 16 = 0.820372   [/home/jon/projects/HElib/src/keys.cpp:779]
  addCtxt: 0.104434 / 96 = 0.00108785   [/home/jon/projects/HElib/src/Ctxt.cpp:1001]
  addPart: 0.030745 / 97 = 0.000316959   [/home/jon/projects/HElib/src/Ctxt.cpp:663]
  addPrimes: 125.226 / 194 = 0.645497   [/home/jon/projects/HElib/src/DoubleCRT.cpp:389]
  decode: 43.5441 / 97 = 0.448908   [/home/jon/projects/HElib/src/EncryptedArray.cpp:343]
  do_mul: 0.658495 / 708 = 0.000930078   [/home/jon/projects/HElib/src/DoubleCRT.cpp:171]
  embedInSlots: 2.98009 / 97 = 0.0307226   [/home/jon/projects/HElib/src/PAlgebra.cpp:885]
  factorT: 3.6e-05 / 19 = 1.89474e-06   [/home/jon/projects/HElib/src/NumbTh.cpp:96]
  iFFT: 178.536 / 2712 = 0.0658319   [/home/jon/projects/HElib/src/CModulus.cpp:457]
  iFFT_division: 85.5809 / 2712 = 0.0315564   [/home/jon/projects/HElib/src/CModulus.cpp:522]
  modDownToSet: 110.899 / 192 = 0.577601   [/home/jon/projects/HElib/src/Ctxt.cpp:305]
  multLowLvl: 113.992 / 96 = 1.18742   [/home/jon/projects/HElib/src/Ctxt.cpp:1243]
  privateAssign: 0.449281 / 97 = 0.00463176   [/home/jon/projects/HElib/src/Ctxt.cpp:227]
  randomize: 0.375217 / 130 = 0.00288628   [/home/jon/projects/HElib/src/DoubleCRT.cpp:1052]
  randomize_stream: 0.210257 / 239010 = 8.797e-07   [/home/jon/projects/HElib/src/DoubleCRT.cpp:1079]
  skEncrypt: 49.2338 / 97 = 0.507564   [/home/jon/projects/HElib/src/keys.cpp:982]
  toPoly: 185.765 / 675 = 0.275208   [/home/jon/projects/HElib/src/DoubleCRT.cpp:730]
  toPoly_CRT: 5.76372 / 675 = 0.00853884   [/home/jon/projects/HElib/src/DoubleCRT.cpp:791]
  toPoly_FFT: 179.726 / 675 = 0.26626   [/home/jon/projects/HElib/src/DoubleCRT.cpp:771]

Total time: 1971.86
--------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------
