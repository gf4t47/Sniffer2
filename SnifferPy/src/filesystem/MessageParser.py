__author__ = 'Kern'

import hypothesis_pb2


def parse_msg(msg_file):
    hyps_his = hypothesis_pb2.Hypotheses_history()

    with open(msg_file, "rb") as msg:
        hyps_his.ParseFromString(msg.read())
    msg.close()

    return hyps_his
