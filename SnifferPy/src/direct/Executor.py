__author__ = 'Kern'

from src.initializer import MapParserJson
from src.direct.message import MessageParserDriect as MessageParser
from src.direct.visualize import MapBuilder
from src.direct.visualize import MethaneBuilder
from src.direct.visualize import DetectionBuilder
from src.direct.visualize import CandidateBuilder
import time


def run(argv):
    map_cfg = argv[1]
    map_output = argv[2]
    mtn_output = argv[3]
    dect_output = argv[4]
    can_output = argv[5]

    m_dict = MapParserJson.parser_json(map_cfg)
    fig_map = MapBuilder.build_from_json(m_dict)

    # mp = MessageParser.parse_binary_file(map_output, MessageParser.strMap)
    # fig_map = MessageParser.MapBuilder.build_from_bin(mp)
    # fig_wind = MessageParser.WindBuilder.build(mp)

    dects = MessageParser.parse_binary_file(dect_output, MessageParser.strDect)
    candidates = MessageParser.parse_binary_file(can_output, MessageParser.strDect)

    start = time.clock()
    hyps_his = MessageParser.parse_binary_file(mtn_output, MessageParser.strMethane)
    print "time for parsing all hyps", time.clock() - start, "s"

    # fig_wind.remove()

    fig_hyp = MethaneBuilder.build(hyps_his[0], [None, None])
    fig_dect = None
    fig_can = None

    manual_move_len = len(dects) - len(candidates)
    if manual_move_len < 0:
        manual_move_len = 0

    for hyps, dect in zip(hyps_his[1: 1 + manual_move_len], dects[: manual_move_len]):
        fig_dect = DetectionBuilder.build(dect, hyps, fig_dect)
        # map(lambda fig: fig.remove(), filter(lambda fig: not fig is None, fig_hyp))
        # fig_hyp = [None, None]
        fig_hyp = MethaneBuilder.build(hyps, fig_hyp)

    for hyps, dect, can in zip(hyps_his[manual_move_len + 1:], dects[manual_move_len:], candidates[:]):
        fig_dect = DetectionBuilder.build(dect, hyps, fig_dect)
        fig_hyp = MethaneBuilder.build(hyps, fig_hyp)
        fig_can = CandidateBuilder.build(can, fig_can)