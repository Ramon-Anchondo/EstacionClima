import serial
import json
import MySQLdb
import datetime
import time

ser = serial.Serial("/dev/ttyACM0")

contador = 0

def insertaDatos():
    db = MySQLdb.connect("localhost","root","osiris2009","clima")
    cursor = db.cursor()
    sql = "SELECT VERSION()"
    sql2 = "insert into lecturas (dirViento, \
                                  fechaHora, \
                                  idEstacion, \
                                  indiceUV, \
                                  precipitacion, \
                                  radGlobal, \
                                  temperatura, \
                                  velViento, \
                                  humedad) \
            values (" + str(d["dirViento"]) + ",'" + 
                        str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) +
                        "', 1 ," +
                        str(d["indiceUV"]) + "," +
                        str(d["precipitacion"]) + "," +
                        str(d["radGlobal"]) + "," +
                        str(d["temperatura"]) + "," +
                        str(d["velViento"]) + "," +
                        str(d["humedad"]) + ")"
    cursor.execute(sql2)
    print(sql2)
    db.commit()
    cursor.close()


while 1:
    if contador >= 3:
        read = ser.readline()
        print read
        print contador
        datos2 = read
        d = json.loads(datos2)
        print d["dirViento"]
        print d["velViento"]
        print d["indiceUV"]
        print d["temperatura"]
        print d["humedad"]
        insertaDatos()
    else:
        contador = contador + 1
ser.close()



