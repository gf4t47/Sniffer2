__author__ = 'kding'

import numpy
import mayavi.mlab as mb


def _loc_vector_calculator(detected_location, vec_scale):
    def vector_calculator(hyp):
        vec = sum(map(lambda leak: leak.coord - detected_location, hyp.leaks))
        return vec * hyp.prob * vec_scale / numpy.linalg.norm(vec)

    return vector_calculator


def build(dect, hyps, fig):
    pair_list = map(lambda leak: (leak.coord, sum([_loc_vector_calculator(leak.coord, len(hyps))(hyp) for hyp in hyps]) / len(
        hyps) if len(hyps) > 0 else 1), dect.leaks)

    size = len(pair_list)
    xs = numpy.empty(size, dtype=int)
    ys = numpy.empty(size, dtype=int)
    zs = numpy.empty(size, dtype=int)
    us = numpy.empty(size)
    vs = numpy.empty(size)
    ws = numpy.empty(size)

    for index, pair in enumerate(pair_list):
        loc, vec = pair
        xs[index], ys[index], zs[index] = loc
        us[index], vs[index], ws[index] = vec

    # print loc, vec

    if not fig is None:
        fig.glyph.color_mode = 'color_by_scalar'

    fig = mb.quiver3d(xs, ys, zs, us, vs, ws, line_width=2.0, scale_factor=4.0, mode="2dthick_arrow",
                      colormap="Spectral")

    # print fig

    return fig