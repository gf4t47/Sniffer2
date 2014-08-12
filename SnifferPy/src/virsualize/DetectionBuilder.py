__author__ = 'kding'

import numpy


def _loc_vector_calculator(detected_location):
    def vector_calculator(hyp):
        vec = sum(map(lambda leak: numpy.frombuffer(leak.location.coord_item) - numpy.frombuffer(detected_location.coord_item), hyp.leak))
        return vec * hyp.probability / numpy.linalg.norm(vec)

    return vector_calculator


def build_hypothesis(hyps, detected_location, scale):
    xs, ys, zs = detected_location.coord_item
    sum([_location_vector_calculator(detected_location)(hyp) for hyp in hyps])
    vec_list = map(_loc_vector_calculator(detected_location), hyps)
    us, vs, ws = sum(vec_list)

    return mb.quiver3d(xs, ys, zs + z_base, us, vs, ws, line_width=2, scale_mode="vector", scale_factor=scale,
                       mode="2dthick_arrow", colormap="Set3")


def refresh_hypothesis(hyps, detected_location, fig):
    xs, ys, zs = detected_location
    vec_list = map(_loc_vector_calculator(detected_location), hyps)
    us, vs, ws = sum(vec_list)

    fig.mlab_source.reset(x=xs, y=ys, z=zs + z_base, u=us, v=vs, w=ws)


def _location_vector_calculator(hyp):
    vec = numpy.array(reduce(lambda leak1, leak2: map(lambda item1, item2: item1 + item2, leak1, leak2), hyp.leak))
    return vec * hyp.probability


def build(dect, hyps, fig):
    for leak in dect.leak:
        vec = sum([_location_vector_calculator(leak.location)(hyp) for hyp in hyps])
    pass