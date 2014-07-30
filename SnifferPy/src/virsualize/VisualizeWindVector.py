__author__ = 'Ding'

import numpy
import mayavi.mlab as mb
from ..model import Cells
from ..model import Cell
from ..model import WindVector as wv
from ..model import Vector2D as v2


def build_all_quivers(ls, l, ws, w, hs, h):
    x, y, z = numpy.mgrid[ls:l + ls, ws: w + ws, hs: h + hs]
    r = numpy.sqrt(x ** 2 + y ** 2 + z ** 4)
    u = y * numpy.sin(r) / (r + 0.001)
    v = -x * numpy.sin(r) / (r + 0.001)
    w = numpy.zeros_like(z)

    return mb.quiver3d(x, y, z, u, v, w, line_width=2, scale_factor=0.8)


def build_quiver(bld, base):
    base += 0.5
    x, y, z = numpy.mgrid[v2.get_x(bld.location) - 1: v2.get_x(bld.location) + bld.length + 1,
              v2.get_y(bld.location) - 1: v2.get_y(bld.location) + bld.width + 1, base: base + bld.height]

    r = numpy.sqrt(x ** 2 + y ** 2 + z ** 4)
    u = y * numpy.sin(r) / (r + 0.001)
    v = -x * numpy.sin(r) / (r + 0.001)
    w = numpy.zeros_like(z)

    return mb.quiver3d(x, y, z, u, v, w, line_width=0.5, scale_factor=0.8, mode="2darrow")


def build_air_cells(air_cells):
    db = Cells.get_db(air_cells)
    size = len(db)

    xs = numpy.zeros(size)
    ys = numpy.zeros(size)
    zs = numpy.zeros(size)
    us = numpy.zeros(size)
    vs = numpy.zeros(size)
    ws = numpy.zeros(size)

    for index, cell in enumerate(db.itervalues()):
        wind = Cell.get_wind(cell)
        if wind is None:
            continue

        coord = Cell.get_coord(cell)
        xs[index] = v3.get_x(coord)
        ys[index] = v3.get_y(coord)
        zs[index] = v3.get_z(coord)

        component = wv.get_vector(wind)
        us[index] = v3.get_x(component)
        vs[index] = v3.get_y(component)
        ws[index] = v3.get_z(component)

    return mb.quiver3d(xs, ys, zs, us, vs, ws, line_width=0.5, scale_factor=0.5, mode="2darrow", colormap="Set3")