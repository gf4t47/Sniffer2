__author__ = 'kding'


import cell_palm
import dect_palm
import hypothesis_palm

def parse_mtn(msg_file):
    # hyps_his = hypothesis_pb2.Hypotheses_history()

    with open(msg_file, "rb") as msg:
        # hyps_his.ParseFromString(msg.read())
        hyps_his = hypothesis_palm.Hypotheses_history(msg_file)
    msg.close()

    return hyps_his


def parse_map(map_file):
    # mp = cell_pb2.Map()

    with open(map_file, "rb") as msg:
        # mp.ParseFromString(msg.read())
        mp = cell_palm.Map(map_file)
    msg.close()

    return mp


def parse_dect(dect_file):
    # dect = dect_pb2.Detections()

    with open(dect_file, "rb") as msg:
        # dect.ParseFromString(msg.read())
        dect = dect_palm.Detections(dect_file)
    msg.close()

    return dect