#ifndef TRIAL_STATUS_H
#define TRIAL_STATUS_H


typedef unsigned int TrialStatus;   // !!!ONLY!!! trial_handler can change this. Do not change this without MUTEX if there is multi threading for handling the messages of mov obj, exp envi etc. handlers
typedef struct __TrialStatusEventItem TrialStatusEventItem;
typedef struct __TrialStatusEvents TrialStatusEvents;

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "../TrialsData/TrialTypes.h"

#define	TRIAL_STATUS_MAX_STRING_LENGTH			50

#define	TRIAL_STATUS_NULL							0
#define	TRIAL_STATUS_TRIALS_DISABLED				1
#define	TRIAL_STATUS_IN_TRIAL						2
#define	TRIAL_STATUS_IN_REFRACTORY				3
#define	TRIAL_STATUS_START_TRIAL_AVAILABLE		4

struct __TrialStatusEventItem
{
	TimeStamp	status_start_time;   
	TrialStatus	trial_status;	// this is set before trial start during simulations. behaviors determines this during in vivo experiments.
	TrialType		trial_type;	// left, right, tracjectroy right etc. 
};

struct __TrialStatusEvents
{
	TrialStatusEventItem	*buff;   
	unsigned int 		buff_write_idx;
	unsigned int 		buffer_size;
	TimeStamp		status_change_latency;   
};

bool get_trial_status_type_string(TrialStatus trial_status_type, char *str);   // pass NULL if you only want checking (to be faster) 

TrialStatusEvents* allocate_trial_status_events_buffer(TrialStatusEvents* trial_status_events, unsigned int buffer_size, TimeStamp status_change_latency);
TrialStatusEvents* deallocate_trial_status_events_buffer(TrialStatusEvents* trial_status_events);
void schedule_trial_status_event(TrialStatusEvents* trial_status_events, TimeStamp trial_status_start_time, TrialStatus trial_status, TrialType trial_type);   // it can have multiple readers. so no read_idx defined.
bool get_next_trial_status_events_buffer_item(TrialStatusEvents* trial_status_events, unsigned int *read_idx, TrialStatusEventItem **event_item);
TrialStatusEventItem get_last_trial_status_events_buffer_item(TrialStatusEvents* trial_status_events);
#endif
