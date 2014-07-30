__author__ = 'Kern'

import sys
from initializer import MapParser
from filesystem import MessageParser
from virsualize import MapBuilder
from virsualize import MethaneBuilder
import mayavi.mlab as mb

if len(sys.argv) < 3:
    print "Usage:", sys.argv[0], "Missing files"
    sys.exit(-1)

fig = mb.figure(size=(1024, 768))

m_dict = MapParser.parser_json(sys.argv[1])
MapBuilder.build(m_dict)

history = MessageParser.parse_msg(sys.argv[2])
MethaneBuilder.build(history)

eng = mb.get_engine()
scene = eng.scenes[0].scene
scene.camera.zoom(1.5)

mb.show()


