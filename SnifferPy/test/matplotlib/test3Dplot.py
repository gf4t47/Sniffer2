__author__ = 'Kern'

import unittest
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt


class MyTestCase(unittest.TestCase):
    def test_something(self):
        mpl.rcParams['legend.fontsize'] = 10

        fig = plt.figure()
        ax = fig.gca(projection='3d')
        x = [50, 50, 49, 49, 49, 43, 43, 42, 42, 41]
        y = [18, 18, 19, 19, 19, 25, 25, 26, 26, 27]
        # z = [2.39, 2.31, 2.35, 2.1, 2.01, 2.09, 2.54, 6.44, 4.51, 5.50]
        z = np.empty(10)
        ax.plot(x, y, z, label='methane concentration')
        ax.legend()

        plt.show()


if __name__ == '__main__':
    unittest.main()
