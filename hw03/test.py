#!/usr/bin/env python
import numpy as np
import pylab as P

#
# The hist() function now has a lot more options
#

#
# first create a single histogram
#
mu, sigma = 200, 25
# x = mu + sigma*P.randn(10000)

with open('random.txt','rb') as infile:
    x = [float(v) for v in infile]

print len(set(x))

# the histogram of the data with histtype='step'
n, bins, patches = P.hist(x, 1000, normed=1, histtype='stepfilled')
P.setp(patches, 'facecolor', 'g', 'alpha', 0.75)

# add a line showing the expected distribution
# y = P.normpdf( bins, mu, sigma)
# l = P.plot(bins, y, 'k--', linewidth=1.5)

P.show()
