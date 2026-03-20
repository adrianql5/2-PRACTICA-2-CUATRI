/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package baseDatos;

import aplicacion.Ejemplar;
import aplicacion.FachadaAplicacion;
import aplicacion.Libro;
import aplicacion.Prestamo;
import aplicacion.TipoUsuario;
import aplicacion.Usuario;
import java.sql.Connection;
import java.time.LocalDate;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author alumnogreibd
 */
class DAOPrestamos extends AbstractDAO{

    DAOPrestamos(Connection conexion, FachadaAplicacion fa) {
        super.setConexion(conexion);
        super.setFachadaAplicacion(fa);
    } 

    void prestarEjemplar(Usuario usuario, Ejemplar e) {
        Connection con;
        PreparedStatement stmPrestamo = null;
        

        con = super.getConexion();

        try {
            stmPrestamo = con.prepareStatement(
                "insert into prestamo(usuario, libro, num_ejemplar, fecha_prestamo, fecha_devolucion) " +
                "values (?, ?, ?, ?, ?)"
            );
            stmPrestamo.setString(1, usuario.getIdUsuario());
            stmPrestamo.setInt(2, e.getLibro().getIdLibro());
            stmPrestamo.setInt(3, e.getNumEjemplar());
            stmPrestamo.setDate(4, java.sql.Date.valueOf(LocalDate.now()));
            stmPrestamo.setNull(5, Types.DATE); 
            
            stmPrestamo.executeUpdate();

        } catch (SQLException ex) {
            System.out.println(ex.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(ex.getMessage());
        } finally {
            try {
                if (stmPrestamo != null) stmPrestamo.close();
            } catch (SQLException ex) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }
    
    
    void devolverEjemplar(Usuario u, Ejemplar e) {
        Connection con;
        PreparedStatement stmDevolucion = null;

        con = super.getConexion();

        try {
            stmDevolucion = con.prepareStatement(
                "UPDATE prestamo " +
                "SET fecha_devolucion = ? " +
                "WHERE usuario = ? AND libro = ? AND num_ejemplar = ? AND fecha_devolucion IS NULL"
            );

            stmDevolucion.setDate(1, java.sql.Date.valueOf(LocalDate.now())); 
            stmDevolucion.setString(2, u.getIdUsuario());
            stmDevolucion.setInt(3, e.getLibro().getIdLibro());
            stmDevolucion.setInt(4, e.getNumEjemplar());
            
            stmDevolucion.executeUpdate();

        } catch (SQLException ex) {
            System.out.println(ex.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(ex.getMessage());
        } finally {
            try {
                if (stmDevolucion != null) stmDevolucion.close();
            } catch (SQLException ex) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

}
