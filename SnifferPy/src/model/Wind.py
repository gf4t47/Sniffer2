__author__ = 'Kern'


class Wind:
    def __init__(self, windvector, potential):
        self.windvector = windvector
        self.potential = potential

    def calc_wind(self):
        if self.potential is None:
            return self.windvector
        else:
            return self.windvector + self.potential