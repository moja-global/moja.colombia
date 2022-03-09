CREATE TABLE import.departamentos_blocks AS 
	WITH
		bbox AS (
			SELECT min(FLOOR(ST_XMin(geom))) AS x_min, max(CEIL(ST_XMax(geom))) AS x_max, 
  				min(FLOOR(ST_YMin(geom))) AS y_min, max(CEIL(ST_YMax(geom))) AS y_max
	 		FROM import.departamentos
		),		
		tiles AS (
		   SELECT DISTINCT trunc(y*-1+90/1)::int*360+trunc(x+180/1)::int as tileidx, 
				ST_SetSRID(ST_MakeBox2D(ST_MakePoint(x, y), ST_MakePoint(x+1, y-1)), 4326) as geom
		   FROM bbox, generate_series(x_min::int, x_max::int-1, 1) AS x, 
					generate_series(y_max::int, y_min::int+1, -1) AS y
		),	
		admin as (
			SELECT ST_Buffer(ST_SubDivide((ST_DUMP(geom)).geom::geometry(Polygon,4326),500),0) AS geom 
			FROM import.departamentos
		),
		admin_tiles as (
			SELECT DISTINCT tileidx, tiles.geom
			FROM admin, tiles 
			WHERE admin.geom && tiles.geom
			AND ST_Intersects(admin.geom, tiles.geom) AND NOT ST_Touches(admin.geom, tiles.geom)																							
		),																															 
		blocks AS (
   			SELECT DISTINCT tileidx, 
				trunc(((y* -1 +90)-trunc((y* -1 +90)+0.000001)::int)/0.1+0.000001)::int *10 + trunc(((x+180)-trunc((x+180)+0.000001)::int)/0.1+0.000001)::int AS blockidx,
				ST_SetSRID(ST_MakeBox2D(ST_MakePoint(x, y), ST_MakePoint(x+0.1, y-0.1)), 4326) AS geom
	   		FROM admin_tiles, generate_series(ST_XMin(geom)::int, ST_XMax(geom)::int-0.1,  0.1) AS x, 
	   			generate_series(ST_YMax(geom)::int, ST_YMin(geom)::int+0.1, -0.1) AS y
	 	)		
	SELECT DISTINCT tileidx, blockidx, b.geom
		FROM blocks b, admin a
		WHERE a.geom && b.geom
		AND st_intersects(a.geom, b.geom) AND NOT ST_Touches(a.geom, b.geom);