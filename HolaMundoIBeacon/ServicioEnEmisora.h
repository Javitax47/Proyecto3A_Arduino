// -*- mode: c++ -*-

#ifndef SERVICIO_EMISORA_H_INCLUIDO
#define SERVICIO_EMISORA_H_INCLUIDO

#include <vector>

/**
 * @file ServicioEnEmisora.h
 * @brief Definición de la clase ServicioEnEmisora y Clase que representa una característica dentro de un servicio BLE que gestionan un servicio BLE con características.
 * 
 * Estass clases representan un servicio en una emisora BLE con soporte para múltiples características.
 */

/**
 * @brief Función que invierte el contenido de un array.
 * 
 * @tparam T Tipo de los elementos en el array.
 * @param p Puntero al array.
 * @param n Tamaño del array.
 * @return T* Puntero al array invertido.
 */
template< typename T >
T * alReves( T * p, int n ) {
  T aux;
  for( int i = 0; i < n / 2; i++ ) {
	aux = p[i];
	p[i] = p[n - i - 1];
	p[n - i - 1] = aux;
  }
  return p;
}

/**
 * @brief Convierte una cadena de caracteres a un array de uint8_t en orden inverso.
 * 
 * @param pString Cadena de entrada.
 * @param pUint Puntero al array de uint8_t donde se copiará la cadena.
 * @param tamMax Tamaño máximo del array.
 * @return uint8_t* Puntero al array resultante.
 */
uint8_t * stringAUint8AlReves( const char * pString, uint8_t * pUint, int tamMax ) {
  int longitudString = strlen( pString );
  int longitudCopiar = ( longitudString > tamMax ? tamMax : longitudString );
  for( int i = 0; i <= longitudCopiar - 1; i++ ) {
	pUint[ tamMax - i - 1 ] = pString[ i ];
  }
  return pUint;
}

/**
 * @class ServicioEnEmisora
 * @brief Clase que gestiona un servicio BLE con características.
 * 
 * Esta clase representa un servicio en una emisora BLE con soporte para múltiples características.
 */
class ServicioEnEmisora {

public:
  /**
   * @brief Definición del tipo de callback que se ejecuta al escribir en una característica.
   */
  using CallbackCaracteristicaEscrita = void (uint16_t conn_handle, BLECharacteristic * chr, uint8_t * data, uint16_t len);

  /**
   * @class Caracteristica
   * @brief Clase que representa una característica dentro de un servicio BLE.
   */
  class Caracteristica {
  private:
	uint8_t uuidCaracteristica[16] = {
	  '0', '1', '2', '3', '4', '5', '6', '7', 
	  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
	};
	BLECharacteristic laCaracteristica;

  public:
	/**
	 * @brief Constructor que inicializa la característica con su UUID.
	 * 
	 * @param nombreCaracteristica_ Nombre que será convertido a UUID.
	 */
	Caracteristica(const char * nombreCaracteristica_)
	  : laCaracteristica(stringAUint8AlReves(nombreCaracteristica_, &uuidCaracteristica[0], 16)) {}

	/**
	 * @brief Constructor que permite definir propiedades y permisos de la característica.
	 * 
	 * @param nombreCaracteristica_ Nombre de la característica.
	 * @param props Propiedades (lectura, escritura, notificación).
	 * @param permisoRead Permiso de lectura.
	 * @param permisoWrite Permiso de escritura.
	 * @param tam Tamaño máximo de los datos.
	 */
	Caracteristica(const char * nombreCaracteristica_, uint8_t props, SecureMode_t permisoRead, SecureMode_t permisoWrite, uint8_t tam) 
	  : Caracteristica(nombreCaracteristica_) {
	  asignarPropiedadesPermisosYTamanyoDatos(props, permisoRead, permisoWrite, tam);
	}

  private:
	void asignarPropiedades(uint8_t props) {
	  laCaracteristica.setProperties(props);
	}

	void asignarPermisos(SecureMode_t permisoRead, SecureMode_t permisoWrite) {
	  laCaracteristica.setPermission(permisoRead, permisoWrite);
	}

	void asignarTamanyoDatos(uint8_t tam) {
	  laCaracteristica.setMaxLen(tam);
	}

  public:
	/**
	 * @brief Asigna propiedades, permisos y tamaño de datos de la característica.
	 */
	void asignarPropiedadesPermisosYTamanyoDatos(uint8_t props, SecureMode_t permisoRead, SecureMode_t permisoWrite, uint8_t tam) {
	  asignarPropiedades(props);
	  asignarPermisos(permisoRead, permisoWrite);
	  asignarTamanyoDatos(tam);
	}

	/**
	 * @brief Escribe datos en la característica.
	 * 
	 * @param str Cadena de caracteres que se escribirá.
	 * @return uint16_t Número de bytes escritos.
	 */
	uint16_t escribirDatos(const char * str) {
	  return laCaracteristica.write(str);
	}

	/**
	 * @brief Notifica datos a los suscriptores de la característica.
	 * 
	 * @param str Cadena de caracteres que será notificada.
	 * @return uint16_t Número de bytes notificados.
	 */
	uint16_t notificarDatos(const char * str) {
	  return laCaracteristica.notify(&str[0]);
	}

	/**
	 * @brief Instala un callback para cuando se escriben datos en la característica.
	 */
	void instalarCallbackCaracteristicaEscrita(CallbackCaracteristicaEscrita cb) {
	  laCaracteristica.setWriteCallback(cb);
	}

	/**
	 * @brief Activa la característica para que esté lista para operar.
	 */
	void activar() {
	  err_t error = laCaracteristica.begin();
	  Globales::elPuerto.escribir("laCaracteristica.begin(); error = ");
	  Globales::elPuerto.escribir(error);
	}
  };

private:
  uint8_t uuidServicio[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7', 
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
  };
  BLEService elServicio;
  std::vector<Caracteristica *> lasCaracteristicas;

public:
  /**
   * @brief Constructor que inicializa el servicio con su UUID.
   * 
   * @param nombreServicio_ Nombre del servicio que será convertido a UUID.
   */
  ServicioEnEmisora(const char * nombreServicio_) 
	: elServicio(stringAUint8AlReves(nombreServicio_, &uuidServicio[0], 16)) {}

  /**
   * @brief Escribe el UUID del servicio en el puerto serie.
   */
  void escribeUUID() {
	Serial.println("**********");
	for (int i = 0; i <= 15; i++) {
	  Serial.print((char) uuidServicio[i]);
	}
	Serial.println("\n**********");
  }

  /**
   * @brief Añade una característica al servicio.
   * 
   * @param car Referencia a la característica que se añadirá.
   */
  void anyadirCaracteristica(Caracteristica & car) {
	lasCaracteristicas.push_back(&car);
  }

  /**
   * @brief Activa el servicio y todas sus características.
   */
  void activarServicio() {
	err_t error = elServicio.begin();
	Serial.print("elServicio.begin(); error = ");
	Serial.println(error);
	for (auto pCar : lasCaracteristicas) {
	  pCar->activar();
	}
  }

  /**
   * @brief Operador de conversión a BLEService.
   * 
   * Permite usar un objeto de esta clase donde se necesita un BLEService.
   */
  operator BLEService&() {
	return elServicio;
  }
};

#endif // SERVICIO_EMISORA_H_INCLUIDO
