#include <iostream>
#include <string>

int buscar_etiqueta(std::string posible_etiqueta){

  std::string etiqueta_a_buscar = posible_etiqueta.substr(1);

  std::string etiquetas[] = {"titulo1", "titulo2", "titulo3", "titulo4", "titulo5", "titulo6", 
    "parrafo", "negrita", "italica", "resaltar", "pequenio", "lista_no_ordenada", "lista_ordenada", "lista_elemento",
    "cursiva", "tachar", "vinculo", "dividir", "seccion", "pie", "cabecera", "navegacion", "aparte",
    "seleccion", "linea_horizontal", "tabla", "tabla_fila", "tabla_celda", "tabla_cabecera", "formulario",
    "boton", "leyenda", "campo", "imagen"
  };
  int canditad_etiquetas = sizeof(etiquetas) / sizeof(std::string);

  int i = 0;
  for (i; i < canditad_etiquetas; i++){
    if(etiquetas[i] == etiqueta_a_buscar){
      return i;
    }
  }
  return -1;
}


int buscar_atributo_solo(std::string posible_atributo_solo){ //solo son para los atributos de nombre nada más, como revert en las listas, o required en los inputs
  std::string atributo_solo_a_buscar = posible_atributo_solo.substr(1);

  std::string atributos_solos[] = {"revertir", "requerir"};
  int canditad_atributos_solos = sizeof(atributos_solos) / sizeof(std::string);

  int i = 0;
  for (i; i < canditad_atributos_solos; i++){
    if(atributos_solos[i] == atributo_solo_a_buscar){
      return i;
    }
  }
  return -1;
}



int buscar_valor_atributo(std::string atributo_a_buscar, std::string posible_valor, int indice){
 std::string valor_tipo[] = {"texto", "numero", "radio", "caja_check", "enviar", "correo", "telefono", "contrasenia"};
  int canditad_valor_tipo = sizeof(valor_tipo) / sizeof(std::string);

  std::string valor_tipo_de_numeracion[] = {"minusculas", "mayusculas", "numeros_romanos_minusculas", "numeros_romanos", "numeros"};
  int canditad_valor_tipo_de_numeracion = sizeof(valor_tipo_de_numeracion) / sizeof(std::string);

  if(atributo_a_buscar == "tipo"){ //Buscar los valores de los inputs
    int j = 0;
    for (j; j < canditad_valor_tipo; j++){
      if(valor_tipo[j] == posible_valor){
        return j;
      }
    }
    return -1;
  }else if(atributo_a_buscar == "tipo_de_numeracion"){ //Buscar los valores de la numeración de listas
    int k = 0;
    for (k; k < canditad_valor_tipo_de_numeracion; k++){
      if(valor_tipo_de_numeracion[k] == posible_valor){
        std:: cout << "lo conseguiste? \n"; 
        return k;
      }
    }
    return -1;
  }
  else{
    return indice;
  } 
}

int buscar_atributo(std::string posible_atributo, std::string posible_valor){

  std::string atributo_a_buscar = posible_atributo.substr(1);

  std::string atributos[] = {"enlace", "tipo", "texto_alternativo", "iniciar_cuenta", "tipo_de_numeracion", "nombre", "identificador", "clase"};
  int canditad_atributos = sizeof(atributos) / sizeof(std::string);

  int i = 0;
  for (i; i < canditad_atributos; i++){
    if(atributos[i] == atributo_a_buscar){

      i = buscar_valor_atributo(atributo_a_buscar, posible_valor, i); 

      return i;
    }
  }
  return -1; 
}
