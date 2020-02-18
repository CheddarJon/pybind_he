--------------------------------------------------------------------------------------------------------------
-------------- bgv_matrix_op with parameters: p = 4999, m = 321090, r = 1, bits = 300, c = 2 -----------------
-------------- timing both vector multiplication and addition ------------------------------------------------
--------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------
-Function name: time in seconds / number of times called = average [path/to/file/where/function/resides:line]-
--------------------------------------------------------------------------------------------------------------

  AAA_embeddingLargest: 4.43861 / 318 = 0.0139579   [/home/jon/projects/HElib/src/norms.cpp:258]
  AAA_embeddingLargest_x2: 2.62508 / 192 = 0.0136723   [/home/jon/projects/HElib/src/norms.cpp:428]
  AAA_modDownEnbeddings: 2.62514 / 192 = 0.0136726   [/home/jon/projects/HElib/src/Ctxt.cpp:384]
  BluesteinFFT: 213.876 / 6677 = 0.0320318   [/home/jon/projects/HElib/src/bluestein.cpp:136]
  CRT_reconstruct: 2.98167 / 97 = 0.0307389   [/home/jon/projects/HElib/src/PAlgebra.cpp:947]
  CompMod: 0.000272 / 97 = 2.80412e-06   [/home/jon/projects/HElib/src/PAlgebra.cpp:911]
  Decrypt: 166.825 / 97 = 1.71985   [/home/jon/projects/HElib/src/keys.cpp:910]
  DoubleCRT: 93.955 / 481 = 0.195333   [/home/jon/projects/HElib/src/DoubleCRT.cpp:474]
  FFT: 100.183 / 3080 = 0.0325269   [/home/jon/projects/HElib/src/CModulus.cpp:427]
  FFT: 100.185 / 675 = 0.148422   [/home/jon/projects/HElib/src/DoubleCRT.cpp:54]
  FFT: 27.9723 / 131 = 0.213529   [/home/jon/projects/HElib/src/DoubleCRT.cpp:73]
  FFT: 27.9718 / 885 = 0.0316065   [/home/jon/projects/HElib/src/CModulus.cpp:441]
  FFT_aux: 125.159 / 3965 = 0.0315659   [/home/jon/projects/HElib/src/CModulus.cpp:358]
  FFT_remainder: 2.90566 / 3080 = 0.000943395   [/home/jon/projects/HElib/src/CModulus.cpp:432]
  FFT_remainder: 0.086129 / 885 = 9.73209e-05   [/home/jon/projects/HElib/src/CModulus.cpp:446]
  GenKeySWmatrix: 12.7158 / 16 = 0.79474   [/home/jon/projects/HElib/src/keys.cpp:779]
  addCtxt: 0.105093 / 96 = 0.00109472   [/home/jon/projects/HElib/src/Ctxt.cpp:1001]
  addPart: 0.03096 / 97 = 0.000319175   [/home/jon/projects/HElib/src/Ctxt.cpp:663]
  addPrimes: 125.008 / 194 = 0.644369   [/home/jon/projects/HElib/src/DoubleCRT.cpp:389]
  decode: 43.5569 / 97 = 0.44904   [/home/jon/projects/HElib/src/EncryptedArray.cpp:343]
  do_mul: 0.659491 / 708 = 0.000931484   [/home/jon/projects/HElib/src/DoubleCRT.cpp:171]
  embedInSlots: 2.98219 / 97 = 0.0307442   [/home/jon/projects/HElib/src/PAlgebra.cpp:885]
  factorT: 3.9e-05 / 19 = 2.05263e-06   [/home/jon/projects/HElib/src/NumbTh.cpp:96]
  iFFT: 178.228 / 2712 = 0.0657182   [/home/jon/projects/HElib/src/CModulus.cpp:457]
  iFFT_division: 85.6248 / 2712 = 0.0315726   [/home/jon/projects/HElib/src/CModulus.cpp:522]
  modDownToSet: 110.491 / 192 = 0.575473   [/home/jon/projects/HElib/src/Ctxt.cpp:305]
  multLowLvl: 113.585 / 96 = 1.18318   [/home/jon/projects/HElib/src/Ctxt.cpp:1243]
  privateAssign: 0.450087 / 97 = 0.00464007   [/home/jon/projects/HElib/src/Ctxt.cpp:227]
  randomize: 0.375371 / 130 = 0.00288747   [/home/jon/projects/HElib/src/DoubleCRT.cpp:1052]
  randomize_stream: 0.210369 / 239015 = 8.8015e-07   [/home/jon/projects/HElib/src/DoubleCRT.cpp:1079]
  skEncrypt: 49.5929 / 97 = 0.511267   [/home/jon/projects/HElib/src/keys.cpp:982]
  toPoly: 185.469 / 675 = 0.274769   [/home/jon/projects/HElib/src/DoubleCRT.cpp:730]
  toPoly_CRT: 5.75445 / 675 = 0.00852511   [/home/jon/projects/HElib/src/DoubleCRT.cpp:791]
  toPoly_FFT: 179.432 / 675 = 0.265825   [/home/jon/projects/HElib/src/DoubleCRT.cpp:771]

--------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------
