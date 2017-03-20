#include <gtk/gtk.h>

GtkWidget *paned;
GtkWidget *addTestDataButton;
GtkWidget *clearAllTestFilesButton;
GtkWidget *applyFeatureWeightsButton;

GtkWidget *noTestDataSelectedLabel;

void test_data_paned_setting(GtkWidget *featurePaned){

  paned = featurePaned;
  gtk_container_set_border_width(GTK_CONTAINER(paned), 12);
  
  
  mainGrid = gtk_grid_new();
  gtk_grid_set_column_homogeneous(mainGrid, TRUE);
  gtk_grid_set_row_homogeneous(mainGrid, TRUE);
  gtk_container_add(GTK_CONTAINER(paned), mainGrid);
  gtk_grid_set_row_spacing(mainGrid, 10);
  gtk_grid_set_column_spacing(mainGrid, 10);

  add_test_data_button_setting();

  clear_all_test_files_button_setting();
  
  no_test_data_selected_label_setting("No Data File Selected");

  GtkWidget *emptyLabel = gtk_label_new("");
  gtk_grid_attach(GTK_GRID(mainGrid), emptyLabel, 0, 5, 3, 13);

  apply_feature_weights_button_setting();

}

void apply_feature_weights_button_setting(){
  applyFeatureWeightsButton = gtk_button_new_with_label("Apply Feature Weights");
  gtk_grid_attach(GTK_GRID(mainGrid), applyFeatureWeightsButton, 1, 18, 4, 2);
}


void no_test_data_selected_label_setting(char *string){
  widget_destroyer(gtk_grid_get_child_at(GTK_GRID(mainGrid), 0, 4));
  noTestDataSelectedLabel = gtk_label_new(string);
  gtk_grid_attach(GTK_GRID(mainGrid), noTestDataSelectedLabel, 0, 4, 6, 1);
}

void clear_all_test_files_button_setting(){
  clearAllTestFilesButton = gtk_button_new_with_label("Clear All Test Files");
  gtk_grid_attach(GTK_GRID(mainGrid), clearAllTestFilesButton, 1, 2, 4, 2);
}


void add_test_data_button_setting(){
  addTestDataButton = gtk_button_new_with_label("Add Test Data");
  gtk_grid_attach(GTK_GRID(mainGrid), addTestDataButton, 1, 0, 4, 2);
}
