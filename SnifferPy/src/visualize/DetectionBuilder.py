__author__ = 'kding'

import numpy
import mayavi.mlab as mb


def _loc_vector_calculator(detected_location, vec_scale):
    def vector_calculator(hyp):
        vec = sum(map(lambda leak: numpy.array([leak.location.coord_x, leak.location.coord_y, leak.location.coord_z])
                                   - numpy.array([detected_location.coord_x, detected_location.coord_y, detected_location.coord_z]), hyp.leak))
        return vec * hyp.probability * vec_scale / numpy.linalg.norm(vec)

    return vector_calculator


def build(dect, hyps, fig):
    pair_list = map(lambda leak:
                    (numpy.array([leak.location.coord_x, leak.location.coord_y, leak.location.coord_z]),
                     sum([_loc_vector_calculator(leak.location, 10)(hyp) for hyp in hyps.hyp]) / len(hyps.hyp) if len(
                         hyps.hyp) > 0 else 1),
                    dect.leak)

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

    fig = mb.quiver3d(xs, ys, zs, us, vs, ws, line_width=2.0, scale_factor=1.0, mode="2dthick_arrow", colormap="Spectral")

    # print fig

    return fig