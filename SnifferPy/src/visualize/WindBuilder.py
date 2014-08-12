__author__ = 'kding'

import numpy
import mayavi.mlab as mb
from src.filesystem import cell_pb2


def build(mp):
    air_cells = filter(lambda cell: cell.tag == cell_pb2.CellTag.Value('Air'), mp.cell)

    size = len(air_cells)

    xs = numpy.zeros(size)
    ys = numpy.zeros(size)
    zs = numpy.zeros(size)
    us = numpy.zeros(size)
    vs = numpy.zeros(size)
    ws = numpy.zeros(size)

    for index, cell in enumerate(air_cells):

        coord = cell.coord.coord_item
        xs[index] = coord[0]
        ys[index] = coord[1]
        zs[index] = coord[2]

        wind = cell.wind.wind.wv_item
        potential = cell.wind.potential.wv_item
        us[index] = wind[0] + potential[0]
        vs[index] = wind[1] + potential[1]
        ws[index] = wind[2] + potential[2]

    return mb.quiver3d(xs, ys, zs, us, vs, ws, line_width=0.5, scale_factor=0.5, mode="2darrow", colormap="Set3")