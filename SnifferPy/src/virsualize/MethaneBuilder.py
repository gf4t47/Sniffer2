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


def _build(vecs, fig):
    xs, ys, zs, us, vs, ws = vecs

    if not fig is None:
        fig.mlab_source.reset(x=xs, y=ys, z=zs, u=us, v=vs, w=ws)
    else:
        fig = mb.quiver3d(xs, ys, zs, us, vs, ws, line_width=2, scale_mode="vector", scale_factor=0.1,
                          mode="2dtriangle")


def build(hyps, fig):
    cells_his_list = map(lambda hyp: hyp.methene_cells, filter(lambda hyp: hyp.probability >= 0.9 / len(hyps.hyp), hyps.hyp))
    for cells_list in zip(*cells_his_list):
        all_cells = reduce(lambda cells1, cells2: cells1.extend(cells2), cells_list)
        all_vecs = _cells_to_vector(all_cells)
        return _build(all_vecs, fig)


