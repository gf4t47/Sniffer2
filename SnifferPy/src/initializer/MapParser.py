__author__ = 'Kern'

import json


def parser_json(map_file):
    with open(map_file) as json_stream:
        json_dict = json.load(json_stream)
    json_stream.close()

    return json_dict