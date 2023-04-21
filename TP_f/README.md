# Driver para el sensor max30205 usando la placa nucleo-f767ZI

El proyecto implementa un sistema de monitoreo de temperatura utilizando el sensor MAX30205. La temperatura se lee a través de una comunicación I2C y se procesa mediante una máquina de estados finitos. El sistema espera recibir comandos a través de una interfaz UART para iniciar o detener la lectura de la temperatura. Cuando la temperatura es mayor o igual a 39.0 grados, se enciende un LED de advertencia, y en caso contrario, se enciende un LED normal. La temperatura medida se envía periódicamente a través de la interfaz UART para que el usuario pueda monitorearla.


Autor: Ing.Elmer Alan Cornejo Quito
