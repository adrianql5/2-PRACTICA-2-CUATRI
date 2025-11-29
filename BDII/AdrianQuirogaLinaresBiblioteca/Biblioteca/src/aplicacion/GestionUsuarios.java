// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package aplicacion;
import gui.FachadaGui;
import baseDatos.FachadaBaseDatos;
import java.util.List;
/**
 *
 * @author basesdatos
 */
public class GestionUsuarios {
     
    FachadaGui fgui;
    FachadaBaseDatos fbd;
    
   
    public GestionUsuarios(FachadaGui fgui, FachadaBaseDatos fbd){
     this.fgui=fgui;
     this.fbd=fbd;
    }  
    
    
  public Boolean comprobarAutentificacion(String idUsuario, String clave){
      Usuario u;

      u=fbd.validarUsuario(idUsuario, clave);
      if (u!=null){
          return u.getTipoUsuario()==TipoUsuario.Administrador;
      } else return false;
  }

  List<Usuario> obtenerUsuarios(String id, String nombre) {
      return fbd.obtenerUsuarios(id,nombre);
  }
  
  public void nuevoUsuario(){
        fgui.nuevoUsuario();
  }
  
  public void guardarUsuario(Usuario u){
      fbd.insertarUsuario(u);
  }
  
  public void eliminarUsuario(String id_usuario){
      fbd.eliminarUsuario(id_usuario);
  }

    void editarUsuario(String u, String text1, String text2, String text3, String text4, TipoUsuario valueOf) {
        fbd.editarUsuario(u,text1,text2,text3,text4,valueOf);
    }
 
  
}
