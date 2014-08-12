__author__ = 'Kern'

import sys
from filesystem import MessageParser
from initializer import MapParser
from virsualize import MapBuilder
from virsualize import MethaneBuilder
from virsualize import DetectionBuilder

import mayavi.mlab as mb

if len(sys.argv) < 5:
    print "Usage:", sys.argv[0], " Missing some argument to indicate input files"
    sys.exit(-1)

map_cfg = sys.argv[1]
map_output = sys.argv[2]
mtn_output = sys.argv[3]
dect_output = sys.argv[4]

fig = mb.figure(size=(1024, 768))

m_dict = MapParser.parser_json(map_cfg)
fig_map = MapBuilder.build_from_json(m_dict)

# mp = MessageParser.parse_map(map_output)
# fig_map = MapBuilder.build_from_bin(mp)
# fig_wind = WindBuilder.build(mp)

dects = MessageParser.parse_dect(dect_output)
hyps_his = MessageParser.parse_mtn(mtn_output)
# fig_wind.remove()

# fig_hyp = MethaneBuilder.build(hyps_his.hyps[0], None)
fig_dect = None
for hyps, dect in zip(hyps_his.hyps[1:], dects.dect):
    fig_dect = DetectionBuilder.build(dect, hyps, fig_dect)
    # fig_hyp = MethaneBuilder.build(hyps, fig_hyp)

# eng = mb.get_engine()
# scene = eng.scenes[0].scene
# scene.camera.zoom(1.5)

mb.show()


