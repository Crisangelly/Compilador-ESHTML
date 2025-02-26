#include <iostream>
#include <string>

int buscar_etiqueta(std::string posible_etiqueta){
  std::string etiquetas[] = {"<titulo1>", "<titulo2>", "<titulo3>", "<titulo4>", "<titulo5>", "<titulo6>", 
    "<parrafo>", "<negrita>", "<italica>", "<resaltar>", "<pequenio>", "<lista_no_ordenada>", "<lista_ordenada>", "<lista_elemento>",
    "<cursiva>", "<tachar>", "<vinculo>", "<dividir>", "<seccion>", "<pie>", "<cabecera>", "<navegacion>", "<aparte>",
    "<seleccion>", "<linea_horizontal>", "<tabla>", "<tabla_fila>", "<tabla_celda>", "<tabla_cabecera>", "<formulario>",
    "<boton>", "<leyenda>", "<campo>", "<imagen>"
  };
  int canditad_etiquetas = sizeof(etiquetas) / sizeof(std::string);
  int i = 0;
  for (i; i < canditad_etiquetas; i++){
    if(etiquetas[i] == posible_etiqueta){
      return i;
    }
  }
  return -1;
}

int buscar_valor_atributo(std::string posible_atributo, std::string posible_valor, int indice){
  std::string valor_tipo[] = {"texto", "numero", "radio", "caja_check", "enviar", "correo", "telefono", "contrasenia"};
  int canditad_valor_tipo = sizeof(valor_tipo) / sizeof(std::string);

  if(posible_atributo == ":tipo"){
    int j = 0;
    for (j; j < canditad_valor_tipo; j++){
      if(valor_tipo[j] == posible_valor){
        return j;
      }
    }
    return -1;
  }else{
    return indice;
  }
}

int buscar_atributo(std::string posible_atributo, std::string posible_valor){
  std::string atributos[] = {":enlace", ":tipo", ":texto_alternativo"};
  int canditad_atributos = sizeof(atributos) / sizeof(std::string);

  int i = 0;
  for (i; i < canditad_atributos; i++){
    if(atributos[i] == posible_atributo){

      i = buscar_valor_atributo(posible_atributo, posible_valor, i); 

      return i;
    }
  }
  return -1;
}
