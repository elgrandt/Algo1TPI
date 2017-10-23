# Algo1TPI

Tutorial de git para newbies:
La idea es que creen un nuevo "branch" cada uno de uds y editen en ese branch y al final combinamos todos los branches en el master.  
-- Se descargan git y lo instalan  
-- Abren la consola y van con el comando CD hasta la carpeta donde quieran clonar el git y escriben el comando:  
git clone https://github.com/elgrandt/Algo1TPI  
-- Entran a la carpeta con: cd Algo1TPI  
-- En esta carpeta van a hacer todos los comandos de git  
-- Para cambiar de branch:  
git checkout "nombre del branch sin comillas"  
-- Si el branch no existe tienen que poner:  
git checkout -b "nombre del branch sin comillas"  
-- Una vez que estan en su branch, editan tranquilos y cuando quieren subir los cambios hacen:  
git commit -m "Una descripcion de los cambios"  
git push origin "Nombre de su branch sin comillas"  
-- Para hacer push les va a pedir su usuario y pass de github, primero me lo tienen que pasar a mi para que les de autorizacion para pushear.
