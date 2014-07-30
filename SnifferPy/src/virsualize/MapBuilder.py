__author__ = 'kding'

import numpy
import mayavi.mlab as mb

strBoundary = "boundary"
strLocation = "location"
strWind = "wind"
strUnit = "unit"
strPotentialStep = "potential"
strBuilding = "building"


def _build_surface(start_index, boundary):
    xs, ys = numpy.mgrid[start_index[0]: start_index[0] + boundary[0], start_index[1]: start_index[1] + boundary[1]]
    zs = numpy.zeros(xs.shape)
    zs.fill(start_index[2])
    surf_fig = mb.surf(xs, ys, zs, colormap="Accent", warp_scale="auto")
    return surf_fig


def _build_building(location, boundary):
    xs, ys = numpy.mgrid[location[0]: location[0] + boundary[0], location[1]: location[1] + boundary[1]]
    zs = numpy.zeros(xs.shape)
    zs.fill(location[2])
    ss = numpy.zeros(xs.shape)
    ss.fill(boundary[2])

    mb.barchart(xs, ys, zs, ss)


def build(m_dict):
    boundary = m_dict[strBoundary]
    start_index = m_dict.get(strLocation, [0, 0, 0])
    _build_surface(start_index, boundary)

    for bld_dict in m_dict[strBuilding]:
        location = bld_dict[strLocation]
        boundary = bld_dict[strBoundary]
        _build_building(location, boundary)