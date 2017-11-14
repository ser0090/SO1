TP3: Modulos
Alumnos:
        -SULCA, Sergio Alejandro
        -BARRERA, Martin Alejandro

intrucciones:
---Cargar ambos modulos(./Encriptador/crypterModule.ko & ./Desencriptador/deCrypterModule.ko)

---En el archivo log del kernel estaran las instrucciones para crear los archivos de dispositivo "/dev/charCryptor" y "/dev/charDecryptor" respectivamente.

---Escribir un mensaje en el Encriptador mediante "$echo #mensaje# > /dev/charCryptor".
    -Si ahora se realiza una lectura de charCryptor (ej: $cat /dev/charCryptor) se observara la cadena encriptada.

---Desencriptar el mensaje cargandolo en el Desencriptador "$cat /dev/charCryptor > /dev/charDecryptor".

---Leer la cadena desencriptada "$cat /dev/charDecryptor".
