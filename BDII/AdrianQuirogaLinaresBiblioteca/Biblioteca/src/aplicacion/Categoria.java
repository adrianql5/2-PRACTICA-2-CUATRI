// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

package aplicacion;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */



/**
 *
 * @author basesdatos
 */
public class Categoria {

    private String nombre;
    private String descripcion;

   public Categoria (String nombre, String descripcion){
    this.nombre=nombre;
    this.descripcion=descripcion;
   }
   
   @Override
    public String toString() {
        return this.nombre; // Ajusta esto según el atributo que represente el nombre de la categoría
    }

   
   public String getNombre(){

       return this.nombre;
   }

   public String getDescripcion(){

       return this.descripcion;
   }
   
   @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true; // Es el mismo objeto
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false; // Si es null o no es de la misma clase, no son iguales
        }
        Categoria categoria = (Categoria) obj;
        return nombre.equalsIgnoreCase(categoria.nombre); // Compara nombres ignorando mayúsculas/minúsculas
    }

    @Override
    public int hashCode() {
        return nombre.toLowerCase().hashCode(); // Convierte el nombre a minúsculas para mantener coherencia con equals
    }

}

