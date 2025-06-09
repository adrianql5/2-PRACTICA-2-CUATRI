/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gui;

import aplicacion.Categoria;

/**
 *
 * @author alumnogreibd
 */
public class ModeloListaCategorias extends javax.swing.AbstractListModel{
    java.util.List<Categoria> elementos;

    public ModeloListaCategorias(){
        this.elementos=new java.util.ArrayList<Categoria>();
    }

    public int getSize(){
        return this.elementos.size();
    }

    public Categoria getElementAt(int i){
        return elementos.get(i);
    }

    public void nuevoElemento(Categoria e){
        this.elementos.add(e);
        fireIntervalAdded(this, this.elementos.size()-1, this.elementos.size()-1);
    }

    public void borrarElemento(int i){
        Categoria e;
        e=this.elementos.get(i);
        this.elementos.remove(i);
        fireIntervalRemoved(this,i,i);
    }

    public void setElementos(java.util.List<Categoria> elementos){
        this.elementos=elementos;
        fireContentsChanged(this, 0, elementos.size()-1);
    }

    public java.util.List<Categoria> getElementos(){
        return this.elementos;
    }
}
