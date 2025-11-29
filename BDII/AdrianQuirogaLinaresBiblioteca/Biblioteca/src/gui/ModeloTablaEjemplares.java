// Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

package gui;

import aplicacion.Ejemplar;
import aplicacion.Libro;
import aplicacion.Prestamo;
import aplicacion.Usuario;
import java.util.List;
import javax.swing.table.AbstractTableModel;
import java.time.LocalDate;

/**
 * Modelo de tabla para mostrar ejemplares en la interfaz gráfica.
 */
public class ModeloTablaEjemplares extends AbstractTableModel {
    private List<Ejemplar> ejemplares;
    private List<Usuario> usuarios;

    public ModeloTablaEjemplares() {
        this.ejemplares = new java.util.ArrayList<>();
        this.usuarios = new java.util.ArrayList<>();
    }

    @Override
    public int getColumnCount() {
        return 6;
    }

    @Override
    public int getRowCount() {
        return ejemplares.size();
    }

    @Override
    public String getColumnName(int col) {
        switch (col) {
            case 0: return "Identificador";
            case 1: return "Localizador";
            case 2: return "Año de compra";
            case 3: return "Usuario";
            case 4: return "Fecha Préstamo";
            case 5: return "Fecha Vencimiento";
            default: return "";
        }
    }

    @Override
    public Class<?> getColumnClass(int col) {
        switch (col) {
            case 0: return Integer.class;
            case 1: return String.class;
            case 2: return String.class;
            case 3: return String.class;
            case 4: return LocalDate.class;
            case 5: return LocalDate.class;
            default: return Object.class;
        }
    }

    @Override
    public boolean isCellEditable(int row, int col) {
        return col == 1 || col == 2; // Solo Localizador y Año de compra son editables
    }

    @Override
    public Object getValueAt(int row, int col) {
        Ejemplar ejemplar = ejemplares.get(row);
        Usuario dueño;
        
        if(ejemplar.getLibro()!= null)
        dueño =  ejemplar.estaPrestado(usuarios);

        else dueño =null;
        
        switch (col) {
            case 0: return ejemplar.getNumEjemplar();
            case 1: return ejemplar.getLocalizador();
            case 2: return ejemplar.getAnoCompra();
            case 3: return (dueño!=null) ? dueño.getNombre() : null;
            case 4: return (dueño != null) ? dueño.getPrestamo(ejemplar).getFechaPrestamo() : null;
            case 5: return (dueño != null) ? dueño.getPrestamo(ejemplar).getFechaVencimiento() : null;
            default: return null;
        }
    }

    @Override
    public void setValueAt(Object v, int row, int col) {
        switch (col) {
            case 1: ejemplares.get(row).setLocalizador((String) v); break;
            case 2: ejemplares.get(row).setAnoCompra((String) v); break;
        }
    }

    public void setFilas(List<Ejemplar> ejem, List<Usuario> usuarios) {
        this.usuarios = usuarios;
        
        this.ejemplares=ejem;
        
        
        fireTableDataChanged();
    }

    public void nuevoEjemplar(Ejemplar e) {
        this.ejemplares.add(e);
        fireTableRowsInserted(this.ejemplares.size() - 1, this.ejemplares.size() - 1);
    }

    public void borrarEjemplar(int indice) {
        this.ejemplares.remove(indice);
        fireTableRowsDeleted(indice, indice);
    }

    public List<Ejemplar> getFilasEjemplares() {
        return this.ejemplares;
    }
    
    public List<Usuario> getFilasUsuario(){
        return this.usuarios;
    }

    public Ejemplar obtenerEjemplar(int i) {
        return this.ejemplares.get(i);
    }
    
    public Usuario obtenerUsuario(int i) {
        Ejemplar ejemplar = ejemplares.get(i);
        return ejemplar.estaPrestado(usuarios);
    }

}
