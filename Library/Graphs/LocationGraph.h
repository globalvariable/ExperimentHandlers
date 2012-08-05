#ifndef LOCATION_GRAPH_H
#define LOCATION_GRAPH_H


typedef struct 	__LocationGraph 	LocationGraph;

#include <stdbool.h>
#include <gtk/gtk.h>
#include <gtkdatabox.h>
#include <gtkdatabox_ruler.h>
#include <gtkdatabox_points.h>
#include <gtkdatabox_grid.h>
#include <pthread.h>
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct  __LocationGraph		
{
	pthread_mutex_t 	mutex;   // required for writing location data and reading by timeout_callback
	GtkWidget		*databox;
	GtkDataboxGraph	*graph;
	float			*x;
	float			*y;
};

LocationGraph* allocate_location_graph(GtkWidget *hbox, LocationGraph *graph);

#endif
