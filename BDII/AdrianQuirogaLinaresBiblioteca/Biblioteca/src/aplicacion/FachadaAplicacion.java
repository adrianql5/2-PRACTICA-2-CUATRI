/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package aplicacion;

import java.time.LocalDate;
import java.util.List;


/**
 *
 * @author basesdatos
 */
public class FachadaAplicacion {
    gui.FachadaGui fgui;
    baseDatos.FachadaBaseDatos fbd;
    GesionLibros cl;
    GestionUsuarios cu;
    GestionCategorias cc;
    GestionPrestamos cp;
    
    
    public FachadaAplicacion(){
      fgui=new gui.FachadaGui(this);
      fbd= new baseDatos.FachadaBaseDatos(this);
      cl= new GesionLibros(fgui, fbd);
      cu= new GestionUsuarios(fgui, fbd);
      cc= new GestionCategorias(fgui,fbd);
      cp= new GestionPrestamos(fgui,fbd);
    }

    public static void main(String args[]) {
        FachadaAplicacion fa;

        fa= new FachadaAplicacion();
        fa.iniciaInterfazUsuario();
    }

    public Libro consultarLibro(Integer l){
        return fbd.consultarLibro(l);
    }
    
    public void iniciaInterfazUsuario(){
        fgui.iniciaVista();
    }

    public void muestraExcepcion(String e){
        fgui.muestraExcepcion(e);
    }

    public java.util.List<Libro> obtenerLibros(Integer id, String titulo, String isbn, String autor){
        return cl.obtenerLibros(id, titulo,  isbn,  autor);
    }

    public void visualizarLibro(Integer idLibro){
        cl.visualizarLibro(idLibro);
    }

    public void nuevoLibro(){
        cl.nuevoLibro();
    }

    public Integer actualizarLibro(Libro l){
        return cl.actualizarLibro(l);
    }

    public void borrarLibro(Integer idLibro){
        cl.borrarLibro(idLibro);
    }

    public void actualizarCategoriasLibro(Integer idLibro, java.util.List<String> categorias){
        cl.actualizarCategoriasLibro(idLibro, categorias);
    }

    public List<Ejemplar> actualizarEjemplaresLibro(Integer libro, java.util.List<Ejemplar> ejemplares, java.util.List<Integer> borrar){
       return cl.actualizarEjemplaresLibro(libro, ejemplares, borrar);
    }


    public Boolean comprobarAutentificacion(String idUsuario, String clave){
        return cu.comprobarAutentificacion(idUsuario, clave);
    }

    public List<Usuario> obtenerUsuarios (String id, String nombre){
      return cu.obtenerUsuarios(id,nombre);
    }

    public void nuevoUsuario(){
       cu.nuevoUsuario();
    }

    public void guardarUsuario(Usuario u){
       cu.guardarUsuario(u);
    }

    public void eliminarUsuario(String id_usuario){
        cu.eliminarUsuario(id_usuario);
    }
    
    public void editarUsuario(String u, String text1, String text2, String text3, String text4, TipoUsuario valueOf) {
        cu.editarUsuario(u,text1,text2,text3,text4,valueOf);
    }

    //SECCIÓN CATEGORIAS
    public void categoria(){
        cc.categoria();
    }

    public void añadirCategoria(Categoria c) {
        cc.añadirCategoria(c);
    }

    public void borrarCategoria(String text) {
        cc.borrarCategoria(text);
    }

    //SECCIÓN PRESTAMOS
    public void prestar(Ejemplar e){
        fgui.prestar(e);
    }

    public void prestarEjemplar(Usuario selectedUser, Ejemplar e) {
        cp.prestarEjemplar(selectedUser,e);
    }

    public void devolverEjemplar(Usuario usuarioSeleccionado, Ejemplar ejemplarSeleccionado) {
        cp.devolverEjemplar(usuarioSeleccionado,ejemplarSeleccionado);
    }

    
   
    


}
