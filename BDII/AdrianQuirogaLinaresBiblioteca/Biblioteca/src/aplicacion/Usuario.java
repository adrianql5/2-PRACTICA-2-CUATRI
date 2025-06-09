package aplicacion;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.List;
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */



/**
 *
 * @author basesdatos
 */
public class Usuario {
    private String idUsuario;
    private String clave;
    private String nombre;
    private String direccion;
    private String email;
    private TipoUsuario tipo;
    private List<Prestamo> prestamos;

   public Usuario (String idUsuario, String clave, String nombre, String direccion, String email, TipoUsuario tipo){
    this.idUsuario=idUsuario;
    this.clave=clave;
    this.nombre=nombre;
    this.direccion=direccion;
    this.email=email;
    this.tipo=tipo;
    this.prestamos= new java.util.ArrayList<Prestamo>();
   }

   public Prestamo getPrestamo(Ejemplar e){
       for(Prestamo p:prestamos){
           if(p.getLibro().equals(e.getLibro().getIdLibro()) && p.getEjemplar().equals(e.getNumEjemplar())) return p;
       }
       return null;
   }
   
   
   public void añadirPrestamo(Prestamo p){
       prestamos.add(p);
   }
   
   public List<Prestamo> getPrestamos(){
       return prestamos;
   }
   
   public Integer getPrestamosVencidos(){
       Integer contador=0;
       for(Prestamo p: prestamos){
           if(LocalDate.now().isAfter(p.getFechaVencimiento()) && p.getFechaDevolucion()==null){
               System.out.println(p.getFechaVencimiento()); 
               System.out.println(LocalDate.now());
               contador ++;
           }
       }
       return contador;
   }
   
   
   
   public String getIdUsuario(){

       return this.idUsuario;
   }

   public String getClave(){

       return this.clave;
   }

   public String getNombre(){

       return this.nombre;
   }

   public String getDireccion(){

       return this.direccion;
   }

   public String getEmail(){

       return this.email;
   }

   public TipoUsuario getTipoUsuario(){

       return this.tipo;
   }
   
   @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true; // Es el mismo objeto
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false; // Si es null o no es de la misma clase, no son iguales
        }
        Usuario usuario = (Usuario) obj;
        return idUsuario != null && idUsuario.equals(usuario.idUsuario); // Compara por ID de usuario
    }
    
    @Override
    public int hashCode() {
        return (idUsuario != null) ? idUsuario.hashCode() : 0;
    }
}
