from src.message.protobuf import hypothesis_pb2, cell_pb2, dect_pb2
from src.model.Cell import *
from src.model.Detection import *
from src.model.Hypothesis import *
from src.model.Wind import *
from src.model.Map3D import *
import numpy

__author__ = 'Kern'


def _trans_coord(msg_coord):
    coord = numpy.empty(3, dtype=int)
    coord[0] = msg_coord.coord_x
    coord[1] = msg_coord.coord_y
    coord[2] = msg_coord.coord_z
    return coord


def _trans_windvector(msg_wv):
    wv = numpy.empty(3)
    wv[0] = msg_wv.wv_x
    wv[1] = msg_wv.wv_y
    wv[2] = msg_wv.wv_z
    return wv


def _trans_tag(msg_tag):
    return proto_enum2tag[msg_tag]


def _trans_wind(msg_wind):
    return Wind(_trans_windvector(msg_wind.wind), _trans_windvector(msg_wind.potential))


def _trans_cell(msg_cell):
    return Cell(_trans_coord(msg_cell.coord), _trans_tag(msg_cell.tag), _trans_wind(msg_cell.wind),
                msg_cell.mtn.concentration)


def _trans_cells(msg_cells):
    return [_trans_cell(cell) for cell in msg_cells.cell]


def _trans_cells_his(msg_his):
    return [_trans_cells(cells) for cells in msg_his]


def _trans_map(msg_map):
    return Map3D(_trans_coord(msg_map.startIndex), _trans_coord(msg_map.boundary), _trans_cells(msg_map.cells))


def _trans_candidate(msg_can):
    return Candidate(_trans_coord(msg_can.location), msg_can.concentration)


def _trans_candidates(msg_cans):
    return [_trans_candidate(leak) for leak in msg_cans]


def _trans_detection(msg_dect):
    return Detection(msg_dect.time, None, _trans_candidates(msg_dect.leak))


def _trans_detections(msg_dect_list):
    return [_trans_detection(dect) for dect in msg_dect_list]


def _trans_hypothesis(msg_hyp):
    return Hypothesis(msg_hyp.probability, _trans_candidates(msg_hyp.leak), _trans_cells_his(msg_hyp.methane_history))


def _trans_hypotheses(msg_hyps):
    return [_trans_hypothesis(hyp) for hyp in msg_hyps.hyp]


def _trans_hypotheses_his(msg_hyps_his):
    return [_trans_hypotheses(hyps) for hyps in msg_hyps_his.hyps]


def parse_mtn(msg_file):
    hyps_his = hypothesis_pb2.Hypotheses_history()

    with open(msg_file, "rb") as msg:
        hyps_his.ParseFromString(msg.read())
    msg.close()

    return _trans_hypotheses_his(hyps_his)


def parse_map(map_file):
    mp = cell_pb2.Map()

    with open(map_file, "rb") as msg:
        mp.ParseFromString(msg.read())
    msg.close()

    return _trans_map(mp)


def parse_dect(dect_file):
    dect_list = dect_pb2.Detections()

    with open(dect_file, "rb") as msg:
        dect_list.ParseFromString(msg.read())
    msg.close()

    return _trans_detections(dect_list.dect)