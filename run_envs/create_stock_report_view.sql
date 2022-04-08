SELECT Dp.dpto_cnmbr,
       F.nomb_mpio,
       F.sistema_si,
       F.año_estab,
       D.year,
       P.name,
       Sum(L.unitcount) as unit_count, 
       Sum(L.unitareasum) as unit_area_sum,
       Sum(S.value) as value
  FROM stock_reporting_results AS S
       INNER JOIN
       date_dimension AS D ON D.date_dimension_id_pk = S.date_dimension_id_fk
       INNER JOIN
       poolinfo_dimension AS P ON S.poolinfo_dimension_id_fk = P.poolinfo_dimension_id_pk
       INNER JOIN
       locationnontemp_dimension AS L ON L.locationnontemp_dimension_id_pk = S.location_dimension_id_fk
       INNER JOIN
       classifierset_dimension AS C ON L.classifierset_dimension_id_fk = C.classifierset_dimension_id_pk
       INNER JOIN
       forestales_2020 AS F ON C.forest_type_id = F.id
       INNER JOIN
       departamentos AS Dp ON C.department = Dp.dpto_ccdgo
GROUP  BY Dp.dpto_cnmbr,
      F.nomb_mpio,
      F.sistema_si,
      F.año_estab,
      D.year, 
      P.name
ORDER  BY Dp.dpto_cnmbr,
      F.nomb_mpio,
      F.sistema_si,
      F.año_estab,
      D.year, 
      P.name