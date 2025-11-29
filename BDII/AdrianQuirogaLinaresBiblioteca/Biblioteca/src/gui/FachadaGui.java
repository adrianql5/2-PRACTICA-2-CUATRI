// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gui;

import aplicacion.Categoria;
import aplicacion.Ejemplar;
import aplicacion.Libro;
import aplicacion.Prestamo;
import java.util.List;

/**
 *
 * @author alumno
 */
public class FachadaGui {
    aplicacion.FachadaAplicacion fa;
    VPrincipal vp;
    
    public FachadaGui(aplicacion.FachadaAplicacion fa){
        this.fa=fa;
        this.vp = new VPrincipal(fa);
    } 
    
    
    
    public void iniciaVista(){
      VAutentificacion va;
    
      va = new VAutentificacion(vp, true, fa);
      vp.setVisible(true);
      va.setVisible(true);
    }
    
   
    public void visualizaLibro(Libro l, java.util.List<String>restoCategorias){
        VLibro vl;
        java.util.List<String> categorias = new java.util.ArrayList<String>();
        
        for(Categoria c:l.getCategorias()){
            categorias.add(c.getNombre());
        }
        
        vl=new VLibro(vp, true, fa, l, categorias, restoCategorias);
        vl.setVisible(true);
    }
    
    public void nuevoLibro(java.util.List<String>  restoCategorias){
        VLibro vl;
        
        vl=new VLibro(vp, true, fa, restoCategorias);
        vl.setVisible(true);
    }
    
    public void muestraExcepcion(String txtExcepcion){
       VAviso va;
       
       va = new VAviso(vp, true, txtExcepcion);
       va.setVisible(true);
    }

    
    public void nuevoUsuario(){
        Vusuarios vu;
        vu = new Vusuarios(vp,true,fa);
        vu.setVisible(true);
    }
    
    public void categoria( java.util.List<Categoria> cat ){
        Vcategorias vc;
        vc = new Vcategorias(vp, true, fa,cat);
        vc.setVisible(true);
    }
   
    
    public void prestar(Ejemplar e){
        Vprestamos vpr;
        vpr= new Vprestamos(vp,true,fa,e);
        vpr.setVisible(true);
    }
    
}
