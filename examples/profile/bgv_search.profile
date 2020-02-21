
--------------------------------------------------------------------------------------------------------------
-------------- bgv_search with parameters: p = 2, m = 4095, r = 1, bits = 500, c = 2 NOT SECURE --------------
-------------- timing both vector multiplication and addition ------------------------------------------------
--------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------
-Function name: time in seconds / number of times called = average [path/to/file/where/function/resides:line]-
--------------------------------------------------------------------------------------------------------------

  AAA_embeddingLargest: 0.081754 / 359 = 0.000227727   [/home/jon/projects/HElib/src/norms.cpp:258]
  AAA_embeddingLargest_x2: 0.044656 / 200 = 0.00022328   [/home/jon/projects/HElib/src/norms.cpp:428]
  AAA_modDownEnbeddings: 0.057462 / 200 = 0.00028731   [/home/jon/projects/HElib/src/Ctxt.cpp:384]
  BlockMatMul1DExec: 0.010159 / 2 = 0.0050795   [/home/jon/projects/HElib/src/matmul.cpp:1460]
  BluesteinFFT: 1.59647 / 9014 = 0.00017711   [/home/jon/projects/HElib/src/bluestein.cpp:136]
  CRT_reconstruct: 0.039272 / 57 = 0.000688982   [/home/jon/projects/HElib/src/PAlgebra.cpp:947]
  CRT_reconstruct: 0.002418 / 88 = 2.74773e-05   [/home/jon/projects/HElib/src/PAlgebra.cpp:947]
  CompMod: 0.002629 / 57 = 4.61228e-05   [/home/jon/projects/HElib/src/PAlgebra.cpp:911]
  CompMod: 0.000618 / 88 = 7.02273e-06   [/home/jon/projects/HElib/src/PAlgebra.cpp:911]
  Decrypt: 0.146519 / 33 = 0.00443997   [/home/jon/projects/HElib/src/keys.cpp:910]
  DoubleCRT: 0.014666 / 6 = 0.00244433   [/home/jon/projects/HElib/src/DoubleCRT.cpp:532]
  DoubleCRT: 0.881645 / 499 = 0.00176682   [/home/jon/projects/HElib/src/DoubleCRT.cpp:474]
  FFT: 1.16248 / 625 = 0.00185996   [/home/jon/projects/HElib/src/DoubleCRT.cpp:54]
  FFT: 1.16195 / 5657 = 0.0002054   [/home/jon/projects/HElib/src/CModulus.cpp:427]
  FFT: 0.156584 / 73 = 0.00214499   [/home/jon/projects/HElib/src/DoubleCRT.cpp:73]
  FFT: 0.156508 / 847 = 0.000184779   [/home/jon/projects/HElib/src/CModulus.cpp:441]
  FFT_aux: 1.19137 / 6504 = 0.000183176   [/home/jon/projects/HElib/src/CModulus.cpp:358]
  FFT_remainder: 0.002028 / 847 = 2.39433e-06   [/home/jon/projects/HElib/src/CModulus.cpp:446]
  FFT_remainder: 0.123741 / 5657 = 2.1874e-05   [/home/jon/projects/HElib/src/CModulus.cpp:432]
  GenKeySWmatrix: 0.147912 / 16 = 0.0092445   [/home/jon/projects/HElib/src/keys.cpp:779]
  KS_loop: 0.053998 / 144 = 0.000374986   [/home/jon/projects/HElib/src/Ctxt.cpp:129]
  KS_loop_1: 0.006576 / 144 = 4.56667e-05   [/home/jon/projects/HElib/src/Ctxt.cpp:136]
  KS_loop_2: 0.004828 / 144 = 3.35278e-05   [/home/jon/projects/HElib/src/Ctxt.cpp:139]
  KS_loop_3: 0.007242 / 144 = 5.02917e-05   [/home/jon/projects/HElib/src/Ctxt.cpp:143]
  KS_loop_4: 0.002718 / 144 = 1.8875e-05   [/home/jon/projects/HElib/src/Ctxt.cpp:146]
  MatMul1DExec: 0.028066 / 13 = 0.00215892   [/home/jon/projects/HElib/src/matmul.cpp:675]
  NORM_VAL: 0.048835 / 144 = 0.000339132   [/home/jon/projects/HElib/src/DoubleCRT.cpp:362]
  addCtxt: 0.001589 / 40 = 3.9725e-05   [/home/jon/projects/HElib/src/Ctxt.cpp:1001]
  addPart: 0.043638 / 476 = 9.16765e-05   [/home/jon/projects/HElib/src/Ctxt.cpp:663]
  addPrimes: 0.591426 / 177 = 0.00334139   [/home/jon/projects/HElib/src/DoubleCRT.cpp:389]
  addPrimes_5: 0.643778 / 144 = 0.00447068   [/home/jon/projects/HElib/src/DoubleCRT.cpp:337]
  automorph: 0.000622 / 8 = 7.775e-05   [/home/jon/projects/HElib/src/Ctxt.cpp:1606]
  breakIntoDigits: 0.64976 / 72 = 0.00902444   [/home/jon/projects/HElib/src/DoubleCRT.cpp:300]
  buildLinPolyCoeffs: 0.000109 / 2 = 5.45e-05   [/home/jon/projects/HElib/src/EncryptedArray.cpp:562]
  buildLinPolyCoeffs: 0.004384 / 2 = 0.002192   [/home/jon/projects/HElib/src/EncryptedArray.cpp:562]
  buildLinPolyCoeffs_invert: 9.8e-05 / 1 = 9.8e-05   [/home/jon/projects/HElib/src/EncryptedArray.cpp:571]
  buildLinPolyCoeffs_invert: 0.004337 / 1 = 0.004337   [/home/jon/projects/HElib/src/EncryptedArray.cpp:571]
  buildUnpackSlotEncoding: 0.000954 / 1 = 0.000954   [/home/jon/projects/HElib/src/intraSlot.cpp:36]
  compEqGt: 2.46624 / 1 = 2.46624   [/home/jon/projects/HElib/src/binaryCompare.cpp:93]
  compEqGt1: 0.515714 / 1 = 0.515714   [/home/jon/projects/HElib/src/binaryCompare.cpp:102]
  compEqGt2: 0 / 1 = 0   [/home/jon/projects/HElib/src/binaryCompare.cpp:117]
  compEqGt3: 1.9504 / 1 = 1.9504   [/home/jon/projects/HElib/src/binaryCompare.cpp:142]
  compResults: 0.000465 / 1 = 0.000465   [/home/jon/projects/HElib/src/binaryCompare.cpp:192]
  compareTwoNumbersImplementation: 2.46672 / 1 = 2.46672   [/home/jon/projects/HElib/src/binaryCompare.cpp:155]
  decode: 0.022648 / 33 = 0.000686303   [/home/jon/projects/HElib/src/EncryptedArray.cpp:343]
  do_mul: 0.02574 / 657 = 3.91781e-05   [/home/jon/projects/HElib/src/DoubleCRT.cpp:171]
  embedInSlots: 0.042046 / 57 = 0.000737649   [/home/jon/projects/HElib/src/PAlgebra.cpp:885]
  embedInSlots: 0.003305 / 88 = 3.75568e-05   [/home/jon/projects/HElib/src/PAlgebra.cpp:885]
  factorT: 9e-06 / 29 = 3.10345e-07   [/home/jon/projects/HElib/src/NumbTh.cpp:96]
  gen1s: 0 / 2 = 0   [/home/jon/projects/pybind_he/examples/bgv_search.cpp:238]
  iFFT: 1.02508 / 2510 = 0.000408398   [/home/jon/projects/HElib/src/CModulus.cpp:457]
  iFFT_division: 0.548947 / 2510 = 0.000218704   [/home/jon/projects/HElib/src/CModulus.cpp:522]
  inv_module: 0.000676 / 2 = 0.000338   [/home/jon/projects/pybind_he/examples/bgv_search.cpp:228]
  keySwitchPart: 0.720743 / 72 = 0.0100103   [/home/jon/projects/HElib/src/Ctxt.cpp:620]
  modDownToSet: 1.78155 / 200 = 0.00890777   [/home/jon/projects/HElib/src/Ctxt.cpp:305]
  multByConstant: 0.00064 / 7 = 9.14286e-05   [/home/jon/projects/HElib/src/Ctxt.cpp:1460]
  multByConstant: 0.013747 / 5 = 0.0027494   [/home/jon/projects/HElib/src/Ctxt.cpp:1496]
  multByConstant: 8.8e-05 / 1 = 8.8e-05   [/home/jon/projects/HElib/src/Ctxt.cpp:1393]
  multLowLvl: 1.21281 / 64 = 0.0189501   [/home/jon/projects/HElib/src/Ctxt.cpp:1243]
  multiplyBy: 2.45942 / 63 = 0.0390385   [/home/jon/projects/HElib/src/Ctxt.cpp:1319]
  privateAssign: 0.014939 / 175 = 8.53657e-05   [/home/jon/projects/HElib/src/Ctxt.cpp:227]
  randomize: 0.032899 / 210 = 0.000156662   [/home/jon/projects/HElib/src/DoubleCRT.cpp:1052]
  randomize_stream: 0.01997 / 22843 = 8.74228e-07   [/home/jon/projects/HElib/src/DoubleCRT.cpp:1079]
  reLinearize: 1.43796 / 72 = 0.0199716   [/home/jon/projects/HElib/src/Ctxt.cpp:544]
  rotate: 0.080249 / 1 = 0.080249   [/home/jon/projects/HElib/src/EncryptedArray.cpp:159]
  rotate1D: 0.149195 / 8 = 0.0186494   [/home/jon/projects/HElib/src/EncryptedArray.cpp:57]
  runningSums: 0.000707 / 1 = 0.000707   [/home/jon/projects/HElib/src/binaryCompare.cpp:38]
  shift: 0.102186 / 1 = 0.102186   [/home/jon/projects/HElib/src/EncryptedArray.cpp:262]
  shift1D: 0.021468 / 2 = 0.010734   [/home/jon/projects/HElib/src/EncryptedArray.cpp:113]
  skEncrypt: 0.13904 / 33 = 0.00421333   [/home/jon/projects/HElib/src/keys.cpp:982]
  smartAutomorph: 0.167808 / 8 = 0.020976   [/home/jon/projects/HElib/src/Ctxt.cpp:1647]
  toPoly: 1.16689 / 641 = 0.00182042   [/home/jon/projects/HElib/src/DoubleCRT.cpp:730]
  toPoly_CRT: 0.129547 / 641 = 0.000202101   [/home/jon/projects/HElib/src/DoubleCRT.cpp:791]
  toPoly_FFT: 1.03318 / 641 = 0.00161182   [/home/jon/projects/HElib/src/DoubleCRT.cpp:771]

Total time: 28.8268
--------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------
