__author__ = 'Kern'

import numpy
import mayavi.mlab as mb


def _cells_to_vector(cells):
    size = len(cells.cell)
    xs = numpy.zeros(size)
    ys = numpy.zeros(size)
    zs = numpy.zeros(size)

    us = numpy.zeros(size)
    vs = numpy.zeros(size)
    ws = numpy.zeros(size)

    for index, cell in enumerate(cells.cell):
        coord = cell.coord
        xs[index] = coord.coord_item[0]
        ys[index] = coord.coord_item[1]
        zs[index] = coord.coord_item[2]

        methane = cell.mtn
        concentration = methane.concentration
        us[index] = concentration
        vs[index] = concentration
        ws[index] = concentration

    return xs, ys, zs, us, vs, ws


def build(hyps_his):
    init = True
    for hyps in hyps_his.hyps:
        for hyp in hyps.hyp:
            for cells in hyp.methene_cells:
                xs, ys, zs, us, vs, ws = _cells_to_vector(cells)
                if init:
                    init = False
                    fig = mb.quiver3d(xs, ys, zs, us, vs, ws, line_width=2, scale_mode="vector", scale_factor=0.1, mode="2dtriangle")
                else:
                    ms = fig.mlab_source
                    ms.reset(x=xs, y=ys, z=zs, u=us, v=vs, w=ws)

