
-- Create the table forest_type
CREATE TABLE IF NOT EXISTS import.forest_type
(
	id integer PRIMARY KEY NOT NULL UNIQUE, 
	name character varying(254) COLLATE pg_catalog."default", 
	density numeric, 
	root_to_shoot numeric, 
	carbon_frac numeric, 
	rotation_length integer, 
	mai numeric, 
	expansion_factor numeric 
);

-- insert the data
	
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (1, 'Tectona grandis', 0.61, 0.24, 0.47, 25, 12.8, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (2, 'Crecimiento lento', 0.6, 0.24, 0.47, 20, 6.0, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (3, 'Acacia mangium', 0.55, 0.24, 0.47, 15, 18.0, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (4, 'Eucalyptus pellita', 0.96, 0.24, 0.47, 12, 20.0, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (5, 'Cedrela odorata', 0.42, 0.24, 0.47, 18, 25.0, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (6, 'Pinus caribaea', 0.51, 0.24, 0.47, 15, 17.5, 1.2);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (7, 'Tabebuia rosea', 0.54, 0.24, 0.47, 20, 15.0, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (8, 'Eucalyptus globulus', 0.55, 0.24, 0.47, 12, 35.0, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (9, 'Hevea brasiliensis', 0.49, 0.24, 0.47, 35, 13.5, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (10, 'Pinus oocarpa', 0.55, 0.24, 0.47, 19, 25.3, 1.2);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (11, 'Crecimiento rápido', 0.49, 0.24, 0.47, 12, 29.0, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (12, 'Gmelina arborea', 0.4, 0.24, 0.47, 12, 19.9, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (13, 'Eucalyptus tereticornis', 0.85, 0.24, 0.47, 16, 15.5, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (14, 'Crecimiento medio', 0.553809524, 0.24, 0.47, 15, 15.0, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (15, 'Eucalyptus grandis', 0.45, 0.24, 0.47, 15, 62.4, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (16, 'Bombacopsis quinata', 0.39, 0.24, 0.47, 25, 12.5, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (17, 'Cariniana pyriformis', 0.55, 0.24, 0.47, 20, 7.0, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (18, 'Cordia alliodora', 0.48, 0.24, 0.47, 20, 21.3, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (19, 'Cordia alliodora ( Ruiz & Pav. ) Cham.', 0.48, 0.24, 0.47, 20, 21.3, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (20, 'Pinus patula', 0.45, 0.24, 0.47, 20, 20.3, 1.2);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (21, 'Cupressus lusitanica', 0.6, 0.24, 0.47, 20, 6.0, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (22, 'Cupressus lusitanica var. benthami', 0.6, 0.24, 0.47, 20, 6.0, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (23, 'Cupressus macrocarpa', 0.6, 0.24, 0.47, 20, 6.0, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (24, 'Quercus humboldtii', 0.6, 0.24, 0.47, 20, 6.0, 1.5);
INSERT INTO import.forest_type (id, name, density, root_to_shoot, carbon_frac, rotation_length, mai, expansion_factor) VALUES (25, 'Cupressus sp.', 0.6, 0.24, 0.47, 20, 6.0, 1.5);

-- Add the tipo_de_cr column
ALTER TABLE import.forestales_2020 
ADD COLUMN tipo_de_cr_id integer;
	
UPDATE import.forestales_2020
	SET tipo_de_cr_id = ft.id
	FROM import.forest_type ft
	WHERE ft.name = tipo_de_cr;	
	
ALTER TABLE import.forestales_2020
    ADD CONSTRAINT fk_forestales_2020_forest_types FOREIGN KEY (tipo_de_cr_id) REFERENCES import.forest_type (id);				
	