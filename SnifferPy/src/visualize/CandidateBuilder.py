__author__ = 'kding'


import numpy
import mayavi.mlab as mb


def build(dect, hyps, fig):
    

    if not fig is None:
        fig.glyph.color_mode = 'color_by_scalar'

    fig = mb.quiver3d(xs, ys, zs, us, vs, ws, line_width=2.0, scale_factor=1.0, mode="2dthick_arrow", colormap="cool")

    return fig