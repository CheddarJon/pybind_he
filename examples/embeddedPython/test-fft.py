#!/usr/bin/python

import emb

def test():
    n, bit_reversed, cos_table, sin_table = emb.getFftTable()
    print('n = {}'.format(n))
    print('bit_reversed = {}'.format(bit_reversed))
    print('cos_table = {}'.format(cos_table))
    print('sin_table = {}'.format(sin_table))

    return 0
