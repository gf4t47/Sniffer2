__author__ = 'Kern'

import sys
from message import MessageParser
from initializer import MapParser
from visualize import MapBuilder
from visualize import MethaneBuilder
from visualize import DetectionBuilder
from visualize import CandidateBuilder

import mayavi.mlab as mb

if len(sys.argv) < 6:
    print "Usage:", sys.argv[0], " Missing some argument to indicate input files"
    sys.exit(-1)

map_cfg = sys.argv[1]
map_output = sys.argv[2]
mtn_output = sys.argv[3]
dect_output = sys.argv[4]
can_output = sys.argv[5]

fig_window = mb.figure(size=(1024, 768))
# eng = mb.get_engine()
# scene = eng.scenes[0].scene
scene = fig_window.scene
# scene.render()
# scene.disable_render = True

# cam = scene.camera
# cam.zoom(2.5)


m_dict = MapParser.parser_json(map_cfg)
fig_map = MapBuilder.build_from_json(m_dict)

# mp = MessageParser.parse_map(map_output)
# fig_map = MapBuilder.build_from_bin(mp)
# fig_wind = WindBuilder.build(mp)

dects = MessageParser.parse_dect(dect_output).dect
candidates = MessageParser.parse_dect(can_output).dect
hyps_his = MessageParser.parse_mtn(mtn_output).hyps
# fig_wind.remove()

fig_hyp = MethaneBuilder.build(hyps_his[0], [None, None])
fig_dect = None

for hyps, dect in zip(hyps_his[1:], dects):
    fig_dect = DetectionBuilder.build(dect, hyps, fig_dect)

    map(lambda fig: fig.remove(), filter(lambda fig: not fig is None, fig_hyp))
    fig_hyp = [None, None]
    fig_hyp = MethaneBuilder.build(hyps, fig_hyp)

fig_can = None
for can in candidates:
    fig_can = CandidateBuilder.build(can, fig_can)

mb.show()


