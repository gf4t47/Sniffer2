__author__ = 'Kern'

import sys
from filesystem import MessageParser
from initializer import MapParser
from virsualize import MapBuilder
from virsualize import WindBuilder
from virsualize import MethaneBuilder

import mayavi.mlab as mb

if len(sys.argv) < 4:
    print "Usage:", sys.argv[0], "Missing some argument to indicate input files"
    sys.exit(-1)

fig = mb.figure(size=(1024, 768))

m_dict = MapParser.parser_json(sys.argv[1])
fig_map = MapBuilder.build_from_json(m_dict)

mp = MessageParser.parse_map(sys.argv[3])
# fig_map = MapBuilder.build_from_bin(mp)
# fig_wind = WindBuilder.build(mp)

hyps_his = MessageParser.parse_mtn(sys.argv[2])
fig_hyp = None
for hyps in hyps_his.hyps:
    fig_hyp = MethaneBuilder.build(hyps, fig_hyp)

eng = mb.get_engine()
scene = eng.scenes[0].scene
scene.camera.zoom(1.5)

mb.show()


