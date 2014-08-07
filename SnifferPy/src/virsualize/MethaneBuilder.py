__author__ = 'Kern'

import numpy
from src.filesystem import cell_pb2
import mayavi.mlab as mb


def _cells_to_vector(cells):
    size = len(cells.cell)
    xs = numpy.zeros(size, dtype=int)
    ys = numpy.zeros(size, dtype=int)
    zs = numpy.zeros(size, dtype=int)

    us = numpy.zeros(size)
    vs = numpy.zeros(size)
    ws = numpy.zeros(size)

    for index, cell in enumerate(filter(lambda c: c.tag == cell_pb2.CellTag.Value('Air'), cells.cell)):
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


def _cells_list_to_vector(cells_list):
    all_vec_list = [_cells_to_vector(cells) for cells in cells_list]
    return reduce(
        lambda vec_list1, vec_list2: map(lambda vec1, vec2: numpy.concatenate((vec1, vec2)), vec_list1, vec_list2),
        all_vec_list)


def _build(vecs, fig):
    xs, ys, zs, us, vs, ws = vecs
    if len(xs) <= 0:
        print "len xs = ", len(xs)
        return fig

    if not fig is None:
        fig.mlab_source.reset(x=xs, y=ys, z=zs, u=us, v=vs, w=ws)
    else:
        fig = mb.quiver3d(xs, ys, zs, us, vs, ws, line_width=2, scale_mode="vector", scale_factor=0.1,
                          mode="2dtriangle")
    return fig


def build(hyps, fig):
    # cells_his_list = map(lambda hyp: hyp.methene_cells, filter(lambda hyp: hyp.probability >= 0, hyps.hyp))
    cells_his_list = map(lambda hyp: hyp.methene_cells, hyps.hyp)
    for index, cells_list in enumerate(zip(*cells_his_list)):
        all_vecs = _cells_list_to_vector(cells_list)
        fig = _build(all_vecs, fig)
        print "iteration : ", index

    return fig


