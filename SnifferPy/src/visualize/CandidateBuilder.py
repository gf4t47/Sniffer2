__author__ = 'kding'


import numpy
import mayavi.mlab as mb


def build(candidate, fig):
    size = len(candidate.leak)
    xs = numpy.empty(size, dtype=int)
    ys = numpy.empty(size, dtype=int)
    zs = numpy.empty(size, dtype=int)
    us = numpy.empty(size)
    vs = numpy.empty(size)
    ws = numpy.empty(size)

    for index, (loc, infor_gain) in enumerate([(leak.location, leak.concentration) for leak in candidate.leak]):
        print "information gain =", loc.coord_item, "->", infor_gain
        xs[index], ys[index], zs[index] = loc.coord_item
        us[index] = infor_gain
        vs[index] = infor_gain
        ws[index] = infor_gain

    if fig is None:
        fig = mb.quiver3d(xs, ys, zs, us, vs, ws, scale_mode="vector", mode="2dcross", colormap="Spectral")
    else:
        fig.reset(x=xs, y=ys, z=zs, u=us, v=vs, w=ws)

    return fig