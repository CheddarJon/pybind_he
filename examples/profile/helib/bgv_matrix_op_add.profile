
--------------------------------------------------------------------------------------------------------------
-------------- bgv_matrix_op with parameters: p = 4999, m = 321090, r = 1, bits = 300, c = 2 -----------------
-------------- only timing vector addition -------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------
-Function name: time in seconds / number of times called = average [path/to/file/where/function/resides:line]-
--------------------------------------------------------------------------------------------------------------

  AAA_embeddingLargest: 4.48199 / 324 = 0.0138333   [/home/jon/projects/HElib/src/norms.cpp:258]
  AAA_embeddingLargest_x2: 2.60688 / 192 = 0.0135775   [/home/jon/projects/HElib/src/norms.cpp:428]
  AAA_modDownEnbeddings: 2.60693 / 192 = 0.0135778   [/home/jon/projects/HElib/src/Ctxt.cpp:384]
  BluesteinFFT: 211.935 / 6677 = 0.0317411   [/home/jon/projects/HElib/src/bluestein.cpp:136]
  CRT_reconstruct: 2.9768 / 97 = 0.0306887   [/home/jon/projects/HElib/src/PAlgebra.cpp:947]
  CompMod: 0.000281 / 97 = 2.89691e-06   [/home/jon/projects/HElib/src/PAlgebra.cpp:911]
  Decrypt: 165.779 / 97 = 1.70906   [/home/jon/projects/HElib/src/keys.cpp:910]
  DoubleCRT: 93.358 / 481 = 0.194091   [/home/jon/projects/HElib/src/DoubleCRT.cpp:474]
  FFT: 99.5908 / 3080 = 0.0323347   [/home/jon/projects/HElib/src/CModulus.cpp:427]
  FFT: 99.5927 / 675 = 0.147545   [/home/jon/projects/HElib/src/DoubleCRT.cpp:54]
  FFT: 27.8182 / 131 = 0.212353   [/home/jon/projects/HElib/src/DoubleCRT.cpp:73]
  FFT: 27.8177 / 885 = 0.0314324   [/home/jon/projects/HElib/src/CModulus.cpp:441]
  FFT_aux: 124.414 / 3965 = 0.0313781   [/home/jon/projects/HElib/src/CModulus.cpp:358]
  FFT_remainder: 2.9041 / 3080 = 0.000942889   [/home/jon/projects/HElib/src/CModulus.cpp:432]
  FFT_remainder: 0.086114 / 885 = 9.7304e-05   [/home/jon/projects/HElib/src/CModulus.cpp:446]
  GenKeySWmatrix: 12.6974 / 16 = 0.793586   [/home/jon/projects/HElib/src/keys.cpp:779]
  addCtxt: 0.105076 / 96 = 0.00109454   [/home/jon/projects/HElib/src/Ctxt.cpp:1001]
  addPart: 0.032123 / 97 = 0.000331165   [/home/jon/projects/HElib/src/Ctxt.cpp:663]
  addPrimes: 124.26 / 194 = 0.640517   [/home/jon/projects/HElib/src/DoubleCRT.cpp:389]
  decode: 43.515 / 97 = 0.448608   [/home/jon/projects/HElib/src/EncryptedArray.cpp:343]
  do_mul: 0.656976 / 708 = 0.000927932   [/home/jon/projects/HElib/src/DoubleCRT.cpp:171]
  embedInSlots: 2.97732 / 97 = 0.030694   [/home/jon/projects/HElib/src/PAlgebra.cpp:885]
  factorT: 3.8e-05 / 19 = 2e-06   [/home/jon/projects/HElib/src/NumbTh.cpp:96]
  iFFT: 176.942 / 2712 = 0.065244   [/home/jon/projects/HElib/src/CModulus.cpp:457]
  iFFT_division: 85.5066 / 2712 = 0.031529   [/home/jon/projects/HElib/src/CModulus.cpp:522]
  modDownToSet: 109.645 / 192 = 0.571069   [/home/jon/projects/HElib/src/Ctxt.cpp:305]
  multLowLvl: 112.737 / 96 = 1.17434   [/home/jon/projects/HElib/src/Ctxt.cpp:1243]
  privateAssign: 0.449321 / 97 = 0.00463218   [/home/jon/projects/HElib/src/Ctxt.cpp:227]
  randomize: 0.375105 / 130 = 0.00288542   [/home/jon/projects/HElib/src/DoubleCRT.cpp:1052]
  randomize_stream: 0.209974 / 238997 = 8.78563e-07   [/home/jon/projects/HElib/src/DoubleCRT.cpp:1079]
  skEncrypt: 49.7196 / 97 = 0.512573   [/home/jon/projects/HElib/src/keys.cpp:982]
  toPoly: 184.166 / 675 = 0.272838   [/home/jon/projects/HElib/src/DoubleCRT.cpp:730]
  toPoly_CRT: 5.75889 / 675 = 0.00853169   [/home/jon/projects/HElib/src/DoubleCRT.cpp:791]
  toPoly_FFT: 178.133 / 675 = 0.2639   [/home/jon/projects/HElib/src/DoubleCRT.cpp:771]

Total time: 1953.85
--------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------
