/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package baseDatos;
import aplicacion.Ejemplar;
import aplicacion.Libro;
import aplicacion.Prestamo;
import aplicacion.Usuario;
import aplicacion.TipoUsuario;
import java.sql.*;
import java.time.LocalDate;
import java.util.List;
/**
 *
 * @author basesdatos
 */
public class DAOUsuarios extends AbstractDAO {

   public DAOUsuarios (Connection conexion, aplicacion.FachadaAplicacion fa){
        super.setConexion(conexion);
        super.setFachadaAplicacion(fa);
    }

    public Usuario validarUsuario(String idUsuario, String clave){
        Usuario resultado=null;
        Connection con;
        PreparedStatement stmUsuario=null;
        ResultSet rsUsuario;

        con=this.getConexion();

        try {
        stmUsuario=con.prepareStatement("select id_usuario, clave, nombre, direccion, email, tipo_usuario "+
                                        "from usuario "+
                                        "where id_usuario = ? and clave = ?");
        stmUsuario.setString(1, idUsuario);
        stmUsuario.setString(2, clave);
        rsUsuario=stmUsuario.executeQuery();
        if (rsUsuario.next())
        {
            resultado = new Usuario(rsUsuario.getString("id_usuario"), rsUsuario.getString("clave"),
                                      rsUsuario.getString("nombre"), rsUsuario.getString("direccion"),
                                      rsUsuario.getString("email"), TipoUsuario.valueOf(rsUsuario.getString("tipo_usuario")));

        }
        } catch (SQLException e){
          System.out.println(e.getMessage());
          this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        }finally{
          try {stmUsuario.close();} catch (SQLException e){System.out.println("Imposible cerrar cursores");}
        }
        return resultado;
    }

    public List<Usuario> obtenerUsuarios(String id, String nombre) {
        java.util.List<Usuario> resultado = new java.util.ArrayList<>();
        Usuario usuarioActual;
        Prestamo prestamoActual;
        Connection con;
        PreparedStatement stmUsuarios = null;
        PreparedStatement stmPrestamos = null;
        ResultSet rsUsuarios;
        ResultSet rsPrestamos;

        con = super.getConexion();

        String consulta = "SELECT id_usuario, clave, nombre, direccion, email, tipo_usuario FROM usuario";

        if (id != null) {
            consulta += " WHERE id_usuario LIKE ?";
            if (nombre != null && !nombre.isEmpty()) {
                consulta += " AND nombre LIKE ?";
            }
        } else if (nombre != null) {
            consulta += " WHERE nombre LIKE ?";
        }

        try {
            stmUsuarios = con.prepareStatement(consulta);
            int paramIndex = 1;
            if (id != null) {
                stmUsuarios.setString(paramIndex++, "%" + id + "%");
                if (nombre != null && !nombre.isEmpty()) {
                    stmUsuarios.setString(paramIndex++, "%" + nombre + "%");
                }
            } else if (nombre != null) {
                stmUsuarios.setString(paramIndex, "%" + nombre + "%");
            }

            rsUsuarios = stmUsuarios.executeQuery();
            while (rsUsuarios.next()) {
                usuarioActual = new Usuario(
                    rsUsuarios.getString("id_usuario"),
                    rsUsuarios.getString("clave"),
                    rsUsuarios.getString("nombre"),
                    rsUsuarios.getString("direccion"),
                    rsUsuarios.getString("email"),
                    TipoUsuario.valueOf(rsUsuarios.getString("tipo_usuario"))
                );

                String consulta2 = "SELECT libro, num_ejemplar, fecha_prestamo, fecha_devolucion FROM prestamo WHERE usuario = ?";
                stmPrestamos = con.prepareStatement(consulta2);
                stmPrestamos.setString(1, rsUsuarios.getString("id_usuario"));
                rsPrestamos = stmPrestamos.executeQuery();

                while (rsPrestamos.next()) {
                    LocalDate fechaPrestamo = rsPrestamos.getDate("fecha_prestamo").toLocalDate();
                    Date fechaDevolucionSQL = rsPrestamos.getDate("fecha_devolucion");
                    LocalDate fechaDevolucion = (fechaDevolucionSQL != null) ? fechaDevolucionSQL.toLocalDate() : null;

                    prestamoActual = new Prestamo(
                        rsPrestamos.getInt("libro"),
                        rsPrestamos.getInt("num_ejemplar"),
                        fechaPrestamo,
                        fechaDevolucion
                    );
                    prestamoActual.setFechaVencimiento(fechaPrestamo.plusDays(30));
                    usuarioActual.añadirPrestamo(prestamoActual);
                }
                resultado.add(usuarioActual);
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmUsuarios != null) stmUsuarios.close();
                if (stmPrestamos != null) stmPrestamos.close();
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
        return resultado;
    }


    
    public void insertarUsuario(Usuario usuario){
        Connection con;
        PreparedStatement stmUsuario = null;
        

        con = super.getConexion();

        try {
            stmUsuario = con.prepareStatement(
                "insert into usuario(id_usuario, clave, nombre, direccion, email, tipo_usuario) " +
                "values (?, ?, ?, ?, ?, ?)"
            );
            stmUsuario.setString(1, usuario.getIdUsuario());
            stmUsuario.setString(2, usuario.getClave());
            stmUsuario.setString(3, usuario.getNombre());
            stmUsuario.setString(4, usuario.getDireccion()); 
            stmUsuario.setString(5, usuario.getEmail());
            stmUsuario.setString(6, usuario.getTipoUsuario().name()); 

            stmUsuario.executeUpdate();

        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmUsuario != null) stmUsuario.close();
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

    public void eliminarUsuario(String id_usuario){
        Connection con;
        PreparedStatement stmUsuario = null;
        con = super.getConexion();
        
        try{
            stmUsuario=con.prepareStatement("delete from usuario where id_usuario = ?");
            stmUsuario.setString(1,id_usuario);
            stmUsuario.executeUpdate();
        }
        catch (SQLException e){
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        }
        finally{
            try{
                if(stmUsuario!=null) stmUsuario.close();
            }
            catch(SQLException e){
                System.out.println("Imposible cerrar cursores");
            }
        }
        
    }

    void editarUsuario(String id_usuario, String clave, String nombre, String email, String direccion, TipoUsuario tipoUsuario) {
        Connection con;
        PreparedStatement stmUsuario = null;

        con = super.getConexion(); 

        try {
            stmUsuario = con.prepareStatement("UPDATE usuario " +
                                  "SET clave = ?, " +
                                  "    nombre = ?, " +
                                  "    direccion = ?, " +
                                  "    email = ?, " +
                                  "    tipo_usuario = ? " +
                                  "WHERE id_usuario = ?");

            stmUsuario.setString(1, clave); 
            stmUsuario.setString(2, nombre);
            stmUsuario.setString(3, direccion);
            stmUsuario.setString(4, email);
            stmUsuario.setString(5, tipoUsuario.name()); 
            stmUsuario.setString(6, id_usuario);
            
            stmUsuario.executeUpdate();

        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmUsuario != null) stmUsuario.close();
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

    
    
}
