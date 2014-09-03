__author__ = 'Kern'

import sys

import mayavi.mlab as mb

import src.message.Parser as Parser
from src.visualize import MapBuilder
from src.visualize import MethaneBuilder
from src.visualize import DetectionBuilder
from src.visualize import CandidateBuilder
from src.visualize import WindBuilder

if len(sys.argv) < 6:
    print "Usage:", sys.argv[0], " Missing some argument to indicate input files"
    sys.exit(-1)

map_cfg = sys.argv[1]
map_output = sys.argv[2]
mtn_output = sys.argv[3]
dect_output = sys.argv[4]
can_output = sys.argv[5]

map_output = None
mp, dects, candidates, hyps_his = Parser.parse(map_cfg, map_output, dect_output, can_output, mtn_output)

fig_window = mb.figure(size=(1024, 768))
# eng = mb.get_engine()
# scene = eng.scenes[0].scene
scene = fig_window.scene
# scene.render()
# scene.disable_render = True

# cam = scene.camera
# cam.zoom(2.5)

if map_output is None:
    fig_map = MapBuilder.build_from_json(mp)
else:
    fig_map = MapBuilder.build_from_bin(mp)
    fig_wind = WindBuilder.build(mp)
    fig_wind.remove()

fig_hyp = MethaneBuilder.build(hyps_his[0], [None, None])
fig_dect = None
fig_can = None

manual_move_len = len(dects) - len(candidates)
if manual_move_len < 0:
    manual_move_len = 0

for hyps, dect in zip(hyps_his[1: 1 + manual_move_len], dects[: manual_move_len]):
    fig_dect = DetectionBuilder.build(dect, hyps, fig_dect)
    # map(lambda fig: fig.remove(), filter(lambda fig: not fig is None, fig_hyp))
    # fig_hyp = [None, None]
    fig_hyp = MethaneBuilder.build(hyps, fig_hyp)

for hyps, dect, can in zip(hyps_his[manual_move_len + 1:], dects[manual_move_len:], candidates[:]):
    fig_dect = DetectionBuilder.build(dect, hyps, fig_dect)
    fig_hyp = MethaneBuilder.build(hyps, fig_hyp)
    fig_can = CandidateBuilder.build(can, fig_can)

mb.show()


