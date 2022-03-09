import os
import json
from datetime import datetime
from argparse import ArgumentParser
from osgeo import gdal
from collections import defaultdict
from multiprocessing import cpu_count

working_dir = os.path.dirname(os.path.realpath(__file__))

def get_start_year(simulation_config):
    start_date = simulation_config["LocalDomain"]["start_date"]
    return datetime.strptime(start_date, "%Y/%m/%d").year

def get_spatial_outputs_dir(simulation_config):
    settings = simulation_config["Modules"]["WriteVariableGeotiff"]["settings"]
    return settings["output_path"]    

def find_spatial_outputs(simulation_config):
    settings = simulation_config["Modules"]["WriteVariableGeotiff"]["settings"]

    sim_output_dir = get_spatial_outputs_dir(simulation_config)
    for item in settings["items"]:
        if item["enabled"] and os.path.isdir(os.path.join(sim_output_dir, item["data_name"])):
            spatial_out = {
                "output_path": sim_output_dir,
                "data_name": item["data_name"],
                "on_notification": item["on_notification"],
                "output_annual_only": item["output_annual_only"] if "output_annual_only" in item else False
            }
            yield spatial_out

def find_indicator_files(spatial_out, start_year):
    indicator_dir = os.path.join(spatial_out["output_path"], spatial_out["data_name"])
    output_annual_only = spatial_out["output_annual_only"]
    indicator_output = defaultdict(list)
    for dir, subdirs, files in os.walk(indicator_dir):
        for file in filter(lambda f: f.endswith(".tif"), files):
            timestep = os.path.splitext(file)[0].split("_")[-1].zfill(3)
            if output_annual_only:
                year = str(start_year + int(int(timestep)/12) - 1)
            else:
                year = 0
            file_path = os.path.relpath(os.path.join(dir, file), working_dir)
            indicator_output[year].append(file_path)
    
    return indicator_output

def find_spatial_output_files(spatial_out, start_year):
    for year, files in find_indicator_files(spatial_out, start_year).items():
        print("{} - {}".format(spatial_out["data_name"], year))
        merge_spatial_output_files(spatial_out, year, files)    

def merge_spatial_output_files(spatial_out, year, rel_files):
    #available_mem = psutil.virtual_memory().available
    #gdal_mem = int(available_mem * 0.75 / cpu_count())
    #gdal.SetCacheMax(gdal_mem)
    gdal.UseExceptions()
    
    sim_output_dir = os.path.join(working_dir, "data", "output", "results")
    data_name = spatial_out["data_name"]
   
    files = [os.path.join(working_dir, rel_file) for rel_file in rel_files]
    if int(year) > 0:
        vrt_filename = os.path.join(sim_output_dir, "spatial_outputs", "grids", data_name, "{}_{}.vrt".format(data_name, year))
    else:
        vrt_filename = os.path.join(sim_output_dir, "spatial_outputs", "grids", data_name, "{}.vrt".format(data_name))
    gdal.BuildVRT(vrt_filename, files)
    
    if int(year) > 0:
        tif_filename = os.path.join(sim_output_dir, "spatial_outputs", "grids", data_name, "{}_{}.tif".format(data_name, year))
    else:
        tif_filename = os.path.join(sim_output_dir, "spatial_outputs", "grids", data_name, "{}.tif".format(data_name))
    gdal.Translate(tif_filename, vrt_filename, creationOptions=["BIGTIFF=YES", "TILED=YES", "COMPRESS=DEFLATE"])
        
    cleanup_items = [vrt_filename]
    for item in cleanup_items:
        try_delete(item)

def try_delete(file):    
    try:
        if os.path.isdir(file) and not os.listdir(file):
            os.rmdir(file)
        else:
            os.remove(file)
    except:
        pass        

if __name__ == "__main__":
    parser = ArgumentParser(description="Merge spatial outputs.")
    parser.add_argument("--config", help="path to the flint config file", required=False, default="growth_mai.json")
    args = parser.parse_args()

    simulation_config = json.load(open(args.config, "r"))

    start_year = get_start_year(simulation_config)

    for output in find_spatial_outputs(simulation_config):
        find_spatial_output_files(output, start_year)
