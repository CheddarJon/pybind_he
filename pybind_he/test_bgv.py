#!/usr/bin/env python3

import helib_bgv

def main():
    p = 4999
    m = 32109
    r = 1
    bits = 300
    c = 2
    print('Initialising context object...')
    context = helib_bgv.Context(m, p, r)
    print('Building modulus chain...')
    helib_bgv.buildModChain(context, bits, c)

    context.zMStar.printout()
    print()

    print('Estimated security level...', context.securityLevel())

    print('Creating secret key...')
    sk = helib_bgv.SecKey(context)

    sk.genSecKey()

    print('Generating key-switching matrices...')
    helib_bgv.addSome1DMatrices(sk)

    pk = helib_bgv.PubKey(sk)

    ea = context.get_ea()

    nslots = len(ea)
    print('Number of slots: ', nslots)

    ptxt = helib_bgv.VectorLong(nslots)

    for i in range(0, nslots):
        ptxt.insert(i, i)

    # TODO Add a __str__ method to std::vector<long> instead of vecToStr.
    print('Initial Ptxt: ', helib_bgv.vecToStr(ptxt))

    ctxt = helib_bgv.Ctxt(pk)
    ea.encrypt(ctxt, pk, ptxt)

    ctxt.Mul(ctxt)
    ctxt.Add(ctxt)

    decrypted = helib_bgv.VectorLong(nslots)
    ea.decrypt(ctxt, sk, decrypted)

    print('Decrypted Ptxt: ', helib_bgv.vecToStr(decrypted))

if __name__ == '__main__':
    main()
