#!/usr/bin/env python
# -*- coding: utf-8 -*-

import json
import os.path


def record_category(name, dict):
    if name not in dict:
        dict[name] = (name, len(dict))
    return dict[name]


if __name__ == "__main__":

    with open('input/Forestales_2020_Orinoquia1.geojson', 'r', encoding='utf-8') as in_file:
        data = json.load(in_file)
        categories = {None: ('', 0)}

        for feature in data["features"]:
            cat = record_category(feature["properties"]["Tipo_de_cr"], categories)
            feature["properties"]["Id_de_cl"] = cat[1]

        if os.path.isfile('input/Forestales_2020_Orinoquia.geojson'):
            os.remove('input/Forestales_2020_Orinoquia.geojson')

        categories_json = [{"id": cat[1], "nombre": cat[0]} for cat in categories.values()]

        with open('input/Forestales_2020.json', 'w', encoding='utf-8') as out_file:
            json.dump(categories_json, out_file)

        with open('input/Forestales_2020_Orinoquia.geojson', 'w', encoding='utf-8') as out_file:
            json.dump(data, out_file)

        with open('input/Forestales_2020_Orinoquia.geojson', 'w', encoding='utf-8') as out_file:
            json.dump(data, out_file)
