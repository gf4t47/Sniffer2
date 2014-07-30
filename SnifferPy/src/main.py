__author__ = 'Kern'

import sys
from initializer import MapParser
from filesystem import MessageParser
from virsualize import MapBuilder
from virsualize import MethaneBuilder

if len(sys.argv) < 3:
    print "Usage:", sys.argv[0], "Missing files"
    sys.exit(-1)

m_dict = MapParser.parser_json(sys.argv[1])
MapBuilder.build(m_dict)

history = MessageParser.parse_msg(sys.argv[2])
MethaneBuilder.build(history)


