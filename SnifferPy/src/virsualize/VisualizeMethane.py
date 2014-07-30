__author__ = 'Ding'

import mayavi.mlab as mb
import numpy

from ..model import Methane as ptc
from ..model import Cell
from ..model import Cells
from ..model import Vector3D as v3


def build_methane(cell, z_base, scale):
    pos = Cell.get_coord(cell)
    methane = Cell.get_methane(cell)
    num = ptc.get_particle_num(methane)
    x, y, z = pos
    u, v, w = numpy.array([num, num, num])
    return mb.quiver3d(x, y, z + z_base, u, v, w, line_width=2, scale_mode="vector", scale_factor=scale,
                       mode="2dtriangle")


def _cells_to_vector(cells):
    db = Cells.get_db(cells)
    size = len(db)

    xs = numpy.zeros(size)
    ys = numpy.zeros(size)
    zs = numpy.zeros(size)
    us = numpy.zeros(size)
    vs = numpy.zeros(size)
    ws = numpy.zeros(size)

    for index, cell in enumerate(db.itervalues()):
        if not Cell.has_methane(cell):
            continue
        methane = Cell.get_methane(cell)

        coord = Cell.get_coord(cell)
        xs[index] = v3.get_x(coord)
        ys[index] = v3.get_y(coord)
        zs[index] = v3.get_z(coord)

        concentration = ptc.get_particle_num(methane)
        us[index] = concentration
        vs[index] = concentration
        ws[index] = concentration

    return xs, ys, zs, us, vs, ws


def build_methane(cells, z_base, scale):
    if Cells.get_size(cells) <= 0:
        return

    xs, ys, zs, us, vs, ws = _cells_to_vector(cells)

    return mb.quiver3d(xs, ys, zs + z_base, us, vs, ws, line_width=2, scale_mode="vector", scale_factor=scale,
                       mode="2dtriangle")


def refresh_methane(cells, fig, z_base):
    if Cells.get_size(cells) <= 0:
        return

    ms = fig.mlab_source
    xs, ys, zs, us, vs, ws = _cells_to_vector(cells)

    ms.reset(x=xs, y=ys, z=zs + z_base, u=us, v=vs, w=ws)

