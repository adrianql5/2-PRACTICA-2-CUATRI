/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package aplicacion;

import baseDatos.FachadaBaseDatos;
import gui.FachadaGui;

/**
 *
 * @author alumnogreibd
 */
public class GestionCategorias {
    FachadaGui fgui;
    FachadaBaseDatos fbd;
    
   
    public GestionCategorias(FachadaGui fgui, FachadaBaseDatos fbd){
     this.fgui=fgui;
     this.fbd=fbd;
    }
    
    public void categoria(){
        java.util.List<Categoria> categorias;
        categorias=fbd.consultarCategorias();
        
        fgui.categoria(categorias);
    }

    void añadirCategoria(Categoria c) {
        fbd.añadirCategoria(c);
    }

    void borrarCategoria(String text) {
        fbd.borrarCategoria(text);
    }
}
