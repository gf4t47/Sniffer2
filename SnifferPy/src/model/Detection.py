__author__ = 'Kern'


class Candidate:
    def __init__(self, coord, conc):
        self.coord = coord
        self.conc = conc


class Detection:
    def __init__(self, time, windvector, leaks):
        self.time = time
        self.windvector = windvector
        self.leaks = leaks