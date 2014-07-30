__author__ = 'kding'

from src.model import Vector3D as v3
from src.backward import Hypothesis as hp
import mayavi.mlab as mb


def _loc_vector_calculator(detected_location):
    def calc_vector(hyp):
        vec = sum(map(lambda loc: loc - detected_location, hp.get_locations(hyp)))
        vec = vec / v3.get_norm(vec)
        return vec * hp.get_probability(hyp)

    return calc_vector


def build_hypothesis(hypothesises, detected_location, z_base, scale):
    xs, ys, zs = detected_location
    vec_list = map(_loc_vector_calculator(detected_location), hypothesises)
    us, vs, ws = sum(vec_list)

    return mb.quiver3d(xs, ys, zs + z_base, us, vs, ws, line_width=2, scale_mode="vector", scale_factor=scale,
                       mode="2dthick_arrow", colormap="Set3")


def refresh_hypothesis(hypothesises, detected_location, fig, z_base):
    ms = fig.mlab_source

    xs, ys, zs = detected_location
    vec_list = map(_loc_vector_calculator(detected_location), hypothesises)
    us, vs, ws = sum(vec_list)

    ms.set(x=xs, y=ys, z=zs + z_base, u=us, v=vs, w=ws)