__author__ = 'kding'

import numpy
import mayavi.mlab as mb
from src.protomsg import cell_pb2


def build(mp):
    air_cells = filter(lambda cell: cell.tag == cell_pb2.Air, mp.cell)

    size = len(air_cells)

    xs = numpy.zeros(size)
    ys = numpy.zeros(size)
    zs = numpy.zeros(size)
    us = numpy.zeros(size)
    vs = numpy.zeros(size)
    ws = numpy.zeros(size)

    for index, cell in enumerate(air_cells):

        coord = cell.coord
        xs[index] = coord.coord_x
        ys[index] = coord.coord_y
        zs[index] = coord.coord_z

        wind = cell.wind.wind
        potential = cell.wind.potential
        us[index] = wind.wv_x + potential.wv_x
        vs[index] = wind.wv_y + potential.wv_y
        ws[index] = wind.wv_z + potential.wv_z
    return mb.quiver3d(xs, ys, zs, us, vs, ws, line_width=0.5, scale_mode="vector", mode="2darrow", colormap="Set1")