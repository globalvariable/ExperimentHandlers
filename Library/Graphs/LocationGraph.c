#include "LocationGraph.h"


LocationGraph* allocate_location_graph(GtkWidget *hbox, LocationGraph *graph)
{
	if (graph != NULL)
	{
		print_message(ERROR_MSG ,"ExperimentHandlers", "LocationGraph", "allocate_location_graph", "graph != NULL");	
		return graph;
	}
	
	graph = g_new0(LocationGraph,1);
	pthread_mutex_init(&(graph->mutex), NULL);	
	graph->x = g_new0(float, 1);  
	graph->y = g_new0(float, 1);

	GdkColor color_bg;
	GdkColor color_dot;
	GdkColor color_grid;

	color_bg.red = 0;
	color_bg.green = 0;
	color_bg.blue = 0;
	
	color_grid.red = 25000;
	color_grid.green = 25000;
	color_grid.blue = 25000;
	
	color_dot.red = 65535;
	color_dot.green = 65535;
	color_dot.blue = 65535;

	graph->databox = gtk_databox_new ();	
	gtk_box_pack_start (GTK_BOX (hbox), graph->databox, TRUE, TRUE, 0);
  	gtk_widget_modify_bg (graph->databox, GTK_STATE_NORMAL, &color_bg);
 	gtk_databox_graph_add (GTK_DATABOX (graph->databox), gtk_databox_grid_new (9, 9, &color_grid, 0)); 	

	graph->graph = GTK_DATABOX_GRAPH(gtk_databox_points_new (1, graph->x, graph->y, &color_dot, 20));
	gtk_databox_graph_add (GTK_DATABOX (graph->databox), graph->graph);	

	gtk_widget_show_all(hbox);	
	gtk_databox_set_total_limits (GTK_DATABOX (graph->databox), 0.1, -0.1, 0.1, -0.1);	

	return graph;				
}


