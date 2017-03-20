#include <gtk/gtk.h>

GtkWidget *paned;
GtkWidget *leaveOneOutButton;

void cross_validate_paned_setting(GtkWidget *featurePaned){

  paned = featurePaned;
  gtk_container_set_border_width(GTK_CONTAINER(paned), 12);
  
  
  mainGrid = gtk_grid_new();
  gtk_grid_set_column_homogeneous(mainGrid, TRUE);
  gtk_grid_set_row_homogeneous(mainGrid, TRUE);
  gtk_container_add(GTK_CONTAINER(paned), mainGrid);
  gtk_grid_set_row_spacing(mainGrid, 10);
  gtk_grid_set_column_spacing(mainGrid, 10);


  GtkWidget *emptyLabel1 = gtk_label_new("");
  gtk_grid_attach(GTK_GRID(mainGrid), emptyLabel1, 0, 0, 6, 2);

  leave_one_out_button_setting();

  GtkWidget *emptyLabel2 = gtk_label_new("");
  gtk_grid_attach(GTK_GRID(mainGrid), emptyLabel2, 0, 4, 6, 2);
  

}

void leave_one_out_button_setting(){
  leaveOneOutButton = gtk_button_new_with_label("Leave One Out");
  gtk_grid_attach(GTK_GRID(mainGrid), leaveOneOutButton, 1, 2, 4, 2);
}


