// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

package aplicacion;

import java.time.LocalDate;

public class Prestamo {
    private Integer libro;
    private Integer ejemplar;  
    private LocalDate fechaPrestamo;
    private LocalDate fechaDevolucion;
    private LocalDate fechaVencimiento;
   
    
    public Boolean estaVencido() {
        return fechaDevolucion == null && LocalDate.now().isAfter(this.fechaVencimiento);
    }
    
    

    
    public Prestamo(Integer libro, Integer ejemplar, LocalDate fechaPrestamo, LocalDate fechaDevolucion) {  
        this.libro=libro;
        this.ejemplar = ejemplar;  
        this.fechaPrestamo = fechaPrestamo;
        
        this.fechaDevolucion = fechaDevolucion;
        
        this.fechaVencimiento = fechaPrestamo.plusDays(30);
        
    }

    
    // Getters
    public Integer getLibro(){
        return libro;
    }
    
    public void setLibro(Integer libro){
        this.libro=libro;
    }
    
    
   
    public Integer getEjemplar() {
        return ejemplar;
    }

    public LocalDate getFechaPrestamo() {
        return fechaPrestamo;
    }

    public LocalDate getFechaDevolucion() {
        return fechaDevolucion;
    }

    public LocalDate getFechaVencimiento() {
        return fechaVencimiento;
    }

   
    public void setEjemplar(Integer ejemplar) {
        this.ejemplar = ejemplar;
    }

    public void setFechaPrestamo(LocalDate fechaPrestamo) {
        this.fechaPrestamo = fechaPrestamo;
    }

    public void setFechaDevolucion(LocalDate fechaDevolucion) {
        this.fechaDevolucion = fechaDevolucion;
    }

    public void setFechaVencimiento(LocalDate fechaVencimiento) {
        this.fechaVencimiento = fechaVencimiento;
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true; // Es el mismo objeto
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false; // Si es null o no es de la misma clase, no son iguales
        }
        Prestamo prestamo = (Prestamo) obj;
        return libro.equals(prestamo.libro) &&
               ejemplar.equals(prestamo.ejemplar) &&
               fechaPrestamo.equals(prestamo.fechaPrestamo);
    }

    @Override
    public int hashCode() {
        int result = libro.hashCode();
        result = 31 * result + ejemplar.hashCode();
        result = 31 * result + fechaPrestamo.hashCode();
        return result;
    }

}
