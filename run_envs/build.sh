#!/usr/bin/env bash

export PGPASSWORD=admin
export POSTGRES_HOST=postgres

export POSTGRES_PORT=5432
export DATABASE=colombia
export POSTGRES_USER=postgres

ogr2ogr -t_srs EPSG:4326 -dim 2 data/input/Forestales_2020_Orinoquia1.shp data/Forestales_2020_Orinoquia1.shp
ogr2ogr -t_srs EPSG:4326 -dim 2 data/input/Departamentos_Orinoquia.shp data/Departamentos_Orinoquia.shp

psql -h ${POSTGRES_HOST} -p ${POSTGRES_PORT} -U ${POSTGRES_USER} -c "DROP DATABASE IF EXISTS colombia"
psql -h ${POSTGRES_HOST} -p ${POSTGRES_PORT} -U ${POSTGRES_USER} -c "CREATE DATABASE colombia;"
psql -h ${POSTGRES_HOST} -p ${POSTGRES_PORT} -U ${POSTGRES_USER} -c "CREATE EXTENSION postgis;" ${DATABASE}
psql -h ${POSTGRES_HOST} -p ${POSTGRES_PORT} -U ${POSTGRES_USER} -d ${DATABASE} -c "CREATE SCHEMA import;"

shp2pgsql -I -D -d -s 4326 "data/input/Forestales_2020_Orinoquia1.shp" import.Forestales_2020 > tempdata.sql
psql -h ${POSTGRES_HOST} -p ${POSTGRES_PORT} -U ${POSTGRES_USER} -d ${DATABASE} -f tempdata.sql
rm tempdata.sql

shp2pgsql -I -D -d -s 4326 "data/input/Departamentos_Orinoquia.shp" import.Departamentos > tempdata.sql
psql -h ${POSTGRES_HOST} -p ${POSTGRES_PORT} -U ${POSTGRES_USER} -d ${DATABASE} -f tempdata.sql
rm tempdata.sql

psql -h ${POSTGRES_HOST} -p ${POSTGRES_PORT} -U ${POSTGRES_USER} -d ${DATABASE} -f create_forest_types.sql
psql -h ${POSTGRES_HOST} -p ${POSTGRES_PORT} -U ${POSTGRES_USER} -d ${DATABASE} -f create_forestales_blocks.sql
psql -h ${POSTGRES_HOST} -p ${POSTGRES_PORT} -U ${POSTGRES_USER} -d ${DATABASE} -f create_forestales_csv.sql 
psql -h ${POSTGRES_HOST} -p ${POSTGRES_PORT} -U ${POSTGRES_USER} -d ${DATABASE} -f create_departamentos_csv.sql 
psql -h ${POSTGRES_HOST} -p ${POSTGRES_PORT} -U ${POSTGRES_USER} -d ${DATABASE} -t -c "SELECT to_jsonb(t.*) - 'geom' FROM import.forestales_blocks t" > data/input/blocks.json
psql -h ${POSTGRES_HOST} -p ${POSTGRES_PORT} -U ${POSTGRES_USER} -d ${DATABASE} -t -f blocks_json.sql > data/input/blocks.geojson


gdal_rasterize -a gid PG:"host=${POSTGRES_HOST} user=${POSTGRES_USER} password=${PGPASSWORD} dbname=${DATABASE}" -sql 'SELECT gid, geom FROM import.Forestales_2020' -te -75.0 1.6 -67.4 7.2 -co "SPARSE_OK=True" -co "TILED=yes" -co "COMPRESS=DEFLATE" -co "BLOCKXSIZE=400" -co "BLOCKYSIZE=400" -tr 0.00025 0.00025 -ot UInt16 -a_nodata 65535  data/input/Forestales_2020.tiff
gdal_rasterize -a DPTO_CCDGO  PG:"host=${POSTGRES_HOST} user=${POSTGRES_USER} password=${PGPASSWORD} dbname=${DATABASE}" -sql 'SELECT DPTO_CCDGO, geom FROM import.Departamentos' -te -75.0 1.6 -67.4 7.2 -co "SPARSE_OK=True" -co "TILED=yes" -co "COMPRESS=DEFLATE" -co "BLOCKXSIZE=400" -co "BLOCKYSIZE=400" -tr 0.00025 0.00025 -ot Byte -a_nodata 255 -at data/input/Departamentos.tiff


