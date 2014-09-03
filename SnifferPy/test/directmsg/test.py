from src.visualize import WindBuilder, MapBuilder

__author__ = 'Kern'

from src.message.direct.MessageParserDirect import *
import mayavi.mlab as mb

# dect_list = parse_binary_file( "../../bridge/output/dect.bin", strDect)
# print dect_list

mp = parse_binary_file("../../bridge/output/map.bin", strMap)
fig_map = MapBuilder.build_from_bin(mp)
fig_wind = WindBuilder.build(mp)
mb.show()
# print map

# hyps_his = parse_binary_file("../../bridge/output/methane.bin", strMethane)
# print hyps_his