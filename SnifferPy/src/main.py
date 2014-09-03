__author__ = 'Kern'

import sys

import mayavi.mlab as mb
import src.direct.Executor as executor

if len(sys.argv) < 6:
    print "Usage:", sys.argv[0], " Missing some argument to indicate input files"
    sys.exit(-1)

fig_window = mb.figure(size=(1024, 768))
# eng = mb.get_engine()
# scene = eng.scenes[0].scene
scene = fig_window.scene
# scene.render()
# scene.disable_render = True

# cam = scene.camera
# cam.zoom(2.5)

executor.run(sys.argv)


mb.show()


