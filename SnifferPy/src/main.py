__author__ = 'Kern'

import sys

import mayavi.mlab as mb
import initializer.MapParserJson as MapParser

import message.Parser as Parser
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

fig_window = mb.figure(size=(1024, 768))
# eng = mb.get_engine()
# scene = eng.scenes[0].scene
scene = fig_window.scene
# scene.render()
# scene.disable_render = True

# cam = scene.camera
# cam.zoom(2.5)

mp = MapParser.parser_json(map_cfg)
fig_map = MapBuilder.build_from_json(mp)
# mb.show()

mp, dects, candidates, hyps_his = Parser.parse(None, dect_output, can_output, mtn_output)

if not mp is None:
    fig_map = MapBuilder.build_from_bin(mp)
    fig_wind = WindBuilder.build(mp)
    # mb.show()
    fig_wind.remove()

if hyps_his is None:
    exit(0)

fig_hyp = MethaneBuilder.build(hyps_his[0], [None, None])
fig_dect = None
fig_can = None

manual_move_len = len(dects) - len(candidates)
if manual_move_len < 0:
    manual_move_len = 0

for hyps, dect in zip(hyps_his[1: 1 + manual_move_len], dects[: manual_move_len]):
    fig_hyp = MethaneBuilder.build(hyps, fig_hyp)
    fig_dect = DetectionBuilder.build(dect, hyps, fig_dect)

for hyps, dect, can in zip(hyps_his[manual_move_len + 1:], dects[manual_move_len:], candidates[:]):
    fig_hyp = MethaneBuilder.build(hyps, fig_hyp)
    fig_dect = DetectionBuilder.build(dect, hyps, fig_dect)
    fig_can = CandidateBuilder.build(can, fig_can)

mb.show()


