from src.protobuf.message import dect_pb2, cell_pb2, hypothesis_pb2

__author__ = 'Kern'


def parse_mtn(msg_file):
    hyps_his = hypothesis_pb2.Hypotheses_history()

    with open(msg_file, "rb") as msg:
        hyps_his.ParseFromString(msg.read())
    msg.close()

    return hyps_his


def parse_map(map_file):
    mp = cell_pb2.Map()

    with open(map_file, "rb") as msg:
        mp.ParseFromString(msg.read())
    msg.close()

    return mp


def parse_dect(dect_file):
    dect = dect_pb2.Detections()

    with open(dect_file, "rb") as msg:
        dect.ParseFromString(msg.read())
    msg.close()

    return dect