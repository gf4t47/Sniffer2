__author__ = 'Kern'
from src.message.protobuf import cell_pb2

str2tag = {"Air": 1, "Ground": 2, "Building": 3}
proto_enum2tag = {cell_pb2.Air: 1, cell_pb2.Ground: 2, cell_pb2.Building: 3}

class Cell:
    def __init__(self, coord, tag, wind, mtn):
        self.coord = coord
        self.tag = tag
        self.wind = wind
        self.mtn = mtn
