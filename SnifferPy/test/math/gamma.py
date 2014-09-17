__author__ = 'Kern'

import unittest

from scipy.stats import gamma
import matplotlib.pyplot as plt
import numpy as np

concentration_per_particle = 5.125E-007


class MyTestCase(unittest.TestCase):
    def _test_fit(self):
        filename = "../../../bridge/cfg/detection.dat"
        dat = np.loadtxt(filename)

        fit_shape, fit_loc, fit_scale = gamma.fit(dat[77:, 1])
        print fit_shape, fit_loc, fit_scale

        mean = fit_shape * fit_scale
        variance = mean * fit_scale
        print mean, variance

        x = np.linspace(0.00001, 0.00009, 10000)
        # ax.plot(x, gamma.pdf(x, shape), 'r-', lw=5, alpha=0.6, label='gamma pdf')

        rv = gamma(fit_shape, loc=fit_loc, scale=fit_scale)

        fig, ax = plt.subplots(1, 1)
        ax.plot(x, rv.pdf(x), 'k-', lw=2, label='frozen pdf')

        plt.show()

    def trans_conc_particle(self, concs):
        return [conc / concentration_per_particle for conc in concs]

    def _test_fit_trans(self):
        filename = "../../../bridge/cfg/detection.dat"
        dat = np.loadtxt(filename)

        fit_shape, fit_loc, fit_scale = gamma.fit(self.trans_conc_particle(dat[77:, 1]))
        print fit_shape, fit_loc, fit_scale

        mean = fit_shape * fit_scale
        variance = mean * fit_scale
        print mean, variance

        x = np.linspace(1, 250, 10000)
        # ax.plot(x, gamma.pdf(x, shape), 'r-', lw=5, alpha=0.6, label='gamma pdf')

        rv = gamma(fit_shape, scale=fit_scale)

        fig, ax = plt.subplots(1, 1)
        ax.plot(x, rv.pdf(x), 'k-', lw=2, label='frozen pdf')

        plt.show()

    def test_gamma(self):
        fig, ax = plt.subplots(1, 1)

        variance = 128.0
        mean = 224.0
        scale = variance / mean
        shape = mean / scale

        x = np.linspace(1, 250, 10000)
        rv = gamma(shape, scale=scale)
        ax.plot(x, rv.pdf(x), 'k-', lw=2, label='gamma pdf')

        mean = 114.0
        scale = variance / mean
        shape = mean / scale

        x = np.linspace(1, 250, 10000)
        rv = gamma(shape, scale=scale)
        ax.plot(x, rv.pdf(x), 'k-', lw=2, label='gamma pdf')

        mean = 24.0
        scale = variance / mean
        shape = mean / scale

        x = np.linspace(1, 250, 10000)
        rv = gamma(shape, scale=scale)
        ax.plot(x, rv.pdf(x), 'k-', lw=2, label='gamma pdf')

        mean = 9.0
        scale = variance / mean
        shape = mean / scale

        x = np.linspace(1, 250, 10000)
        rv = gamma(shape, scale=scale)
        ax.plot(x, rv.pdf(x), 'k-', lw=2, label='gamma pdf')

        plt.show()

    def _test_draw(self):
        fig, gamma_plot = plt.subplots(1, 1)

        variance = 188.0
        mean = 60.0
        var = 110
        scale = variance / mean
        shape = mean / scale

        x = np.linspace(1, 250, 10000)
        rv = gamma(shape, scale=scale)

        gamma_plot.plot(x, rv.pdf(x), 'k-', lw=2, c='blue', label='gamma')
        gamma_plot.plot([0, var], [rv.pdf(var), rv.pdf(var)], 'k--', lw=1, c='red', label='pdf')
        gamma_plot.plot([var, var], [0, rv.pdf(var)], 'k-', lw=1, label='x')

        plt.show()


if __name__ == '__main__':
    unittest.main()
