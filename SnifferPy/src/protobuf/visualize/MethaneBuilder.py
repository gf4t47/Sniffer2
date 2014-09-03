from src.protobuf.message import cell_pb2

__author__ = 'Kern'

import numpy
import mayavi.mlab as mb


def _cells_to_vector(cells):
    size = len(cells.cell)
    xs = numpy.zeros(size, dtype=int)
    ys = numpy.zeros(size, dtype=int)
    zs = numpy.zeros(size, dtype=int)

    us = numpy.zeros(size)
    vs = numpy.zeros(size)
    ws = numpy.zeros(size)

    for index, cell in enumerate(filter(lambda c: c.tag == cell_pb2.Air, cells.cell)):
        coord = cell.coord
        xs[index] = coord.coord_x
        ys[index] = coord.coord_y
        zs[index] = coord.coord_z

        concentration = cell.mtn.concentration
        us[index] = concentration
        vs[index] = concentration
        ws[index] = concentration

    return xs, ys, zs, us, vs, ws


def _cells_list_to_vector(cells_list):
    all_vec_list = [_cells_to_vector(cells) for cells in cells_list]
    return reduce(
        lambda vec_list1, vec_list2: map(lambda vec1, vec2: numpy.concatenate((vec1, vec2)), vec_list1, vec_list2),
        all_vec_list)


def _build(vecs, fig, color):
    xs, ys, zs, us, vs, ws = vecs

    # print "vec length = ", len(xs), len(ys), len(zs), len(us), len(vs), len(ws)
    # time.sleep(0.1)

    if not fig is None:
        # fig.mlab_source.reset(x=xs, y=ys, z=zs, u=us, v=vs, w=ws)
        fig.remove()
        fig = mb.quiver3d(xs, ys, zs, us, vs, ws, line_width=2.0, scale_mode="vector", mode="2dtriangle", colormap=color)
    else:
        fig = mb.quiver3d(xs, ys, zs, us, vs, ws, line_width=2.0, scale_mode="vector", mode="2dtriangle", colormap=color)
        # fig.glyph.scale_mode = 'scale_by_vector'

    # time.sleep(0.1)
    # print fig

    return fig


def build(hyps, figs):
    low_fig, high_fig = figs

    prob_list = [hyp.probability for hyp in hyps.hyp]
    cells_his_list = [hyp.methene_cells for hyp in hyps.hyp]
    print "probability =", prob_list

    high_cells = None
    low_cells = cells_his_list

    if len(prob_list) > 1:
        max_prob = max(prob_list)
        max_index_list = [index for index, val in enumerate(prob_list) if val == max_prob]
        if len(max_index_list) < len(prob_list):
            high_cells = [cells_his_list[index] for index in max_index_list]
            low_cells = [cells_his for index, cells_his in enumerate(cells_his_list) if not index in max_index_list]

    if high_cells is None:
        for low_cells_list in zip(*low_cells):
            low_vecs = _cells_list_to_vector(low_cells_list)
            if not high_fig is None:
                high_fig.remove()
                high_fig = None
            low_fig = _build(low_vecs, low_fig, "Pastel2")
    else:
        for low_cells_list, high_cells_list in zip(zip(*low_cells), zip(*high_cells)):
            low_vecs = _cells_list_to_vector(low_cells_list)
            high_vecs = _cells_list_to_vector(high_cells_list)
            low_fig = _build(low_vecs, low_fig, "Pastel2")
            high_fig = _build(high_vecs, high_fig, "blue-red")

    return low_fig, high_fig


