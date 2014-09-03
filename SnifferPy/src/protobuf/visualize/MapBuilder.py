from src.protobuf.message import cell_pb2

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

    return mb.surf(xs, ys, zs, colormap="Accent", warp_scale="auto")


def _build_building(location, boundary):
    xs, ys = numpy.mgrid[location[0]: location[0] + boundary[0], location[1]: location[1] + boundary[1]]
    zs = numpy.zeros(xs.shape, dtype=int)
    zs.fill(location[2])
    ss = numpy.zeros(xs.shape, dtype=int)
    ss.fill(boundary[2])

    return map(lambda arr: arr.reshape(arr.size, 1), [xs, ys, zs, ss])


def _build_buildings(bld_cells):
    vecs = [[], [], [], []]
    for cell in bld_cells:
        map(lambda item, item_list: item_list.append(item),
            [cell.coord.coord_x, cell.coord.coord_y, cell.coord.coord_z], vecs)

    vecs[3] = numpy.ones(len(vecs[1]))

    return vecs


def build_from_json(m_dict):
    boundary = m_dict[strBoundary]
    start_index = m_dict.get(strLocation, [0, 0, 0])
    fig = _build_surface(start_index, boundary)
    if m_dict.get(strBuilding) is None:
        return fig

    all_list = [], [], [], []
    for bld_dict in m_dict[strBuilding]:
        location = bld_dict[strLocation]
        boundary = bld_dict[strBoundary]
        ret = _build_building(location, boundary)
        map(lambda item, item_list: item_list.extend(item), ret, all_list)

    return mb.barchart(*all_list)


def build_from_bin(mp):
    boundary = [mp.boundary.coord_x, mp.boundary.coord_y, mp.boundary.coord_z]
    start_index = [mp.startIndex.coord_x, mp.startIndex.coord_y, mp.startIndex.coord_z]
    _build_surface(start_index, boundary)

    bld_cells = filter(lambda cell: cell.tag == cell_pb2.Building, mp.cell)
    bld_vecs = _build_buildings(bld_cells)
    return mb.barchart(*bld_vecs)

