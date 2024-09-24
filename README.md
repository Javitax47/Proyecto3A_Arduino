# Proyecto3A_Arduino

Este proyecto implementa una emisora Bluetooth Low Energy (BLE) que permite la publicación de datos de sensores, como CO2 y temperatura, utilizando la arquitectura de clases en C++. Utiliza un servicio BLE para transmitir datos a dispositivos conectados.

## Tabla de Contenidos

- [Descripción](#descripción)
- [Características](#características)
- [Instalación](#instalación)
- [Uso](#uso)
- [Estructura de Archivos](#estructura-de-archivos)
- [Contribuciones](#contribuciones)
- [Licencia](#licencia)

## Descripción

La emisora BLE está diseñada para transmitir datos de medición a través de un servicio BLE. Este programa utiliza clases para encapsular la funcionalidad de la emisora, las características y el servicio BLE, facilitando su reutilización y mantenimiento.

## Características

- Publicación de datos de mediciones (CO2, temperatura, ruido).
- Interfaz de comunicación por puerto serie.
- Soporte para múltiples características en un servicio BLE.
- Posibilidad de añadir características dinámicamente.

## Instalación

1. **Requisitos**:
   - Arduino IDE instalado en tu máquina.
   - Biblioteca BLE para Arduino (puede ser instalada a través del gestor de bibliotecas del IDE).

2. **Clonar el repositorio**:
    ```
    git clone https://github.com/tu_usuario/tu_repositorio.git
    ```

3. **Importar el proyecto**:

    - Abre el Arduino IDE y selecciona Archivo > Abrir... para importar los archivos del proyecto.

4. **Cargar el programa**:

    - Conecta tu dispositivo Arduino y selecciona la placa adecuada en Herramientas > Placa.
    - Carga el programa en el dispositivo.

 ## Uso

1. **Inicializar la Emisora**: Llama al método encenderEmisora() en el setup() de tu programa para activar la emisora BLE.

2. **Publicar Mediciones**:

    - Utiliza publicarCO2(valorCO2, contador, tiempoEspera) para publicar el nivel de CO2.

    - Utiliza publicarTemperatura(valorTemperatura, contador, tiempoEspera) para publicar la temperatura.

3. **Verificar Datos**: Conecta un dispositivo BLE y utiliza una aplicación compatible para verificar los datos publicados.

 ## Estructura de Archivos

```
/proyecto-emisora-ble
├── Publicador.h            # Clase que gestiona la emisora BLE y la publicación de datos.
├── PuertoSerie.h           # Clase para gestionar la comunicación por puerto serie.
├── ServicioEmisora.h       # Clase que define el servicio BLE y sus características.
└── README.md               # Este archivo.
```

 ## Contribuciones

Las contribuciones son bienvenidas. Si deseas contribuir, por favor sigue estos pasos:

1. Haz un fork del repositorio.

2. Crea una nueva rama (git checkout -b feature/nueva-funcionalidad).

3. Realiza tus cambios y haz commit (git commit -m 'Añadir nueva funcionalidad').

4. Haz push a la rama (git push origin feature/nueva-funcionalidad).

5. Crea un nuevo Pull Request.

 ## Licencia
 
Este proyecto está licenciado bajo la MIT License - consulta el archivo LICENSE para más detalles.