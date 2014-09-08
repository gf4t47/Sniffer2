__author__ = 'Kern'
from struct import *
import numpy as np
from src.model.Cell import *
from src.model.Detection import *
from src.model.Hypothesis import *
from src.model.Wind import *
from src.model.Map3D import *

strDect = "dect"
strMap = "map"
strMethane = "mtn"

int_len = 4
double_len = 8


def _parse_windvector(content, index):
    wv = np.empty(3)

    wv_len = double_len * 3
    wv[0], wv[1], wv[2] = unpack("d" * 3, content[index: index + wv_len])

    return wv, wv_len


def _parse_wind(content, index, two_vector):
    ori_index = index

    if two_vector is True:
        wv, wv_len = _parse_windvector(content, index)
        index += wv_len
        potential, p_len = _parse_windvector(content, index)
        index += p_len
        wind = Wind(wv, potential)
    elif two_vector is None:
        wv, wv_len = _parse_windvector(content, index)
        index += wv_len
        wind = Wind(wv, None)
    else:
        wind = None

    return wind, index - ori_index


def _parse_coordinate(content, index):
    coord = np.empty(3, dtype=int)
    coord_len = int_len * 3
    coord[0], coord[1], coord[2] = unpack("i" * 3, content[index: index + coord_len])
    return coord, coord_len


def _parse_candidate(content, index):
    ori_index = index

    coord, coord_len = _parse_coordinate(content, index)
    index += coord_len

    concentration, = unpack("d", content[index: index + double_len])
    index += double_len

    return Candidate(coord, concentration), index - ori_index


def _parse_cell(content, index, include_wind):
    ori_index = index

    coord, coord_len = _parse_coordinate(content, index)
    index += coord_len

    tag, = unpack("i", content[index: index + int_len])
    index += int_len

    mtn, = unpack("d", content[index: index + double_len])
    index += double_len

    if not include_wind is False:
        wv, wv_len = _parse_wind(content, index, include_wind)
        index += wv_len
    else:
        wv = None

    return Cell(coord, tag, wv, mtn), index - ori_index


def _parse_dect(content, index):
    dect_num, = unpack("i", content[index: index + int_len])
    index += int_len

    dect_list = []
    for i in range(dect_num):
        time, = unpack("i", content[index: index + int_len])
        index += int_len

        wv, wv_len = _parse_windvector(content, index)
        index += wv_len

        can_num, = unpack("i", content[index: index + int_len])
        index += int_len

        can_list = []
        for j in range(can_num):
            can, can_len = _parse_candidate(content, index)
            index += can_len

            can_list.append(can)

        dect_list.append(Detection(time, wv, can_list))

    return dect_list


def _parse_map(content, index):
    start_index, start_len = _parse_coordinate(content, index)
    index += start_len

    boundary, boundary_len = _parse_coordinate(content, index)
    index += boundary_len

    num, = unpack("i", content[index: index + int_len])
    index += int_len

    cell_list = []
    for i in range(num):
        cell, cell_len = _parse_cell(content, index, True)
        index += cell_len

        cell_list.append(cell)

    return Map3D(start_index, boundary, cell_list)


def _parse_hypothesis(content, index):
    ori_index = index

    prob, = unpack("d", content[index: index + double_len])
    if prob < 0:
        raise "negative probability"
    index += double_len

    leak_num, = unpack("i", content[index: index + int_len])
    index += int_len

    leak_list = []
    for i in range(leak_num):
        leak, leak_len = _parse_candidate(content, index)
        index += leak_len

        leak_list.append(leak)

    his_num, = unpack("i", content[index: index + int_len])
    index += int_len

    cells_list = []
    for j in range(his_num):
        cell_num, = unpack("i", content[index: index + int_len])
        index += int_len

        cell_list = []
        for k in range(cell_num):
            cell, cell_len = _parse_cell(content, index, False)
            index += cell_len

            cell_list.append(cell)

        cells_list.append(cell_list)

    return Hypothesis(prob, leak_list, cells_list), index - ori_index


def _parse_hypotheses(content, index):
    ori_index = index

    num, = unpack("i", content[index: index + int_len])
    index += int_len

    hyp_list = []
    for i in range(num):
        hyp, hyp_len = _parse_hypothesis(content, index)
        index += hyp_len

        hyp_list.append(hyp)

    return hyp_list, index - ori_index


def _parse_methane(content, index):
    num, = unpack("i", content[index: index + int_len])
    index += int_len

    hyps_list = []
    for i in range(num):
        hyps, hyps_len = _parse_hypotheses(content, index)
        index += hyps_len

        hyps_list.append(hyps)

    return hyps_list


parse_func_dict = {strDect: _parse_dect, strMap: _parse_map, strMethane: _parse_methane}


def parse_binary_file(file_name, type_key):
    with open(file_name, "rb") as msg_stream:
        ret = parse_func_dict[type_key](msg_stream.read(), 0)
    msg_stream.close()

    return ret
