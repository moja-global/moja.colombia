\COPY (SELECT dpto_ccdgo, dpto_cnmbr, "región_na" FROM import.departamentos) TO 'departamentos.csv' DELIMITER ',' CSV HEADER;