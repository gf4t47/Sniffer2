__author__ = 'Kern'

from src.initializer import MapParserJson
import time


def _protobuf_parse(map_cfg, map_output, dect_output, can_output, mtn_output):
    import protobuf.MessageParserPb as MessageParser

    if map_output is None:
        mp = MapParserJson.parser_json(map_cfg)
    else:
        mp = MessageParser.parse_map(map_output)

    dects = MessageParser.parse_dect(dect_output)
    candidates = MessageParser.parse_dect(can_output)

    start = time.clock()
    hyps_his = MessageParser.parse_mtn(mtn_output)
    print "time for parsing all hyps", time.clock() - start, "s"

    return mp, dects, candidates, hyps_his


def _direct_parse(map_cfg, map_output, dect_output, can_output, mtn_output):
    import direct.MessageParserDirect as MessageParser

    if map_output is None:
        mp = MapParserJson.parser_json(map_cfg)
    else:
        mp = MessageParser.parse_binary_file(map_output, MessageParser.strMap)

    dects = MessageParser.parse_binary_file(dect_output, MessageParser.strDect)
    candidates = MessageParser.parse_binary_file(can_output, MessageParser.strDect)

    start = time.clock()
    hyps_his = MessageParser.parse_binary_file(mtn_output, MessageParser.strMethane)
    print "time for parsing all hyps", time.clock() - start, "s"

    return mp, dects, candidates, hyps_his


def parse(map_cfg, map_output, dect_output, can_output, mtn_output):
    return _direct_parse(map_cfg, map_output, dect_output, can_output, mtn_output)
    # return _protobuf_parse(map_cfg, map_output, dect_output, can_output, mtn_output)