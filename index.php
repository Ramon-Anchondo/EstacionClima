<!DOCTYPE html>
<html>
<head><meta http-equiv="Content-type" content="text/html; charset=utf-8" />
<meta http-equiv="refresh" content="10" />
   <title>tabla</title>

</head>
<body>
 <center>
         <table bgcolor="DFDFDF" border="1">
                 <thead>
                         <tr>
                                 
                                 <th colspan="12">Clima en Chihuahua</th>
                         </tr>
                 </thead>
                 <tbody>
                         <tr>
                        <td style="vertical-align: top; width: 50px; text-align: center; font-family:Comic Sans MS">idEstacion</td>
                        <td style="vertical-align: top; width: 80px; text-align: center; font-family:Comic Sans MS">fecha y Hora</td>
                        <td style="vertical-align: top; width: 188px; text-align: center; font-family:Comic Sans MS">direccion del Viento</td>
                        <td style="vertical-align: top; width: 180px; text-align: center; font-family:Comic Sans MS">velocidad Viento (km/hr)</td>
                        <td style="vertical-align: top; width: 180px; text-align: center; font-family:Comic Sans MS">Indice UV</td>
                        <td style="vertical-align: top; width: 180px; text-align: center; font-family:Comic Sans MS">radiacion Global (W/m2)</td>
                        <td style="vertical-align: top; width: 180px; text-align: center; font-family:Comic Sans MS">temperatura (ºC)</td>
                        <td style="vertical-align: top; width: 180px; text-align: center; font-family:Comic Sans MS">Humedad (%HR)</td>
                        <td style="vertical-align: top; width: 180px; text-align: center; font-family:Comic Sans MS">precipitacion (mm)</td>
      

                         </tr>

<?php
include("conexion2.php");
                             //$query="SELECT MAX(id) AS id, `ciudad`,`temperatura`,`fecha` FROM clientes";
//$query="SELECT id, ciudad, temperatura, fecha FROM clientes order by id desc limit 1 ";
$query="SELECT idEstacion, fechaHora, dirViento, indiceUV, precipitacion, radGlobal, temperatura, humedad, velViento FROM lecturas order by idLecturas desc limit 1 ";
                             $resultado= $conexion->query($query);
                             while($row=$resultado->fetch_assoc()){
                                         ?>
                                         <tr style="vertical-align: top; width: 50px; text-align: center; font-family:ARIAL">
                                                 <td><?php echo $row['idEstacion']; ?> </td>
                                                  <td><?php echo $row['fechaHora']; ?> </td>
                                                  <?php $viento = $row['dirViento'];
														if (($viento > 337.5) or ($viento <=  22.5)) {
															$respuesta = 'N';
														} elseif (($viento > 22.5) and ($viento <=  67.5)) {
															$respuesta = 'NE'; 
														} elseif (($viento > 67.5) and ($viento <=  112.5)) {
															$respuesta = 'E';
														} elseif (($viento > 112.5) and ($viento <=  157.5)) {
															$respuesta = 'SE';
														} elseif (($viento > 157.5) and ($viento <=  202.5)) {
															$respuesta = 'S';
														} elseif (($viento > 202.5) and ($viento <=  247.5)) {
															$respuesta = 'S0';
														} elseif (($viento > 247.5) and ($viento <=  292.5)) {
															$respuesta = '0';
														} else {
															$respuesta = 'NO';
														}
												  ?>
                                                  <td><?php echo $respuesta . ' - ' .$viento; ?> </td>
                                                 
                                                  <td><?php echo $row['velViento'] ; ?> </td>
                                                   <td><?php echo $row['indiceUV']; ?> </td>
                                                   <td><?php echo $row['radGlobal']; ?> </td>
                                                   <td><?php echo $row['temperatura']; ?> </td>
                                                   <td><?php echo $row['humedad']; ?> </td>
                                                   <td><?php echo $row['precipitacion']; ?> </td>
                                                  
                                                    

                                         </tr>
                                         <?php
                }
                                 ?>
                                         </tbody>
                 </table>
<br><br>

</body>
</html>
 
