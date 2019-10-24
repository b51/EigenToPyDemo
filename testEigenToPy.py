#!/usr/bin/env python3
#########################################################################
#
#              Author: b51
#                Mail: b51live@gmail.com
#            FileName: testEigenToPy.py
#
#          Created On: Thu 24 Oct 2019 12:30:32 PM CST
#     Licensed under The MIT License [see LICENSE for details]
#
#########################################################################

import sys
sys.path.append('./lib/python3.6/site-packages')

import EigenToPy

r = EigenToPy.toRotationMatrix(0, 0, 0)
print(r)
