#!/usr/bin/env python3

import pybind_he

import unittest
import os


'''
    The pybind_he module needs to be installed (e.g. dist-packages)
    1. setup --> module
    2. import pybind_he  
    3. pybind_he.method()
'''


class TestHead(unittest.TestCase):

    # _test_pathname = os.path.join(os.path.dirname(os.path.realpath(__file__)), "code")
    

    def setUp(self):
        pass

    def test_john(self):

        print(pybind_he.john())

        pass


