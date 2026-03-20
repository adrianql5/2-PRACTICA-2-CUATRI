package aplicacion;

import java.util.List;

/**
 * Clase Ejemplar que representa una copia de un libro en la biblioteca.
 */
public class Ejemplar {

    private Integer numEjemplar;
    private String localizador;
    private String anoCompra;
    private Libro libro;
    private Usuario usuario;

    // Constructor actualizado con los nuevos atributos
    public Ejemplar(Libro libro, Integer numEjemplar, String localizador, String anoCompra) {
        this.numEjemplar = numEjemplar;
        this.localizador = localizador;
        this.anoCompra = anoCompra;
        this.libro = libro;
        this.usuario = null;
    }
    
    public void setUsuario(Usuario u){
        this.usuario=u;
    }

    public Usuario estaPrestado(List<Usuario> us){
        for(Usuario u: us){
          List<Prestamo> prestamos= u.getPrestamos();
            for (Prestamo p: prestamos){
                if(p.getLibro().equals(libro.getIdLibro()) && p.getEjemplar().equals(this.numEjemplar) && p.getFechaDevolucion()==null) return u;
            }  
        }
        return null;
    }
    
    
    // Métodos getter
    public Integer getNumEjemplar() {
        return numEjemplar;
    }

    public String getAnoCompra() {
        return anoCompra;
    }

    public String getLocalizador() {
        return localizador;
    }

    public Libro getLibro() {
        return libro;
    }
    


    // Métodos setter
    public void setLocalizador(String localizador) {
        this.localizador = localizador;
    }

    public void setAnoCompra(String anoCompra) {
        this.anoCompra = anoCompra;
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true; // Es el mismo objeto
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false; // Si es null o no es de la misma clase, no son iguales
        }
        Ejemplar ejemplar = (Ejemplar) obj;
        return numEjemplar.equals(ejemplar.numEjemplar) && libro.equals(ejemplar.libro);
    }

    @Override
    public int hashCode() {
        int result = numEjemplar.hashCode();
        result = 31 * result + libro.hashCode();
        return result;
    }

}
