
CREATE TABLE forestales_2020 (
    id            [INTEGER]          PRIMARY KEY
                                     NOT NULL,
    dptompio      [TEXT],
    nom_dep       [TEXT],
    nomb_mpio     [TEXT],
    sistema_si    [TEXT],
    nombre_cie    [TEXT],
    modo_siemb    [TEXT],
    fuente        [TEXT],
    area_has      [REAL],
    año_estab     [REAL],
    tipo_de_cr    [TEXT],
    turno         [REAL],
    bio_aerea     [REAL],
    bio_total     [REAL],
    tipo_de_cr_id [INTEGER]
);

