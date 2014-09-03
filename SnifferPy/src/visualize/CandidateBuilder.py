__author__ = 'kding'


import numpy
import mayavi.mlab as mb


def build(candidate, fig):
    can_list = candidate.leaks

    size = len(can_list)
    xs = numpy.empty(size, dtype=int)
    ys = numpy.empty(size, dtype=int)
    zs = numpy.empty(size, dtype=int)
    us = numpy.empty(size)
    vs = numpy.empty(size)
    ws = numpy.empty(size)

    for index, can in enumerate(can_list):
        loc = can.coord
        infor_gain = can.conc

        print "information gain =", [loc[0], loc[1], loc[2]], "->", infor_gain
        xs[index] = loc[0]
        ys[index] = loc[1]
        zs[index] = loc[2]
        us[index] = infor_gain
        vs[index] = infor_gain
        ws[index] = 0

    if fig is None:
        fig = mb.quiver3d(xs, ys, zs, us, vs, ws, scale_mode="vector", mode="2dthick_cross", colormap="cool")
    else:
        fig.mlab_source.reset(x=xs, y=ys, z=zs, u=us, v=vs, w=ws)

    return fig