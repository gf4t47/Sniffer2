__author__ = 'kding'

import numpy
import mayavi.mlab as mb


def _loc_vector_calculator(detected_location):
    def vector_calculator(hyp):
        vec = sum(map(lambda leak: numpy.array(leak.location.coord_item) - numpy.array(detected_location.coord_item),
                      hyp.leak))
        return vec * hyp.probability / numpy.linalg.norm(vec)

    return vector_calculator


def build_detection(vecs, scale):
    xs, ys, zs, us, vs, ws = vecs

    return mb.quiver3d(xs, ys, zs, us, vs, ws, line_width=2, scale_mode="vector", scale_factor=scale,
                       mode="2dthick_arrow", colormap="Set3")


def refresh_detection(vecs, fig):
    xs, ys, zs, us, vs, ws = vecs

    fig.mlab_source.reset(x=xs, y=ys, z=zs, u=us, v=vs, w=ws)


def build(dect, hyps, fig):
    pair_list = map(lambda leak: (numpy.array(leak.location.coord_item),
                                  sum([_loc_vector_calculator(leak.location)(hyp) for hyp in hyps.hyp])),
                    dect.leak)
    if not fig is None:
        refresh_detection(pair_list, fig)
    else:
        build_detection(pair_list, 0.1)