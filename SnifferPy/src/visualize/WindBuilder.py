__author__ = 'kding'

import numpy
import mayavi.mlab as mb
from src.model.Cell import str2tag


def build(mp):
    air_cells = filter(lambda cell: cell.tag == str2tag["Air"] and numpy.any(cell.wind.potential > 0), mp.cells)

    size = len(air_cells)

    xs = numpy.zeros(size)
    ys = numpy.zeros(size)
    zs = numpy.zeros(size)
    us = numpy.zeros(size)
    vs = numpy.zeros(size)
    ws = numpy.zeros(size)

    for index, cell in enumerate(air_cells):
        coord = cell.coord
        xs[index] = coord[0]
        ys[index] = coord[1]
        zs[index] = coord[2] + 0.5

        # wind = cell.wind.potential
        wind = cell.wind.calc_wind()

        us[index] = wind[0]
        vs[index] = wind[1]
        ws[index] = wind[2]
        # us[index] = potential.wv_x
        # vs[index] = potential.wv_y
        # ws[index] = potential.wv_z

    return mb.quiver3d(xs, ys, zs, us, vs, ws, line_width=0.5, scale_mode="vector", mode="2darrow")