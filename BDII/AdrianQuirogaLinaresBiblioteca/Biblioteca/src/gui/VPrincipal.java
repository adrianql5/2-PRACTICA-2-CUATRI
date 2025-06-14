/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * VPrincipal.java
 *
 * Created on 27-ene-2011, 10:31:24
 */

package gui;


/**
 *
 * @author basesdatos
 */
public class VPrincipal extends javax.swing.JFrame {
  
    aplicacion.FachadaAplicacion fa;
    
    /** Creates new form VPrincipal */
    public VPrincipal(aplicacion.FachadaAplicacion fa) {
        this.fa=fa;
        initComponents();
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        buscaTitulo = new javax.swing.JTextField();
        etiquetaTitulo = new javax.swing.JLabel();
        buscaIsbn = new javax.swing.JTextField();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        buscaAutor = new javax.swing.JTextField();
        jScrollPane1 = new javax.swing.JScrollPane();
        tablaLibros = new javax.swing.JTable();
        btnBuscar = new javax.swing.JButton();
        btnSalir = new javax.swing.JButton();
        btnNuevoLibro = new javax.swing.JButton();
        btnEditarLibro = new javax.swing.JButton();
        jLabel3 = new javax.swing.JLabel();
        buscaId = new javax.swing.JTextField();
        jMenuBar1 = new javax.swing.JMenuBar();
        Adminsitración = new javax.swing.JMenu();
        Usuario = new javax.swing.JMenuItem();
        Categorias = new javax.swing.JMenuItem();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Biblioteca de Informática");
        setName("vPrincipal"); // NOI18N
        setResizable(false);

        buscaTitulo.setToolTipText("Titulo a buscar");

        etiquetaTitulo.setText("Título:");

        jLabel1.setText("Isbn:");

        jLabel2.setText("Autor:");

        buscaAutor.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                buscaAutorActionPerformed(evt);
            }
        });

        tablaLibros.setModel(new ModeloTablaLibros());
        tablaLibros.setColumnSelectionAllowed(true);
        tablaLibros.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        tablaLibros.getTableHeader().setReorderingAllowed(false);
        jScrollPane1.setViewportView(tablaLibros);
        tablaLibros.getColumnModel().getSelectionModel().setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);

        btnBuscar.setText("Buscar");
        btnBuscar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnBuscarActionPerformed(evt);
            }
        });

        btnSalir.setText("Salir");
        btnSalir.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnSalirActionPerformed(evt);
            }
        });

        btnNuevoLibro.setText("Nuevo");
        btnNuevoLibro.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnNuevoLibroActionPerformed(evt);
            }
        });

        btnEditarLibro.setText("Editar");
        btnEditarLibro.setEnabled(false);
        btnEditarLibro.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnEditarLibroActionPerformed(evt);
            }
        });

        jLabel3.setText("Id:");

        Adminsitración.setText("Administración");

        Usuario.setText("Usuarios");
        Usuario.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                UsuarioActionPerformed(evt);
            }
        });
        Adminsitración.add(Usuario);

        Categorias.setText("Categorias");
        Categorias.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                CategoriasActionPerformed(evt);
            }
        });
        Adminsitración.add(Categorias);
        Categorias.getAccessibleContext().setAccessibleName("Categorias");

        jMenuBar1.add(Adminsitración);

        setJMenuBar(jMenuBar1);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 630, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(etiquetaTitulo)
                            .addComponent(jLabel1))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                .addComponent(buscaIsbn, javax.swing.GroupLayout.PREFERRED_SIZE, 144, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(jLabel2)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(buscaAutor, javax.swing.GroupLayout.DEFAULT_SIZE, 360, Short.MAX_VALUE))
                            .addComponent(buscaTitulo, javax.swing.GroupLayout.DEFAULT_SIZE, 578, Short.MAX_VALUE)))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(btnNuevoLibro)
                        .addGap(18, 18, 18)
                        .addComponent(btnEditarLibro)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 408, Short.MAX_VALUE)
                        .addComponent(btnSalir))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(jLabel3)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(buscaId, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(btnBuscar)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(31, 31, 31)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(buscaTitulo, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(etiquetaTitulo))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(buscaAutor, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel1)
                    .addComponent(buscaIsbn, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel2))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(btnBuscar)
                        .addComponent(jLabel3))
                    .addComponent(buscaId, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(12, 12, 12)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 292, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btnSalir)
                    .addComponent(btnNuevoLibro)
                    .addComponent(btnEditarLibro))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        getAccessibleContext().setAccessibleName("Biblioteca Informática");

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void buscaAutorActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_buscaAutorActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_buscaAutorActionPerformed

    private void btnSalirActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnSalirActionPerformed
                // TODO add your handling code here:
        System.exit(0);
    }//GEN-LAST:event_btnSalirActionPerformed

    private void btnBuscarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnBuscarActionPerformed
        // TODO add your handling code here:
        buscarLibros();
    }//GEN-LAST:event_btnBuscarActionPerformed

    private void btnEditarLibroActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnEditarLibroActionPerformed
        // TODO add your handling code here:
        ModeloTablaLibros mtl = (ModeloTablaLibros) tablaLibros.getModel();
        int idLibro;
        idLibro = mtl.obtenerLibro(tablaLibros.getSelectedRow()).getIdLibro();
        fa.visualizarLibro(idLibro);
    }//GEN-LAST:event_btnEditarLibroActionPerformed

    private void btnNuevoLibroActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnNuevoLibroActionPerformed
        // TODO add your handling code here:
        fa.nuevoLibro();
    }//GEN-LAST:event_btnNuevoLibroActionPerformed

    private void UsuarioActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_UsuarioActionPerformed
        // TODO add your handling code here:
        fa.nuevoUsuario();
    }//GEN-LAST:event_UsuarioActionPerformed

    private void CategoriasActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_CategoriasActionPerformed
        fa.categoria();
    }//GEN-LAST:event_CategoriasActionPerformed

    /**
    * @param args the command line arguments
    */

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JMenu Adminsitración;
    private javax.swing.JMenuItem Categorias;
    private javax.swing.JMenuItem Usuario;
    private javax.swing.JButton btnBuscar;
    private javax.swing.JButton btnEditarLibro;
    private javax.swing.JButton btnNuevoLibro;
    private javax.swing.JButton btnSalir;
    private javax.swing.JTextField buscaAutor;
    private javax.swing.JTextField buscaId;
    private javax.swing.JTextField buscaIsbn;
    private javax.swing.JTextField buscaTitulo;
    private javax.swing.JLabel etiquetaTitulo;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTable tablaLibros;
    // End of variables declaration//GEN-END:variables

    public void buscarLibros(){
        ModeloTablaLibros m;

        m=(ModeloTablaLibros) tablaLibros.getModel();
        m.setFilas(fa.obtenerLibros((buscaId.getText().isEmpty())?null:Integer.parseInt(buscaId.getText()), buscaTitulo.getText(), buscaIsbn.getText(), buscaAutor.getText()));
        if (m.getRowCount() > 0) {
            tablaLibros.setRowSelectionInterval(0, 0);
            btnEditarLibro.setEnabled(true);
        }
        else btnEditarLibro.setEnabled(false);
    }
  
}
