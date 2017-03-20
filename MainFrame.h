#include <gtk/gtk.h>
#include "TrainingDataPaned.h"
#include "FeatureWeightsPaned.h"
#include "TestDataPaned.h"
#include "CrossValidatePaned.h"
#include "StatusPaned.h"


GtkWidget *MainWindow;
GtkWidget *labelAlign;
GtkWidget *label;
GtkWidget *mainPaned;
GtkWidget *controlPaned;
GtkWidget *trainingDataPaned;
GtkWidget *titlePaned;

GtkWidget *subPaned;
GtkWidget *featureAndTestAndCrossPaned;

GtkWidget *featureAndCrossPaned;

GtkWidget *featureWeightsPaned;
GtkWidget *testDataPaned;
GtkWidget *crossValidatePaned;
GtkWidget *statusPaned;

void init_GUI(GtkWidget *Window){

  MainWindow = Window;
  
  MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(MainWindow),"P300 GUI REMASTERED");
  gtk_window_set_default_size(GTK_WINDOW(MainWindow), 1000, 800);
  gtk_window_set_position(GTK_WINDOW(MainWindow), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(MainWindow), 5);

//set main Paned and label of the app
  mainPaned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  titlePaned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  gtk_widget_set_size_request(titlePaned, 70,20);
  gtk_container_add(GTK_CONTAINER(MainWindow),mainPaned);
  gtk_container_add(GTK_CONTAINER(mainPaned), titlePaned);
  set_title(titlePaned,"Checkerboard Version");

  controlPaned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add(GTK_CONTAINER(mainPaned), controlPaned);

//set training Data Paned
  trainingDataPaned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  gtk_widget_set_size_request(trainingDataPaned, 300,700);
  GtkWidget *trainingLabel = gtk_frame_new("Taining Data");
  gtk_frame_set_shadow_type(GTK_FRAME(trainingLabel), GTK_SHADOW_IN);
  gtk_container_add(GTK_CONTAINER(controlPaned), trainingLabel);
  gtk_container_add(GTK_CONTAINER(trainingLabel), trainingDataPaned);
  
  training_data_paned_setting(trainingDataPaned);
  
  subPaned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  gtk_container_add(GTK_CONTAINER(controlPaned), subPaned);
  
  featureAndTestAndCrossPaned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add(GTK_CONTAINER(subPaned), featureAndTestAndCrossPaned);
  
  featureAndCrossPaned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  gtk_container_add(GTK_CONTAINER(featureAndTestAndCrossPaned), featureAndCrossPaned);
  
  featureWeightsPaned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  gtk_widget_set_size_request(featureWeightsPaned, 300,350);
  GtkWidget *featureWeightsLabel = gtk_frame_new("Feature Weights");
  gtk_frame_set_shadow_type(GTK_FRAME(featureWeightsLabel), GTK_SHADOW_IN);
  gtk_container_add(GTK_CONTAINER(featureAndCrossPaned), featureWeightsLabel);
  gtk_container_add(GTK_CONTAINER(featureWeightsLabel), featureWeightsPaned);
  feature_weights_paned_setting(featureWeightsPaned);
  
  crossValidatePaned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  gtk_widget_set_size_request(crossValidatePaned, 300,170);
  GtkWidget *crossValidateLabel = gtk_frame_new("Cross Validate");
  gtk_frame_set_shadow_type(GTK_FRAME(crossValidateLabel), GTK_SHADOW_IN);
  gtk_container_add(GTK_CONTAINER(featureAndCrossPaned), crossValidateLabel);
  gtk_container_add(GTK_CONTAINER(crossValidateLabel), crossValidatePaned);
  cross_validate_paned_setting(crossValidatePaned);
	
  testDataPaned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  gtk_widget_set_size_request(testDataPaned, 300,550);
  GtkWidget *testDataLabel = gtk_frame_new("Test Data");
  gtk_frame_set_shadow_type(GTK_FRAME(testDataLabel), GTK_SHADOW_IN);
  gtk_container_add(GTK_CONTAINER(featureAndTestAndCrossPaned), testDataLabel);
  gtk_container_add(GTK_CONTAINER(testDataLabel), testDataPaned);
  test_data_paned_setting(testDataPaned);

  statusPaned = gtk_paned_new(GTK_ORIENTATION_VERTICAL); 
  gtk_widget_set_size_request(statusPaned, 600,100);
  GtkWidget *statusLabel = gtk_frame_new("Status");
  gtk_frame_set_shadow_type(GTK_FRAME(statusLabel), GTK_SHADOW_IN);
  gtk_container_add(GTK_CONTAINER(subPaned), statusLabel);
  gtk_container_add(GTK_CONTAINER(statusLabel), statusPaned);
  status_paned_setting(statusPaned);
  
  
  gtk_widget_show_all(MainWindow);
  
  g_signal_connect(G_OBJECT(MainWindow), "", G_CALLBACK(gtk_main_quit), NULL);
}

void set_title(GtkWidget *paned, char ** title){
  label = gtk_label_new(title);
  labelAlign = gtk_alignment_new(0, 0, 0, 0);
  
  gtk_container_add(GTK_CONTAINER(labelAlign), label);
  gtk_container_add(GTK_CONTAINER(paned), labelAlign);


}
