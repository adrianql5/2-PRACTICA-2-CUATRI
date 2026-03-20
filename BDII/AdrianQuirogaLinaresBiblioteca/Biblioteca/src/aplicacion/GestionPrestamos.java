package aplicacion;

import baseDatos.FachadaBaseDatos;
import gui.FachadaGui;
import java.time.LocalDate;
import java.util.List;

/**
 * Clase para gestionar los préstamos de ejemplares.
 */
public class GestionPrestamos {
    
    private FachadaGui fgui;
    private FachadaBaseDatos fbd;
    
    public GestionPrestamos(FachadaGui fgui, FachadaBaseDatos fbd) {
        this.fgui = fgui;
        this.fbd = fbd;
    }


    void prestarEjemplar(Usuario selectedUser, Ejemplar e) {
        fbd.prestarEjemplar(selectedUser,e);
    }

    void devolverEjemplar(Usuario usuarioSeleccionado, Ejemplar ejemplarSeleccionado) {
        fbd.devolverEjemplar(usuarioSeleccionado, ejemplarSeleccionado);
    }
}
