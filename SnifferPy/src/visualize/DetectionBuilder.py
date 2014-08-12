__author__ = 'kding'

import numpy
import mayavi.mlab as mb


def _loc_vector_calculator(detected_location):
    def vector_calculator(hyp):
        vec = sum(map(lambda leak: numpy.array(leak.location.coord_item) - numpy.array(detected_location.coord_item),
                      hyp.leak))
        return vec * hyp.probability / numpy.linalg.norm(vec)

    return vector_calculator


def build(dect, hyps, fig):
    pair_list = map(lambda leak: (numpy.array(leak.location.coord_item),
                                  sum([_loc_vector_calculator(leak.location)(hyp) for hyp in hyps.hyp])),
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

    if not fig is None:
        fig.mlab_source.reset(x=xs, y=ys, z=zs, u=us, v=vs, w=ws)
    else:
        fig = mb.quiver3d(xs, ys, zs, us, vs, ws, line_width=2, scale_mode="vector", scale_factor=4,
                          mode="2dthick_arrow", colormap="Set3")

    return fig