CREATE VIEW flux_report AS
    SELECT Dp.dpto_cnmbr,
           Fr.nomb_mpio,
           Fr.sistema_si,
           Fr.año_estab,
           D.year,
           Ps.name AS src_pool,
           Pd.name AS sink_pool,
           Sum(L.unitcount) AS unit_count,
           Sum(L.unitareasum) AS unit_area_sum,
           Sum(F.flux) flux,
           Sum(F.itemcount) Flux_agg_count
      FROM flux_reporting_results AS F
           INNER JOIN
           date_dimension AS D ON D.date_dimension_id_pk = F.date_dimension_id_fk
           INNER JOIN
           poolinfo_dimension AS Ps ON F.source_poolinfo_dimension_id_fk = Ps.poolinfo_dimension_id_pk
           INNER JOIN
           poolinfo_dimension AS Pd ON F.sink_poolinfo_dimension_id_fk = Pd.poolinfo_dimension_id_pk
           INNER JOIN
           locationnontemp_dimension AS L ON L.locationnontemp_dimension_id_pk = F.location_dimension_id_fk
           INNER JOIN
           classifierset_dimension AS C ON L.classifierset_dimension_id_fk = C.classifierset_dimension_id_pk
           INNER JOIN
           forestales_2020 AS Fr ON C.forest_type_id = Fr.id
           INNER JOIN
           departamentos AS Dp ON C.department = Dp.dpto_ccdgo
     GROUP BY Dp.dpto_cnmbr,
              Fr.nomb_mpio,
              Fr.sistema_si,
              Fr.año_estab,
              D.year,
              Ps.name,
              Pd.name
     ORDER BY Dp.dpto_cnmbr,
              Fr.nomb_mpio,
              Fr.sistema_si,
              Fr.año_estab,
              D.year,
              Ps.name,
              Pd.name;
